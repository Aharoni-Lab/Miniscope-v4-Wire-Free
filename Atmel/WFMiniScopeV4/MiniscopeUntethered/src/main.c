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
#include "definitions.h"
#include "initiate.h"
#include "PYTHON480.h"
#include "sdImaging.h"
#include "time_tick.h"


/************************************************************************/
/*                        VARIABLE DEFINITIONS                          */
/************************************************************************/

volatile uint32_t time_ms;
volatile uint32_t tick_start;
// #define F_CPU 1000000UL
// #define I2C_ADDR 0x10

// Wired V4 uses I2C to directly communicate to Python480, and the MCU listens in.



/************************************************************************/
/*                           LOCAL FUNCTIONS                            */
/************************************************************************/

// Sets up initial register values in the PYTHON 480
void PYTHON480_Init()
{
	Enable_Clock_Management1();
	delay_ms(10);			// Small pause here for things to stabilize.
	Enable_Clock_Management2();
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
	
	//	if (LEDNum & 0x01)
	//	{
	//		LED_ENT_PORT |= (1 << LED_ENT_PIN);		// = 0 | 2^(LED_ENT1_PIN)
	//	}
	
	//	if (LEDNum & 0x02)
	//	{
	//		LED_ENT_PORT |= (1 << LED_ENT2_PIN);
	//  }
}

// Excitation LED power off
void Disable_Excit_LED()
{
	ioport_set_pin_level(LED_ENT_PIN, 0);

	//	if (LEDNum & 0x01)
	//	{
	//		LED_ENT_PORT &= ~(1 << LED_ENT_PIN);		// 0 & ~(1 << 0) = whatever it is, it's 0
	//	}
	
	//	if (LEDNum & 0x02)
	//	{
	//		LED_ENT_PORT &= ~(1 << LED_ENT2_PIN);
	//	}
}

void SD_Card_Write_Test()
{
	Fill_Buffer();			// Fills imageBuffer location with 0x11223344 a bunch of times
	
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
	

	while (1) 		//  Wait For Another Frame?
	{
		testPoint++;
		testPoint++;
		delay_ms(1000);
	}
}



/************************************************************************/
/*                            MAIN FUNCTION                             */
/************************************************************************/

int main(void)
{
	// ========== Variable Definitions ========== //
	uint32_t writeNum = 0;
	uint32_t writeFrameNum = 0;
	uint32_t WXB = 0;				// Wired Expansion Board
	uint32_t MSD = 0;				// Micro SD Card


	// ========== Interrupt Managements ========== //
	WDT->WDT_MR = WDT_MR_WDDIS;		//  //Disables Watch Dog Timer
	irq_initialize_vectors();		// IRQ: Interrupt Request Line
	cpu_irq_enable();

	
	// ========== Microcontroller Initiation ========== //
	sysclk_init();
	board_init();		
	ioport_init();					// Turns on all peripheral clocks. Could remove this to save power. This is redundant, so maybe get rid of it later.
									

	// ========== Clock Initiation ========== //
	Enable_Source_Clock();			// Turn on SCK1 from MCU to drive CMOS sensor	
	time_tick_init();				// Initialization for 1 ms time clock
//	PWM_Init();						// This is for older MiniScopes. Get the codes for the I2C communication to potentiometer from V4 codes 


	// ========== Setup Microcontroller for PYTHON480 ========== //
	// Power on the peripheral clock for each port
	pmc_enable_periph_clk(ID_PIOA);
	pmc_enable_periph_clk(ID_PIOB);
	pmc_enable_periph_clk(ID_PIOD);
	
	// Enable imaging sensor control pins (Status LED off, Excitation LED on, Reset off, Trigger off, Monitor off, Begin SPI, Begin I2C)
	#ifdef NOIP1SN0480A
		PYTHON480_Pin_Setup();
		
		// Python480 uses SPI, and lens & LED use I2C
		SPI_BitBang_init();
		TWIHS_init();
	#endif
	
	
	// ========== Power Up PYTHON480 ========== //
	PYTHON480_Init();
	
	// Check SPI Communication: Read the Python480 ID using the SPI connection
	uint16_t Python_ID;
	Python_ID = SPI_Read(0x0008);
	if (Python_ID == 0x5004)
	{
		ioport_toggle_pin_level(LED_PIN);
	}
	
	
	// ========== Micro SD Card Initialization ========== //
	sd_mmc_init();
	
	// Micro SD card slot connection check
	uint32_t SD_Check;
	SD_Check = sd_mmc_check(SD_SLOT_NB);
	while (SD_Check != SD_MMC_OK) 
	{
		ioport_toggle_pin_level(LED_PIN);					// while the SD connection is NOT okay.. wait
		delay_ms(100);										// delete later when expansion PCB
		SD_Check = sd_mmc_check(SD_SLOT_NB);
	}																
		
	
	// ========== Connection Type Check (Micro SD Card vs. Wired Expansion Board) ========== //
	if (sd_mmc_get_type(SD_SLOT_NB) == (CARD_TYPE_SD|CARD_TYPE_HC)) // Bitwise OR --> 9 = 8 + 1
	{							
		ioport_set_pin_level(LED_PIN, 1);					// If SDHC, turn on status LED
		WXB = 0;											// set WXB = 0 and SD = 1. Go to: Micro SD Card Data Transfer.
		MSD = 1;
	}
	
	else
	{
		ioport_set_pin_level(LED_PIN, 0);					// if not SDHC, turn off status LED
		WXB = 1;											// set WXB = 1 and SD = 0. Go to: Wired Expansion PCB Data Transfer.
		MSD = 0;
	}
	
	
	// ========== Micro SD Card Data Transfer ========== //
	if (MSD == 1 && WXB == 0)
	{
		uint32_t sdCapacity = sd_mmc_get_capacity(SD_SLOT_NB);		// Get the SD card capacity in KB
	
		delay_ms(5000);												// Wait for things to stabilize

	
		// ========== SD Card Write Test ========== //
		// SD_Card_Write_Test();
		
		
		// ========== Stream Data from Imaging Sensor to SD Card ========= //
		// This is where MCU begins accepting data/sending it to micro SD
		imagingSensorLoadHeader();			// 1. Take in settings from SD card
		
		
		if (ledValue >= PWM_PERIOD_VALUE)	// 2. Check if the excit. LED value is acceptable --> This is done I2C, so check V4 algorithm
		{
			ledValue = 0;
		}
		pwm_channel_update_duty(PWM0, &g_pwm_channel_led, ledValue);	// 3. Set the excit. LED brightness

		imagingSensorSetup();	// 4. Sets interrupts, configures IO pins for DMA CMOS sensor

		// imagingSensorConfigure();	// 5. Configure the image sensor through I2C --> PYTHON480 has been initialized earlier in the code
		Enable_Subsample();				// 5. For PYTHON480, enable subsampling is the sole config. for now
		
		delay_ms(5000);	// 6. Wait 5 seconds for stabilization
		
		// 7. Set up the SD card space to begin writing frames
		if (SD_MMC_OK != sd_mmc_init_write_blocks(SD_SLOT_NB, STARTING_BLOCK, 50 * NB_BLOCKS_PER_FRAME))		// Why 50 times?
		{
			ioport_toggle_pin_level(LED_PIN);
			return;
		}
		// sd_mmc_init_write_blocks(SD_SLOT_NB, STARTING_BLOCK, 50 * NB_BLOCKS_PER_FRAME);
		
		uint32_t curBlock = STARTING_BLOCK;		// Current SD card block - updates after each 50 frames
		uint32_t writeLineCount = 0;
		uint32_t writeCount = 0;
		
		tick_start = time_tick_get();			// Initial time to compare frame times against
		startRecording = 1;						// About to begin recording
		
		// 8. Power up the imaging sensor, excitation LED, and status LED
		ioport_set_pin_level(TRIGGER0_PIN, 1);	// Starts acquisition of image
		ioport_set_pin_level(LED_ENT_PIN, 1);	// Enable excitation LED
		ioport_set_pin_level(LED_PIN, 1);		// TUrn on the status LED
		
		// ** Now data is streaming out from the imaging sensor and SD card is ready to accept data. **//
		while (1)
		{
			if (frameNumber > writeFrameNum)		// If there are more frames to write than the current frame		// They're both zero...what's going on? --> Try reconnecting the imaging sensor board
			{
				#ifdef NOIP1SN0480A					// 9. Write the current frame to one of the buffers
				switch (writeFrameNum % 3)			// Have three sets of buffer, each for rotating 3 frames
				{
					case (0):
						imageBuffer0[buffSize - 2] = time_tick_calc_delay(tick_start, time_tick_get());		// Record the frame time at the end of the buffer0
						sd_mmc_start_write_blocks(&imageBuffer0[0], NB_BLOCKS_PER_WRITE);					// Write the frame at buffer0
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

				if (SD_MMC_OK != sd_mmc_wait_end_of_write_blocks(false))		// 10. Don't stop writing on SD - more frames coming
				{
					ioport_toggle_pin_level(LED_PIN);
					return;
				}
				// sd_mmc_wait_end_of_write_blocks(false);
				
				writeFrameNum++;												// 11. (a) Increase the current frame number
				sdImageWriteFrameNum = writeFrameNum;							// 11. (b) Increase the number of frames written in SD card
				
				#ifdef NOIP1SN0480A
					//if (frameNumber > sdImageWriteFrameNum + 1)
					// {
					startRecording = 1;											// 12. Continue recording (probably an unnecessary line)
					// }
				#endif
				
				if (writeFrameNum % 50 == 0)									// 13. After writing 50 frames, update the current SD card memory block and prepare the following 50 frame space.
				{
					curBlock += 50*NB_BLOCKS_PER_FRAME;
					sd_mmc_init_write_blocks(SD_SLOT_NB, curBlock, 50 * NB_BLOCKS_PER_FRAME);
				}

			}

			// Writing frame as it is being acquired
			// if ((frameNumber == writeFrameNum) && ((lineCount * IMAGE_HEIGHT) > ((writeNum + 1) * NB_BLOCKS_PER_WRITE * 512)))
			// {
			// sd_mmc_start_write_blocks(&imageBuffer[writeNum * NB_BLOCKS_PER_WRITE * 128], NB_BLOCKS_PER_WRITE);	// NB_BLOCKS_PER_WRITE
			// sd_mmc_wait_end_of_write_blocks(false);
			// writeNum++;
			// }
			
			// Writing frame after it has been acquired
			// if ((frameNumber > writeFrameNum) && (writeNum < 4))
			// {
			// sd_mmc_start_write_blocks(&imageBuffer[writeNum * NB_BLOCKS_PER_WRITE * 128], NB_BLOCKS_PER_WRITE);	// NB_BLOCKS_PER_WRITE
			// sd_mmc_wait_end_of_write_blocks(false);
			// writeNum++;
			// }
			
			// Writing last block of frame
			// if ((frameNumber > writeFrameNum) && (writeNum==4))
			// {
			// imageBuffer[buffSize-2] = time_tick_calc_delay(tick_start, time_tick_get());
			// sd_mmc_start_write_blocks(&imageBuffer[writeNum * NB_BLOCKS_PER_WRITE * 128], NB_BLOCKS_PER_WRITE);	// NB_BLOCKS_PER_WRITE
			// sd_mmc_wait_end_of_write_blocks(false);
			// writeFrameNum++;
			// startRecording = 1;
			// if (writeFrameNum % 50 == 0)
			// {
			// curBlock+= 50 * NB_BLOCKS_PER_FRAME;
			// sd_mmc_init_write_blocks(SD_SLOT_NB, curBlock, 50 * NB_BLOCKS_PER_FRAME);
			// }
			// writeNum = 0;
			//}

			
			// test[(frameNumber - 1) * 4]		= imageBuffer[0];
			// test[(frameNumber - 1) * 4 + 1]	= imageBuffer[1];
			// test[(frameNumber - 1) * 4 + 2]	= imageBuffer[2];
			// test[(frameNumber - 1) * 4 + 3]	= imageBuffer[3];

			// for (writeNum = 0; writeNum < 5; ++writeNum)
			// {
			// sd_mmc_start_write_blocks(&imageBuffer[writeNum * NB_BLOCKS_PER_WRITE * 128], NB_BLOCKS_PER_WRITE);	// NB_BLOCKS_PER_WRITE
			// sd_mmc_wait_end_of_write_blocks(false);
			// }
			// ioport_toggle_pin_level(LED_PIN);
			// ioport_toggle_pin_level(ENT_PIN);

			// valueLED = (valueLED + 400) & 0x0FFF;	// higher value less bright
			// DACC_updateOutput(valueLED , 1);
			
			// End at number of frames
			// if (frameNumber >= numFramesToRecord)
			// {
			if (time_tick_calc_delay(tick_start, time_tick_get()) >= numFramesToRecord * 1000)		// After recording for more than number-of-frames-to-record seconds, turn the status and excitation LEDs off and wait
			{
				// sd_mmc_init_write_blocks(SD_SLOT_NB, STARTING_BLOCK - 1, 1);
				// sd_mmc_start_write_blocks(&test[0], 1);	// NB_BLOCKS_PER_WRITE
				// sd_mmc_wait_end_of_write_blocks(false);
				ioport_set_pin_level(LED_PIN, 0);
				ioport_set_pin_level(LED_ENT_PIN, 0);
				
				while (1)
				{}
			}
			testPoint = 0;					// Reset the testPoint after each frame
		}
	}


	// ========== Wired Expansion Board Data Transfer ========== //
	if (MSD == 0 && WXB == 1)
	{
		// Should I turn off sd_mmc_init?
		
		pmc_enable_periph_clk(ID_PIOA);						// Already initiated before, but check again

		// Define pins and input/output functions
		ioport_set_pin_dir(SD_CLK, IOPORT_DIR_OUTPUT);
		ioport_set_pin_dir(SD_PIN_1, IOPORT_DIR_OUTPUT);
		ioport_set_pin_dir(SD_PIN_2, IOPORT_DIR_OUTPUT);
		ioport_set_pin_dir(SD_PIN_3, IOPORT_DIR_OUTPUT);
		ioport_set_pin_dir(SD_PIN_4, IOPORT_DIR_OUTPUT);
		ioport_set_pin_dir(SD_CONFIG, IOPORT_DIR_INPUT);
		
		// clock up
		// {
			// clock down
			// send 4 bits of data
			// wait 10 us
			// clock up
			// clock down
			// send 4 bits of data
			// wait 10 us
			// clock up
			// clock down
			// send 4 bits of data
			// wait 10 us
			// and so on
		// }
		// refer to the algorithm from Wired V4
	}
	
	return 0;
}
