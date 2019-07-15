/*
 *  sdImaging.h
 *
 *  Created: 5/11/2016 9:02:14 PM
 *  Author: Daniel Aharoni
 *	Edits: Raymond Chang
 */ 

 /* Notes:
	Should set reset_n to 1 then SPI configuration then trigger to 1 to start acquisition.
 */

#ifndef SDIMAGING_H_
#define SDIMAGING_H_

/************************************************************************/
/*                             DEFINITIONS                              */
/************************************************************************/

// ========== IMAGING SENSORS ========== //
// Which CMOS imaging sensor are we using. Defined in conf_clock.h and sdImaging.h
// #define EV76C454_SUBSAMP
#define NOIP1SN0480A



// ========== IMAGING SENSOR SPECS ========== //
#ifdef NOIP1SN0480A		// Python480
	#define IMAGING_SENSOR_ADR		0x00				// I2C stuff. Code this to SPI.
	#define D_SIZE					2					// data size is 2?
	#define ALWYS					0
	#define HALFS					0
	#define FRSTS					0
	
	#define PIXELS_PER_WORD			1 << D_SIZE			// 1 * 2^D_SIZE = 4
	#define FRAME_RATE				20
	#define IMAGE_WIDTH				800					// What does this comment mean? -->> //Full sensor is 752 //Will be subsampled by 2x
	#define IMAGE_HEIGHT			600					// same deal -->> // Will be subsampled by 2x
	#define IMAGE_SUBSAMPLE			2					// This possibly will end up being 2x binning
	#define NUM_PIXELS				(IMAGE_HEIGHT * IMAGE_WIDTH) / (IMAGE_SUBSAMPLE * IMAGE_SUBSAMPLE)	// Currently needs to be a multiple of PIXELS_PER_WORD and SDMMC_BLOCK_SIZE
	#define FRAME_FOOTER_LENGTH		0					// Last 32 bits of footer is frame number. The rest is used to fill up sdCard multi block write. Has units of WORDS
	#define NUM_PIXEL_WORDS			(NUM_PIXELS / ((uint32_t)PIXELS_PER_WORD))

	#define VSYNC_MASK				PIO_PA14X1_PIODCEN1 // VSync pin
	#define VSYNC_ID				PIO_PA14_IDX

	#define HSYNC_MASK				PIO_PA21X1_PIODCEN2 // HSync pin
	#define HSYNC_ID				PIO_PA21_IDX
#endif /*NOIP1SN0480A*/

#ifdef  EV76C454_SUBSAMP
	#define IMAGING_SENSOR_ADR			0x18	// A0 A1 = 0, 0x18 is the 7 bit address
	// #define AUTO_GAIN_EXPOSURE_ADR	0xAF	// Bit 0 is for Exposure | bit 1 is for Gain
	// #define SHUTTER_WIDTH_ADR		0x0B	// Default = 480

	// #define COLUMN_START_ADR			0x01	// Default = 1
	// #define ROW_START_ADR			0x02	// Default = 4
	// #define WINDOW_HEIGHT_ADR		0x03	// Default = 480
	// #define WINDOW_WIDTH_ADR			0x04	// Default = 752

	// #define HORZ_BLANKING_ADR		0x05	// Default = 94
	// #define VERT_BLANKING_ADR		0x06	// Default = 45
	// #define NOISE_CORRECTION_ADR		0x70	// Bit 5 enables noise correction

	#define D_SIZE					2
	#define ALWYS					0
	#define HALFS					0
	#define FRSTS					0

	#define PIXELS_PER_WORD			1 << D_SIZE
	#define FRAME_RATE				20
	#define IMAGE_WIDTH				640		// Will be sub-sampled by 2x
	#define IMAGE_HEIGHT			640		// Will be sub-sampled by 2x
	#define IMAGE_SUBSAMPLE			2
	#define NUM_PIXELS				(IMAGE_HEIGHT * IMAGE_WIDTH) / (IMAGE_SUBSAMPLE * IMAGE_SUBSAMPLE)	// Currently needs to be a multiple of PIXELS_PER_WORD and SDMMC_BLOCK_SIZE
	#define FRAME_FOOTER_LENGTH		0											// Last 32bit of footer is frame number. The rest is used to fill up sdCard multi block write. Has units of WORDS
	#define NUM_PIXEL_WORDS			(NUM_PIXELS / ((uint32_t)PIXELS_PER_WORD))

	#define VSYNC_MASK				PIO_PA14X1_PIODCEN1		// VSync pin
	#define VSYNC_ID				PIO_PA14_IDX

	#define HSYNC_MASK				PIO_PA21X1_PIODCEN2		// HSync pin
	#define HSYNC_ID				PIO_PA21_IDX
#endif /*EV76C454_SUBSAMP*/



// ========== SD CARD SPECS ========== //
#ifdef NOIP1SN0480A
	#define SD_SLOT_NB					0
	#define SDMMC_BLOCK_SIZE			512		// Number of bytes in a single block (sector)
	#define NB_BLOCKS_PER_WRITE			165		// Number of blocks to write in each SDMMC write instance
	#define NB_LINES_PER_WRITE			(NB_BLOCKS_PER_WRITE * SDMMC_BLOCK_SIZE) / (IMAGE_HEIGHT / IMAGE_SUBSAMPLE)
	#define NB_BLOCKS_PER_FRAME			NUM_PIXELS / SDMMC_BLOCK_SIZE	// 600 * 800 / 512 = 937.5 --> 937
	#define STARTING_BLOCK				1024
#endif

#ifdef EV76C454_SUBSAMP
	#define SD_SLOT_NB					0
	#define SDMMC_BLOCK_SIZE			512		// Number of bytes in a single block (sector)
	#define NB_BLOCKS_PER_WRITE			200		// Number of blocks to write in each SDMMC write instance
	#define NB_LINES_PER_WRITE			(NB_BLOCKS_PER_WRITE * SDMMC_BLOCK_SIZE) / (IMAGE_HEIGHT / IMAGE_SUBSAMPLE)
	#define NB_BLOCKS_PER_FRAME			NUM_PIXELS / SDMMC_BLOCK_SIZE
	#define STARTING_BLOCK				1024
#endif



// ========== HEADER ========== //
#define START_SECTOR				STARTING_BLOCK

// #define WRITE_KEY0				0x0D7CBA17
// #define WRITE_KEY1				0x0D7CBA17
// #define WRITE_KEY2				0x0D7CBA17
// #define WRITE_KEY3				0x0D7CBA17

#define HEADER_SECTOR				START_SECTOR - 1
// #define HEADER_LENGTH			512
#define HEADER_GAIN_POS				4
#define HEADER_LED_POS				5
#define HEADER_NUM_FRAMES_POS		6



// ========== DMA ========== //
#define IMAGING_SENSOR_XDMAC_CH		1



/************************************************************************/
/*                          Global Variables                            */
/************************************************************************/

extern volatile uint32_t xferDMAComplete;		// Changed in XDMAC_Handler
 
volatile uint32_t nbErrors;						// Number or errors detected
extern const uint32_t buffSize;


COMPILER_ALIGNED(8)


#ifdef NOIP1SN0480A
	uint32_t imageBuffer0[NUM_PIXEL_WORDS + FRAME_FOOTER_LENGTH];	// static --> all initialize to zero and refuse to change.. so delete "static"
	uint32_t imageBuffer1[NUM_PIXEL_WORDS + FRAME_FOOTER_LENGTH];
	uint32_t imageBuffer2[NUM_PIXEL_WORDS + FRAME_FOOTER_LENGTH];
#endif

#ifdef EV76C454_SUBSAMP
	static uint32_t imageBuffer0[NUM_PIXEL_WORDS + FRAME_FOOTER_LENGTH];
	static uint32_t imageBuffer1[NUM_PIXEL_WORDS + FRAME_FOOTER_LENGTH];
	static uint32_t imageBuffer2[NUM_PIXEL_WORDS + FRAME_FOOTER_LENGTH];			// static --> all initialize to zero (But this doesn't work in other compilers..)
#endif


extern volatile uint32_t numWritesPerFrame;

extern volatile uint32_t ledValue;
extern volatile uint32_t numFramesToRecord;

extern volatile uint8_t	captureEnabled;
extern volatile uint8_t startRecording;
extern volatile uint32_t frameNumber;
extern volatile uint32_t overflowCount;
extern volatile uint32_t pcISR;
extern volatile uint32_t lineCount;

extern volatile uint32_t testPoint;

extern volatile uint32_t sdImageWriteFrameNum;



/************************************************************************/
/*                              Functions                               */
/************************************************************************/

// ========== Interrupt Handlers: Overwrites the Stock Functions ========== //
/**
	PIOA_Handler: Interruption handler for the peripherals in IO Port A (also in pio_handler.h)
*/
void PIOA_Handler(void);

/**
	PIOA_Handler: Interruption handler for DMA (also in same70n21.h)
*/
void XDMAC_Handler(void);



// ========== Set Up Clock Speed for CMOS Sensor ========== //
/**
	Enable_Source_Clock: Power on/Calibrate SCK1 from MCU to drive CMOS sensor	
*/
void Enable_Source_Clock();



// ========== Load In Custom Settings ========== //
/**
	imagingSensorLoadHeader: Read in the imaging sensor settings from the micro SD card
*/
void imagingSensorLoadHeader();



// ========== Set up the Microcontroller to Handle Imaging Sensor ========== //
/**
	imagingSensorSetup: Set up the port, imaging sensor, vertical/horizontal interrupts. Initialize the parameters and Direct Memory Access (DMA)
*/
void imagingSensorSetup();

/**
	imagingSensorParamInit: Set up the data size of each pixel (byte for Python480), And whether always accept data or only half (even/odd) of them. 
*/
void imagingSensorParamInit();

/**
	imagingSensorDMAInit: Initialize the Direct Memory Access (DMA) to receive data from the imaging sensor
*/
void imagingSensorDMAInit();



// ========== Imaging Sensor Interrupts ========== //
/**
	imagingSensorItInit: 
*/
void imagingSensorItInit();

/**
	imageSensorVSyncItInit: Sets up VSync interrupt to detect end of frame
*/
void imageSensorVSyncItInit();

/**
	imageSensorHSyncItInit: Set up HSync for row counter
*/
void imageSensorHSyncItInit();



// ========== Begin Direct Memory Access ========== //
/**
	checkVSync:
*/
void checkVSync();

/**
	imagingSensorStartDMA:
*/
void imagingSensorStartDMA();



// ========== Parallel Capture Enable/Disable ========== //
/**
	Enable_Imaging_Sensor_Capture: Enables the parallel capture mode
*/
void Enable_Imaging_Sensor_Capture();

/**
	Disable_Imaging_Sensor_Capture: Disables the parallel capture mode
*/
void Disable_Imaging_Sensor_Capture();



// ========== I2C Communications with E-wetting Lens and Excitation LED (Move to another file) ========== //
/**
	EMPTY??
	Imaging_Sensor_TWI_Init: Initiate I2C for Imaging Sensor --> Change this to lens & excit. LED potentiometer
*/
void Imaging_Sensor_TWI_Init();



// ========== Micro SD Card Test ========== //
/**
	Fill_Buffer: fills the buffer with a repeating hexadecimal number
*/
void Fill_Buffer();



// ========== No Longer Used ========== //
extern volatile uint32_t gain;

extern volatile uint8_t i2cbuf[2];
extern volatile uint32_t blockNum;
extern volatile uint32_t SDWriteNum;
extern volatile uint32_t pixelWordCounter;

twihs_packet_t packetCMOS;


/**
	imaging_Sensor_Configure_EV76C541:
*/
void imaging_Sensor_Configure_EV76C541();

/**
	imaging_Sensor_Configure:
*/
void imaging_Sensor_Configure();




#endif /* SDIMAGING_H_ */