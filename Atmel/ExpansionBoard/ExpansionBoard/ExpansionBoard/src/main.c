/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include "expansion.h"
#include "definitions.h"
#include "serializer.h"


int main (void)
{
	uint32_t D_In = 0;
	WDT->WDT_MR = WDT_MR_WDDIS;
	irq_initialize_vectors();
	cpu_irq_enable();
	
	sysclk_init();
	board_init();
	ioport_init();
	TWIHS_init();
	
	twihs_packet_t Ser_Packet;
	// SDA and SCL to communicate with the serializer and set it up.
	// define object.addr[0], .buffer, .length
	Ser_Packet.addr[0]		 = 0x01;
	Ser_Packet.buffer[0] 	|= 0x10;		// VDDIO = 1.8V
	Ser_Packet.length		 = 1;
	while (twihs_master_write(TWIHS1, Ser_Packet) != TWIHS_SUCCESS)
	{}
	
	// something about starting to accept data = 1 (include it in the interrupt function)
	D_In = 1;
	
	BB_Serializer();	
}