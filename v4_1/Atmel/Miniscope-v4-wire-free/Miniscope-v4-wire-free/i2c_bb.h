/*
 * i2c_bb.h
 *
 * Created: 5/26/2021 7:52:03 PM
 *  Author: dbaha
 */ 


#ifndef I2C_BB_H_
#define I2C_BB_H_

#include "atmel_start_pins.h"

#define SLEEP_LENGTH 1000


void I2C_BB_init(void);

uint8_t I2C_BB_read(uint8_t addr, uint8_t reg, uint8_t *buf, uint8_t length);

uint8_t I2C_BB_write(uint8_t addr, uint8_t *buf, uint8_t length);

void I2C_BB_end();
uint8_t I2C_BB_begin(uint8_t addr, uint8_t read);
void I2C_BB_sleep(void);
uint8_t I2C_BB_byte_out(uint8_t byte);

#endif /* I2C_BB_H_ */