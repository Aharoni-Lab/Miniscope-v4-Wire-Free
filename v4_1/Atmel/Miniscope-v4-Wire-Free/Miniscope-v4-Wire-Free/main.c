#include <atmel_start.h>

#include "i2c_bb.h"

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	// Sets up I2C Bitbang
	I2C_BB_init();
	
	
	while (1) {
	}
}
