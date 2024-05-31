/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef ATMEL_START_PINS_H_INCLUDED
#define ATMEL_START_PINS_H_INCLUDED

#include <hal_gpio.h>

// SAMD51 has 14 pin functions

#define GPIO_PIN_FUNCTION_A 0
#define GPIO_PIN_FUNCTION_B 1
#define GPIO_PIN_FUNCTION_C 2
#define GPIO_PIN_FUNCTION_D 3
#define GPIO_PIN_FUNCTION_E 4
#define GPIO_PIN_FUNCTION_F 5
#define GPIO_PIN_FUNCTION_G 6
#define GPIO_PIN_FUNCTION_H 7
#define GPIO_PIN_FUNCTION_I 8
#define GPIO_PIN_FUNCTION_J 9
#define GPIO_PIN_FUNCTION_K 10
#define GPIO_PIN_FUNCTION_L 11
#define GPIO_PIN_FUNCTION_M 12
#define GPIO_PIN_FUNCTION_N 13

#define BATT_VOLT GPIO(GPIO_PORTA, 2)
#define SPI_MOSI GPIO(GPIO_PORTA, 4)
#define SPI_SCK GPIO(GPIO_PORTA, 5)
#define SPI_MISO GPIO(GPIO_PORTA, 6)
#define MONITOR0 GPIO(GPIO_PORTA, 7)
#define SDCMD GPIO(GPIO_PORTA, 8)
#define SDDAT0 GPIO(GPIO_PORTA, 9)
#define SDDAT1 GPIO(GPIO_PORTA, 10)
#define SDDAT2 GPIO(GPIO_PORTA, 11)
#define PCC_FV GPIO(GPIO_PORTA, 12)
#define PCC_HV GPIO(GPIO_PORTA, 13)
#define PCC_CLK GPIO(GPIO_PORTA, 14)
#define TRIGGER0 GPIO(GPIO_PORTA, 15)
#define PCC_D0 GPIO(GPIO_PORTA, 16)
#define PCC_D1 GPIO(GPIO_PORTA, 17)
#define PCC_D2 GPIO(GPIO_PORTA, 18)
#define PCC_D3 GPIO(GPIO_PORTA, 19)
#define PCC_D4 GPIO(GPIO_PORTA, 20)
#define PCC_D5 GPIO(GPIO_PORTA, 21)
#define PCC_D6 GPIO(GPIO_PORTA, 22)
#define PCC_D7 GPIO(GPIO_PORTA, 23)
#define EN_3V3 GPIO(GPIO_PORTA, 24)
#define PUSH_BUT_MCU GPIO(GPIO_PORTA, 25)
#define I2C_BB_SDA GPIO(GPIO_PORTB, 0)
#define ENT_LED GPIO(GPIO_PORTB, 1)
#define I2C_BB_SCL GPIO(GPIO_PORTB, 2)
#define CARD_DETECT_0 GPIO(GPIO_PORTB, 5)
#define LED_STATUS GPIO(GPIO_PORTB, 9)
#define SDDAT3 GPIO(GPIO_PORTB, 10)
#define SDCK GPIO(GPIO_PORTB, 11)
#define SPI_NSS GPIO(GPIO_PORTB, 16)
#define RESET_CMOS GPIO(GPIO_PORTB, 13)
#define FrameValid GPIO(GPIO_PORTB, 14)
#define GCLK1_OUT GPIO(GPIO_PORTB, 15)
#define IR_REC GPIO(GPIO_PORTB, 22)
#define nCHRG GPIO(GPIO_PORTB, 23)
#define LED_PWM GPIO(GPIO_PORTB, 30)

#endif // ATMEL_START_PINS_H_INCLUDED
