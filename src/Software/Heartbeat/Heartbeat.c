/*
 * Heartbeat.c - BladeCore-M54E Heartbeat LED (PWM fade in/out)
 *
 * Smoothly fades the onboard blue heartbeat LED on GPIO36 using
 * hardware PWM.  Brightness ramps linearly from off to 100% duty
 * and back for a clean, visible breathing effect.
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "hardware/i2c.h"
#include "CONFIG.h"

/* PWM wrap value -- higher gives finer brightness resolution */
#define PWM_WRAP 65535
#define FADE_STEPS 128

static void heartbeat_pwm_init(void)
{
    gpio_set_function(PIN_HEARTBEAT, GPIO_FUNC_PWM);

    uint slice = pwm_gpio_to_slice_num(PIN_HEARTBEAT);
    uint channel = pwm_gpio_to_channel(PIN_HEARTBEAT);

    pwm_config cfg = pwm_get_default_config();

    float divider = (float)clock_get_hz(clk_sys) /
                    ((float)HEARTBEAT_PWM_FREQ_HZ * (PWM_WRAP + 1));
    if (divider < 1.0f)
        divider = 1.0f;

    pwm_config_set_clkdiv(&cfg, divider);
    pwm_config_set_wrap(&cfg, PWM_WRAP);

    pwm_init(slice, &cfg, true);
    pwm_set_chan_level(slice, channel, 0);
}

static inline void heartbeat_set_brightness(uint16_t level)
{
    uint slice = pwm_gpio_to_slice_num(PIN_HEARTBEAT);
    uint channel = pwm_gpio_to_channel(PIN_HEARTBEAT);
    pwm_set_chan_level(slice, channel, level);
}

/* Write a single byte to an MCP23017 register.  Returns true on success. */
static bool mcp23017_write_reg(uint8_t reg, uint8_t val)
{
    uint8_t buf[2] = {reg, val};
    int ret = i2c_write_blocking(MCP23017_I2C_INSTANCE,
                                 MCP23017_I2C_ADDR,
                                 buf, 2, false);
    return (ret == 2);
}

/* Reset and initialise the MCP23017.  Returns true if the device responds. */
static bool mcp23017_init(void)
{
    /* Hardware reset (active low) */
    gpio_init(PIN_MCP23017_RST);
    gpio_set_dir(PIN_MCP23017_RST, GPIO_OUT);
    gpio_put(PIN_MCP23017_RST, 0);
    sleep_ms(1);
    gpio_put(PIN_MCP23017_RST, 1);
    sleep_ms(1);

    /* Configure I2C1 pins */
    i2c_init(MCP23017_I2C_INSTANCE, MCP23017_I2C_BAUDRATE);
    gpio_set_function(PIN_I2C1_SDA, GPIO_FUNC_I2C);
    gpio_set_function(PIN_I2C1_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(PIN_I2C1_SDA);
    gpio_pull_up(PIN_I2C1_SCL);

    /*
     * GPA1, GPA3, GPA5, GPA7 -> output high
     * IODIRA: 0 = output, 1 = input (default 0xFF)
     *   bits 1,3,5,7 cleared -> 0x55
     * OLATA:  bits 1,3,5,7 set   -> 0xAA
     */
    if (!mcp23017_write_reg(MCP23017_REG_OLATA, 0xAA))
        return false;
    if (!mcp23017_write_reg(MCP23017_REG_IODIRA, 0x55))
        return false;

    return true;
}

int main(void)
{
    stdio_init_all();
    heartbeat_pwm_init();

    gpio_init(PIN_5V_BUCK_EN);
    gpio_set_dir(PIN_5V_BUCK_EN, GPIO_OUT);
    gpio_put(PIN_5V_BUCK_EN, 1);

    mcp23017_init();

    /*
     * Simple fade in / fade out:
     *   step 0 -> 127  = off to full brightness  (fade in)
     *   step 127 -> 0  = full brightness to off  (fade out)
     *   Cycle time ~ 128 * 2 * 8 ms = ~2.0 s
     */
    int step = 0;
    int direction = 1;

    while (true)
    {
        /* Linear ramp: step/127 * PWM_WRAP */
        uint32_t brightness = ((uint32_t)step * PWM_WRAP) / (FADE_STEPS - 1);
        heartbeat_set_brightness((uint16_t)brightness);

        sleep_ms(HEARTBEAT_FADE_STEP_MS);

        step += direction;
        if (step >= FADE_STEPS)
        {
            step = FADE_STEPS - 1;
            direction = -1;
        }
        else if (step < 0)
        {
            step = 0;
            direction = 1;
        }
    }
}
