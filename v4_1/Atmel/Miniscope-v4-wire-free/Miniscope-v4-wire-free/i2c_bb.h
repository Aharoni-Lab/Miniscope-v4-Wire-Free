/*
 * i2c_bb.h
 *
 * Created: 5/26/2021 7:52:03 PM
 *  Author: dbaha
 */ 


#ifndef I2C_BB_H_
#define I2C_BB_H_

#include "atmel_start_pins.h"

#define SLEEP_LENGTH 100 // in us. Uses delay_us() function


void I2C_BB_init(void);

uint8_t I2C_BB_read(uint8_t addr, uint8_t reg, uint8_t *buf, uint8_t length);

uint8_t I2C_BB_write(uint8_t addr, uint8_t *buf, uint8_t length);

void I2C_BB_end();
uint8_t I2C_BB_begin(uint8_t addr, uint8_t read);


uint8_t I2C_BB_byte_out(uint8_t byte);

void SDA_low(void);
void SDA_high(void);
uint8_t SDA_read(void);
void SCL_low(void);
void SCL_high(void);
void I2C_BB_sleep(void);

#endif /* I2C_BB_H_ */