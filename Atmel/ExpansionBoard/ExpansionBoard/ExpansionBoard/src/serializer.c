#include "serializer.h"



void TWIHS_init()
{
	//Make sure you have the correct TWIHS
	twihs_options_t twihsOpt;
	twihsOpt.master_clk = sysclk_get_cpu_hz() / 2; // make sure this is the correct clock to be checking
	twihsOpt.speed = 100000; // 100kHz
	
	matrix_set_system_io(matrix_get_system_io() | CCFG_SYSIO_SYSIO4 | CCFG_SYSIO_SYSIO5);
	
	ioport_set_pin_mode(TWCK_PIN,TWCK_MODE);
	ioport_disable_pin(TWCK_PIN);
	
	ioport_set_pin_mode(TWD_PIN,TWD_MODE);
	ioport_disable_pin(TWD_PIN);

	pmc_enable_periph_clk(ID_TWIHS1);

	twihs_master_init(TWIHS1,&twihsOpt);
}



void Serializer_Init()
{
	// 1. Use PIO_PER (Pin Enable Register), PIO_PDR (Pin Disable Register) to release the pins from SD peripheral.
	// PIO_PER = 1: Enable the PIO control of the corresponding pin
	// Check PIO_PSR (Pin Status Register) to make sure its value is 1.
	// Use PIO_OER (Output Enable Register) to designate output pins
/*
	arch_ioport_pin_to_base(PIXEL_CLK)->PIO_PER |= arch_ioport_pin_to_mask(PIXEL_CLK);
	
	arch_ioport_pin_to_base(DOUT_1)->PIO_PER |= arch_ioport_pin_to_mask(DOUT_1);
	arch_ioport_pin_to_base(DOUT_2)->PIO_PER |= arch_ioport_pin_to_mask(DOUT_2);
	arch_ioport_pin_to_base(DOUT_3)->PIO_PER |= arch_ioport_pin_to_mask(DOUT_3);
	arch_ioport_pin_to_base(DOUT_4)->PIO_PER |= arch_ioport_pin_to_mask(DOUT_4);
	arch_ioport_pin_to_base(DOUT_5)->PIO_PER |= arch_ioport_pin_to_mask(DOUT_5);
	arch_ioport_pin_to_base(DOUT_6)->PIO_PER |= arch_ioport_pin_to_mask(DOUT_6);
	arch_ioport_pin_to_base(DOUT_7)->PIO_PER |= arch_ioport_pin_to_mask(DOUT_7);
	arch_ioport_pin_to_base(DOUT_8)->PIO_PER |= arch_ioport_pin_to_mask(DOUT_8);
	
	arch_ioport_pin_to_base(LINE_VAL)->PIO_PER |= arch_ioport_pin_to_mask(LINE_VAL);
	arch_ioport_pin_to_base(FRAME_VAL)->PIO_PER |= arch_ioport_pin_to_mask(FRAME_VAL);
*/
	
	// Or if all in one port, just..
	PIOD->PIO_PER |= 0x16FF000;

	// 2. Set pin directions/initial values
	ioport_set_pin_dir(PIXEL_CLK, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIXEL_CLK, 1);
	
	ioport_set_pin_dir(LINE_VAL, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LINE_VAL, 1);
	
	ioport_set_pin_dir(FRAME_VAL, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(FRAME_VAL, 1);
	
	/* Maybe these are unnecessary?
	ioport_set_pin_dir(WXB_PIN_1, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(WXB_PIN_1, 0);
	ioport_set_pin_dir(WXB_PIN_2, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(WXB_PIN_2, 0);	
	ioport_set_pin_dir(WXB_PIN_3, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(WXB_PIN_3, 0);
	ioport_set_pin_dir(WXB_PIN_4, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(WXB_PIN_4, 0);
	*/
}



void BB_Serializer()
{
	PIOD->PIO_OWER |= 0xFF000;
	// arch_ioport_pin_to_base(WXB_PIN_1)->PIO_OWER |= arch_ioport_pin_to_mask(WXB_PIN_1);			// pin 31

	// bit bang sending the data to serializer... is there a way to expedite this?
	// Send data to serializer
		
	// line, frame valids up
	ioport_set_pin_level(FRAME_VAL, 1);
	ioport_set_pin_level(LINE_VAL, 1);

	// pixel clock up
	ioport_set_pin_level(PIXEL_CLK, 1);
	
	// pixel clock down
	ioport_set_pin_level(PIXEL_CLK, 0);
	// send 8 bit data (use the PIOD module)
	PIOD->PIO_ODSR |= ;
	// pixel clk up
	// repeat until line sent (pixels/line)
	// line valid down
	// line valid up
	// repeat for number of lines (lines/frame)
	// .. line valid down
	// frame valid down
	// repeat for the number of frames in the buffer (frames/buffer)
}