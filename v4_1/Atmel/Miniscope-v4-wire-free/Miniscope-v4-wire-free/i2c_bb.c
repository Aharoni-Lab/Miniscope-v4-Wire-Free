/*
 * i2c_bb.c
 *
 * Created: 5/26/2021 7:52:14 PM
 *  Author: dbaha
 */ 

#include "i2c_bb.h"
// I2C_BB_SDA and I2C_BB_SCL pins are defined in atmel_start_pins.h

inline void SDA_low()
{
	gpio_set_pin_direction(I2C_BB_SDA, GPIO_DIRECTION_OUT);	
}
inline void SDA_high()
{
	gpio_set_pin_direction(I2C_BB_SDA, GPIO_DIRECTION_IN);
}
inline uint8_t SDA_read()
{
	return gpio_get_pin_level(I2C_BB_SDA);
}
inline void SCL_low()
{
	gpio_set_pin_direction(I2C_BB_SCL, GPIO_DIRECTION_OUT);
}
inline void SCL_high()
{
	gpio_set_pin_direction(I2C_BB_SCL, GPIO_DIRECTION_IN);
}

void I2C_BB_sleep(void)
{
//	SLEEP_LENGTH
}



void I2C_BB_end()
{
	SDA_low();
	I2C_BB_sleep();
	SCL_high();
	I2C_BB_sleep();
	SDA_high();
	I2C_BB_sleep();
}

uint8_t I2C_BB_begin(uint8_t addr, uint8_t read)
{
	SDA_low();
	I2C_BB_sleep();
	SCL_low();
	if (read)
		addr++;
		
	return I2C_BB_byte_out(addr);
}

uint8_t I2C_BB_byte_out(uint8_t byte)
{
	uint8_t i, ack;

	// send byte	
	for (i = 0; i < 8; i++) {
		if (byte & 0x80)
			SDA_high();
		else
			SDA_low();
		SCL_high();
		I2C_BB_sleep();
		SCL_low();
		byte <<= 1;
		I2C_BB_sleep();
	}
	// read ack bit
	SDA_high();
	SCL_high();
	I2C_BB_sleep();
	ack = SDA_read();
	SCL_low();
	I2C_BB_sleep();
	SDA_low();
	return (ack == 0) ? 1:0;
}

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



uint8_t I2C_BB_read(uint8_t addr, uint8_t reg, uint8_t *buf, uint8_t length)
{
	// TODO: fill this out!
}

uint8_t I2C_BB_write(uint8_t addr, uint8_t *buf, uint8_t length)
{
	uint8_t rc = 0;
	uint8_t originalLength = length;
	uint8_t byte;
	
	rc = I2C_BB_begin(addr, 0);
	if (rc == 1) { // ack was received
		rc = 1;
		while (length && rc == 1) {
			byte = *buf++;
			rc = I2C_BB_byte_out(byte);
			if (rc == 1)
				length--;
		}
	}
	I2C_BB_end();
	
	return (rc == 1) ? (originalLength - length) : 0; // returns number of bytes written
}

