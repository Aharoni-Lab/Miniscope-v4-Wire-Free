/*
 * i2c_bb.c
 *
 * Created: 5/26/2021 7:52:14 PM
 *  Author: dbaha
 */ 

#include "i2c_bb.h"
// I2C_BB_SDA and I2C_BB_SCL pins are defined in atmel_start_pins.h

void I2C_BB_init(void)
{
	// Set I2C lines initially as input to let pull-up resistors hold the lines high
	
	// SDA
	gpio_set_pin_level(I2C_BB_SDA, false);
	gpio_set_pin_direction(I2C_BB_SDA, GPIO_DIRECTION_IN);
	gpio_set_pin_function(I2C_BB_SDA, GPIO_PIN_FUNCTION_OFF);
	
	// SCL
	gpio_set_pin_level(I2C_BB_SCL, false);
	gpio_set_pin_direction(I2C_BB_SCL, GPIO_DIRECTION_IN);
	gpio_set_pin_function(I2C_BB_SCL, GPIO_PIN_FUNCTION_OFF);
}

void I2C_BB_pin_high(uint32_t pin)
{

}

void I2C_BB_pin_low(uint32_t pin)
{

}

void I2C_BB_end()
{

}

void I2C_BB_begin()
{

}

void I2C_BB_sleep(uint32_t uSec)
{

}

uint8_t I2C_BB_read(I2C_BB *pI2C, uint8_t addr, uint8_t reg, uint8_t *buf, uint8_t length)
{

}

uint8_t I2C_BB_write(I2C_BB *pI2C, uint8_t addr, uint8_t *buf, uint8_t length)
{

}
