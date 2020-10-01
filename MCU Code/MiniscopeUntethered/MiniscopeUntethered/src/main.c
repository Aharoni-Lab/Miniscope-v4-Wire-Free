/**
 * \file
 *
 * \brief Empty user application template
 *
 */


#include <asf.h>
#include <sdImaging.h>
#include <time_tick.h>
// #include <definitions.h>
#include <initiate.h>
#include <PYTHON480.h>
#include <conf_uart_serial.h>


// #define DEBUG_MODE
// #define SWEEP_MODE
// #define LED_BOARD_TEST_MODE


volatile uint32_t tick_start;
volatile uint32_t UARTRecBuff;
uint32_t rx_buffer[2];				// Chip Address & Write Value
uint8_t rx_letter = 0x00;			// Which 8 bits within a word
uint8_t rx_location = 0x00;			// Element within rx_buffer array

/************************************************************************/
/*                           LOCAL FUNCTIONS                            */
/************************************************************************/
void usart_write_word(Usart *p_usart, uint32_t four_bytes);

void PYTHON480_Init()
{
	Enable_Clock_Management1();
	delay_ms(10);			// Small pause here for things to stabilize.
	Enable_Clock_Management2();
	delay_ms(10);
	Required_Uploads();
	Soft_PowerUp();
	// Enable_Seq();			// Sequencer has already been enabled in Required Uploads..
}

void PYTHON480_Pin_Setup()
{
	// Set up STATUS LED
	ioport_set_pin_dir(LED_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LED_PIN, 0);

	// Set up RESET_N PIN
	ioport_set_pin_dir(RESET_N_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(RESET_N_PIN, 0);
	delay_ms(100);
	ioport_set_pin_level(RESET_N_PIN, 1);					// SPI only responds up to register 38 when RESET_N pin is high. When it's low its just all 0xffff.
	
	// Set up TRIGGER PIN
	ioport_set_pin_dir(TRIGGER0_PIN, IOPORT_DIR_OUTPUT);	// Should be high for CMOS to acquire or can be left 0 and controlled by SPI
	ioport_set_pin_level(TRIGGER0_PIN, 0);
	
	// Set up MONITOR PIN
	ioport_set_pin_dir(MONITOR0_PIN, IOPORT_DIR_INPUT);		// Monitors for the first line of each frame (high when first line)
	ioport_set_pin_level(MONITOR0_PIN, 0);					// Default (when no input) value is 0
}

void SD_Card_Write_Test()
{
	fillBuffer();			// Fills imageBuffer location with 0x11223344 a bunch of times
	
	/*
	@SD_Slot_NB: Slot number to use
	@Starting_Block: Start block number to be written = 1024, 
	@NB_Blocks_Per_Frame: Total number of blocks to be written. = (# pixels/subsample^2) / 512 (Number of bytes in a single block (sector)) = 234
	*/		
	if (SD_MMC_OK != sd_mmc_init_write_blocks(SD_SLOT_NB, STARTING_BLOCK, NB_BLOCKS_PER_FRAME))
	{
		ioport_toggle_pin_level(LED_PIN);
		return;
	}
	volatile uint32_t tick_begin;
	tick_begin = time_tick_get();
	/*
	@imageBuffer: pointer to write buffer
	@numWritesPerFrame: # pixels/subsample^2 / blocksize * # blocks_per_write
	@NB_BLOCKS_PER_FRAME: # of blocks to be written
	*/
	uint32_t i;
	for (i = 0; i < numWritesPerFrame; ++i)
	{
		if (SD_MMC_OK != sd_mmc_start_write_blocks(imageBuffer0, NB_BLOCKS_PER_FRAME))
		{
			ioport_toggle_pin_level(LED_PIN);
			return;
		}
	}
	
	/*
	Wait for the end of write blocks of data
	@True: Abort writing process initialized by sd_mmc_init_write_blocks()
			after the writing issued by sd_mmc_start_write_blocks() is done.
	*/
	if (SD_MMC_OK != sd_mmc_wait_end_of_write_blocks(true))
	{
		ioport_toggle_pin_level(LED_PIN);
		return;
	}

	while (1)
	{
		ioport_toggle_pin_level(LED_PIN);
		delay_ms(500);
	}
}


void testLEDBoardSetup()
{
	uint32_t testLED = 30;
	uint32_t testFocalLength = 100;
	
	twihs_packet_t packetTestLED;
	uint8_t TestLEDBuff[2];
	packetTestLED.chip = POTENTIOMETER_ADR;	// This is the slave address
	packetTestLED.addr[0] = 0x00;	 // This is register address for potentiometer A.
	//	packetExcLED.addr[1] = 0x01;	 // This is register address for potentiometer B.
	packetTestLED.addr_length = 1;	// The register value didn't use to get sent without this..but now it does
	TestLEDBuff[0] = 114;
	TestLEDBuff[1] = 0xFF - testLED; // Make sure the LED value makes sense/between 0 and 255
	packetTestLED.buffer = (uint8_t *) TestLEDBuff; // Location of the value to send
	packetTestLED.length = 2;
	while (twihs_master_write(TWIHS1, &packetTestLED)  != TWIHS_SUCCESS)
	{}
	
	twihs_packet_t packetTestEWLDriveInit;
	uint8_t testEWLInitBuff[2];
	packetTestEWLDriveInit.chip = EWL_DRIVER_ADR;// 0b 0111 0111
	packetTestEWLDriveInit.addr[0] = 0x03;
	packetTestEWLDriveInit.addr_length = 1;
	testEWLInitBuff[0] = 0x03;
	packetTestEWLDriveInit.buffer = (uint8_t *) testEWLInitBuff;
	packetTestEWLDriveInit.length = 1;
	while (twihs_master_write(TWIHS1, &packetTestEWLDriveInit)  != TWIHS_SUCCESS)
	{}
	
	twihs_packet_t packetTestEWLDrive;
	uint8_t testEWLBuff[2];
	packetTestEWLDrive.chip = EWL_DRIVER_ADR;// 0b 0111 0111
	packetTestEWLDrive.addr[0] = 0x08;
	packetTestEWLDrive.addr_length = 1;
	testEWLBuff[0] = testFocalLength;
	testEWLBuff[1] = 0x02;
	packetTestEWLDrive.buffer = (uint8_t *) testEWLBuff;
	packetTestEWLDrive.length = 2;
	while (twihs_master_write(TWIHS1, &packetTestEWLDrive)  != TWIHS_SUCCESS)
	{}
}


int main (void)
{
	/** Local Variable Definitions */
	uint32_t writeFrameNum = 0;
	
	/* LED Board TWI Variables */
	twihs_packet_t p_ExcLED;
	uint8_t led_buff[2];
	p_ExcLED.chip = POTENTIOMETER_ADR;		// This is the slave address
	p_ExcLED.addr[0] = 0x00;				// This is register address for potentiometer A.
	//	packetExcLED.addr[1] = 0x01;			// This is register address for potentiometer B.
	p_ExcLED.addr_length = 1;				// The register value didn't use to get sent without this..but now it does
	led_buff[0] = 114;
	led_buff[1] = 0xFF - ledValue;			// Make sure the LED value makes sense/between 0 and 255
	p_ExcLED.buffer = (uint8_t *) led_buff;	// Location of the value to send
	p_ExcLED.length = 2;
	
	twihs_packet_t p_EWL_init;
	uint8_t EWL_init_buff[2];
	p_EWL_init.chip = EWL_DRIVER_ADR;	// 0b 0111 0111
	p_EWL_init.addr[0] = 0x03;
	p_EWL_init.addr_length = 1;
	EWL_init_buff[0] = 0x03;
	p_EWL_init.buffer = (uint8_t *) EWL_init_buff;
	p_EWL_init.length = 1;
	
	twihs_packet_t p_EWL_focus;
	uint8_t EWL_focus_buff[2];
	p_EWL_focus.chip = EWL_DRIVER_ADR;		// 0b 0111 0111
	p_EWL_focus.addr[0] = 0x08;
	p_EWL_focus.addr_length = 1;
	EWL_focus_buff[0] = focalLength;
	EWL_focus_buff[1] = 0x02;
	p_EWL_focus.buffer = (uint8_t *) EWL_focus_buff;
	p_EWL_focus.length = 2;

	/** initialize MCU */
	irq_initialize_vectors();
	cpu_irq_enable();

	sysclk_init();
	board_init();	// Sets up SD card slot pins.
	ioport_init();	// Turns on all peripheral clocks. Could remove this to save power.
	
	time_tick_init();
	
	/** Initialize TWIHS Module */
	TWIHS_init();
	
	/** Initialize USART Module */
	USART_init();

	/** Initialize Image Sensor */
	enableSourceClk();	// Turns on SCK1 from MCU to drive CMOS sensor

	#ifdef PYTHON480
		PYTHON480_Pin_Setup();
		SPI_BitBang_init();
	#endif

	ioport_set_pin_level(LED_PIN, 0);
	
	PYTHON480_Init();
	
	uint16_t Python_Check;
	Python_Check = SPI_Read(200);
	
	if (Python_Check == 5000)
	{
		ioport_set_pin_level(LED_PIN, 1);
		tick_start = time_tick_get();
//		while (time_tick_calc_delay(tick_start, time_tick_get()) < 1000)
//		{}
		ioport_set_pin_level(LED_PIN, 0);
	}
		
	
	#ifdef DEBUG_MODE
//	NO_Subsample_ROI();
	#else
	Enable_Subsample();
	ROI_Configuration();
	#endif
		
	/** Boot up excitation LED & EWL driver */
	ioport_set_pin_dir(LED_ENT_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LED_ENT_PIN, 1);
	while (twihs_master_write(TWIHS1, &p_EWL_init) != TWIHS_SUCCESS)
	{}
	#ifdef DEBUG_MODE
	ioport_set_pin_level(LED_ENT_PIN, 0);
	ioport_set_pin_level(LED_ENT_PIN, 1);
	#endif
	#ifdef LED_BOARD_TEST_MODE
	testLEDBoardSetup();
	#endif // LED_BOARD_TEST_MODE
	
	
	/** Sets interrupts, configures IO pins for DMA CMOS sensor */
	imagingSensorSetup();


	/** Initialize SD Card Module */
	sd_mmc_init();

	
	/** Send frames to UART-USB Board */
	writeFrameNum = 0;
	frameNumber = 0;
	tick_start = time_tick_get();
	start_time = tick_start;
	startRecording = 1;
	ioport_set_pin_level(TRIGGER0_PIN, 1);	// Starts acquiring imaging sensor data
	ioport_set_pin_level(LED_ENT_PIN, 1);
	ioport_set_pin_level(LED_PIN, 1);
	
	while (sd_mmc_check(SD_SLOT_NB) != SD_MMC_OK) 
	{
		if (writeFrameNum > frameNumber)
		{
			switch (writeFrameNum % 3)
			{
				case (0):
				for (uint32_t j = 0; j < buffSize; ++j)
				{
					usart_write_word(USART2, imageBuffer0[j]);
				}
				case (1):
				for (uint32_t j = 0; j < buffSize; ++j)
				{
					usart_write_word(USART2, imageBuffer1[j]);
				}
				case (2):
				for (uint32_t j = 0; j < buffSize; ++j)
				{
					usart_write_word(USART2, imageBuffer2[j]);
				}
			}
			++writeFrameNum;
		}
	}

	/** Stop recording until SD card */
	startRecording = 0;
	ioport_set_pin_level(TRIGGER0_PIN, 0);	// Stops acquiring imaging sensor data
	ioport_set_pin_level(LED_ENT_PIN, 0);
	ioport_set_pin_level(LED_PIN, 0);
	
	
	if (sd_mmc_get_type(SD_SLOT_NB) == (CARD_TYPE_SD|CARD_TYPE_HC))		// This is the correct type of card (SDHC)
	{}
	uint32_t sdCapacity = sd_mmc_get_capacity(SD_SLOT_NB);				// in KB
	
//	SD_Card_Write_Test();
	// if (sd_mmc_is_write_protected(SD_SLOT_NB) == true)
	// {
	//This is a problem. Maybe turn off the LED
	// }

	/** Configure Miniscope */
	imagingSensorLoadHeader();
	
	while (twihs_master_write(TWIHS1, &p_ExcLED) != TWIHS_SUCCESS)
	{}
	while (twihs_master_write(TWIHS1, &p_EWL_focus) != TWIHS_SUCCESS)
	{}

	if (gain == 1)
	{
		SPI_Write(204, 0x00E1); 	// (gain 1x : 0x00E1 // gain 2x : 0x00E4 // gain 3.5x : 0x0024)
	}
	else if (gain == 2)
	{
		SPI_Write(204, 0x00E4); 	// (gain 1x : 0x00E1 // gain 2x : 0x00E4 // gain 3.5x : 0x0024)
	}
	else if (gain == 3)
	{
		SPI_Write(204, 0x0024); 	// (gain 1x : 0x00E1 // gain 2x : 0x00E4 // gain 3.5x : 0x0024)
	}
	else
	{}


	/** Wait 5 seconds*/
	tick_start = time_tick_get();
	while (time_tick_calc_delay(tick_start, time_tick_get()) < 5000)
	{}

	
	/** Set up to write to SD card */
	sd_mmc_init_write_blocks(SD_SLOT_NB, STARTING_BLOCK, 50 * NB_BLOCKS_PER_FRAME);	
	uint32_t curBlock = STARTING_BLOCK;
	uint32_t writeLineCount = 0;
	uint32_t writeCount = 0;
	
	
	/** Set up to begin data recording */
	writeFrameNum = 0;
	frameNumber = 0;
	tick_start = time_tick_get();
	start_time = tick_start;
	startRecording = 1;
	ioport_set_pin_level(TRIGGER0_PIN, 1);	// Starts acquiring imaging sensor data
	ioport_set_pin_level(LED_ENT_PIN, 1);
	ioport_set_pin_level(LED_PIN, 1);
	
	
	/** Sweep Mode */
	uint8_t voltageStep = focusMin;			// VLL_4RMS = 44.5mV_RMS x N + 24.4V_RMS, where N = code 0x000 to 0x3FF in decimal (0-1023), voltageStep is the 8 MSBs (0-255)
	
	twihs_packet_t packetEWLTest;
	uint8_t EWLTestBuff[2];
	packetEWLTest.chip = EWL_DRIVER_ADR;	// 0b 0111 0111
	packetEWLTest.addr[0] = 0x08;
	packetEWLTest.addr_length = 1;
	packetEWLTest.buffer = (uint8_t *) EWLTestBuff;
	EWLTestBuff[1] = 0x02;
	packetEWLTest.length = 2;

	
	while (1) 
	{	
		if (frameNumber > writeFrameNum) 
		{
			if (recMode == 2)
			{
				// Testing EWL distance by changing calibration every (20fps * plane-duration(s)) frames
				if (writeFrameNum % (20 * focusStepLen)  == 0)
				{
					// Send different number to EWL Drive
					EWLTestBuff[0] = voltageStep;
	//				while (twihs_master_write(TWIHS1, &packetEWLTest) != TWIHS_SUCCESS)
	//				{}
					twihs_master_write(TWIHS1, &packetEWLTest);
				
					if (voltageStep <= focusMax)
					{
						voltageStep += ((focusMax + 1 - focusMin) / focusSteps);
					}
				}
			}
			
			
			/** Writing footers and image sensor data to SD Card */
			#ifdef PYTHON480
			switch (writeFrameNum % 3)
			{
				case (0):
				if (recMode == 2)
				{
					imageBuffer0[buffSize - 5] = voltageStep;
				}
				else
				{
					imageBuffer0[buffSize - 5] = focalLength;
				}
				imageBuffer0[buffSize - 6] = time_tick_calc_delay(tick_start, time_tick_get());
				imageBuffer0[buffSize - 7] = frameNumber - writeFrameNum;
				sd_mmc_start_write_blocks(&imageBuffer0[0], NB_BLOCKS_PER_WRITE);
				break;
				
				case (1):
				if (recMode == 2)
				{
					imageBuffer1[buffSize - 5] = voltageStep;
				}
				else
				{
					imageBuffer1[buffSize - 5] = focalLength;
				}
				imageBuffer1[buffSize - 6] = time_tick_calc_delay(tick_start, time_tick_get());		// time when beginning to write to SD
				imageBuffer1[buffSize - 7] = frameNumber - writeFrameNum;
				sd_mmc_start_write_blocks(&imageBuffer1[0], NB_BLOCKS_PER_WRITE);
				break;
				
				case (2):
				if (recMode == 2)
				{
					imageBuffer2[buffSize - 5] = voltageStep;
				}
				else
				{
					imageBuffer2[buffSize - 5] = focalLength;
				}
				imageBuffer2[buffSize - 6] = time_tick_calc_delay(tick_start, time_tick_get());
				imageBuffer2[buffSize - 7] = frameNumber - writeFrameNum;
				sd_mmc_start_write_blocks(&imageBuffer2[0], NB_BLOCKS_PER_WRITE);
				break;
			}
			#endif
			
			#ifdef EV76C454
				imageBuffer[buffSize - 2] = time_tick_calc_delay(tick_start, time_tick_get());
				sd_mmc_start_write_blocks(&imageBuffer[0 * NB_BLOCKS_PER_WRITE * 128], NB_BLOCKS_PER_WRITE * 5);
			#endif

			#ifdef EV76C454_SUBSAMP
				switch (writeFrameNum % 3)
				{
				case (0):
					imageBuffer0[buffSize - 2] = time_tick_calc_delay(tick_start, time_tick_get());
					sd_mmc_start_write_blocks(&imageBuffer0[0], NB_BLOCKS_PER_WRITE);
					break;
				case (1):
					imageBuffer1[buffSize - 2] = time_tick_calc_delay(tick_start, time_tick_get());
					sd_mmc_start_write_blocks(&imageBuffer1[0], NB_BLOCKS_PER_WRITE);
					break;
				case (2):
					imageBuffer2[buffSize - 2] = time_tick_calc_delay(tick_start, time_tick_get());
					sd_mmc_start_write_blocks(&imageBuffer2[0], NB_BLOCKS_PER_WRITE);
					break;
				}				
			#endif

			#ifdef EV76C541
				switch (writeFrameNum % 3)
				{
					case (0):
					imageBuffer0[buffSize - 2] = time_tick_calc_delay(tick_start, time_tick_get());
					sd_mmc_start_write_blocks(&imageBuffer0[0], NB_BLOCKS_PER_WRITE);
					break;
					case (1):
					imageBuffer1[buffSize - 2] = time_tick_calc_delay(tick_start, time_tick_get());
					sd_mmc_start_write_blocks(&imageBuffer1[0], NB_BLOCKS_PER_WRITE);
					break;
					case (2):
					imageBuffer2[buffSize - 2] = time_tick_calc_delay(tick_start, time_tick_get());
					sd_mmc_start_write_blocks(&imageBuffer2[0], NB_BLOCKS_PER_WRITE);
					break;
				}			
			#endif

			sd_mmc_wait_end_of_write_blocks(false);
			writeFrameNum++;	
			sdImageWriteFrameNum = writeFrameNum;

			#ifdef EV76C541
				startRecording = 1;
			#endif
			#ifdef EV76C454_SUBSAMP
					startRecording = 1;
			#endif
			#ifdef PYTHON480
				startRecording = 1;
			#endif
			#ifdef EV76C454
				startRecording = 1;
			#endif
			
			if (writeFrameNum % 50 == 0)
			{
				curBlock += 50 * NB_BLOCKS_PER_FRAME;
				sd_mmc_init_write_blocks(SD_SLOT_NB, curBlock, 50 * NB_BLOCKS_PER_FRAME);
			}
		}
		
		if (time_tick_calc_delay(tick_start, time_tick_get()) >= numFramesToRecord * 1000)
		{
			ioport_set_pin_level(LED_PIN, 0);
			ioport_set_pin_level(LED_ENT_PIN, 0);
			while (1)
			{}
		}
		testPoint = 0;						
	}
}


void miniscope_calibrate(uint32_t buffer[2])
{
	if (rx_buffer[0] == 1)					// Option 1 = LED brightness
	{
		ledValue = rx_buffer[1];
		
		twihs_packet_t p_LED_cal;
		uint8_t led_buff[2];
		p_LED_cal.chip = POTENTIOMETER_ADR;		// This is the slave address
		p_LED_cal.addr[0] = 0x00;				// This is register address for potentiometer A.
		p_LED_cal.addr_length = 1;				// The register value didn't use to get sent without this..but now it does
		led_buff[0] = 114;
		led_buff[1] = 0xFF - ledValue;			// Make sure the LED value makes sense/between 0 and 255
		p_LED_cal.buffer = (uint8_t *) led_buff;	// Location of the value to send
		p_LED_cal.length = 2;
		
		while (twihs_master_write(TWIHS1, &p_LED_cal) != TWIHS_SUCCESS)
		{}
	}
	
	else if (rx_buffer[0] == 2)				// Option 2 = EWL focal length
	{
		focalLength = rx_buffer[2];
		
		twihs_packet_t p_EWL_cal;
		uint8_t EWL_focus_buff[2];
		p_EWL_cal.chip = EWL_DRIVER_ADR;		// 0b 0111 0111
		p_EWL_cal.addr[0] = 0x08;
		p_EWL_cal.addr_length = 1;
		EWL_focus_buff[0] = focalLength;
		EWL_focus_buff[1] = 0x02;
		p_EWL_cal.buffer = (uint8_t *) EWL_focus_buff;
		p_EWL_cal.length = 2;
		
		while (twihs_master_write(TWIHS1, &p_EWL_cal) != TWIHS_SUCCESS)
		{}
	}
	
	else if (rx_buffer[0] == 3)				// Option 3 = image sensor gain
	{
		if (rx_buffer[1] == 1)
		{
			SPI_Write(204, 0x00E1); 			// (gain 1x : 0x00E1 // gain 2x : 0x00E4 // gain 3.5x : 0x0024)
		}
		else if (rx_buffer[1] == 2)
		{
			SPI_Write(204, 0x00E4); 			// (gain 1x : 0x00E1 // gain 2x : 0x00E4 // gain 3.5x : 0x0024)
		}
		else if (rx_buffer[1] == 3)
		{
			SPI_Write(204, 0x0024); 			// (gain 1x : 0x00E1 // gain 2x : 0x00E4 // gain 3.5x : 0x0024)
		}
	}
}


/** Write into a 32 bit variable with USART
/*  Reads in 4 8-bit chunks in sequence, going from MSB to LSB */
void usart_write_word(Usart *p_usart, uint32_t four_bytes)
{
	for (uint32_t i = 0; i < 4; ++i)
	{
		while(usart_write(p_usart, four_bytes >> (8 * (3 - i))))
		{}
	}
}


/** UART interrupt handler
/*  Receives data from UART into a 2-word buffer, then calibrates Miniscope when both elements are fully written */
void USART_ISR_HANDLER(void)
{
	uint32_t dw_status = usart_get_status(USART2);

	if (dw_status & US_CSR_RXRDY)
	{
		uint32_t received_byte;
		
		usart_read(USART2, &received_byte);

		rx_buffer[rx_location] = (rx_buffer[rx_location] & ~(0xFF << (8 * (3 - rx_letter)))) | (received_byte << (8 * (3 - rx_letter)));		// Writes from MSB to LSB, 8 bits at a time

		rx_letter = (rx_letter + 1) % 4;		// Move 8 bits to the right (towards LSB)
		
		if (rx_letter % 4 == 0)					// If an entire word is written
		{
			if (rx_location == 1)					// and if it's the second word (both address & value received)
			{
				miniscope_calibrate(rx_buffer);		// Calibrate the Miniscope
			}
			
			rx_location = (rx_location + 1) % 2;	// Move between address & value
		}
	}
}