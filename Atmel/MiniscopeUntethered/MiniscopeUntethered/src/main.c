/************************************************************************/
/************************************************************************/
/**                    MiniScope V4 Wire-free Ver.                     **/
/**                     Author: Daniel Aharoni                         **/
/**                     Edits by Raymond Chang                         **/
/************************************************************************/
/************************************************************************/


//===========================================================//
// Untethered MiniScope main code for Python 480 CMOS sensor //
//===========================================================//
 
 
#include <asf.h>
#include "sdImaging.h"
#include "time_tick.h"
#include "definitions.h"
#include "initiate.h"
#include "PYTHON480.h"



/************************************************************************/
/*                        VARIABLE DEFINITIONS                          */
/************************************************************************/

volatile uint32_t time_ms;
volatile uint32_t tick_start;
volatile uint32_t sdCount = 0;
volatile uint32_t sdCount2 = 0;
volatile uint32_t valueLED = 0; //PWM duty value
volatile uint32_t test[128];

//Holds PWM channel information
pwm_channel_t g_pwm_channel_led;



/************************************************************************/
/*                           LOCAL FUNCTIONS                            */
/************************************************************************/

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
	// Set up SPI
	ioport_set_pin_dir(SPI_BB_MOSI, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(SPI_BB_SCK, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(SPI_BB_SS, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(SPI_BB_MISO, IOPORT_DIR_INPUT);
	
	ioport_set_pin_level(SPI_BB_SS, 1);
	ioport_set_pin_level(SPI_BB_SCK, 0);

	// Set up STATUS LED
	ioport_set_pin_dir(LED_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LED_PIN, 0);
	
	// Set up EXCITATION LED
	ioport_set_pin_dir(LED_ENT_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LED_ENT_PIN, 1);
	
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

// Excitation LED power on
void Enable_Excit_LED()
{
	ioport_set_pin_level(LED_ENT_PIN, 1);
}

// Excitation LED power off
void Disable_Excit_LED()
{
	ioport_set_pin_level(LED_ENT_PIN, 0);
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

// Wired Expansion PCB Data Transfer
// initiate the pins
void Wired_Expansion_Board_Init()
{
	// 1. Use PIO_PER (Pin Enable Register), PIO_PDR (Pin Disable Register) to release the pins from SD peripheral.
	// PIO_PER = 1: Enable the PIO control of the corresponding pin
	// Check PIO_PSR (Pin Status Register) to make sure its value is 1.
	// Use PIO_OER (Output Enable Register) to designate output pins
	arch_ioport_pin_to_base(WXB_CLK)->PIO_PER |= arch_ioport_pin_to_mask(WXB_CLK);
	arch_ioport_pin_to_base(WXB_PIN_1)->PIO_PER |= arch_ioport_pin_to_mask(WXB_PIN_1);
	arch_ioport_pin_to_base(WXB_PIN_2)->PIO_PER |= arch_ioport_pin_to_mask(WXB_PIN_2);
	arch_ioport_pin_to_base(WXB_PIN_3)->PIO_PER |= arch_ioport_pin_to_mask(WXB_PIN_3);
	arch_ioport_pin_to_base(WXB_PIN_4)->PIO_PER |= arch_ioport_pin_to_mask(WXB_PIN_4);
	arch_ioport_pin_to_base(WXB_CONFIG)->PIO_PER |= arch_ioport_pin_to_mask(WXB_CONFIG);
	
	// Or if all in one port, just..
	// PIOA->PIO_PER |= 0x....

	// 2. Set pin directions/initial values
	ioport_set_pin_dir(WXB_CLK, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(WXB_CLK, 0);
	
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
	
	ioport_set_pin_dir(WXB_CONFIG, IOPORT_DIR_INPUT);		// To configure WF while WXB is plugged in
	ioport_set_pin_level(WXB_CONFIG, 0);
}

// Write buffers into the wired expansion board
void BitBang_Write_WXB()
{
	// 1. Set bit-banging pins so they can send signal parallel.
	// The PIO Controller offers a direct control of PIO outputs by single write access to PIO_ODSR (Output Data Status Register)
	// Only bits unmasked by the PIO_OWSR (Output Write Status Register) are written.
	// The mask bits in PIO_OWSR are set by writing to the PIO_OWER (Output Write Enable Register)
	// and cleared by writing to the PIO_OWDR (Output Write Disable Register)
	// After reset, the synchronous data output is disabled on all the I/O lines as PIO_OWSR resets at 0x0.
//	arch_ioport_pin_to_base(WXB_CLK)->PIO_OWER |= arch_ioport_pin_to_mask(WXB_CLK);			// Should I include the clock?
	arch_ioport_pin_to_base(WXB_PIN_1)->PIO_OWER |= arch_ioport_pin_to_mask(WXB_PIN_1);			// pin 31
	arch_ioport_pin_to_base(WXB_PIN_2)->PIO_OWER |= arch_ioport_pin_to_mask(WXB_PIN_2);			// pin 26
	arch_ioport_pin_to_base(WXB_PIN_3)->PIO_OWER |= arch_ioport_pin_to_mask(WXB_PIN_3);			// pin 27
	arch_ioport_pin_to_base(WXB_PIN_4)->PIO_OWER |= arch_ioport_pin_to_mask(WXB_PIN_4);			// pin 30
//	arch_ioport_pin_to_base(WXB_CONFIG)->PIO_OWDR |= arch_ioport_pin_to_mask(WXB_CONFIG);		// Unnecessary?

	// 2. Send a complete buffer, 4 bits at a time.
	// imageBuffer size = (NUM_PIXEL_WORDS + FRAME_FOOTER_LENGTH) * 32 bits per word
	
	uint32_t Write_Frame_Num = 0;
	#define SD_BUS_SIZE		4
	
	while(1)
	{
		if (frameNumber > Write_Frame_Num)			// If there are more frames to write..
		{
			#ifdef NOIP1SN0480A
		
			ioport_set_pin_level(WXB_CLK, 1);		// Pull clock pin high
			delay_us(10);
		
			uint32_t i = 0;
			
			switch (Write_Frame_Num % 3)				// Three different buffers
			{
				case (0):
				for (i = 0; i < (NUM_PIXELS + FRAME_FOOTER_LENGTH); ++i)		// For each 32-bit word in the buffer...
				{
					uint32_t four_pxs = imageBuffer0[i];
					uint8_t j;
					for (j = 0; j < (32 / SD_BUS_SIZE); ++j)					// Each word needs to be bussed 8 times
					{
						uint32_t four_bits = 0;
						four_bits |= (((four_pxs & 0x80000000) >> (31 - arch_ioport_pin_to_mask(WXB_PIN_1)))					// MSB of four_pxs goes to WXB_PIN_1 location
									 | (((four_pxs << 1) & 0x80000000) >> (31 - arch_ioport_pin_to_mask(WXB_PIN_2)))			// Next bit of four_pxs goes to WXB_PIN_2 location
									 | (((four_pxs << 2) & 0x80000000) >> (31 - arch_ioport_pin_to_mask(WXB_PIN_3))) 
									 | (((four_pxs << 3) & 0x80000000) >> (31 - arch_ioport_pin_to_mask(WXB_PIN_4))));		// check if the four_pxs itself gets moved

						ioport_set_pin_level(WXB_CLK, 0);							// Pull clock pin low
						arch_ioport_pin_to_base(WXB_PIN_1)->PIO_ODSR |= (four_bits);			// Send four bits on the SD but simultaneously
						delay_us(10);
					
						ioport_set_pin_level(WXB_CLK, 1);							// Pull clock pin high
						delay_us(10);
			
						four_pxs = (four_pxs << SD_BUS_SIZE);						// Move the word up bitwise by the bus size (4 data pins)
					}
				}
			
				case (1):
				for (i = 0; i < (NUM_PIXELS + FRAME_FOOTER_LENGTH); ++i)		// For each 32-bit word in the buffer...
				{
					uint32_t four_pxs = imageBuffer1[i];
					uint8_t j;
					for (j = 0; j < (32 / SD_BUS_SIZE); ++j)					// Each word needs to be bussed 8 times
					{
						uint32_t four_bits = 0;
						four_bits |= (((four_pxs & 0x80000000) >> (31 - arch_ioport_pin_to_mask(WXB_PIN_1)))					// MSB of four_pxs goes to WXB_PIN_1 location
						| (((four_pxs << 1) & 0x80000000) >> (31 - arch_ioport_pin_to_mask(WXB_PIN_2)))			// Next bit of four_pxs goes to WXB_PIN_2 location
						| (((four_pxs << 2) & 0x80000000) >> (31 - arch_ioport_pin_to_mask(WXB_PIN_3)))
						| (((four_pxs << 3) & 0x80000000) >> (31 - arch_ioport_pin_to_mask(WXB_PIN_4))));		// check if the four_pxs itself gets moved

						ioport_set_pin_level(WXB_CLK, 0);							// Pull clock pin low
						arch_ioport_pin_to_base(WXB_PIN_1)->PIO_ODSR |= (four_bits);			// Send four bits on the SD but simultaneously
						delay_us(10);
					
						ioport_set_pin_level(WXB_CLK, 1);							// Pull clock pin high
						delay_us(10);
					
						four_pxs = (four_pxs << SD_BUS_SIZE);						// Move the word up bitwise by the bus size (4 data pins)
					}
				}
			
				case (2):
				for (i = 0; i < (NUM_PIXELS + FRAME_FOOTER_LENGTH); ++i)		// For each 32-bit word in the buffer...
				{
					uint32_t four_pxs = imageBuffer2[i];
					uint8_t j;
					for (j = 0; j < (32 / SD_BUS_SIZE); ++j)					// Each word needs to be bussed 8 times
					{
						uint32_t four_bits = 0;
						four_bits |= (((four_pxs & 0x80000000) >> (31 - arch_ioport_pin_to_mask(WXB_PIN_1)))					// MSB of four_pxs goes to WXB_PIN_1 location
						| (((four_pxs << 1) & 0x80000000) >> (31 - arch_ioport_pin_to_mask(WXB_PIN_2)))			// Next bit of four_pxs goes to WXB_PIN_2 location
						| (((four_pxs << 2) & 0x80000000) >> (31 - arch_ioport_pin_to_mask(WXB_PIN_3)))
						| (((four_pxs << 3) & 0x80000000) >> (31 - arch_ioport_pin_to_mask(WXB_PIN_4))));		// check if the four_pxs itself gets moved

						ioport_set_pin_level(WXB_CLK, 0);							// Pull clock pin low
						arch_ioport_pin_to_base(WXB_PIN_1)->PIO_ODSR |= (four_bits);			// Send four bits on the SD but simultaneously
						delay_us(10);
					
						ioport_set_pin_level(WXB_CLK, 1);							// Pull clock pin high
						delay_us(10);
					
						four_pxs = (four_pxs << SD_BUS_SIZE);						// Move the word up bitwise by the bus size (4 data pins)
					}
				}
			}
			#endif // NOIP1SN0480A
			Write_Frame_Num++;
		
			#ifdef NOIP1SN0480A
			startRecording = 1;
			#endif
		}
	}
}


/************************************************************************/
/*                            MAIN FUNCTION                             */
/************************************************************************/

int main (void)
{
	// ========== Variable Definitions ========== //
	uint32_t writeNum = 0;
	uint32_t writeFrameNum = 0;
	
	
	// ========== Interrupt Managements ========== //	
	WDT->WDT_MR = WDT_MR_WDDIS;		// Disables WatchDog Timer
	//SCB_EnableICache();
	//SCB_EnableDCache();
	irq_initialize_vectors();		// IRQ: Interrupt Request Line
	cpu_irq_enable();


	// ========== Microcontroller Initiation ========== //
	sysclk_init();
	board_init();		// Sets up SD card slot pins
	ioport_init();		// Turns on all peripheral clocks. could remove this to save power


	// ========== Clock Initiation ========== //
	enableSourceClk();	// Turns on SCK1 from MCU to drive CMOS sensor
	time_tick_init();
	PWM_Init();
	//DACC_init(); //The DAC cannot run at 1.8V. This needs to be replaced with PWM to drive the LED current source
	//DACC_updateOutput(0x0FFF,1);
	
	
	// ========== Setup Microcontroller for PYTHON480 ========== //
	#ifdef NOIP1SN0480A
		PYTHON480_Pin_Setup();
	
		// Python480 uses SPI, and lens & LED use I2C
		SPI_BitBang_init();
		TWIHS_init();
	#endif
	
	
	// ========== Power Up PYTHON480 ========== //
	PYTHON480_Init();
	
	uint16_t Python_ID;
	Python_ID = SPI_Read(474);
	
	// Check SPI Communication: Read the Python480 register using the SPI connection
	if (Python_ID == 0x003F)
	{
		ioport_toggle_pin_level(LED_PIN);
	}

	//pmc_switch_pck_to_mck(ID_PIOA, 1);

	
	// ========== Configure PYHTON480 ========== //	
	ROI_Configuration();		// Check if 4 px vs 8px granularity
	
	Enable_Subsample();


	// ========== Micro SD Card Initialization ========== //
	sd_mmc_init();
	
	// Micro SD card slot connection check
	uint32_t SD_Check;
	
// 	while (sd_mmc_check(SD_SLOT_NB) != SD_MMC_OK)
// 	{}
	SD_Check = sd_mmc_check(SD_SLOT_NB);
	while (SD_Check != SD_MMC_OK) 
 	{
		ioport_toggle_pin_level(LED_PIN);					// while the SD connection is NOT okay.. wait
		delay_ms(100);										// delete later when expansion PCB
		SD_Check = sd_mmc_check(SD_SLOT_NB);
	}
	
	if (sd_mmc_get_type(SD_SLOT_NB) == (CARD_TYPE_SD|CARD_TYPE_HC))
	{
		ioport_set_pin_level(LED_PIN, 1);					// If SDHC, turn on status LED
		#define MSD											// set MSD. Go to: Micro SD Card Data Transfer.
	}
	else
	{
		ioport_set_pin_level(LED_PIN, 0);					// if not SDHC, turn off status LED	
		#define WXB											// set WXB. Go to: Wired Expansion PCB Data Transfer.
	}
	
	uint32_t curBlock = STARTING_BLOCK;
	uint32_t writeLineCount = 0;
	uint32_t writeCount = 0;
	
	#ifdef MSD
	// ========== Micro SD Card Data Transfer ========== //
	uint32_t sdCapacity = sd_mmc_get_capacity(SD_SLOT_NB);	// in KB
//	SD_Card_Write_Test();

	// ========== Stream Data from Imaging Sensor to SD Card ========= //
	imagingSensorLoadHeader();
	
	if (ledValue >= PWM_PERIOD_VALUE)
		ledValue = 0;
	pwm_channel_update_duty(PWM0, &g_pwm_channel_led, ledValue);
	
	// ========== Try This ========== //
	numFramesToRecord = 1;		// More like number of seconds to record.. so # frames = numFramesToRecord * fps (20)

	imagingSensorSetup(); //sets interrupts, configures IO pins for DMA CMOS sensor

	tick_start = time_tick_get();
	while (time_tick_calc_delay(tick_start, time_tick_get()) < 5000)
	{}
	
	sd_mmc_init_write_blocks(SD_SLOT_NB, STARTING_BLOCK, 50 * NB_BLOCKS_PER_FRAME);	
	
//	uint32_t curBlock = STARTING_BLOCK;
//	uint32_t writeLineCount = 0;
//	uint32_t writeCount = 0;
	
	tick_start = time_tick_get();
	
	startRecording = 1;
	ioport_set_pin_level(TRIGGER0_PIN, 1);	// Starts acquisition of imaging sensor
	ioport_set_pin_level(LED_ENT_PIN, 1);	// Enable PWM LED Control Driver
	ioport_set_pin_level(LED_PIN, 1);
	
	while (1)
	{	
		if (frameNumber > writeFrameNum)
		{
			#ifdef EV76C454
				imageBuffer[buffSize-2] = time_tick_calc_delay(tick_start, time_tick_get());
				sd_mmc_start_write_blocks(&imageBuffer[0*NB_BLOCKS_PER_WRITE*128],NB_BLOCKS_PER_WRITE*5);//NB_BLOCKS_PER_WRITE
			#endif

			#ifdef EV76C454_SUBSAMP
				switch (writeFrameNum%3)
				{
				case (0):
					imageBuffer0[buffSize-2] = time_tick_calc_delay(tick_start, time_tick_get());
					sd_mmc_start_write_blocks(&imageBuffer0[0],NB_BLOCKS_PER_WRITE);//NB_BLOCKS_PER_WRITE
					break;
				case (1):
					imageBuffer1[buffSize-2] = time_tick_calc_delay(tick_start, time_tick_get());
					sd_mmc_start_write_blocks(&imageBuffer1[0],NB_BLOCKS_PER_WRITE);//NB_BLOCKS_PER_WRITE
					break;
				case (2):
					imageBuffer2[buffSize-2] = time_tick_calc_delay(tick_start, time_tick_get());
					sd_mmc_start_write_blocks(&imageBuffer2[0],NB_BLOCKS_PER_WRITE);//NB_BLOCKS_PER_WRITE
					break;
				}				
			#endif
			
			#ifdef NOIP1SN0480A
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
				switch (writeFrameNum%3)
				{
					case (0):
					imageBuffer0[buffSize-2] = time_tick_calc_delay(tick_start, time_tick_get());
					sd_mmc_start_write_blocks(&imageBuffer0[0],NB_BLOCKS_PER_WRITE);//NB_BLOCKS_PER_WRITE
					break;
					case (1):
					imageBuffer1[buffSize-2] = time_tick_calc_delay(tick_start, time_tick_get());
					sd_mmc_start_write_blocks(&imageBuffer1[0],NB_BLOCKS_PER_WRITE);//NB_BLOCKS_PER_WRITE
					break;
					case (2):
					imageBuffer2[buffSize-2] = time_tick_calc_delay(tick_start, time_tick_get());
					sd_mmc_start_write_blocks(&imageBuffer2[0],NB_BLOCKS_PER_WRITE);//NB_BLOCKS_PER_WRITE
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
				//if (frameNumber>sdImageWriteFrameNum +1) {
					startRecording = 1;
				//}
			#endif
			
			#ifdef NOIP1SN0480A
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


		//if ((frameNumber == writeFrameNum) && ((lineCount*IMAGE_HEIGHT) > ((writeNum+1)*NB_BLOCKS_PER_WRITE*512))){ //Writing frame as it is being acquired
			//sd_mmc_start_write_blocks(&imageBuffer[writeNum*NB_BLOCKS_PER_WRITE*128],NB_BLOCKS_PER_WRITE);//NB_BLOCKS_PER_WRITE
			//sd_mmc_wait_end_of_write_blocks(false);
			//writeNum++;		
		//}
		//if ((frameNumber > writeFrameNum) && (writeNum<4)){ //Writing frame after it has been acquired
			//sd_mmc_start_write_blocks(&imageBuffer[writeNum*NB_BLOCKS_PER_WRITE*128],NB_BLOCKS_PER_WRITE);//NB_BLOCKS_PER_WRITE
			//sd_mmc_wait_end_of_write_blocks(false);
			//writeNum++;
		//}
		//if ((frameNumber > writeFrameNum) && (writeNum==4)){ //Writing last block of frame
			//imageBuffer[buffSize-2] = time_tick_calc_delay(tick_start, time_tick_get());
			//sd_mmc_start_write_blocks(&imageBuffer[writeNum*NB_BLOCKS_PER_WRITE*128],NB_BLOCKS_PER_WRITE);//NB_BLOCKS_PER_WRITE
			//sd_mmc_wait_end_of_write_blocks(false);
			//writeFrameNum++;
			//startRecording = 1;
			//if (writeFrameNum%50 == 0) {
				//curBlock+= 50*NB_BLOCKS_PER_FRAME;
				//sd_mmc_init_write_blocks(SD_SLOT_NB,curBlock,50*NB_BLOCKS_PER_FRAME);
			//}
			//writeNum = 0;
		//}

		
		//test[(frameNumber-1)*4] = imageBuffer[0];
		//test[(frameNumber-1)*4+1] = imageBuffer[1];
		//test[(frameNumber-1)*4+2] = imageBuffer[2];
		//test[(frameNumber-1)*4+3] = imageBuffer[3];

		//for (writeNum=0;writeNum <5;writeNum++){
			//sd_mmc_start_write_blocks(&imageBuffer[writeNum*NB_BLOCKS_PER_WRITE*128],NB_BLOCKS_PER_WRITE);//NB_BLOCKS_PER_WRITE
			//sd_mmc_wait_end_of_write_blocks(false);
		//}
		//ioport_toggle_pin_level(LED_PIN);
		//ioport_toggle_pin_level(ENT_PIN);

		//valueLED = (valueLED+400)&0x0FFF; //higher value less bright
		//DACC_updateOutput(valueLED,1);

		//if (frameNumber>=numFramesToRecord)
		//{ //end at number of frames
		if (time_tick_calc_delay(tick_start, time_tick_get()) >= numFramesToRecord * 1000)
		{
			//sd_mmc_init_write_blocks(SD_SLOT_NB,STARTING_BLOCK-1,1);
			//sd_mmc_start_write_blocks(&test[0],1);//NB_BLOCKS_PER_WRITE
			//sd_mmc_wait_end_of_write_blocks(false);
			ioport_set_pin_level(LED_PIN, 0);
			ioport_set_pin_level(LED_ENT_PIN, 0);
			
			while(1)
			{}
		}
//		startRecording = 1;
		testPoint = 0;				
	}
	#endif	// MSD
	
	#ifdef WXB
	// ========== Stream Data from Imaging Sensor to SD Card ========= //
	imagingSensorLoadHeader();
		
	if (ledValue >= PWM_PERIOD_VALUE)
	ledValue = 0;
	pwm_channel_update_duty(PWM0, &g_pwm_channel_led, ledValue);
	
	imagingSensorSetup(); //sets interrupts, configures IO pins for DMA CMOS sensor

	tick_start = time_tick_get();
	while (time_tick_calc_delay(tick_start, time_tick_get()) < 5000)
	{}
			
// 	uint32_t curBlock = STARTING_BLOCK;
// 	uint32_t writeLineCount = 0;
// 	uint32_t writeCount = 0;
		
	tick_start = time_tick_get();
		
	startRecording = 1;
	ioport_set_pin_level(TRIGGER0_PIN, 1);	// Starts acquisition of imaging sensor
	ioport_set_pin_level(LED_ENT_PIN, 1);	// Enable PWM LED Control Driver
	ioport_set_pin_level(LED_PIN, 1);
	
	Wired_Expansion_Board_Init();
	BitBang_Write_WXB();
	#endif	//WXB
}