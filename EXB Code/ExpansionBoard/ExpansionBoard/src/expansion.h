#ifndef EXPANSION_H_
#define EXPANSION_H_


// ========== IMAGE SENSOR ========== //
#define PYTHON480



// ========== IMAGE SENSOR DATA ========== //
#ifdef  PYTHON480
	#define IMAGING_SENSOR_ADR		0x18 //A0 A1 = 0, 0x18 is the 7bit address

	#define D_SIZE					2
	#define ALWYS					0
	#define HALFS					0
	#define FRSTS					0

	#define PIXELS_PER_WORD			1 << D_SIZE		// inside a word (32-bit) how many pixels fit in? --> 4 pixels
	#define FRAME_RATE				20
	#define IMAGE_WIDTH				768 //Will be subsampled by 2x
	#define IMAGE_HEIGHT			592 //Will be subsampled by 2x
	#define IMAGE_SUBSAMPLE			2
	#define NUM_PIXELS				(IMAGE_HEIGHT*IMAGE_WIDTH)/(IMAGE_SUBSAMPLE*IMAGE_SUBSAMPLE) //Currently needs to be a multiple of PIXELS_PER_WORD and SDMMC_BLOCK_SIZE
	#define FRAME_FOOTER_LENGTH		0 //Last 32bit of footer is frame number. The rest is used to fill up sdCard multi block write. Has units of WORDS
	#define NUM_PIXEL_WORDS			(NUM_PIXELS / ((uint32_t)PIXELS_PER_WORD))	// # of words per frame

	#define CLK_SYNC_MASK			PIO_PA14X1_PIODCEN1 // Clock sync pin
	#define CLK_SYNC_ID				PIO_PA14_IDX

//	#define HSYNC_MASK				PIO_PA21X1_PIODCEN2 // HSync pin
//	#define HSYNC_ID				PIO_PA21_IDX
#endif /*NOIPSN10480A*/



// ========== DATA PACKAGE CONFIG ========== //
#ifdef PYTHON480
	#define SD_SLOT_NB					0
	#define SDMMC_BLOCK_SIZE			512		// Number of bytes in a single block (sector)
	#define NB_BLOCKS_PER_WRITE			NUM_PIXELS / SDMMC_BLOCK_SIZE	// Number of blocks to write in each SD/MMC write instance
	#define NB_LINES_PER_WRITE			(NB_BLOCKS_PER_WRITE*SDMMC_BLOCK_SIZE)/(IMAGE_HEIGHT/IMAGE_SUBSAMPLE)	// = IMAGE_WIDTH/IMAGE_SUBSAMPLE
	#define NB_BLOCKS_PER_FRAME			NUM_PIXELS / SDMMC_BLOCK_SIZE
	#define STARTING_BLOCK				1024
#endif

// ========== DMA ========== //
#define IMAGING_SENSOR_XDMAC_CH		1



// ========== GLOBAL VARIABLES ========== //
volatile uint32_t xferDMAComplete = 0; //changed in XDMAC_Handler

volatile uint32_t nbErrors; /** Number or errors detected */
const uint32_t buffSize = NUM_PIXEL_WORDS+FRAME_FOOTER_LENGTH;
COMPILER_ALIGNED(8)

#ifdef PYTHON480
// maybe uint8_t and 4 times the length? (Also in Start_DMA)
    static uint32_t imageBuffer0[NUM_PIXEL_WORDS+FRAME_FOOTER_LENGTH];
    static uint32_t imageBuffer1[NUM_PIXEL_WORDS+FRAME_FOOTER_LENGTH];
	static uint32_t imageBuffer2[NUM_PIXEL_WORDS+FRAME_FOOTER_LENGTH];
#endif

volatile uint32_t numWritesPerFrame = ((NUM_PIXEL_WORDS+FRAME_FOOTER_LENGTH)*4)/(SDMMC_BLOCK_SIZE*NB_BLOCKS_PER_WRITE); //This should be an integer

volatile uint8_t i2cbuf[2];
volatile uint32_t blockNum			= 0;
volatile uint32_t SDWriteNum		= 0;
volatile  uint8_t captureEnabled	= 0;
volatile uint8_t startRecording		= 0;
volatile uint32_t pixelWordCounter	= 0;
volatile uint32_t frameNumber		= 0;
volatile uint32_t overflowCount		= 0;
volatile uint32_t pcISR				= 0;
volatile uint32_t lineCount			= 0;

volatile uint32_t gain				= 1;
volatile uint32_t ledValue			= 0;
volatile uint32_t numFramesToRecord	= 0;

volatile uint32_t testPoint			= 0;

volatile uint32_t sdImageWriteFrameNum = 0;

// twihs_packet_t packetCMOS;



// ========== FUNCTION DECLARATIONS ========== //
void WXB_DMA_Init();
void WXB_Start_DMA();
void Clk_Interrupt_Init(); //Set up HSync for row counter


// ========== FUNCTIONS DEFINITIONS ========== //
/*
void PIOA_Handler(void)
{
	// I need to set up a frame valid "interrupt" here, or something to signal an end of a frame.
	// Something to watch 
	
	pcISR = PIOA->PIO_ISR;
	if (pcISR & CLK_SYNC_MASK)
	{
		Clk_Capture_Disable();
		
		#ifdef PYTHON480
		switch (frameNumber % 3)
		{
			case (0):
			imageBuffer0[buffSize - 1] = frameNumber;
			imageBuffer0[buffSize - 3] = lineCount;
			imageBuffer0[buffSize - 4] = xferDMAComplete; //Overflow flag
			break;
			
			case (1):
			imageBuffer1[buffSize - 1] = frameNumber;
			imageBuffer1[buffSize - 3] = lineCount;
			imageBuffer1[buffSize - 4] = xferDMAComplete; //Overflow flag
			break;
			
			case (2):
			imageBuffer2[buffSize - 1] = frameNumber;
			imageBuffer2[buffSize - 3] = lineCount;
			imageBuffer2[buffSize - 4] = xferDMAComplete; //Overflow flag
			break;
		}
		#endif
		
		lineCount = 0;
		frameNumber++;
		overflowCount = 0;
		xferDMAComplete = 0;
		
		#ifdef PYTHON480 //immediately start recording of next frame
		if (frameNumber <= sdImageWriteFrameNum + 2)
		{
			startRecording = 1;
			captureEnabled = 1;
			WXB_Start_DMA();
			Clk_Capture_Enable();
		}
		#endif
	}
}
*/

void XDMAC_Handler(void)
{
	uint32_t dma_status;

	dma_status = XDMAC->XDMAC_CHID[IMAGING_SENSOR_XDMAC_CH].XDMAC_CIS;

	if (dma_status & XDMAC_CIS_BIS)
	{
		xferDMAComplete = 1;
		++frameNumber;
	}
}



void WXB_DMA_Init()
{
	//Single Block With Single Microblock Transfer
	uint32_t channelStatus = 0;
	/* Initialize and enable DMA controller */
	pmc_enable_periph_clk(ID_XDMAC);

	/*Enable XDMA interrupt */
	NVIC_ClearPendingIRQ(XDMAC_IRQn);
	NVIC_SetPriority(XDMAC_IRQn, 1);
	NVIC_EnableIRQ(XDMAC_IRQn);
}

void WXB_Start_DMA()
{
	uint32_t channelStatus = 0;

	XDMAC->XDMAC_GD =(XDMAC_GD_DI0 << IMAGING_SENSOR_XDMAC_CH); //disables DMA channel

	channelStatus = XDMAC->XDMAC_GS;			// Global status of XDMAC channels. Should make sure IMAGING_SENSOR_XDMAC_CH is available
	XDMAC->XDMAC_CHID[IMAGING_SENSOR_XDMAC_CH].XDMAC_CIS;								 // Clears interrupt status bit
	XDMAC->XDMAC_CHID[IMAGING_SENSOR_XDMAC_CH].XDMAC_CSA = (uint32_t)&(PIOA->PIO_PCRHR); // Source address

	#ifdef PYTHON480
	switch(frameNumber % 3)
	{
		case (0):
		XDMAC->XDMAC_CHID[IMAGING_SENSOR_XDMAC_CH].XDMAC_CDA = (uint32_t)imageBuffer0;	// CDA: Channel Destination Address
		break;
		
		case (1):
		XDMAC->XDMAC_CHID[IMAGING_SENSOR_XDMAC_CH].XDMAC_CDA = (uint32_t)imageBuffer1;
		break;
		
		case(2):
		XDMAC->XDMAC_CHID[IMAGING_SENSOR_XDMAC_CH].XDMAC_CDA = (uint32_t)imageBuffer2;
		break;
	}
	#endif

	XDMAC->XDMAC_CHID[IMAGING_SENSOR_XDMAC_CH].XDMAC_CUBC = XDMAC_CUBC_UBLEN(NUM_PIXEL_WORDS);
	XDMAC->XDMAC_CHID[IMAGING_SENSOR_XDMAC_CH].XDMAC_CC = XDMAC_CC_TYPE_PER_TRAN |	// Synchronized Mode
	XDMAC_CC_MBSIZE_SINGLE |	// Memory burst size is set to one. Might be able to make burst size larger along with chunk size
	XDMAC_CC_DSYNC_PER2MEM |	// Peripheral to memory
	XDMAC_CC_SWREQ_HWR_CONNECTED |	// Hardware request line is connected to the peripheral request line.
	XDMAC_CC_MEMSET_NORMAL_MODE |	// Memset is not activated. Could be wrong
	XDMAC_CC_CSIZE_CHK_1 |	// 1 data transferred. (?) Might be able to make chunk size larger for faster writing
	XDMAC_CC_DWIDTH_WORD |	// Data size is set to 32 bits. I could set this to 8 to make transfer easier... right?
	XDMAC_CC_SIF_AHB_IF1 |	// The data is read through the system bus interface 1. Not sure about this.
	XDMAC_CC_DIF_AHB_IF0 |	// The data is read through the system bus interface 0. Not sure about this.
	XDMAC_CC_SAM_FIXED_AM |	// The address remains unchanged. Fixed source memory.
	XDMAC_CC_DAM_INCREMENTED_AM |	// The addressing mode is incremented (the increment size is set to the data size). Increment destination memory
	XDMAC_CC_PERID(XDMAC_CHANNEL_HWID_PIOA);	// Peripheral ID for Parallel Capture

	//Clearing the following registers indicates that the linked list is disabled and that there is only 1 block
	XDMAC->XDMAC_CHID[IMAGING_SENSOR_XDMAC_CH].XDMAC_CNDC = 0;
	XDMAC->XDMAC_CHID[IMAGING_SENSOR_XDMAC_CH].XDMAC_CBC = 0;
	XDMAC->XDMAC_CHID[IMAGING_SENSOR_XDMAC_CH].XDMAC_CDS_MSP = 0;
	XDMAC->XDMAC_CHID[IMAGING_SENSOR_XDMAC_CH].XDMAC_CSUS = 0;
	XDMAC->XDMAC_CHID[IMAGING_SENSOR_XDMAC_CH].XDMAC_CDUS = 0;

	XDMAC->XDMAC_CHID[IMAGING_SENSOR_XDMAC_CH].XDMAC_CIE |= XDMAC_CIE_BIE;	// Enables end of block interrupt. CIE: Channel Interrupt Enable
	XDMAC->XDMAC_GIE |= (XDMAC_GIE_IE0 << IMAGING_SENSOR_XDMAC_CH);			// Enables Channel 1 interrupt. GIE: Global Interrupt Enable
	XDMAC->XDMAC_GE |= (XDMAC_GE_EN0 << IMAGING_SENSOR_XDMAC_CH);			// Enables DMA Channel 1. GE: Global Channel Enable
}

void Clk_Interrupt_Init() 
{
	PIOA->PIO_PER		|= CLK_SYNC_MASK; //PIO Enable. Takes control away from peripheral (is this OK?)
	PIOA->PIO_ODR		|= CLK_SYNC_MASK; //Disables output on this pin.
	PIOA->PIO_PPDER		|= CLK_SYNC_MASK; //Enables pulldown resistor
	PIOA->PIO_IER		|= CLK_SYNC_MASK; //Enables the input change interrupt
	PIOA->PIO_AIMER		|= CLK_SYNC_MASK; //Enables additional Interrupt modes
	PIOA->PIO_ESR		|= CLK_SYNC_MASK; //Enables edge detect. (Edge detect is on by default)
	PIOA->PIO_FELLSR	|= CLK_SYNC_MASK; //Edge detect is for falling edge (Falling edge is on by default)
}

void Clk_Capture_Enable()
{
	PIOA->PIO_PCMR |= PIO_PCMR_PCEN;
}

void Clk_Capture_Disable()
{
	PIOA->PIO_PCMR &= (uint32_t)(~PIO_PCMR_PCEN);
}


#endif	// EXPANSION_H_