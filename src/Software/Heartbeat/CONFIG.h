/*
 * CONFIG.h - BladeCore-M54E Board Pin Configuration
 *
 * Pin assignments derived from the BladeCore-M54E hardware schematics (v1.0.0).
 * MCU: RP2354B (QFN-80)
 */

#ifndef CONFIG_H
#define CONFIG_H

/* -------------------------------------------------------------------------- */
/*  W5500 Ethernet (SPI1)                                                     */
/* -------------------------------------------------------------------------- */
#define PIN_ETH_MISO 28 /* SPI1 RX  - W5500 MISO             */
#define PIN_ETH_CS 29   /* SPI1 CSn - W5500 SCSn             */
#define PIN_ETH_SCK 30  /* SPI1 SCK - W5500 SCLK            */
#define PIN_ETH_MOSI 31 /* SPI1 TX  - W5500 MOSI            */

/* -------------------------------------------------------------------------- */
/*  I2C0 - Onboard EEPROM (AT24C256) + M.2 connector                         */
/* -------------------------------------------------------------------------- */
#define PIN_I2C0_SDA 32 /* I2C0 data  (4.7K pull-up)         */
#define PIN_I2C0_SCL 33 /* I2C0 clock (4.7K pull-up)         */

/* -------------------------------------------------------------------------- */
/*  W5500 Ethernet Control                                                    */
/* -------------------------------------------------------------------------- */
#define PIN_ETH_RST 34 /* W5500 hardware reset              */
#define PIN_ETH_INT 35 /* W5500 interrupt (active low)      */

/* -------------------------------------------------------------------------- */
/*  Onboard Heartbeat LED                                                     */
/* -------------------------------------------------------------------------- */
#define PIN_HEARTBEAT 36 /* Blue LED, 100R series resistor    */

/* -------------------------------------------------------------------------- */
/*  ADC - Onboard                                                             */
/* -------------------------------------------------------------------------- */
#define PIN_ADC_VUSB 46 /* GPIO46/ADC6 - USB VBUS sense (5.1K-5.1K divider) */
#define PIN_ADC_VREF 47 /* GPIO47/ADC7 - 3.00V 0.1% ref (10K-10K divider)   */

/* -------------------------------------------------------------------------- */
/*  Unused GPIOs - M.2 Connector (directly accent through M.2 edge connector) */
/* -------------------------------------------------------------------------- */
// #define PIN_GPIO0             0       /* M.2 pin 57 - Unused */
// #define PIN_GPIO1             1       /* M.2 pin 55 - Unused */
// #define PIN_GPIO2             2       /* M.2 pin 53 - Unused */
// #define PIN_GPIO3             3       /* M.2 pin 51 - Unused */
// #define PIN_GPIO4             4       /* M.2 pin 49 - Unused */
// #define PIN_GPIO5             5       /* M.2 pin 47 - Unused */
// #define PIN_GPIO6             6       /* M.2 pin 45 - Unused */
// #define PIN_GPIO7             7       /* M.2 pin 43 - Unused */
// #define PIN_GPIO8             8       /* M.2 pin 39 - Unused */
// #define PIN_GPIO9             9       /* M.2 pin 37 - Unused */
// #define PIN_GPIO10            10      /* M.2 pin 35 - Unused */
// #define PIN_GPIO11            11      /* M.2 pin 33 - Unused */
// #define PIN_GPIO12            12      /* M.2 pin 31 - Unused */
// #define PIN_GPIO13            13      /* M.2 pin 29 - Unused */
// #define PIN_GPIO14            14      /* M.2 pin 27 - Unused */
// #define PIN_GPIO15            15      /* M.2 pin 25 - Unused */
// #define PIN_GPIO16            16      /* M.2 pin 21 - Unused */
// #define PIN_GPIO17            17      /* M.2 pin 19 - Unused */
// #define PIN_GPIO18            18      /* M.2 pin 17 - Unused */
// #define PIN_GPIO19            19      /* M.2 pin 15 - Unused */
// #define PIN_GPIO20            20      /* M.2 pin 13 - Unused */
// #define PIN_GPIO21            21      /* M.2 pin 9  - Unused */
// #define PIN_GPIO22            22      /* M.2 pin 7  - Unused */
// #define PIN_GPIO23            23      /* M.2 pin 5  - Unused */
// #define PIN_GPIO24            24      /* M.2 pin 3  - Unused */
// #define PIN_GPIO25            25      /* M.2 pin 8  - Unused */
// #define PIN_GPIO26            26      /* M.2 pin 6  - Unused */
// #define PIN_GPIO27            27      /* M.2 pin 4  - Unused */

/* GPIO37, GPIO38, GPIO39 are NOT connected on BladeCore-M54E */
#ifdef PIN_GPIO37
#error "GPIO37 is not connected on BladeCore-M54E"
#endif
#ifdef PIN_GPIO38
#error "GPIO38 is not connected on BladeCore-M54E"
#endif
#ifdef PIN_GPIO39
#error "GPIO39 is not connected on BladeCore-M54E"
#endif

// #define PIN_ADC0              40      /* M.2 pin 46 / ADC0 - Unused */
// #define PIN_ADC1              41      /* M.2 pin 48 / ADC1 - Unused */
// #define PIN_ADC2              42      /* M.2 pin 50 / ADC2 - Unused */
// #define PIN_ADC3              43      /* M.2 pin 52 / ADC3 - Unused */
// #define PIN_ADC4              44      /* M.2 pin 54 / ADC4 - Unused */
// #define PIN_ADC5              45      /* M.2 pin 56 / ADC5 - Unused */

/* -------------------------------------------------------------------------- */
/*  SPI1 instance used by W5500                                               */
/* -------------------------------------------------------------------------- */
#define ETH_SPI_INSTANCE spi1
#define ETH_SPI_BAUDRATE (10 * 1000 * 1000) /* 10 MHz               */

/* -------------------------------------------------------------------------- */
/*  I2C0 instance used by EEPROM                                              */
/* -------------------------------------------------------------------------- */
#define EEPROM_I2C_INSTANCE i2c0
#define EEPROM_I2C_ADDR 0x50             /* AT24C256 base address (A0=A1=GND) */
#define EEPROM_I2C_BAUDRATE (400 * 1000) /* 400 kHz             */

/* -------------------------------------------------------------------------- */
/*  Heartbeat LED - PWM configuration                                         */
/* -------------------------------------------------------------------------- */
/*  GPIO36 -> PWM slice 2, channel A (RP2354B: slice = (gpio >> 1) & 0xF)    */
#define HEARTBEAT_PWM_FREQ_HZ 1000
#define HEARTBEAT_FADE_STEP_MS 8

#endif /* CONFIG_H */
