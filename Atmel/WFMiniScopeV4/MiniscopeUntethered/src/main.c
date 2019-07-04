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



/************************************************************************/
/*                           LOCAL FUNCTIONS                            */
/************************************************************************/
// #define F_CPU 1000000UL
// #define I2C_ADDR 0x10

// V4 uses I2C to directly communicate to Python480, and the MCU listens in.

// Excitation LED power on
void enableLED() 
{
//	if (LEDNum&0x01)
//	LED_ENT_PORT |= (1 << LED_ENT_PIN);		// = 0 | 2^(LED_ENT1_PIN)
	ioport_set_pin_level(LED_ENT_PIN, 1);
//	if (LEDNum&0x02)
//	LED_ENT_PORT |= (1<<LED_ENT2_PIN);
}

// Excitation LED power off
void disableLED()
{
//	if (LEDNum&0x01)
//	LED_ENT_PORT &= ~(1 << LED_ENT_PIN);		// 0 & ~(1 << 0) = whatever it is, it's 0
	ioport_set_pin_level(LED_ENT_PIN, 0);
//	if (LEDNum&0x02)
//	LED_ENT_PORT &= ~(1<<LED_ENT2_PIN);
}

// Sets up initial register values in the PYTHON 480
void init_PYTHON480()
{
	EnableClockMngmnt1();
	delay_ms(10);			// Maybe a small pause here for things to stabilize
	EnableClockMngmnt2();
	RequiredUploads();
	SoftPowerUp();

	//EnableSeq(); // Sequencer is enabled already in Required Uploads...
}

void initBoard()
{
	// Setup SPI
	/* This MCU has an on-board SPI module
	SPI_DDR |= (1 << MOSI) | (1 << SCK) | (1 << SS);//|(1<<RTS);
	SPI_SS_DDR |= (1 << SS);
	SPI_DDR &= ~(1 << MISO);
	
	SPI_SS_PORT |= (1 << SS); //Pull SS high
	SPI_PORT &= ~(1 << SCK);
	*/
	
	// Setup status LED
	ioport_set_pin_dir(LED_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LED_PIN, 0);
	
	// Setup excitation LED
	ioport_set_pin_dir(LED_ENT_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LED_ENT_PIN, 1);
	
	// Setup pins connecting to PYTHON480
	ioport_set_pin_dir(RESET_N_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(RESET_N_PIN, 0);
}


/************************************************************************/
/*                            MAIN FUNCTION                             */
/************************************************************************/

int main (void)
{
	// ========== Variable Definitions ========== //
	uint32_t writeNum = 0;
	uint32_t writeFrameNum = 0;
	uint32_t PCB;
	uint32_t SD;


	// ========== Interrupt Managements ========== //
	irq_initialize_vectors();		// IRQ: Interrupt Request Line
	cpu_irq_enable();

	
	// ========== MCU Initiations ========== //
	sysclk_init();
	board_init();		
	ioport_init();					// turns on all peripheral clocks. could remove this to save power
									// this is redundant, so maybe get rid of it after.

	// ========== CMOS Sensor Connection ========== //
	enableSourceClk();				// Turns on SCK1 from MCU to drive CMOS sensor	
	time_tick_init();
//	PWM_Init();						// This is for older MiniScopes
	
	#ifdef NOIP1SN0480A
		SPI_BitBang_init();
		TWIHS_init();
	#else
//		Python480 uses SPI, and lens & LED use I2C
	#endif
	
	tick_start = time_tick_get();
	time_ms = time_tick_calc_delay(tick_start, time_tick_get());		// 1000Hz...?


	// ========== Power On Status LED ========== //
	pmc_enable_periph_clk(ID_PIOD);
	ioport_set_pin_dir(LED_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LED_PIN, 1);
	
	
	// ========== PYTHON480 Connection ========== //
	// BEGIN PERIPHERAL CLOCK
	// Enable control of sensor control pins (Reset on, trigger off, Monitor off)
	pmc_enable_periph_clk(ID_PIOA);
	pmc_enable_periph_clk(ID_PIOB);


	// RESET PIN
	// goes off and on
	ioport_set_pin_dir(RESET_N_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(RESET_N_PIN, 0);					// not sure if this can stay high the whole time.

	tick_start = time_tick_get();
	delay_ms(100);
	// while (time_tick_calc_delay(tick_start, time_tick_get()) < 100) {}
	ioport_set_pin_level(RESET_N_PIN, 1);
	
	
	// TRIGGER PIN
	ioport_set_pin_dir(TRIGGER0_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(TRIGGER0_PIN, 0);					// Should be high for CMOS to acquire or can be left 0 and controlled by TWI (Find address (= 0x0F)?)
	
	
	// MONITOR PIN
	ioport_set_pin_dir(MONITOR0_PIN, IOPORT_DIR_INPUT);
	ioport_set_pin_level(MONITOR0_PIN, 0);
	
	
	// STANDBY PIN
	/* No standby in Python480 */

	// ========== Power Up Python480 ========== //
	init_PYTHON480();
	
	// Check SPI Communication: Read the Python480 ID using the SPI connection
	uint16_t PythonID;
	PythonID = SPI_Read(0x0000);
	if (PythonID == 0x5004)
	{
		ioport_toggle_pin_level(LED_PIN);
	}
	
	
	// ========== Power Up the Excitation LED ========== //
	enableLED();
	
	
	// ========== SD Card ========== //
	sd_mmc_init();
	
	// Check connection
	uint32_t sdCheck;
	sdCheck = sd_mmc_check(SD_SLOT_NB);
	while (sdCheck != SD_MMC_OK) 
	{
		ioport_toggle_pin_level(LED_PIN);					// while the SD connection is NOT okay.. wait
		delay_ms(100);										// delete later when expansion PCB
		sdCheck = sd_mmc_check(SD_SLOT_NB);
	}																
		
	// Check SD Card Type
	if (sd_mmc_get_type(SD_SLOT_NB) == (CARD_TYPE_SD|CARD_TYPE_HC)) // Bitwise OR --> 9 = 8 + 1
	{							
		ioport_set_pin_level(LED_PIN, 1);					// If SDHC, turn LED on
		PCB = 0;											// set MCU = 0 and SD = 1. Do the SD card thing.
		SD = 1;
	}
	else
	{
		ioport_set_pin_level(LED_PIN, 0);					// if not SDHC, turn off LED
		PCB = 1;											// set MCU = 1 and SD = 0. Do the MCU thing.
		SD = 0;
	}
	
	// If SD card...
	if (SD == 1 && PCB == 0)
	{
		// Get the SD card capacity in KB
		uint32_t sdCapacity = sd_mmc_get_capacity(SD_SLOT_NB);
	
		// Wait for things to stabilize?
		tick_start = time_tick_get();
		delay_ms(5000);
		// while (time_tick_calc_delay(tick_start, time_tick_get()) < 5000) {}
		
		// This is a problem. Maybe turn off the LED
		if (sd_mmc_is_write_protected(SD_SLOT_NB) == true)
		{
			ioport_toggle_pin_level(LED_PIN);
		}
	
		// ========== SD Card Write Test ========== //
		// fills imageBuffer location with 0x11003344 a bunch of times
		fillBuffer();
	
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
			if (SD_MMC_OK != sd_mmc_start_write_blocks(imageBuffer, NB_BLOCKS_PER_FRAME))
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
	
	
	
		// ========== Wait For Another Frame? ========== //
		while (1) 
		{
			testPoint++;
			testPoint++;
			delay_ms(1000);
			// while (time_tick_calc_delay(tick_start, time_tick_get()) < 1000) {}
		}
	}

	// If PlugIn PCB...
	if (SD == 0 && PCB == 1)
	{
		// Should I turn off sd_mmc_init?
		// sd_mmc_init something something...
		
		// Define pins and input/output functions
		ioport_set_pin_dir(SD_CLK, IOPORT_DIR_OUTPUT);
		ioport_set_pin_dir(SD_PIN_1, IOPORT_DIR_OUTPUT);
		ioport_set_pin_dir(SD_PIN_2, IOPORT_DIR_OUTPUT);
		ioport_set_pin_dir(SD_PIN_3, IOPORT_DIR_OUTPUT);
		ioport_set_pin_dir(SD_PIN_4, IOPORT_DIR_OUTPUT);
		ioport_set_pin_dir(SD_CONFIG, IOPORT_DIR_INPUT);
		
		pmc_enable_periph_clk(ID_PIOA);						// Already initiated before, so check again
		// clock up
		// send 4 bits of data
		// clock down
		// send 4 bits of data
		// clock up
		// send 4 bits of data
		// and so on
	}
	
	return 0;
}
