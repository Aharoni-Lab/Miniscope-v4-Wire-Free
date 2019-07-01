#include "SPI_BB_PYTHON480.h"
#include "definitions.h"


// SPI_Write: writes value on a register of the slave
void SPI_Write(uint16_t reg, uint16_t val)
{
	uint8_t count = 0;
//	reg = reg | 0x100;					// Sets write bit to 1 (100(hex) = 1 0000 0000(bin))
	
	// ==== Open the communication line with Python480
	ioport_set_pin_level(SPI_BB_SS, 1);			// 1. Slave Select (SS) pin up
	delay_us(10);
	ioport_set_pin_level(SPI_BB_SS, 0);			// 2. SS pin down (Open the channel)
	delay_us(10);
	
	// ==== Send Address
	for(count = 0; count < 9; ++count)			// 1. 9 bit address, going from MSD (Most Significant Digit) to LSD (Least)
	{
		ioport_set_pin_level(SPI_BB_SCK, 0);	// 2. Clock down	
												// 3. Send the shifted MSD bit through MOSI pin
		if (reg & 0x100)							// If bit value 1 (0x100 is 1 0000 0000, so (if condition is 1 --> the MSD is 1))
		{
			ioport_set_pin_level(SPI_BB_MOSI, 1);		// MOSI pin at 1
		}
		else										// If 0
		{
			ioport_set_pin_level(SPI_BB_MOSI, 0);		// MOSI pin at 0
		}
		delay_us(10);

		ioport_set_pin_level(SPI_BB_SCK, 1);	// 4. Clock up
		delay_us(10);
		
		reg = reg << 1;							// 5. Move the next MSD to the top
	}
	
	// ===== Notify Python480 that it's a WRITE command
	ioport_set_pin_level(SPI_BB_SCK, 0);	// 1. Clock down
	ioport_set_pin_level(SPI_BB_MOSI, 1);	// 2. MOSI up
	delay_us(10);
	ioport_set_pin_level(SPI_BB_SCK, 0);	// 3. Clock up
	delay_us(10);

	// ===== Send value
	for(count = 0; count < 16; ++count)			// 1. 16 bit value, going from MSD to LSD
	{
		ioport_set_pin_level(SPI_BB_SCK, 0);	// 2. Clock down
												// 3. Send the shifted MSD bit through MOSI pin
		if (val & 0x8000)							// If bit value 1
		{
			ioport_set_pin_level(SPI_BB_MOSI, 1);		// MOSI pin at 1
		}
		else										// If bit value 0
		{
			ioport_set_pin_level(SPI_BB_MOSI, 0);		// MOSI pin at 0
		}
		delay_us(10);
		
		ioport_set_pin_level(SPI_BB_SCK, 1);	// 4. Clock up
		delay_us(10);
		
		val = val << 1;							// 5. Move next MSD to the top
	}
	
	// ===== Shut down the communication line
	ioport_set_pin_level(SPI_BB_SCK, 1);	// 1. Clock down
	delay_us(10);
	ioport_set_pin_level(SPI_BB_SS, 1);		// 2. Chip select high
}


uint16_t SPI_Read(uint16_t reg)
{
	uint8_t count = 0;
	uint16_t value = 0;
	//	reg = reg | 0x100;					// Sets write bit to 1 (100(hex) = 1 0000 0000(bin))
	
	// ==== Open the communication line with Python480
	ioport_set_pin_level(SPI_BB_SS, 1);			// 1. Slave Select (SS) pin up
	delay_us(10);
	ioport_set_pin_level(SPI_BB_SS, 0);			// 2. SS pin down (Open the channel)
	delay_us(10);
	
	// ==== Send Address
	for(count = 0; count < 9; ++count)			// 1. 9 bit address, going from MSD (Most Significant Digit) to LSD (Least)
	{
		ioport_set_pin_level(SPI_BB_SCK, 0);	// 2. Clock down
		// 3. Send the shifted MSD bit through MOSI pin
		if (reg & 0x100)							// If bit value 1 (0x100 is 1 0000 0000, so (if condition is 1 --> the MSD is 1))
		{
			ioport_set_pin_level(SPI_BB_MOSI, 1);		// MOSI pin at 1
		}
		else										// If 0
		{
			ioport_set_pin_level(SPI_BB_MOSI, 0);		// MOSI pin at 0
		}
		delay_us(10);

		ioport_set_pin_level(SPI_BB_SCK, 1);	// 4. Clock up
		delay_us(10);
		
		reg = reg << 1;							// 5. Move the next MSD to the top
	}
	
	// ===== Notify Python480 that it's a READ command
	ioport_set_pin_level(SPI_BB_SCK, 0);	// 1. Clock down
	ioport_set_pin_level(SPI_BB_MOSI, 0);	// 2. MOSI up
	delay_us(10);
	ioport_set_pin_level(SPI_BB_SCK, 1);	// 3. Clock up
	delay_us(10);
	ioport_set_pin_level(SPI_BB_SCK, 0);	// 4. Clock down
	delay_us(10);
	ioport_set_pin_level(SPI_BB_SCK, 1);	// 5. Clock up
	delay_us(10);
	
	// ===== Receive the value coming in from Python480
	for(count = 0; count < 16; ++count)			// 1. 16 bit value, going from MSD to LSD
	{
		ioport_set_pin_level(SPI_BB_SCK, 0);					// 2. Clock down
		value |= (0x01 & ioport_get_pin_level(SPI_BB_MISO));	// 3. Put value into the next MSD (currently LSD)
		delay_us(10);
		
		ioport_set_pin_level(SPI_BB_SCK, 1);					// 4. Clock up
		delay_us(10);
		
		if (count == 15)						// 5. Don't move a bit up if we got all the data
		{
			break;
		}
		value = value << 1;						// 6. Free up the bit space for the bit coming in the next loop
	}
	
	// ===== Finish communication with Python480
	ioport_set_pin_level(SPI_BB_SCK, 0);		// 1. Clock down
	ioport_set_pin_level(SPI_BB_SS, 1);			// 2. Slave select up
	
	return value;
}
	

/************************************************************************/
/*                           For Atmega328P                             */
/************************************************************************/
/*
uint32_t spi_BB_Read(uint32_t address)		// Why were these uint32_t?? (different from .h file)
{
	// Bit-bang SPI Master.
	// Assuming SS starts high and clock starts low
	
	int8_t i = 0;
	uint32_t value = 0;
	SPI_SS_PORT &= ~(1 << SS);
	
	for (i = 8; i >= 0; --i) 
	{ // 9 bit address
		SPI_PORT &= ~(1 << SCK);
		// Set MOSI pin to next bit value
		if (0x0001 & (address >> i)) //a 1
		SPI_PORT |= (1 << MOSI);
		else // a 0
		SPI_PORT &= ~(1 << MOSI);
		
		delay_us(10);
		
		SPI_PORT |= (1 << SCK);
		delay_us(10);
	}
	//_delay_us(100);
	// Read bit
	SPI_PORT &= ~(1 << SCK);
	SPI_PORT &= ~(1 << MOSI);
	delay_us(10);
	SPI_PORT |= (1 << SCK);
	delay_us(10);
	SPI_PORT &= ~(1 << SCK);
	delay_us(10);
	SPI_PORT |= (1 << SCK);
	delay_us(10);
	
	// Value
	for (i = 15; i >= 1; --i) 
	{
		SPI_PORT &= ~(1 << SCK);
		value |= (0x01 & (SPI_PORT >> MISO)) << i;

		delay_us(10);
		
		SPI_PORT |= (1 << SCK);
		delay_us(10);
	}
	
	SPI_PORT &= ~(1 << SCK);
	value |= (0x01 & (SPI_PORT >> MISO));
	delay_us(10);
	SPI_SS_PORT |= (1 << SS);
	
	return value;
}

void spi_BB_Write(uint32_t address, uint32_t value) 
{
	//Bit-bang SPI Master.
	//Assuming SS starts high and clock starts low
	
	int8_t i = 0;
	
	SPI_SS_PORT &= ~(1 << SS);				// a &= b means a = (a & b)
	
	for (i = 8; i >= 0; --i)				// 9 bit address
	{ 
		SPI_PORT &= ~(1 << SCK);	
				
		// Set MOSI pin to next bit value
		if (0x0001 & (address >> i))		// a 1
		{
			SPI_PORT |= (1 << MOSI);		// a |= b means a = (a | b)
		}
		else								// a 0
		{
			SPI_PORT &= ~(1 << MOSI);
		}
		delay_us(10);
		
		SPI_PORT |= (1 << SCK);
		delay_us(10);
	}
	//_delay_us(100);
	// Write bit
	SPI_PORT &= ~(1 << SCK);
	SPI_PORT |= (1 << MOSI);
	delay_us(10);
	SPI_PORT |= (1 << SCK);
	delay_us(10);
	
	// Value
	for (i = 15; i >= 0; --i) 
	{
		SPI_PORT &= ~(1 << SCK);
		// Set MOSI pin to next bit value
		if (0x0001 & (value >> i)) //a 1
		{
			SPI_PORT |= (1 << MOSI);
		}
		else // a 0
		{
			SPI_PORT &= ~(1 << MOSI);
		}
		
		delay_us(10);
		
		SPI_PORT |= (1 << SCK);
		delay_us(10);
	}
	
	SPI_PORT &= ~(1 << SCK);
	delay_us(10);
	SPI_SS_PORT |= (1 << SS);
}
*/
