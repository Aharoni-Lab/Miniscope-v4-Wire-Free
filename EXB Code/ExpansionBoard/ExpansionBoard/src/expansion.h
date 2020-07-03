#ifndef EXPANSION_H_
#define EXPANSION_H_


/************************************************************************/
/*                           CONFIGURATIONS                             */
/************************************************************************/
// ========== IMAGE SENSOR CHOICE ========== //
#define PYTHON480




// ========== IMAGE SENSOR CONFIG ========== //
#ifdef PYTHON480
	#define D_SIZE					0		// 2 Change buffer size from word to byte
	#define ALWYS					0
	#define HALFS					0
	#define FRSTS					0

	#define PIXELS_PER_BYTE			1 << D_SIZE
	#define IMAGE_WIDTH				768		// Will be sub-sampled by 2x
	#define IMAGE_HEIGHT			592		// Will be sub-sampled by 2x
	#define IMAGE_SUBSAMPLE			2
	#define NUM_PIXELS				(IMAGE_HEIGHT*IMAGE_WIDTH) / (IMAGE_SUBSAMPLE*IMAGE_SUBSAMPLE)    // Currently needs to be a multiple of PIXELS_PER_WORD and SDMMC_BLOCK_SIZE
	#define FRAME_FOOTER_LENGTH		0		// Last 32bit of footer is frame number. The rest is used to fill up sdCard multi block write. Has units of WORDS
	#define NUM_PIXEL_BYTE			(NUM_PIXELS) / ((uint32_t)PIXELS_PER_BYTE)


#endif /* PYTHON480 */




// ========== DIRECT MEMORY ACCESS CONFIG ========== //
#define PIOA_XDMAC_CH					1




// ========== GLOBAL VARIABLES ========== //
const uint32_t buffSize = NUM_PIXEL_BYTE+FRAME_FOOTER_LENGTH;

volatile uint32_t TxDMAComplete			= 0;
volatile uint32_t frameNumber			= 0;
volatile uint32_t DAQTxFrameNum			= 0;
volatile uint32_t captureEnabled		= 0;
volatile uint32_t fullBlock				= 0;
volatile uint32_t pcISR					= 0;
volatile uint32_t pinDSR				= 0;



#ifdef PYTHON480
	static uint8_t imageBuffer0[NUM_PIXEL_BYTE+FRAME_FOOTER_LENGTH];
	static uint8_t imageBuffer1[NUM_PIXEL_BYTE+FRAME_FOOTER_LENGTH];
	static uint8_t imageBuffer2[NUM_PIXEL_BYTE+FRAME_FOOTER_LENGTH];
	static int32_t DATA_MASKS = (DAT0_MASK | DAT1_MASK | DAT2_MASK | DAT3_MASK);
#endif



// ========== FUNCTION DECLARATIONS ========== //
/* 
WXB_DMA_Init: Powers DMA module, clear interrupt, set priority and enable DMA interrupt
*/
void WXB_DMA_Init();

/*
WXB_Start_DMA: Reset DMA, set data location, chunk size, specify different types of interrupts
*/
void WXB_Start_DMA();

/*
Clk_Interrupt_Init: Set up clock signal edge detect
*/
void Clk_Interrupt_Init();



// ========== FUNCTION DEFINITIONS ========== //
void Dinput_Pin_Setup(void)
{
	Clk_Interrupt_Init();	// enable port A interrupt (pixel clock falling edge)

	PIOA->PIO_PER	|= DATA_MASKS;    // PIO Enable. Takes control away from peripheral (is this OK?)
	PIOA->PIO_ODR	|= DATA_MASKS;    // Disables output on this pin.
}



/*
	PIOA_Handler: Every time the pixel clock pin triggers (**Match with MiniscopeUntethered**) the status of the 4 data pins are stored into the buffer.
	@ DAT0, DAT1, DAT2, and DAT3: The data pins
	@ pcISR: pixel clock interrupt status register. Triggered by the pixel clock.
	@ PIO_PDSR: pin data status register. Grabs the status of all 32 pins and stores it into a 32 bit variable (pinDSR)
	@ pinDSR: DAT3 is not connected consecutively to the other three pins, and thus when PIO_PDSR grabs the data statuses, the relevant bit positions are: 3, 4, 5, and 9.
	
	Steps are taken to: 1. Move the 9th bit to the 6th bit; 2. Move all four bits to the lowest 4 bit positions; 3. Clear all higher, irrelevant bits.
	Then pinDSR is saved into the buffer, but since the buffer dtype is 8 bits, it must be saved twice - the lower 4, and then the higher 4 (**Match with MiniscopeUntethered**)
*/
void PIOA_Handler(void) // We're going to bit bang this. Every time clock goes down, (or UP. Match with MiniscopeUntethered.) grab the data line values.
{	
	pcISR = PIOA->PIO_ISR;								// pixel clock interrupt status register
	if (pcISR & PXLCLK_MASK)
	{
		switch (frameNumber % 3)
		{			
			case(0):
				for (int i = 0; i < buffSize * 2; ++i)
				{
					pinDSR = (PIOA->PIO_PDSR);								// data line status (value) register
					pinDSR = (pinDSR & ~(DAT2_MASK << 1)) | (!!(pinDSR & DAT3_MASK) << (DAT2_ID + 1));				// move datum 3 bit into consecutive position
					pinDSR = (pinDSR >> DAT0_ID) % 16;								// move to the lowest 4 bits, then modulus to clear all higher bits
					switch (i % 2)
					{
						case(0):
							imageBuffer0[i / 2] |= pinDSR;						// only the rightmost bits
						break;
						case(1):
							imageBuffer0[i / 2] |= (pinDSR >> 4);
						break;
					}
				}
			break;
			
			case(1):
				for (int i = 0; i < buffSize * 2; ++i)
				{
					pinDSR = (PIOA->PIO_PDSR);								// data line status (value) register
					pinDSR = (pinDSR & ~(DAT2_MASK << 1)) | (!!(pinDSR & DAT3_MASK) << (DAT2_ID + 1));				// move datum 3 bit into consecutive position
					pinDSR = (pinDSR >> DAT0_ID) % 16;								// move to the lowest 4 bits, then modulus to clear all higher bits
					switch (i % 2)
					{
						case(0):
							imageBuffer1[i / 2] |= pinDSR;						// only the rightmost bits
						break;
						case(1):
							imageBuffer1[i / 2] |= (pinDSR >> 4);
						break;
					}
				}
			break;
				
			case(2):
				for (int i = 0; i < buffSize * 2; ++i)
				{
					pinDSR = (PIOA->PIO_PDSR);								// data line status (value) register
					pinDSR = (pinDSR & ~(DAT2_MASK << 1)) | (!!(pinDSR & DAT3_MASK) << (DAT2_ID + 1));				// move datum 3 bit into consecutive position
					pinDSR = (pinDSR >> DAT0_ID) % 16;								// move to the lowest 4 bits, then modulus to clear all higher bits
					switch (i % 2)
					{
						case(0):
							imageBuffer2[i / 2] |= pinDSR;						// only the rightmost bits
						break;
						case(1):
							imageBuffer2[i / 2] |= (pinDSR >> 4);
						break;
					}
				}
			break;
		}
		++frameNumber;
	}	
}



void XDMAC_Handler(void)
{
	uint32_t dma_status;

	dma_status = XDMAC->XDMAC_CHID[PIOA_XDMAC_CH].XDMAC_CIS;

	if (dma_status & XDMAC_CIS_BIS)
	{
		TxDMAComplete = 1;
	}
}



void WXB_DMA_Init()
{
	// Single Block With Single Microblock Transfer
	uint32_t channelStatus = 0;
	
	/* Initialize and enable DMA controller */
	pmc_enable_periph_clk(ID_XDMAC);

	/* Enable XDMA interrupt */
	NVIC_ClearPendingIRQ(XDMAC_IRQn);   // Clear pending interrupt
	NVIC_SetPriority(XDMAC_IRQn, 1);	// Highest priority
	NVIC_EnableIRQ(XDMAC_IRQn);			// Enable interrupt
	PIOA->PIO_PCIDR |= (PIO_PCIDR_DRDY)|(PIO_PCIDR_RXBUFF)|(PIO_PCIDR_ENDRX)|(PIO_PCIDR_OVRE);	// Makes sure other interrupts are disabled
}



void WXB_Start_DMA()
{
	uint32_t channelStatus = 0;

	XDMAC->XDMAC_GD =(XDMAC_GD_DI0 << PIOA_XDMAC_CH);   // Disables DMA channel

	channelStatus = XDMAC->XDMAC_GS;					// Global status of XDMAC channels. Should make sure PIOA_XDMAC_CH is available
	XDMAC->XDMAC_CHID[PIOA_XDMAC_CH].XDMAC_CIS;			// Clears interrupt status bit
	XDMAC->XDMAC_CHID[PIOA_XDMAC_CH].XDMAC_CSA = (uint32_t)&(PIOA->PIO_PCRHR);     // Source address

	// Where to save
	#ifdef PYTHON480
	switch(frameNumber % 3)
	{
		case (0):
		XDMAC->XDMAC_CHID[PIOA_XDMAC_CH].XDMAC_CDA = (uint32_t)imageBuffer0;	  // CDA: Channel Destination Address
		break;
		
		case (1):
		XDMAC->XDMAC_CHID[PIOA_XDMAC_CH].XDMAC_CDA = (uint32_t)imageBuffer1;
		break;
		
		case(2):
		XDMAC->XDMAC_CHID[PIOA_XDMAC_CH].XDMAC_CDA = (uint32_t)imageBuffer2;
		break;
	}
	#endif

	XDMAC->XDMAC_CHID[PIOA_XDMAC_CH].XDMAC_CUBC = XDMAC_CUBC_UBLEN(NUM_PIXEL_BYTE);    // Number of data in microblock
	XDMAC->XDMAC_CHID[PIOA_XDMAC_CH].XDMAC_CC = XDMAC_CC_TYPE_PER_TRAN |	// Synchronized Mode
	XDMAC_CC_MBSIZE_SINGLE |			// Memory burst size is set to one. Might be able to make burst size larger along with chunk size
	XDMAC_CC_DSYNC_PER2MEM |			// Peripheral to memory
	XDMAC_CC_SWREQ_HWR_CONNECTED |		// Hardware request line is connected to the peripheral request line.
	XDMAC_CC_MEMSET_NORMAL_MODE |		// Memset is not activated. Could be wrong
	XDMAC_CC_CSIZE_CHK_1 |				// 1 data transferred. (?) Might be able to make chunk size larger for faster writing
	XDMAC_CC_DWIDTH_BYTE |				// Data size is set to 8 bits
	XDMAC_CC_SIF_AHB_IF1 |				// The data is read through the system bus interface 1. Not sure about this.
	XDMAC_CC_DIF_AHB_IF0 |				// The data is read through the system bus interface 0. Not sure about this.
	XDMAC_CC_SAM_FIXED_AM |				// The address remains unchanged. Fixed source memory.
	XDMAC_CC_DAM_INCREMENTED_AM |		// The addressing mode is incremented (the increment size is set to the data size). Increment destination memory
	XDMAC_CC_PERID(XDMAC_CHANNEL_HWID_PIOA);	// Peripheral ID for Parallel Capture

	// Clearing the following registers indicates that the linked list is disabled and that there is only 1 block
	XDMAC->XDMAC_CHID[PIOA_XDMAC_CH].XDMAC_CNDC = 0;
	XDMAC->XDMAC_CHID[PIOA_XDMAC_CH].XDMAC_CBC = 0;
	XDMAC->XDMAC_CHID[PIOA_XDMAC_CH].XDMAC_CDS_MSP = 0;
	XDMAC->XDMAC_CHID[PIOA_XDMAC_CH].XDMAC_CSUS = 0;
	XDMAC->XDMAC_CHID[PIOA_XDMAC_CH].XDMAC_CDUS = 0;

	XDMAC->XDMAC_CHID[PIOA_XDMAC_CH].XDMAC_CIE |= XDMAC_CIE_BIE;		// Enables end of block interrupt. CIE: Channel Interrupt Enable
	XDMAC->XDMAC_GIE	|= (XDMAC_GIE_IE0 << PIOA_XDMAC_CH);			// Enables Channel 1 interrupt. GIE: Global Interrupt Enable
	XDMAC->XDMAC_GE		|= (XDMAC_GE_EN0 << PIOA_XDMAC_CH);				// Enables DMA Channel 1. GE: Global Channel Enable
}



void Clk_Interrupt_Init() 
{
	PIOA->PIO_PER		|= PXLCLK_MASK;    // PIO Enable. Takes control away from peripheral (is this OK?)
	PIOA->PIO_ODR		|= PXLCLK_MASK;    // Disables output on this pin.
	PIOA->PIO_PPDER		|= PXLCLK_MASK;    // Enables pull-down resistor
	PIOA->PIO_IER		|= PXLCLK_MASK;    // Enables the input change interrupt
	PIOA->PIO_AIMER		|= PXLCLK_MASK;    // Enables additional Interrupt modes
	PIOA->PIO_ESR		|= PXLCLK_MASK;    // Enables edge detect. (Edge detect is on by default)
	PIOA->PIO_FELLSR	|= PXLCLK_MASK;    // Edge detect is for falling edge (Falling edge is on by default)
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