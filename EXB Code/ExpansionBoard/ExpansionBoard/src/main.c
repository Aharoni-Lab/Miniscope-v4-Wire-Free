/**
 * \file
 *
 * Code for the Wired Expansion Board that can be plugged into the Wireless Miniscope Microcontroller Board.
 *
 */

/**
 * 1. The WXB MCU programs the serializer through I2C.
 *    (a) Find the correct data output rates, etc.
 *    (b) Uses SDA and SCL lines
 *
 * 2. The WXB MCU grabs data from WF MCU through interrupts.
 *    (a) Uses 4 data-in lines, 1 clock-in line, and 1 command-out line
 *    (b) Clock-in line is used as an interrupt signal, where every drop triggers a data grab from the 4 data-in lines
 *    (c) The data are saved into ImageBuffer.
 *
 * 3. The WXB MCU sends data to the serializer.
 *    (a) Uses 8 data-out lines, 1 pixel-clock line
 *    (b) With every clock-down, 8 bits (a pixel) is sent.
 *
 * 4. The WXB MCU sends commands to the WF MCU.
 *    (a) Not sure how this will be implemented, since the coax cable leads to the DOUT of the serializer
 *    (b) Maybe can program the serializer to take in data through DOUT and relay it to DIN?
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
	uint8_t Ser_Buff[2];
	Ser_Packet.chip =		 = ;
	Ser_Packet.addr[0]		 = 0x01;
	Ser_Packet.addr_length	 = ;
	Ser_Buff[0]				|= 0x10;
	Ser_Packet.buffer 		|= (uint8_t *) Ser_Buff;		// VDDIO = 1.8V
	Ser_Packet.length		 = 1;
	while (twihs_master_write(TWIHS1, Ser_Packet) != TWIHS_SUCCESS)
	{}
	
	// something about starting to accept data = 1 (include it in the interrupt function)
	D_In = 1;
	
	BB_Serializer();	
}