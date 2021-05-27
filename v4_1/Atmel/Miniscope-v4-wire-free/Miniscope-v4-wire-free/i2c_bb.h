/*
 * i2c_bb.h
 *
 * Created: 5/26/2021 7:52:03 PM
 *  Author: dbaha
 */ 


#ifndef I2C_BB_H_
#define I2C_BB_H_

#include "atmel_start_pins.h"

typedef struct i2c_bb 
{
	uint32_t SDA_pin, SCL_pin;
	uint32_t delay;
} I2C_BB;

void I2C_BB_init(void);

uint8_t I2C_BB_read(I2C_BB *pI2C, uint8_t addr, uint8_t reg, uint8_t *buf, uint8_t length);

uint8_t I2C_BB_write(I2C_BB *pI2C, uint8_t addr, uint8_t *buf, uint8_t length);

void I2C_BB_pin_high(uint32_t pin);
void I2C_BB_pin_low(uint32_t pin);
void I2C_BB_end();
void I2C_BB_begin();
void I2C_BB_sleep(uint32_t uSec);

#endif /* I2C_BB_H_ */