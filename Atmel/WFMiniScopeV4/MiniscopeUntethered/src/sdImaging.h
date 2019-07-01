/*
 * sdImaging.h
 *
 * Created: 5/11/2016 9:02:14 PM
 *  Author: Daniel Aharoni
 */ 

 /* Notes for EV76C541
 Internal osc is not divided
 CLK_CTRL is from CLK_ADC
 CLK_ADC is from CLK_REF (Default is PLL)
 CLK_CHAIN is from CLK_REF (Default is PLL)
 CLK_CTRL is divided by 4 ???? Reg 0x08
 CLK_CHAIN is divided by 4 ???? Reg 0x08

 Integration time multiplication factor = 8. defined in 0x0A
 Trig is active high, Trig pin is enabled Reg = 0x0B

 should set resetn to 1 then spi configuration then trigger to 1 to start acq
 */

#ifndef SDIMAGING_H_
#define SDIMAGING_H_

/************************************************************************/
/*                             DEFINITIONS                              */
/************************************************************************/



// ========== IMAGING SENSORS ========== //
//Which CMOS imaging sensor are we using. Defined in conf_clock.h and sdImaging.h
//#define MT9V032
//#define EV76C454_SUBSAMP
// #define EV76C454
// #define EV76C541
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
	#define NUM_PIXELS				(IMAGE_HEIGHT * IMAGE_WIDTH)/(IMAGE_SUBSAMPLE * IMAGE_SUBSAMPLE)	// Currently needs to be a multiple of PIXELS_PER_WORD and SDMMC_BLOCK_SIZE
	#define FRAME_FOOTER_LENGTH		0					// Last 32 bits of footer is frame number. The rest is used to fill up sdCard multi block write. Has units of WORDS
	#define NUM_PIXEL_WORDS			(NUM_PIXELS / ((uint32_t)PIXELS_PER_WORD))

	#define VSYNC_MASK				PIO_PA14X1_PIODCEN1 // VSync pin
	#define VSYNC_ID				PIO_PA14_IDX

	#define HSYNC_MASK				PIO_PA21X1_PIODCEN2 // HSync pin
	#define HSYNC_ID				PIO_PA21_IDX
#endif /*NOIP1SN0480A*/


#ifdef  EV76C541		// E2V Jade Sensor
	#define IMAGING_SENSOR_ADR			0x00			// No address since uses SPI
	//#define AUTO_GAIN_EXPOSURE_ADR	0xAF			// bit0 is for Exposure | bit1 is for Gain
	//#define SHUTTER_WIDTH_ADR			0x0B			// Default = 480

	//#define COLUMN_START_ADR			0x01			// Default = 1
	//#define ROW_START_ADR				0x02			// Default = 4
	//#define WINDOW_HEIGHT_ADR			0x03			// Default = 480
	//#define WINDOW_WIDTH_ADR			0x04			// Default = 752

	//#define HORZ_BLANKING_ADR			0x05			// Default = 94
	//#define VERT_BLANKING_ADR			0x06			// Default = 45
	//#define NOISE_CORRECTION_ADR		0x70			// bit 5 enables noise correction

	#define D_SIZE					2
	#define ALWYS					0
	#define HALFS					0
	#define FRSTS					0

	#define PIXELS_PER_WORD			1<<D_SIZE			// 1 * 2^D_SIZE = 4
	#define FRAME_RATE				20
	#define IMAGE_WIDTH				704					// Full sensor is 752 //Will be subsampled by 2x
	#define IMAGE_HEIGHT			480					// Will be subsampled by 2x
	#define IMAGE_SUBSAMPLE			2					// This possibly will end up being 2x binning
	#define NUM_PIXELS				(IMAGE_HEIGHT*IMAGE_WIDTH)/(IMAGE_SUBSAMPLE*IMAGE_SUBSAMPLE) //Currently needs to be a multiple of PIXELS_PER_WORD and SDMMC_BLOCK_SIZE
	#define FRAME_FOOTER_LENGTH		0					// Last 32bit of footer is frame number. The rest is used to fill up sdCard multi block write. Has units of WORDS
	#define NUM_PIXEL_WORDS			(NUM_PIXELS/((uint32_t)PIXELS_PER_WORD))

	#define VSYNC_MASK				PIO_PA14X1_PIODCEN1 // VSync pin
	#define VSYNC_ID				PIO_PA14_IDX

	#define HSYNC_MASK				PIO_PA21X1_PIODCEN2 // HSync pin
	#define HSYNC_ID				PIO_PA21_IDX
#endif /*EV76C541*/

#ifdef  EV76C454
	#define IMAGING_SENSOR_ADR		0x18 //A0 A1 = 0, 0x18 is the 7bit address

	#define D_SIZE					2
	#define ALWYS					0
	#define HALFS					0
	#define FRSTS					0

	#define PIXELS_PER_WORD			1<<D_SIZE
	#define FRAME_RATE				30
	#define IMAGE_WIDTH				480
	#define IMAGE_HEIGHT			752
	#define NUM_PIXELS				(IMAGE_HEIGHT*IMAGE_WIDTH) //Currently needs to be a multiple of PIXELS_PER_WORD and SDMMC_BLOCK_SIZE
	#define FRAME_FOOTER_LENGTH		0 //Last 32bit of footer is frame number. The rest is used to fill up sdCard multi block write. Has units of WORDS
	#define NUM_PIXEL_WORDS			(NUM_PIXELS/((uint32_t)PIXELS_PER_WORD))

	#define VSYNC_MASK				PIO_PA14X1_PIODCEN1 //VSync pin
	#define VSYNC_ID				PIO_PA14_IDX

	#define HSYNC_MASK				PIO_PA21X1_PIODCEN2 //HSync pin
	#define HSYNC_ID				PIO_PA21_IDX
#endif /*EV76C454*/


// ========== SD CARD SPECS ========== //
#ifdef NOIP1SN0480A
	#define SD_SLOT_NB					0
	#define SDMMC_BLOCK_SIZE			512 // Number of bytes in a single block (sector)
	#define NB_BLOCKS_PER_WRITE			165 // Number of blocks to write in each sdmmc write instance
	#define NB_LINES_PER_WRITE			(NB_BLOCKS_PER_WRITE*SDMMC_BLOCK_SIZE)/(IMAGE_HEIGHT/IMAGE_SUBSAMPLE)
	#define NB_BLOCKS_PER_FRAME			NUM_PIXELS / SDMMC_BLOCK_SIZE	// 600*800/512 = 937.5 --> 937
	#define STARTING_BLOCK				1024
#endif

#ifdef EV76C541
	#define SD_SLOT_NB					0
	#define SDMMC_BLOCK_SIZE			512 //Number of bytes in a single block (sector)
	#define NB_BLOCKS_PER_WRITE			165 //Number of blocks to write in each sdmmc write instance
	#define NB_LINES_PER_WRITE			(NB_BLOCKS_PER_WRITE*SDMMC_BLOCK_SIZE)/(IMAGE_HEIGHT/IMAGE_SUBSAMPLE)
	#define NB_BLOCKS_PER_FRAME			NUM_PIXELS/SDMMC_BLOCK_SIZE
	#define STARTING_BLOCK				1024
#endif

#ifdef EV76C454
	#define SD_SLOT_NB					0
	#define SDMMC_BLOCK_SIZE			512 //Number of bytes in a single block (sector)
	#define NB_BLOCKS_PER_WRITE			141 //Number of blocks to write in each sdmmc write instance
	#define NB_LINES_PER_WRITE			(NB_BLOCKS_PER_WRITE*SDMMC_BLOCK_SIZE)/(IMAGE_HEIGHT)
	#define NB_BLOCKS_PER_FRAME			NUM_PIXELS/SDMMC_BLOCK_SIZE
	#define STARTING_BLOCK				1024
#endif


// ========== HEADER ========== //
#define START_SECTOR			STARTING_BLOCK

#define WRITE_KEY0				0x0D7CBA17
#define WRITE_KEY1				0x0D7CBA17
#define WRITE_KEY2				0x0D7CBA17
#define WRITE_KEY3				0x0D7CBA17

#define HEADER_SECTOR			START_SECTOR - 1
#define HEADER_LENGTH			512
#define HEADER_GAIN_POS			4
#define HEADER_LED_POS			5
#define HEADER_NUM_FRAMES_POS	6

// ========== DMA ========== //
#define IMAGING_SENSOR_XDMAC_CH		1
//const uint32_t testVal = 0x00441122;



/************************************************************************/
/*                          Global Variables                            */
/************************************************************************/
extern volatile uint32_t xferDMAComplete;		//changed in XDMAC_Handler
 
volatile uint32_t nbErrors;				// Number or errors detected
extern const uint32_t buffSize;

COMPILER_ALIGNED(8)
/*
#ifdef NOIP1SN0480A
	static uint32_t imageBuffer0[NUM_PIXEL_WORDS+FRAME_FOOTER_LENGTH];	// static --> all initialize to zero (But this doesn't work in other compilers..)
	static uint32_t imageBuffer1[NUM_PIXEL_WORDS+FRAME_FOOTER_LENGTH];
	static uint32_t imageBuffer2[NUM_PIXEL_WORDS+FRAME_FOOTER_LENGTH];
#endif
*/
// ========== Try This ========== //
#ifdef NOIP1SN0480A
	uint32_t imageBuffer[NUM_PIXEL_WORDS+FRAME_FOOTER_LENGTH];
#endif

#ifdef EV76C541
	static uint32_t imageBuffer0[NUM_PIXEL_WORDS+FRAME_FOOTER_LENGTH];	// static --> all initialize to zero (But this doesn't work in other compilers..)
	static uint32_t imageBuffer1[NUM_PIXEL_WORDS+FRAME_FOOTER_LENGTH];
	static uint32_t imageBuffer2[NUM_PIXEL_WORDS+FRAME_FOOTER_LENGTH];
#endif

#ifdef EV76C454
	static uint32_t imageBuffer[NUM_PIXEL_WORDS+FRAME_FOOTER_LENGTH];
#endif


extern volatile uint32_t numWritesPerFrame;

extern volatile uint8_t i2cbuf[2];
extern volatile uint32_t blockNum;
extern volatile uint32_t SDWriteNum;
extern volatile uint8_t captureEnabled;
extern volatile uint8_t startRecording;
extern volatile uint32_t pixelWordCounter;
extern volatile uint32_t frameNumber;
extern volatile uint32_t overflowCount;
extern volatile uint32_t pcISR;
extern volatile uint32_t lineCount;

extern volatile uint32_t gain;
extern volatile uint32_t ledValue;
extern volatile uint32_t numFramesToRecord;

extern volatile uint32_t testPoint;

extern volatile uint32_t sdImageWriteFrameNum;

twihs_packet_t packetCMOS;


/************************************************************************/
/*                              Functions                               */
/************************************************************************/

// ========== IMAGING SENSOR SETUP ========== //
/**
	PIOA_Handler: Handler for the peripherals in IO Port A
*/
void PIOA_Handler(void);

/**
	enableSourceClk: Sets PCK1 as clock output using Main Clocks
*/
void enableSourceClk();

/**
	imagingSensorSetup:
*/
void imagingSensorSetup();

/**
	imagingSensorParamInit:
*/
void imagingSensorParamInit();

/**
	imagingSensorItInit:
*/
void imagingSensorItInit();

/**
	imagingSensorDMAInit:
*/
void imagingSensorDMAInit();

/**
	imagingSensorStartDMA:
*/
void imagingSensorStartDMA();

/**
	imageSensorVSyncItInit: Sets up VSync interrupt to detect end of frame
*/
void imageSensorVSyncItInit();

/**
	imageSensorHSyncItInit: Set up HSync for row counter
*/
void imageSensorHSyncItInit();

/**
	imagingSensorLoadHeader:
*/
void imagingSensorLoadHeader();

/**
	imagingSensorCaptureEnable:
*/
void imagingSensorCaptureEnable();

/**
	imagingSensorCaptureDisable:
*/
void imagingSensorCaptureDisable();

/**
	imagingSensorTWIInit: Initiate I2C for Imaging Sensor --> Change this to lens & excit. LED potentiometer
*/
void imagingSensorTWIInit(); // Nothing here????

/**
	checkVSync:
*/
void checkVSync();



// ========== SD CARD TEST ========== //
/**
	fillBuffer: fills the buffer with a repeating hexadecimal number
*/
void fillBuffer();



// ========== No Longer Used ========== //
/**
	imagingSensorConfigureEV76C541:
*/
void imagingSensorConfigureEV76C541();

/**
	imagingSensorConfigure:
*/
void imagingSensorConfigure();




#endif /* SDIMAGING_H_ */