/*
 * SPI_BB_PYTHON480.h
 *
 * Created: 7/21/2018 9:49:03 PM
 *  Author: DBAharoni
 */ 


#ifndef SPI_BB_PYTHON480_H_
#define SPI_BB_PYTHON480_H_

#include <asf.h>


/**
	SPI_Write: Bit-banging SPI master writing sequence
	@reg: register base address (9 bits)
	@val: value to write (16 bits)
*/
void SPI_Write(uint16_t reg, uint16_t val);


/**
	SPI_Read: Bit-banging SPI master reading sequence
	@reg: register base address
	@return: the value of the register
*/
uint16_t SPI_Read(uint16_t reg);


/*
// ========== For ATmega328P ========== //
// Bit-bang SPI Master.
// Assuming SS starts high and clock starts low
uint32_t spi_BB_Read(uint32_t address);


// Bit-bang SPI Master.
// Assuming SS starts high and clock starts low
void spi_BB_Write(uint32_t address, uint32_t value);
*/

#endif /* SPI_BB_PYTHON480_H_ */