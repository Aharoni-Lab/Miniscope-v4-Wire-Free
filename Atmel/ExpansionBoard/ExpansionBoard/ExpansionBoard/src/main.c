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

int main (void)
{
	WDT->WDT_MR = WDT_MR_WDDIS;
	irq_initialize_vectors();
	cpu_irq_enable();
	
	sysclk_init();
	board_init();
	ioport_init();
	
	// SDA and SCL to communicate with the serializer and set it up.
	// define object.addr, .buffer, .length
	// while (twihs_master_write(TWIHS?, twihs_packet_t object) != TWIHS_SUCESS)
	// {}
	
	// something about starting to accept data = 1 (include it in the interrupt function)
	
	// bit bang sending the data to serializer... is there a way to expedite this?
	// Send data to serializer
	// line, frame valids up
		// pixel clock up
		// send 8 bit data (use the PIOD module)
		// pixel clock down
	// repeat until line sent
	// line valid down
	// line valid up
	// repeat for number of lines
	// .. line valid down
	// frame valid down
	
	// repeat for the number of frames in the buffer
}