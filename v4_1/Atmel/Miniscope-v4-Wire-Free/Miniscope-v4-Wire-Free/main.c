#include <atmel_start.h>

#include "definitions.h"

#include "i2c_bb.h"

// ------- SET WIRE-FREE DEVICE TYPE ----
#define MINISCOPE_V4_WF
// --------------------------------------


// ------------ GLOBAL VARIABLES --------
volatile uint32_t dataBuffer[NUM_BUFFERS][BUFFER_BLOCK_LENGTH * BLOCK_SIZE_IN_WORDS]; //Allocate memory for DMA image buffers

volatile uint8_t deviceState = DEVICE_STATE_IDLE;
volatile DmacDescriptor linkedList[NUM_BUFFERS];

volatile uint32_t frameNum = 0;
volatile uint32_t bufferCount = 0;
volatile uint32_t frameBufferCount = 0;

volatile uint32_t startTimeMS;
// --------------------------------------

// ----------- FUNCTIONS ----------------
void imageSensorInit(void);
void linkedListInit(void);

void setExcitationLED(uint8_t value);
void setGain(uint8_t value);
void setFPS(uint8_t value);;
void setEWL(uint8_t value);

void setStatusLED(bool value);
// --------------------------------------

void linkedListInit(void)
{
	for (uint8_t i = 0; i < NUM_BUFFERS; i++) {
		if (i == (NUM_BUFFERS - 1))
			// Last buffer in list. Need to loop back
			linkedList[i].DESCADDR.reg = (uint32_t)&linkedList[0];
		else
			linkedList[i].DESCADDR.reg = (uint32_t)&linkedList[i + 1];
		linkedList[i].BTCNT.reg = (BUFFER_BLOCK_LENGTH * BLOCK_SIZE_IN_WORDS);
		linkedList[i].BTCTRL.reg = DMAC_BTCTRL_STEPSIZE(0) | (CONF_DMAC_STEPSEL_0 << DMAC_BTCTRL_STEPSEL_Pos)						\
								| (CONF_DMAC_DSTINC_0 << DMAC_BTCTRL_DSTINC_Pos) | (CONF_DMAC_SRCINC_0 << DMAC_BTCTRL_SRCINC_Pos)	\
								| DMAC_BTCTRL_BEATSIZE(CONF_DMAC_BEATSIZE_0) | DMAC_BTCTRL_BLOCKACT(CONF_DMAC_BLOCKACT_0)            \
								| DMAC_BTCTRL_EVOSEL(CONF_DMAC_EVOSEL_0);
	
		linkedList[i].SRCADDR.reg = (uint32_t)(&PCC->RHR.reg);
		// Destination address when incrementing address needs to be the end address and not the start address.
		linkedList[i].DSTADDR.reg = (uint32_t)(&dataBuffer[i][BUFFER_HEADER_LENGTH]) + (BUFFER_BLOCK_LENGTH * BLOCK_SIZE_IN_WORDS) * 4;
	}
	// Set up initial dma descriptor for DMA channel handling PCC. BTCNT is already setup in dma init step
	_dma_set_source_address(CONF_PCC_DMA_CHANNEL, linkedList[0].SRCADDR.reg);
	_dma_set_destination_address(CONF_PCC_DMA_CHANNEL, linkedList[0].DSTADDR.reg);
	_dma_set_data_amount(CONF_PCC_DMA_CHANNEL, (BUFFER_BLOCK_LENGTH * BLOCK_SIZE_IN_WORDS));
	_dma_set_destination_address(CONF_PCC_DMA_CHANNEL, linkedList[0].DSTADDR.reg); // Overwrite destination address since set_data_amount function modifies this
	_dma_set_next_descriptor(CONF_PCC_DMA_CHANNEL, linkedList[0].DESCADDR.reg)
	
	// To turn on DMA channel: 
	// _dma_enable_transaction(CONF_PCC_DMA_CHANNEL, false);
}


int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	I2C_BB_init();
	
	linkedListInit(); // Sets up a set of circularly linked list for camera DMA.
	
	while (1) {
	}
}
