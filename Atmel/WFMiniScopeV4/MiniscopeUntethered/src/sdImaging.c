#include <asf.h>
#include "sdImaging.h"
#include "definitions.h"
#include "SPI_BB_PYTHON480.h"

/************************************************************************/
/*                          Global Definitions                          */
/************************************************************************/
volatile	uint32_t	xferDMAComplete		= 0;
const		uint32_t	buffSize			= NUM_PIXEL_WORDS+FRAME_FOOTER_LENGTH;
volatile	uint32_t	numWritesPerFrame	= ((NUM_PIXEL_WORDS+FRAME_FOOTER_LENGTH) * 4)
												/ (SDMMC_BLOCK_SIZE * NB_BLOCKS_PER_WRITE); // This should be an integer
volatile	uint32_t	blockNum			= 0;
volatile	uint32_t	SDWriteNum			= 0;
volatile	uint8_t		captureEnabled		= 0;
volatile	uint8_t		startRecording		= 0;
volatile	uint32_t	pixelWordCounter	= 0;
volatile	uint32_t	frameNumber			= 0;
volatile	uint32_t	overflowCount		= 0;
volatile	uint32_t	pcISR				= 0;
volatile	uint32_t	lineCount			= 0;

volatile	uint32_t	gain				= 1;
volatile	uint32_t	ledValue			= 0;
volatile	uint32_t	numFramesToRecord	= 0;

volatile	uint32_t	testPoint			= 0;

volatile	uint32_t	sdImageWriteFrameNum= 0;



/************************************************************************/
/*                         Function Definitions                         */
/************************************************************************/
// Fills buffer with data
void fillBuffer()
{
	#ifdef NOIP1SN0480A
		uint32_t* pBuf;
		uint32_t i;
		for (i = 0; i < NUM_PIXEL_WORDS; ++i)
		{
			// &var: address to the var
			// *: the value of the pointer
			pBuf = (&imageBuffer[i]);	// these are all zero --> the pointer points at the address of each of these zeroes
			*pBuf = 0x11223344;			// Each of these locations is filled with 0x11223344
		}
	#endif
}

void enableSourceClk() 
{
	// Sets PCK1 as clock output using Main Clocks
	// PMC: Power Management Controller
	// PCK: Programmable Clock
	// CSS: Clock Source Selection
	// Sets PIO clock
	ioport_set_pin_mode(SCK1_PIN,IOPORT_MODE_MUX_B);
	ioport_disable_pin(SCK1_PIN);	// Not sure if this is necessary

	PMC->PMC_SCER = (PMC_SCER_PCK1);
	
	#ifdef EV76C454
		PMC->PMC_PCK[1] = (PMC->PMC_PCK[1] & ~(uint32_t)PMC_PCK_CSS_Msk)|(PMC_PCK_CSS_PLLA_CLK)|PMC_PCK_PRES(5); //Should make output = 48MHz
	#endif
	#ifdef EV76C454_SUBSAMP //Trying to run MCU slower
		PMC->PMC_PCK[1] = (PMC->PMC_PCK[1] & ~(uint32_t)PMC_PCK_CSS_Msk)|(PMC_PCK_CSS_PLLA_CLK)|PMC_PCK_PRES(2); //Should make output = 48MHz
	#endif
	#ifdef EV76C541 //Trying to run MCU slower
		PMC->PMC_PCK[1] = (PMC->PMC_PCK[1] & ~(uint32_t)PMC_PCK_CSS_Msk)|(PMC_PCK_CSS_PLLA_CLK)|PMC_PCK_PRES(5); //Should make output = 24MHz. Sensor divides by 4
	#endif
	#ifdef NOIP1SN0480A //Trying to run MCU slower
		PMC->PMC_PCK[1] = (PMC->PMC_PCK[1] & ~(uint32_t)PMC_PCK_CSS_Msk)|(PMC_PCK_CSS_PLLA_CLK)|PMC_PCK_PRES(5); //Should make output = 24MHz. Sensor divides by 2^5 = 32
	#endif
}

void imagingSensorSetup() 
{
	
	imagingSensorCaptureDisable(); // makes sure PIo Capture is disabled
	
	pmc_enable_periph_clk(ID_PIOA); //Sets PIO clock
	
	//NVIC_DisableIRQ( PIOA_IRQn );
	NVIC_ClearPendingIRQ(PIOA_IRQn);
	NVIC_SetPriority(PIOA_IRQn, 2);
	NVIC_EnableIRQ(PIOA_IRQn);

	imagingSensorItInit(); // Sets up interrupts //Might need to change interrupts for DMA transfer
	imagingSensorDMAInit();
	imagingSensorParamInit(); // Configures PIO Capture settings
	imageSensorVSyncItInit(); // Sets up VSync interrupt to detect end of frame
	imageSensorHSyncItInit();
	
	
	packetCMOS.chip = IMAGING_SENSOR_ADR;
	packetCMOS.addr_length = 1;

	
}

void imagingSensorParamInit() 
{
	PIOA->PIO_PCMR |= PIO_PCMR_DSIZE(D_SIZE);		// PIOA is a pointer to a struct. It has a member called PIO_PCMR. This member PIO_PCMR equals (PIO_PCMR or PIO_PCMR_DSIZE(D_SIZE)).
	
	if (ALWYS == 1)
	{
		PIOA->PIO_PCMR |= PIO_PCMR_ALWYS;
	}
	if (HALFS == 1)
	{
		PIOA->PIO_PCMR |= PIO_PCMR_HALFS;
	}
	if (FRSTS == 1)
	{
		PIOA->PIO_PCMR |= PIO_PCMR_FRSTS;
	}
}

void imagingSensorDMAInit() 
{
	//Single Block With Single Microblock Transfer
	uint32_t channelStatus = 0;
	/* Initialize and enable DMA controller */
	pmc_enable_periph_clk(ID_XDMAC);

	/*Enable XDMA interrupt */
	NVIC_ClearPendingIRQ(XDMAC_IRQn);
	NVIC_SetPriority( XDMAC_IRQn ,1);
	NVIC_EnableIRQ(XDMAC_IRQn);
}

void imagingSensorStartDMA() 
{
	
	uint32_t channelStatus = 0;

	XDMAC->XDMAC_GD =(XDMAC_GD_DI0 << IMAGING_SENSOR_XDMAC_CH); //disables DMA channel

	channelStatus = XDMAC->XDMAC_GS; //Global status of XDMAC channels. Should make sure IMAGING_SENSOR_XDMAC_CH is available
	XDMAC->XDMAC_CHID[IMAGING_SENSOR_XDMAC_CH].XDMAC_CIS;//clears interrupt status bit
	XDMAC->XDMAC_CHID[IMAGING_SENSOR_XDMAC_CH].XDMAC_CSA = (uint32_t)&(PIOA->PIO_PCRHR); //source address

	#ifdef EV76C454
		XDMAC->XDMAC_CHID[IMAGING_SENSOR_XDMAC_CH].XDMAC_CDA = (uint32_t)imageBuffer;
	#endif

	#ifdef EV76C454_SUBSAMP
	switch(frameNumber%3)
	{
		case (0):
			XDMAC->XDMAC_CHID[IMAGING_SENSOR_XDMAC_CH].XDMAC_CDA = (uint32_t)imageBuffer0;
		break;
		case (1):
			XDMAC->XDMAC_CHID[IMAGING_SENSOR_XDMAC_CH].XDMAC_CDA = (uint32_t)imageBuffer1;
		break;
		case(2):
			XDMAC->XDMAC_CHID[IMAGING_SENSOR_XDMAC_CH].XDMAC_CDA = (uint32_t)imageBuffer2;
		break;
	}
	#endif

	#ifdef EV76C541
	switch(frameNumber%3)
	{
		case (0):
			XDMAC->XDMAC_CHID[IMAGING_SENSOR_XDMAC_CH].XDMAC_CDA = (uint32_t)imageBuffer0;
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
	XDMAC->XDMAC_CHID[IMAGING_SENSOR_XDMAC_CH].XDMAC_CC = XDMAC_CC_TYPE_PER_TRAN |
	XDMAC_CC_MBSIZE_SINGLE | //might be able to make burst size larger along with chunk size
	XDMAC_CC_DSYNC_PER2MEM |
	XDMAC_CC_SWREQ_HWR_CONNECTED |
	XDMAC_CC_MEMSET_NORMAL_MODE | //Could be wrong
	XDMAC_CC_CSIZE_CHK_1 | //might be able to make chunk size larger for faster writing
	XDMAC_CC_DWIDTH_WORD |
	XDMAC_CC_SIF_AHB_IF1 | //not sure about this
	XDMAC_CC_DIF_AHB_IF0 | //not sure about this
	XDMAC_CC_SAM_FIXED_AM | //fixed source memory
	XDMAC_CC_DAM_INCREMENTED_AM | //increment destination memory
	XDMAC_CC_PERID(XDAMC_CHANNEL_HWID_PIOA); // Peripheral ID for Parallel Capture

	//Clearing the following registers indicates that the linked list is disabled and that there is only 1 block
	XDMAC->XDMAC_CHID[IMAGING_SENSOR_XDMAC_CH].XDMAC_CNDC = 0;
	XDMAC->XDMAC_CHID[IMAGING_SENSOR_XDMAC_CH].XDMAC_CBC = 0;
	XDMAC->XDMAC_CHID[IMAGING_SENSOR_XDMAC_CH].XDMAC_CDS_MSP = 0;
	XDMAC->XDMAC_CHID[IMAGING_SENSOR_XDMAC_CH].XDMAC_CSUS = 0;
	XDMAC->XDMAC_CHID[IMAGING_SENSOR_XDMAC_CH].XDMAC_CDUS = 0;

	XDMAC->XDMAC_CHID[IMAGING_SENSOR_XDMAC_CH].XDMAC_CIE |= XDMAC_CIE_BIE; //Enables end of block interrupt
	XDMAC->XDMAC_GIE |= (XDMAC_GIE_IE0 <<IMAGING_SENSOR_XDMAC_CH); //Enables channel interrupt
	XDMAC->XDMAC_GE |= (XDMAC_GE_EN0 << IMAGING_SENSOR_XDMAC_CH); //Enables DMA channel
}
void imagingSensorItInit() 
{
	//PIOA->PIO_PCIER = PIO_PCISR_DRDY; //Enable Data Ready Interrupt
	//PIOA->PIO_PCIDR |= (PIO_PCIDR_RXBUFF)|(PIO_PCIDR_ENDRX)|(PIO_PCIDR_OVRE); //Makes sure other interrupts are disabled

	//PIOA->PIO_PCIER = (PIO_PCIDR_OVRE); //Enable Data Ready Interrupt
	PIOA->PIO_PCIDR |= (PIO_PCIDR_DRDY)|(PIO_PCIDR_RXBUFF)|(PIO_PCIDR_ENDRX)|(PIO_PCIDR_OVRE); //Makes sure other interrupts are disabled
}

void imageSensorVSyncItInit() 
{
	PIOA->PIO_PER		|= VSYNC_MASK; //PIO Enable. Takes control away from peripheral (is this OK?)
	PIOA->PIO_ODR		|= VSYNC_MASK; //Disables output on this pin.
	PIOA->PIO_PPDER		|= VSYNC_MASK; //Enables pulldown resistor
	
	PIOA->PIO_IER		|= VSYNC_MASK; //Enables the input change interrupt
	PIOA->PIO_AIMER		|= VSYNC_MASK; //Enables additional Interrupt modes
	PIOA->PIO_ESR		|= VSYNC_MASK; //Enables edge detect. (Edge detect is on by default)
	PIOA->PIO_FELLSR	|= VSYNC_MASK; //Edge detect is for falling edge (Falling edge is on by default)
	
	//	if((PIOA->PIO_OSR&VSYNC_MASK) == VSYNC_MASK)
	//		printf("VSync is set as input");
	
}

void imageSensorHSyncItInit() 
{
	PIOA->PIO_PER		|= HSYNC_MASK; //PIO Enable. Takes control away from peripheral (is this OK?)
	PIOA->PIO_ODR		|= HSYNC_MASK; //Disables output on this pin.
	PIOA->PIO_PPDER		|= HSYNC_MASK; //Enables pulldown resistor
	
	PIOA->PIO_IER		|= HSYNC_MASK; //Enables the input change interrupt
	PIOA->PIO_AIMER		|= HSYNC_MASK; //Enables additional Interrupt modes
	PIOA->PIO_ESR		|= HSYNC_MASK; //Enables edge detect. (Edge detect is on by default)
	PIOA->PIO_FELLSR	|= HSYNC_MASK; //Edge detect is for falling edge (Falling edge is on by default)
	
	
}

void imagingSensorLoadHeader()
{
	uint8_t headerTemp[SDMMC_BLOCK_SIZE] = {0};
	uint32_t *header = (uint32_t *)headerTemp;

	uint32_t writeKey[4] = {0};
	sd_mmc_init_read_blocks(SD_SLOT_NB,HEADER_SECTOR,1);
	sd_mmc_start_read_blocks(headerTemp,1);
	sd_mmc_wait_end_of_read_blocks(false);

	gain				= header[HEADER_GAIN_POS];
	//ledValue			= ((100- header[HEADER_LED_POS])*0x0FFF)/100; //header should be between 0 and 100; Used for DAC
	ledValue			= header[HEADER_LED_POS]; //header should be between 0 and 255;
	numFramesToRecord	= header[HEADER_NUM_FRAMES_POS];
}

void imagingSensorCaptureEnable() 
{
	PIOA->PIO_PCMR |= PIO_PCMR_PCEN ;
}

void imagingSensorCaptureDisable()
{
	PIOA->PIO_PCMR &= (uint32_t)(~PIO_PCMR_PCEN) ;
}

void checkVSync() 
{
	if (pcISR & VSYNC_MASK)
	 { //VSync signal is detected. End of frame capture
		//printf("VSYNC!\n");
		//while(pcISR & VSYNC_MASK) {}
		
		//frameNumber++;
		//if (frameNumber%10==1)
		//	ioport_toggle_pin_level(PIO_PD1_IDX);

		if (captureEnabled && startRecording) 
		{
			
			// -------------- For initial testing ------------
			captureEnabled = 0;
			startRecording = 0;
			imagingSensorCaptureDisable();
			
			#ifdef EV76C454
				imageBuffer[buffSize-1] = frameNumber;
				imageBuffer[buffSize-3] = lineCount;
				imageBuffer[buffSize-4] = xferDMAComplete; //Overflow flag
			#endif
			
			// ========== Try this =========== /
			#ifdef NOIP1SN0480A
				imageBuffer[buffSize-1] = frameNumber;
				imageBuffer[buffSize-3] = lineCount;
				imageBuffer[buffSize-4] = xferDMAComplete; //Overflow flag
			#endif

			#ifdef EV76C454_SUBSAMP
			switch (frameNumber%3)
			{
				case (0):
					imageBuffer0[buffSize-1] = frameNumber;
					imageBuffer0[buffSize-3] = lineCount;
					imageBuffer0[buffSize-4] = xferDMAComplete; //Overflow flag
				break;
				case (1):
					imageBuffer1[buffSize-1] = frameNumber;
					imageBuffer1[buffSize-3] = lineCount;
					imageBuffer1[buffSize-4] = xferDMAComplete; //Overflow flag
				break;
				case (2):
					imageBuffer2[buffSize-1] = frameNumber;
					imageBuffer2[buffSize-3] = lineCount;
					imageBuffer2[buffSize-4] = xferDMAComplete; //Overflow flag
				break;
			}
			#endif

			#ifdef EV76C541
			switch (frameNumber%3)
			{
				case (0):
				imageBuffer0[buffSize-1] = frameNumber;
				imageBuffer0[buffSize-3] = lineCount;
				imageBuffer0[buffSize-4] = xferDMAComplete; //Overflow flag
				break;
				case (1):
				imageBuffer1[buffSize-1] = frameNumber;
				imageBuffer1[buffSize-3] = lineCount;
				imageBuffer1[buffSize-4] = xferDMAComplete; //Overflow flag
				break;
				case (2):
				imageBuffer2[buffSize-1] = frameNumber;
				imageBuffer2[buffSize-3] = lineCount;
				imageBuffer2[buffSize-4] = xferDMAComplete; //Overflow flag
				break;
			}
			#endif

			lineCount = 0;
			frameNumber++;
			overflowCount = 0;
			xferDMAComplete = 0;
			
			#ifdef EV76C541 //immediately start recording of next frame
			if (frameNumber<=sdImageWriteFrameNum +2) 
			{
				startRecording = 1;
				captureEnabled = 1;
				imagingSensorStartDMA();
				imagingSensorCaptureEnable();
			}
			#endif

			#ifdef EV76C454_SUBSAMP //immediately start recording of next frame
			if (frameNumber<=sdImageWriteFrameNum +2)
			{
				startRecording = 1;
				captureEnabled = 1;
				imagingSensorStartDMA();
				imagingSensorCaptureEnable();
			}

			#endif
			//testPoint = 1;
			//------------------------------------------------
		}
		else if(startRecording) 
		{ //waits for the first VSync to start capture. This makes sure we capture a full first frame
			captureEnabled = 1;
			
			//frameNumber = 0;
			lineCount = 0;
			overflowCount = 0;
			imagingSensorStartDMA();
			imagingSensorCaptureEnable();
		}


		//Need to add an overflow check.
		//Added a check to make sure pixelWordCount == NUM_PIXEL/4
		//Consider adding HSync to label each row in case missing pixels is an issue
	}
}

/************************************************************************/
/*	         Overwrites the Stock Functions in pio_handler.h            */
/************************************************************************/
void PIOA_Handler(void) 
{
	pcISR = PIOA->PIO_ISR;
	if (pcISR & HSYNC_MASK) 
	{
		if (captureEnabled == 1)
		{
			lineCount++;
		}
	}
	checkVSync();
}

void XDMAC_Handler(void)
{
	uint32_t dma_status;

	dma_status = XDMAC->XDMAC_CHID[IMAGING_SENSOR_XDMAC_CH].XDMAC_CIS;

	if (dma_status & XDMAC_CIS_BIS) 
	{
		xferDMAComplete = 1;
	}
}


/************************************************************************/
/*                           No Longer In Use                           */
/************************************************************************/
void imagingSensorConfigure()
{
	//------- Synchro Reg -----------
	//bit 6,7: Master clock div
	//bit 5: Data clock polarity, 1 Data are output on falling edge
	//bit 4: Flash polarity FLO
	//bit 3: Frame Enable Polarity, 0->FEN is active low
	//bit 2: Line Enable Polarity, 0->LEN is active low
	//bit 1: Data activity when FEN or LEN are inactive, 1->No activity
	//bit 0: LEN activity when FEN is inactive, 0->passes all calced LEN
	//default->0b00100010
	packetCMOS.addr[0] = 0x0A; //Synchro
	
	#ifdef EV76C454
	i2cbuf[0] = 0b01101111;
	#endif
	
	#ifdef EV76C454_SUBSAMP
	i2cbuf[0] = 0b10101111; //clock div by 4
	#endif
	
	packetCMOS.buffer = (uint8_t *) i2cbuf;
	packetCMOS.length = 1;
	while (twihs_master_write(TWIHS1,&packetCMOS) != TWIHS_SUCCESS)
	{}
	////------ frame_config ------
	////bit 4: 0-> No vertical flip
	////bit 3: 0-> No horizontal flip
	////bit 0,1,2: Subsample factor = 2^value
	////default->0x00;

	#ifdef EV76C454_SUBSAMP
	packetCMOS.addr[0] = 0x0B; //frame_config
	i2cbuf[0] = 0x01; //Subsamp by 2
	packetCMOS.buffer = (uint8_t *) i2cbuf;
	packetCMOS.length = 1;
	while (twihs_master_write(TWIHS1,&packetCMOS) != TWIHS_SUCCESS)
	{}
	#endif
	
	////----- frame_line_log ----------- ?????
	////bit 0-3: 0000= Do not use, 0001 liner mode 0,225V?
	////default->0x01;
	//packetCMOS.addr[0] = 0x0C; //frame_line_log
	//i2cbuf[0] = 0x01;
	//packetCMOS.buffer = (uint8_t *) i2cbuf;
	//packetCMOS.length = 1;
	//while (twihs_master_write(TWIHS1,&packetCMOS) != TWIHS_SUCCESS) {
	//}
	// ------ frame_tint -----
	//Integration duration adjustment.
	//Software step = (800 x Master clock) ? 16.7 us @ 48 MHz if
	//div_clk=00
	//Real duration: The integration time is rounded at the nearest
	//number of lines above the programmed time.
	//default:0x012C (d300) -> I think this is ~5ms, I think 2000 should be 30FPS
	packetCMOS.addr[0] = 0x80;//frame_tint
	#ifdef EV76C454
	i2cbuf[0] = (2000>>8)&0x00FF;
	i2cbuf[1] = (2000)&0x00FF;
	#endif
	#ifdef EV76C454_SUBSAMP
	i2cbuf[0] = (3000>>8)&0x00FF; //Clock div shouldn't effect total value here
	i2cbuf[1] = (3000)&0x00FF;		//3000 should result in about 20FPS
	#endif
	packetCMOS.buffer = (uint8_t *) i2cbuf;
	packetCMOS.length = 2;
	while (twihs_master_write(TWIHS1,&packetCMOS)  != TWIHS_SUCCESS)
	{}
	// ---------- frame_twait --------
	//default 0x0000 (no wait), max 0x0FFF (68,2ms)
	packetCMOS.addr[0] = 0x81;//frame_twait
	i2cbuf[0] = (100>>8)&0x00FF; //value should only really matter if integration time is shorter than data transmission time
	i2cbuf[1] = (100)&0x00FF;
	packetCMOS.buffer = (uint8_t *) i2cbuf;
	packetCMOS.length = 2;
	while (twihs_master_write(TWIHS1,&packetCMOS)  != TWIHS_SUCCESS)
	{}
	//
	//// ---------- frame_gain --------------
	////---- --00 0--- ---- frame_gain_analog
	////bit 7,8,9: Analog gain (Min 000->1,Max 111->8)
	////---- ---- -000 0000 frame_gain_digital
	////bit 0-6: digital gain, applied after the offset substraction digital gain = 1 + dig_gain / 32
	////Min 0000000 digital gain = 1
	////Max 1111111 digital gain = 4.97
	////default: 0x0000
	packetCMOS.addr[0] = 0x82;//frame_gain
	switch (gain)
	{
		case (1):
		i2cbuf[0] = (0x0000>>8)&0x00FF;
		i2cbuf[1] = (0x0000)&0x00FF;
		break;
		case (2):
		i2cbuf[0] = (0x0100>>8)&0x00FF;
		i2cbuf[1] = (0x0100)&0x00FF;
		break;
		case (4):
		i2cbuf[0] = (0x0200>>8)&0x00FF;
		i2cbuf[1] = (0x0200)&0x00FF;
		break;
		case (8):
		i2cbuf[0] = (0x0300>>8)&0x00FF;
		i2cbuf[1] = (0x0300)&0x00FF;
		break;
		default:
		i2cbuf[0] = (0x0000>>8)&0x00FF;
		i2cbuf[1] = (0x0000)&0x00FF;
		break;
	}
	packetCMOS.buffer = (uint8_t *) i2cbuf;
	packetCMOS.length = 2;
	while (twihs_master_write(TWIHS1,&packetCMOS)  != TWIHS_SUCCESS)
	{}
	// ----- frame_roi_0c
	//pixel of first column to read
	//default 0x0006, range (d0 to d875)
	packetCMOS.addr[0] = 0x83;//frame_roi_0c
	#ifdef EV76C454
	i2cbuf[0] = ((32+50)>>8)&0x00FF;
	i2cbuf[1] = (32+50)&0x00FF;
	#endif
	#ifdef EV76C454_SUBSAMP
	i2cbuf[0] = ((32+50+56)>>8)&0x00FF;
	i2cbuf[1] = (32+50+56)&0x00FF;
	#endif
	packetCMOS.buffer = (uint8_t *) i2cbuf;
	packetCMOS.length = 2;
	while (twihs_master_write(TWIHS1,&packetCMOS)  != TWIHS_SUCCESS)
	{}
	// ----- frame_roi_0l
	//pixel of first line to read
	//default 0x0006, range (d0 to d651)
	packetCMOS.addr[0] = 0x84;//frame_roi_0l
	#ifdef EV76C454
	i2cbuf[0] = ((6+100)>>8)&0x00FF;
	i2cbuf[1] = (6+100)&0x00FF;
	#endif
	#ifdef EV76C454_SUBSAMP
	i2cbuf[0] = ((6)>>8)&0x00FF;
	i2cbuf[1] = (6)&0x00FF;
	#endif
	packetCMOS.buffer = (uint8_t *) i2cbuf;
	packetCMOS.length = 2;
	while (twihs_master_write(TWIHS1,&packetCMOS)  != TWIHS_SUCCESS)
	{}
	// ----- frame_roi_w
	//pixel of first column to read
	//default 0x0360 (d864), range (d16 to d876)
	packetCMOS.addr[0] = 0x85;//frame_roi_w

	i2cbuf[0] = (IMAGE_HEIGHT>>8)&0x00FF;
	i2cbuf[1] = (IMAGE_HEIGHT)&0x00FF;
	packetCMOS.buffer = (uint8_t *) i2cbuf;
	packetCMOS.length = 2;
	while (twihs_master_write(TWIHS1,&packetCMOS)  != TWIHS_SUCCESS)
	{}
	// ----- frame_roi_h
	//pixel of first column to read
	//default 0x0280 (d640), range (d16 to d652)
	packetCMOS.addr[0] = 0x86;//frame_roi_h
	i2cbuf[0] = (IMAGE_WIDTH>>8)&0x00FF;
	i2cbuf[1] = (IMAGE_WIDTH)&0x00FF;
	packetCMOS.buffer = (uint8_t *) i2cbuf;
	packetCMOS.length = 2;
	while (twihs_master_write(TWIHS1,&packetCMOS)  != TWIHS_SUCCESS)
	{}
	// --------- Enable Pattern Generator
	//bit 0,1:
	//00->No test pattern: video is output (default)
	//01->Moving test pattern
	//10->Fixed test pattern
	//11->Functional test pattern
	packetCMOS.addr[0] = 0x13; //Synchro
	i2cbuf[0] = 0b00000000;
	packetCMOS.buffer = (uint8_t *) i2cbuf;
	packetCMOS.length = 1;
	while (twihs_master_write(TWIHS1,&packetCMOS) != TWIHS_SUCCESS)
	{}

	// ------ miscel_ctrl
	//bit 6: 1->Forces all output pads to high impedance
	//bit 4: 3x3 filter bypass, 1->turns off F0-7
	//bit 1: trig, set to 0 to only use trig_pin. set to 1 to soft start acq
	//bit 0: stdby_rqst: set to 0 to take off standby mode.
	//default:0x67, 0b01100111
	packetCMOS.addr[0] = 0x0F;//miscel_ctrl
	i2cbuf[0] = 0b00110100;
	packetCMOS.buffer = (uint8_t *) i2cbuf;
	packetCMOS.length = 1;
	while (twihs_master_write(TWIHS1,&packetCMOS)  != TWIHS_SUCCESS)
	{}
}

void imagingSensorConfigureEV76C541()
{ //SPI configuration of sensor
	uint16_t value = 0x0000;
	uint8_t reg = 0x00;

	// ----- These initialize the registers from the EV76V541 Initialization Values PDF
	uint8_t initReg[42] = {0x07,0x3A,0x3F,0x47,0x48,0x49,
		0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
		0x51,0x52,0x53,0x54,0x55,0x56,
		0x57,0x58,0x59,0x5A,0x5B,0x5C,
		0x5E,0x67,0x68,0x69,0x6A,0x6B,
		0x6C,0x6E,0x6F,0x70,0x71,0x73,
	0x79,0x7A,0x7B,0x41,0x46,0x6D};
	uint16_t initValue[42] = {0x0A06,0x80AF,0x1E1E,0x034F,0xFFFD,0x8D6F,
		0xBAC8,0x0127,0x0B1E,0x161C,0xA0B9,0x0124,
		0x308C,0x8383,0x053D,0x6F8C,0x053C,0x3F44,
		0x3F4E,0x053C,0x708B,0x0760,0x053D,0x6F8C,
		0x5257,0x4452,0x0541,0x5471,0x0941,0x5470,
		0x0871,0x0941,0x0745,0x0541,0x5471,0x5053,
	0x2000,0x308A,0x0101,0x9922,0x4300,0x516E};

	for (uint8_t i = 0; i < 42; ++i)
	SPI_Write(initReg[i], initValue[i]);
	//---------------------------------------------------

	//reg-miscel1
	reg = 0x06;
	value = 0x345A; //Default value
	value &= 0xFF00; //Sets the knee point of 10 to 8 bit conversion. Using direct 10 to 8 bit conversion with 0 knee point
	SPI_Write(reg, value);

	//Miscellaneous register 2
	reg = 0x07;
	//value = 0x0A01; //Default value
	value = 0x0A06; //Value that is set on startup. Not sure about the bottom 4 bits
	value |= 1<<13; //LEN Invert
	value |= 1<<12; //FEN Invert
	//value = value&0b1111110111111111; //Clamp_auto_en
	value |= (0<<5)|(0<<4); //Test pattern selection. 0 is video output
	SPI_Write(reg, value);

	//Clock configuration
	reg = 0x08;
	value = 0xDF22; //Default value
	value = 0b1101010100100010; //Selects source of clocks and downsample factors
	SPI_Write(reg, value);

	//Chain configuration
	reg = 0x0A;
	//value = 0x0200; //Default value
	value = 0x0000;
	value |= (1<<9); //binning division factor (1,2 or 4)
	value |= 1<<4; //range compression for 10 to 8 bit. uses knee defined in 0x06
	//value |= 1<<0; //bin ROI1
	//value = 0b0000000000000001; //Last bit bins pixels, middle bits sets bin division factor
	SPI_Write(reg, value);

	//Control configuration
	reg = 0x0B;
	value = 0x0005; //Default value. sets overlap mode and Trig pin polarity
	value |= 1<<8; //Trig pin enabled
	value = value&(0xFFFE); //Turns standby mode off
	SPI_Write(reg, value);

	//Wait time
	//reg = 0x0D;
	//value = 0x0000; //Default value.
	//spiWrite(reg,value);

	//-------------- ROI1 control Regs
	//ROI1 int time
	reg = 0x0E;
	value = 682; //Int time in number of lines. time for 1 line = 15.4us*57MHz/(CLK_CTRL in MHz)
	//682 lines at 12MHz clock should get us 20FPS
	SPI_Write(reg, value);

	//Analog and digital Gain
	reg = 0x11;
	value = 0; //Default gain of 1. Top 8 are analog, bottom 8 are digital
	switch (gain){
		case (1):
		value = 0;
		break;
		case (2):
		value = (2 << 8);
		break;
		case (4):
		value = (4 << 8);
		break;
		case (8):
		value = (6 << 8);
		break;
		default:
		value = 0;
		break;
	}
	//value |= 0x0040; //Add some digital gain (2x)
	SPI_Write(reg, value);

	//Horizontal size
	//reg = 0x13;
	//value = 0x01E0; //480lines
	//spiWrite(reg,value);

	//Vertical size
	reg = 0x15;
	value = 704; //704lines. Max is 752
	SPI_Write(reg, value);

	//Sub-sampling RO1
	reg = 0x1A;
	value = (8<<8)|(8<<0); //2 x 2 down sample
	SPI_Write(reg, value);
}
