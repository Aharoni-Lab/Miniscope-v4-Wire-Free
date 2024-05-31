#include <atmel_start.h>
#include "sd_mmc.h"

#include "definitions.h"
#include "hpl_dmac_config.h"
#include "hpl_pcc_config.h"

#include "hpl_dma.h"

#include "python480.h"
#include "i2c_bb.h"

//#define DEBUG

#define ADMA_ENABLE

// ------- SET WIRE-FREE DEVICE TYPE ----
#define MINISCOPE_V4_WF
// --------------------------------------

#define EWL_I2C_ADDR 0x23  //7 bit address!

// ------------ GLOBAL VARIABLES --------
COMPILER_ALIGNED(4)
volatile uint32_t dataBuffer[NUM_BUFFERS][BUFFER_BLOCK_LENGTH * BLOCK_SIZE_IN_WORDS]; //Allocate memory for DMA image buffers

volatile uint8_t headerBlock[SD_BLOCK_SIZE] = {0}; // Will hold the 512 bytes from the header block of sd card
volatile uint8_t configBlock[SD_BLOCK_SIZE] = {0}; // Will hold the device config information to be written to the starting block
	
volatile uint32_t currentBlock = STARTING_BLOCK;
volatile uint32_t initBlocksRemaining = 0;

volatile uint32_t deviceState = DEVICE_STATE_IDLE;

COMPILER_ALIGNED(16) // Taken from hpl_dmac.c but I think this could be '8' since descriptors need to be 64bit aligned from data sheet
volatile DmacDescriptor linkedList[NUM_BUFFERS];

// Probably should turn this into a struct to be more easily understandable
volatile uint64_t SDTransferDescriptor; // I think we will only use 1 of these for now. Each descriptor is 64bits long 

volatile uint32_t frameNum = 0;
volatile uint32_t bufferCount = 0;
volatile uint32_t frameBufferCount = 0;

volatile uint32_t startTimeMS;
volatile uint32_t timeMS = 0;

volatile uint8_t battVolt;

static struct timer_task TIMER_0_task1, TIMER_0_task2;

// used for tracking recording and inc. DMA buffers
volatile uint32_t writeFrameNum;
volatile uint32_t writeBufferCount;
volatile uint32_t droppedBufferCount;
volatile uint32_t droppedFrameCount;
volatile uint32_t framesToDrop;
volatile uint32_t *bufferToWrite;
volatile uint32_t numBlocks = BUFFER_BLOCK_LENGTH;
volatile uint32_t numBuffersPerFrame = 0; 

// Debugging and checking stuff
volatile uint16_t chip_id; // Reads the chip id from Python480 to make sure we can talk to it
volatile uint32_t ewlvalue;
volatile uint32_t batteryvalue;
volatile uint32_t ledvalue; 
volatile uint32_t frameratevalue;
volatile uint32_t delayvalue;
volatile uint32_t reclengthvalue;

//Variables for EWL scan

volatile uint16_t ewlSCan_Mode;
volatile uint16_t ewlStart;
volatile uint16_t ewlStop; 
volatile uint16_t ewlStep;
volatile uint16_t ewlStepTime;
volatile uint32_t ewlCount = 0;


volatile uint16_t regValue[2]; 
volatile uint32_t tempPCC[4];
volatile uint32_t tempHeader[100][4];
volatile uint32_t tempCount = 0;
volatile uint32_t tempTimestamp[100];
volatile uint8_t timerIndex = 0;
// --------------------------------------

// ----------- FUNCTIONS ----------------
uint8_t loadSDCardHeader(void);
uint32_t getPropFromHeader(uint8_t headerPos);
void setConfigBlockProp(uint8_t position, uint32_t value);
void setBufferHeader(uint32_t dataWordLength);

void setSDDescriptor(uint32_t *address, uint16_t length, uint8_t attribute);

void imageSensorInit(void);
void linkedListInit(void);
void setPCCCurrentLinkedListPosition(uint8_t pos);

void setExcitationLED(uint32_t value, bool enable);
void setEWL(uint32_t value);
void setStatusLED(bool value);

void startRecording();
void stopRecording();
void recording();

uint32_t getCurrentTimeMS(void);
// callbacks
static void millisecondTimer_cb(const struct timer_task *const timer_task);
static void checkBattVoltage_cb(const struct timer_task *const timer_task);

static void battCharging_cb(void);
static void irReceive_cb(void);
static void pushButton_cb(void);
static void frameValid_cb(void);
// --------------------------------------
uint32_t getCurrentTimeMS(void)
{
	return timeMS;
}

uint8_t loadSDCardHeader(void){
	sd_mmc_init_read_blocks(0,HEADER_BLOCK,1);
	sd_mmc_start_read_blocks(headerBlock,1);
	if (sd_mmc_wait_end_of_read_blocks(false) == SD_MMC_OK)
		return MS_SUCCESS;
	else 
		return MS_ERROR;
}

uint32_t getPropFromHeader(uint8_t headerPos) {
	uint32_t *header32bit = (uint32_t *)headerBlock;
	
	return header32bit[headerPos];
}

void setConfigBlockProp(uint8_t position, uint32_t value) {
	uint32_t *configBlock32bit = (uint32_t *)configBlock;
	
	configBlock32bit[position] = value;
}

//void setEWLScanProp(uint8_t startPlane, uint8_t endPlane, uint8_t stepSize ) {
//	uint32_t *configBlock32bit = (uint32_t *)configBlock;
	
//	configBlock32bit[position] = value;
//}

void setBufferHeader(uint32_t dataWordLength) {
	uint32_t numBuffer = bufferCount % NUM_BUFFERS;
	dataBuffer[numBuffer][BUFFER_HEADER_HEADER_LENGTH_POS] = BUFFER_HEADER_LENGTH;
	dataBuffer[numBuffer][BUFFER_HEADER_LINKED_LIST_POS] = bufferCount % NUM_BUFFERS;
	dataBuffer[numBuffer][BUFFER_HEADER_FRAME_NUM_POS] = frameNum;
	dataBuffer[numBuffer][BUFFER_HEADER_BUFFER_COUNT_POS] = bufferCount;
	dataBuffer[numBuffer][BUFFER_HEADER_FRAME_BUFFER_COUNT_POS] = frameBufferCount;
	dataBuffer[numBuffer][BUFFER_HEADER_WRITE_BUFFER_COUNT_POS] = writeBufferCount;   
	dataBuffer[numBuffer][BUFFER_HEADER_DROPPED_BUFFER_COUNT_POS] = droppedBufferCount; 
	dataBuffer[numBuffer][BUFFER_HEADER_TIMESTAMP_POS] = getCurrentTimeMS() - startTimeMS;
	dataBuffer[numBuffer][BUFFER_HEADER_BATTERY_POS] = battVolt; 
	dataBuffer[numBuffer][BUFFER_HEADER_EWL_POS] = ewlvalue;
	
	// TODO: Put the correct value for data length. This will change if it is a partially filled buffer
	// UBLEN in XDMAC_CUBC gets decremented by MBSIZE or CSIZE for each memory or chunk transfer. We can calculate from this
	dataBuffer[numBuffer][BUFFER_HEADER_DATA_LENGTH_POS] = dataWordLength * 4; // In bytes
}

void setSDDescriptor(uint32_t *address, uint16_t length, uint8_t attribute)
// address holds the pointer location to the front of a data buffer
// Length is in bytes
// attribute holds the lower 6 bits of the descriptor table
{
	uint64_t temp = address;
	temp = temp<<32;
	SDTransferDescriptor = (temp)|attribute|SD_DESCRIPTOR_LENGTH(length);
}

static void millisecondTimer_cb(const struct timer_task *const timer_task)
{
	timeMS++;
}

static void checkBattVoltage_cb(const struct timer_task *const timer_task)
{
	uint8_t adcValue;
	uint8_t i;
	uint16_t sum = 0;
	uint16_t num[8];
	
	// Uses ADC0 to check battery voltage
	adc_sync_read_channel(&ADC_0, 0, &adcValue,1);
	battVolt = adcValue;
	
	//for (i = 0; i < 8; ++i) {
    //    sum += num[i];
	//}
	
	//average = sum/8;
	
	// If under voltage, set device state to ...
	// Compare to 1.1V band gap
	// Battery voltage goes through a 1/5x voltage divider
	// ADCvalue = ((1/5*Vsample)/1.1)*255
	
	// Raise issue if voltage is under 3.4V
	// 3.4V = 158
	// 3.3V = 148
	if (adcValue < 0) {   //140
		// Low voltage problem
		deviceState |= DEVICE_STATE_LOW_VOLTAGE;
		deviceState |= DEVICE_STATE_STOP_RECORDING;
	}
}

static void battCharging_cb(void)
{
	bool pinState = gpio_get_pin_level(nCHRG);
	if (pinState == true) {
		// Not charging
		while(deviceState &= ~(DEVICE_STATE_CHARGING)){
					gpio_toggle_pin_level(LED_STATUS);
					delay_ms(5000);
		}
		}

	else {
		// charging
		while(deviceState |= DEVICE_STATE_CHARGING){
		gpio_toggle_pin_level(LED_STATUS);
		delay_ms(250);
		}
	}
}

static void irReceive_cb(void)
{
	bool pinState = gpio_get_pin_level(IR_REC);
	if (pinState == true) {
		delay_ms(13); //13 ms after the pin gets high we check if there is a 0
		if (gpio_get_pin_level(IR_REC) == false) {
			   for( uint8_t i = 0; i < delayvalue; i++ ){
					gpio_toggle_pin_level(LED_STATUS);
					delay_ms(1000);
				}
		deviceState = DEVICE_STATE_START_RECORDING;		
		}
		
		else{}
	
	}
	else {
		
	}	
}

static void pushButton_cb(void)
{
	bool pinState = gpio_get_pin_level(PUSH_BUT_MCU);
	if (pinState == true) {
		
	}
	else {
		
	}
}

static void frameValid_cb(void)
{
	bool pinState = gpio_get_pin_level(FrameValid);
	
	if (gpio_get_pin_level(LED_STATUS) == 1) {
		setStatusLED(0);
		//
	}
	else {
		setStatusLED(1);
	}
	
	if (pinState == true) {
		// beginning of new frame acquisition
		
	}
	else {
		// Handles end of frame
		
		if (deviceState & (DEVICE_STATE_RECORDING | DEVICE_STATE_STOP_RECORDING)) {
			// At the end of frame the current buffer is likely only partially filled.
			// Disable DMA to flush DMA FIFO then start DMA again but with the next linked list
			
			PCC->MR.reg &= ~(PCC_MR_PCEN); // Disables PCC
			
			DMAC->Channel[CONF_PCC_DMA_CHANNEL].CHCTRLA.reg &= ~(DMAC_CHCTRLA_ENABLE); // Disables PCC DMA
			
			// Some debugging stuff here
			//tempHeader[tempCount][0] = frameNum;
			//tempHeader[tempCount][1] = bufferCount;
			//tempHeader[tempCount][2] = 4 * _dma_get_WRB_data(CONF_PCC_DMA_CHANNEL);
			//tempHeader[tempCount][3] = PCC->ISR.reg;;		
			//if (tempCount < 99)
				//tempCount++;
			
			setBufferHeader((BUFFER_BLOCK_LENGTH * BLOCK_SIZE_IN_WORDS - BUFFER_HEADER_LENGTH) - _dma_get_WRB_data(CONF_PCC_DMA_CHANNEL)); // This should get total beats transferred through DMA
	
			frameBufferCount = 0;
			bufferCount++; // A buffer has been filled (likely partially) and is ready for writing to SD card
			frameNum++; // Zero-Indexed
			
			if (deviceState & DEVICE_STATE_RECORDING) { // Keep recording
				// Update Linked List
				setPCCCurrentLinkedListPosition(bufferCount % NUM_BUFFERS); // Moves to next buffer/linked list element
				_dma_enable_transaction(CONF_PCC_DMA_CHANNEL, false); // Should enable DMA transfer
	
				PCC->MR.reg |= PCC_MR_PCEN; // Enables PCC
			}
			if (deviceState & DEVICE_STATE_STOP_RECORDING) {
				// Reset linked lists so we will be ready to start recording again in the future
				
				//deviceState &= ~(DEVICE_STATE_RECORDING);
				//deviceState &= ~(DEVICE_STATE_STOP_RECORDING);
				//deviceState |= DEVICE_STATE_IDLE;
			}
		}
		else if (deviceState & DEVICE_STATE_START_RECORDING_WAITING) {
			// We wait till !FV to enable recording so the first buffer starts at the beginning and not middle of a frame
			
			frameNum = 0;
			bufferCount = 0;
			frameBufferCount = 0;
			
			linkedListInit();
			setPCCCurrentLinkedListPosition(0); // Moves to next buffer/linked list element
			_dma_enable_transaction(CONF_PCC_DMA_CHANNEL, false); // Should enable DMA transfer
		
			PCC->MR.reg |= PCC_MR_PCEN; // Enables PCC
	
			deviceState &= ~(DEVICE_STATE_START_RECORDING_WAITING);
			deviceState |= DEVICE_STATE_RECORDING;
		}
	}
}

static void pcc_dma_cb(struct camera_async_descriptor *const descr, uint32_t ch)
{
	if (ch == CONF_PCC_DMA_CHANNEL) {
		
		// add header to current buffer
		
		// Some debugging stuff here
		//tempHeader[tempCount][0] = frameNum;
		//tempHeader[tempCount][1] = bufferCount;
		//tempHeader[tempCount][2] = 4 * _dma_get_WRB_data(CONF_PCC_DMA_CHANNEL);
		//tempHeader[tempCount][3] = PCC->ISR.reg;
		//if (tempCount < 99)
			//tempCount++;
			
		setBufferHeader(BUFFER_BLOCK_LENGTH * BLOCK_SIZE_IN_WORDS - BUFFER_HEADER_LENGTH);
		bufferCount++;// increment counters
		frameBufferCount++;
	}
}

void setExcitationLED(uint32_t value, bool enable)
{
	// Value is a percentage of brightness from 0 to 100.
	// PWM runs at 1ms period using 16bit MAX counter and a ~60MHz clock	
	if (value > 100)
		value = 100;
	
	value = (0xFFFF * value ) /100;
	
	pwm_set_parameters(&PWM_0, value, 0); // value sets duty cycle out of 2^16. We aren't using CC1 so just send it 0
	pwm_enable(&PWM_0); //Only actually needs to be done once. Consider moving to init stuff at top of main()
	
	gpio_set_pin_level(ENT_LED, enable);
}

void setEWL(uint32_t value)
{
	I2C_BB_write(EWL_I2C_ADDR,value);
}

void setStatusLED(bool value)
{
	gpio_set_pin_level(LED_STATUS, value);
}

void linkedListInit(void)
{
	for (uint8_t i = 0; i < NUM_BUFFERS; i++) {
		if (i == (NUM_BUFFERS - 1))
			// Last buffer in list. Need to loop back
			linkedList[i].DESCADDR.reg = (uint32_t)&linkedList[0];
		else
			linkedList[i].DESCADDR.reg = (uint32_t)&linkedList[i + 1];
			
		linkedList[i].BTCNT.reg = (BUFFER_BLOCK_LENGTH * BLOCK_SIZE_IN_WORDS - BUFFER_HEADER_LENGTH);
		// We aren't actually using the STEPSIZE part of incrementing the destination address. 
		linkedList[i].BTCTRL.reg = DMAC_BTCTRL_STEPSIZE(0) | (CONF_DMAC_STEPSEL_0 << DMAC_BTCTRL_STEPSEL_Pos)						\
								| (CONF_DMAC_DSTINC_0 << DMAC_BTCTRL_DSTINC_Pos) | (CONF_DMAC_SRCINC_0 << DMAC_BTCTRL_SRCINC_Pos)	\
								| DMAC_BTCTRL_BEATSIZE(CONF_DMAC_BEATSIZE_0) | DMAC_BTCTRL_BLOCKACT(CONF_DMAC_BLOCKACT_0 | 0x01)            \
								| DMAC_BTCTRL_EVOSEL(CONF_DMAC_EVOSEL_0) | DMAC_BTCTRL_VALID;
	
		linkedList[i].SRCADDR.reg = (uint32_t)(&PCC->RHR.reg); //(void *)&(((Pcc *)device->hw)->RHR.reg)
		
		// Destination address when incrementing address needs to be the end address and not the start address.
		// I think the last scale multiplication needs to be either 3 or 5 but _dma_set_data_amount() uses a 4.
		linkedList[i].DSTADDR.reg = (uint32_t)(&dataBuffer[i][BUFFER_HEADER_LENGTH]) + linkedList[i].BTCNT.reg * 4;
	}
	//setPCCCurrentLinkedListPosition(0);
}
void setPCCCurrentLinkedListPosition(uint8_t pos)
{
	// Set up initial DMA descriptor for DMA channel handling PCC. BTCNT is already setup in DMA init step
	_dma_set_source_address(CONF_PCC_DMA_CHANNEL, (void *)linkedList[pos].SRCADDR.reg);
	_dma_set_destination_address(CONF_PCC_DMA_CHANNEL, (void *)linkedList[pos].DSTADDR.reg);
	_dma_set_data_amount(CONF_PCC_DMA_CHANNEL, (void *)linkedList[pos].BTCNT.reg);
	_dma_set_BTCTRL(CONF_PCC_DMA_CHANNEL, (void *)linkedList[pos].BTCTRL.reg);
	_dma_set_destination_address(CONF_PCC_DMA_CHANNEL, (void *)linkedList[pos].DSTADDR.reg); // Overwrite destination address since set_data_amount function modifies this

	_dma_set_DESCADDR(CONF_PCC_DMA_CHANNEL, linkedList[pos].DESCADDR.reg);
}

void startRecording()
{
	writeFrameNum = 0;
	writeBufferCount = 0;
	droppedBufferCount = 0;
	droppedFrameCount = 0;
	framesToDrop = 0;
	
	// This gets the next set of blocks ready to be written into
	#ifndef ADMA_ENABLE
	sd_mmc_init_write_blocks(0, currentBlock, BUFFER_BLOCK_LENGTH * NB_BUFFER_WRITES_PER_CHUNK); 
	initBlocksRemaining = BUFFER_BLOCK_LENGTH * NB_BUFFER_WRITES_PER_CHUNK;
	#endif // not ADMA_ENABLE
		
	startTimeMS = getCurrentTimeMS();
	
	setEWL(getPropFromHeader(HEADER_EWL_POS));
	setExcitationLED(getPropFromHeader(HEADER_LED_POS), 1);	
	python480SetGain(getPropFromHeader(HEADER_GAIN_POS));
	python480SetFPS(getPropFromHeader(HEADER_FRAME_RATE_POS));
	setStatusLED(1);
	
	deviceState &= ~(DEVICE_STATE_IDLE);
	deviceState &= ~(DEVICE_STATE_START_RECORDING);
	deviceState |= DEVICE_STATE_START_RECORDING_WAITING;
	
	
}

void stopRecording()
{
	
	deviceState &= ~(DEVICE_STATE_STOP_RECORDING);
	deviceState &= ~(DEVICE_STATE_RECORDING);
	deviceState |= DEVICE_STATE_IDLE;
	
	// Must be a better way of doing this. This finishes up the remaining init blocks so we can then write to the config block
	
	#ifndef ADMA_ENABLE
	while (initBlocksRemaining > BUFFER_BLOCK_LENGTH) {
		if (sd_mmc_start_write_blocks(dataBuffer[0], BUFFER_BLOCK_LENGTH) != SD_MMC_OK)
			deviceState |= DEVICE_STATE_SDCARD_WRITE_ERROR;
		initBlocksRemaining -= BUFFER_BLOCK_LENGTH;				
		sd_mmc_wait_end_of_write_blocks(false);
	}
	if (initBlocksRemaining > 0) {
		if (sd_mmc_start_write_blocks(dataBuffer[0], initBlocksRemaining) != SD_MMC_OK)
			deviceState |= DEVICE_STATE_SDCARD_WRITE_ERROR;
		initBlocksRemaining = 0;			
		sd_mmc_wait_end_of_write_blocks(false);
	}
	#endif // not ADMA_ENABLE
				
	//sd_mmc_wait_end_of_write_blocks(true); // Abort any initalized write blocks
	// TODO: Change status LEDs
	
	// TODO: Update currentBlock maybe to get ready for next recording??
	
	// Write end of recording info to a block
	// TODO: Add more meta data to this (frames dropped?, blocks written?, overall time, data starting block?)!
	setConfigBlockProp(CONFIG_BLOCK_NUM_BUFFERS_RECORDED_POS, writeBufferCount);
	setConfigBlockProp(CONFIG_BLOCK_NUM_BUFFERS_DROPPED_POS, droppedBufferCount);
	
	// Currently not using ADMA. Might consider switching everything over to ADMA to be consistent
	sd_mmc_init_write_blocks(0,CONFIG_BLOCK, 1);
	sd_mmc_start_write_blocks(configBlock, 1);
	sd_mmc_wait_end_of_write_blocks(false);
	
	setExcitationLED(0, false);
	setEWL(0x00);	//Sets the EWL to standby mode
	setStatusLED(0);	
	
}

void recording()
{
	
	setStatusLED(1);
	if (bufferCount > (writeBufferCount + droppedBufferCount)) {
		// This means there are filled buffer(s) ready to be written to SD card
		
		// We need to check if the writing to sd card of data buffers has fallen too far behind where we are at risk
		// of writing overwritten data. We need to detect this and decide what to do in this case
		if (bufferCount > (writeBufferCount + droppedBufferCount + NUM_BUFFERS)) {
			// We  are at risk of at least the current buffer that we want to write to SD card being overflown with new image data
			// We are going to just drop writing the rest of this frame
			
			// Let's figure out how many buffers need to be dropped
			// TODO: I think NUM_BUFFERS here should actually be number_of_buffers_per_frame
			droppedBufferCount += (numBuffersPerFrame - (writeBufferCount + droppedBufferCount) % numBuffersPerFrame);
		}
		else {
			// Actual writing of good buffers
			bufferToWrite = (uint32_t)(&dataBuffer[(writeBufferCount + droppedBufferCount) % NUM_BUFFERS]);
			numBlocks = (bufferToWrite[BUFFER_HEADER_DATA_LENGTH_POS] + (BUFFER_HEADER_LENGTH * 4) + (SD_BLOCK_SIZE - 1)) / SD_BLOCK_SIZE;
			
			// This if statement shouldn't be needed
			if (numBlocks > BUFFER_BLOCK_LENGTH)
				numBlocks = BUFFER_BLOCK_LENGTH;
				
			bufferToWrite[BUFFER_HEADER_WRITE_BUFFER_COUNT_POS] = writeBufferCount;
			bufferToWrite[BUFFER_HEADER_DROPPED_BUFFER_COUNT_POS] = droppedBufferCount;
			bufferToWrite[BUFFER_HEADER_WRITE_TIMESTAMP_POS] = getCurrentTimeMS() - startTimeMS;
			
			tempTimestamp[(writeBufferCount + droppedBufferCount) % 100] = getCurrentTimeMS() - startTimeMS;
			
			#ifdef ADMA_ENABLE
			// Sets up ADMA descriptor for writing 1 full buffer
			setSDDescriptor(bufferToWrite, numBlocks * SD_BLOCK_SIZE, 
							SD_DESCRIPTOR_ATT_TRANSFER|SD_DESCRIPTOR_ATT_VALID|SD_DESCRIPTOR_ATT_END);
			
			
			sd_mmc_write_with_ADMA(0, currentBlock, (uint32_t)&SDTransferDescriptor, numBlocks);
			
			
			sd_mmc_wait_end_of_ADMA_write(false);
			currentBlock += numBlocks;
			
			
			
			#else // not ADMA_ENABLE
			if (numBlocks < initBlocksRemaining) {
				// There are enough init blocks for this write
				if (sd_mmc_start_write_blocks(bufferToWrite, numBlocks) != SD_MMC_OK)
					deviceState |= DEVICE_STATE_SDCARD_WRITE_ERROR;
				sd_mmc_wait_end_of_write_blocks(false);
				
				initBlocksRemaining -= numBlocks;
				currentBlock += numBlocks;
			}
			else if (numBlocks == initBlocksRemaining)
			{
				if (sd_mmc_start_write_blocks(bufferToWrite, numBlocks) != SD_MMC_OK)
					deviceState |= DEVICE_STATE_SDCARD_WRITE_ERROR;
				sd_mmc_wait_end_of_write_blocks(false);
				currentBlock += numBlocks;
				
				if (sd_mmc_init_write_blocks(0, currentBlock, BUFFER_BLOCK_LENGTH * NB_BUFFER_WRITES_PER_CHUNK) != SD_MMC_OK)
					deviceState |= DEVICE_STATE_SDCARD_WRITE_ERROR;
				
				initBlocksRemaining = (BUFFER_BLOCK_LENGTH * NB_BUFFER_WRITES_PER_CHUNK);
			}
			else {
				// TODO: error checking with LED showing status
				
				// This finishes up the remaining blocks in the current set of initialized blocks
				if (sd_mmc_start_write_blocks(bufferToWrite, initBlocksRemaining) != SD_MMC_OK)
					deviceState |= DEVICE_STATE_SDCARD_WRITE_ERROR;				
				sd_mmc_wait_end_of_write_blocks(false);
				currentBlock += initBlocksRemaining;
				
				// We now initialize the next set of blocks
				// TODO: Probably handle errors better here and don't go forward with writing if init fails
				if (sd_mmc_init_write_blocks(0, currentBlock, BUFFER_BLOCK_LENGTH * NB_BUFFER_WRITES_PER_CHUNK) != SD_MMC_OK)
					deviceState |= DEVICE_STATE_SDCARD_INIT_WRITE_ERROR;
				
				// And write remaining data from buffer
				if (sd_mmc_start_write_blocks((uint32_t)(&bufferToWrite[initBlocksRemaining * SD_BLOCK_SIZE / 4]), numBlocks - initBlocksRemaining) != SD_MMC_OK)
					deviceState |= DEVICE_STATE_SDCARD_WRITE_ERROR;
				sd_mmc_wait_end_of_write_blocks(false);
				
				currentBlock += numBlocks - initBlocksRemaining;
				initBlocksRemaining = (BUFFER_BLOCK_LENGTH * NB_BUFFER_WRITES_PER_CHUNK) - (numBlocks - initBlocksRemaining);
				
			}
			#endif // not ADMA_ENABLE
			
			writeBufferCount++;	
		}
		//Code for demonstration
		//I jump through three planes using the EWL and different LED values
		//if (((getCurrentTimeMS() - startTimeMS) < 6*1000*10
		//)){
			//if((getCurrentTimeMS() - startTimeMS)<5*1000*2.5)
			//{
				//setExcitationLED(1,1);
				//setEWL(0x20);
			//}
			////num >= lower && num <= upper
			////else if(2*1000*2.5<=(getCurrentTimeMS() - startTimeMS)<2*1000*5)
			//else if((getCurrentTimeMS() - startTimeMS)>=5*1000*2.5 && (getCurrentTimeMS() - startTimeMS)<=5*1000*5)
			//{
				////setExcitationLED(5,1);
				//setExcitationLED(2,1);
				//setEWL(0x50);
			//}
			//else if((getCurrentTimeMS() - startTimeMS)>5*1000*5)
			//{
				//setExcitationLED(4,1);
				//
			//}
		//}				
		if (((getCurrentTimeMS() - startTimeMS) >= getPropFromHeader(HEADER_RECORD_LENGTH_POS) * 1000) && (getPropFromHeader(HEADER_RECORD_LENGTH_POS) != 0)){
		// Recording time has elapsed	
			deviceState |= DEVICE_STATE_STOP_RECORDING; // Sets the flag to want to end current recording	
		}
		
		if (((getCurrentTimeMS() - startTimeMS) <= getPropFromHeader(HEADER_RECORD_LENGTH_POS) * 1000) && (getPropFromHeader(HEADER_ewlSCan_Mode_POS) == 1) && (getPropFromHeader(HEADER_RECORD_LENGTH_POS) != 0)){
			//We set a new plane
			if(ewlvalue > 0 && ewlvalue<= 255 && ewlvalue <= ewlStop){  //We make sure that we don't take invalid EWL planes and that we stop at the last value of EWL
					if ((getCurrentTimeMS() - startTimeMS) >= ewlStepTime*1000 *(ewlCount+1)){
					ewlvalue = ewlStart + (ewlCount+1)*ewlStep;
					setEWL(ewlvalue);
					ewlCount++;
					}
			
			}
		}			
		// Code used during testing to record for a fixed, hard-coded lengths 	
		//if (((getCurrentTimeMS() - startTimeMS) >= 1000*15))
		//{

		//	deviceState |= DEVICE_STATE_STOP_RECORDING; // Sets the flag to want to end current recording			
		//}
		
	}
	
}


// ===================== Check list ===============================
// ADC for battery voltage monitoring: Working with ~192 showing full battery
// Status LED control: Working
// PWM excitation LED control: Working using NPWM. Cannot use MPWM unless reroute PCB to use WO1 pin
// Python480 SPI communication: Working
// MCU output clock GCLK1: Working
// Timers to check lipo level and to count in milliseconds: Working
// Verify SDCard interface: Working
// Pushbutton to power up system from battery: Working
// Linked List: Working
// Set up EWL configuration and control: WORKING
// Bit Bang I2C: Done and working with the HV892 EWL driver
// Consider putting ADC value and deviceState in frame header: ADC Value saved on the header
// Set up IR communication: Done. Currently it only triggers the recording
// Make sure lipo charge callback works: Works with LED animations to show that the battery is charging and charged
// Check callbacks working: All working
// EWL scan: done


// Finish building state machine: TODO

// Optimize power: TODO
// Setup wired USART data connection: TODO
// Enable push button cb to start recording: TODO


// Check SD card write speed by directly measuring the clock pin with oscilloscope. Potentially it needs to be sped up: TODO

// ================================================================
int main(void)
{
	uint32_t lastTime = 0;
	bool lastMonitor0 = 0;
	bool thisMonitor0 = 0;
	
	// Probably should put this somewhere else or as a define
	numBuffersPerFrame = (WIDTH * HEIGHT) / (BUFFER_BLOCK_LENGTH * SD_BLOCK_SIZE - (BUFFER_HEADER_LENGTH * 4));
	if ((WIDTH * HEIGHT) % (BUFFER_BLOCK_LENGTH * SD_BLOCK_SIZE - (BUFFER_HEADER_LENGTH * 4)) != 0)
	// Need to add 1 to account for partially filled buffer
		numBuffersPerFrame += 1;
		
	
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();	
	// We need to change the PWM mode from MPWM to NPWM because we are using WO[0] as waveform output
	hri_tc_write_WAVE_reg(TC0, TC_WAVE_WAVEGEN_NPWM_Val);	
	// Enable the 3.3V regulator
	gpio_set_pin_level(EN_3V3, true);
	// Enable ADC for checking battery voltage
	adc_sync_enable_channel(&ADC_0, 0);
	//setStatusLED(1);
	
	//setStatusLED(0);	
	
	I2C_BB_init();
	//setEWL(0xFE);
	//setExcitationLED(2,1);
	
	// Setup a timer to count in milliseconds
	TIMER_0_task1.interval = 1; // Need to check this value
	TIMER_0_task1.cb       = millisecondTimer_cb;
	TIMER_0_task1.mode     = TIMER_TASK_REPEAT;
	
	TIMER_0_task2.interval = 500; // Units are in ms so 1000 should check every 1 second
	TIMER_0_task2.cb       = checkBattVoltage_cb;
	TIMER_0_task2.mode     = TIMER_TASK_REPEAT;
	
	timer_add_task(&TIMER_0, &TIMER_0_task1);
	timer_add_task(&TIMER_0, &TIMER_0_task2);
	timer_start(&TIMER_0);
	
			
	// Setup callbacks for external interrupts
	ext_irq_register(PIN_PB22, irReceive_cb);
	ext_irq_register(PIN_PB23, battCharging_cb);
	ext_irq_register(PIN_PB14, frameValid_cb);
	ext_irq_register(PIN_PA25, pushButton_cb);
	
	
	// Sets up a set of circularly linked list for camera DMA.
	linkedListInit(); 
	
	setStatusLED(0);
	//delay_ms(1000);
	// Wait for SD Card and then load config from it
	//while (SD_MMC_OK != sd_mmc_check(0)) {}
	//	if (loadSDCardHeader() == MS_SUCCESS)
	//		deviceState |= DEVICE_STATE_CONFIG_LOADED;
	//	else
	//		deviceState |= DEVICE_STATE_ERROR;
			
	//delay_ms(5000);
	//setStatusLED(0);
	
	// Give capabilities info of sd card
	tempPCC[0] = SDHC0->CA0R.reg;
	tempPCC[1] = SDHC0->CA1R.reg;
	tempPCC[2] = SDHC0->HC1R.reg;
	
	// Select ADMA as the DMA to use. This should be moved to where other bits of HC1R get set.
	SDHC0->HC1R.reg |= 1<<4;
	
	
	// Setup Image Sensor
	// TODO: Work on minimizing power draw
	// Trigger pin gets init'ed as output low and shouldn't need to be adjusted
	gpio_set_pin_level(RESET_CMOS, 0); // Make sure N_RESET of the PYTHON480 is low for a bit before going high. Shouldn't be needed
	delay_ms(1000);
	gpio_set_pin_level(RESET_CMOS, 1);
	delay_us(1000); // minimum delay is 10us
	chip_id = spi_BB_Read(0x00); // can use this to make sure MCU can talk to Python480
	ewlvalue = getPropFromHeader(HEADER_EWL_POS);
	batteryvalue = getPropFromHeader(HEADER_BATT_CUTOFF_POS);
	ledvalue = getPropFromHeader(HEADER_LED_POS);
	frameratevalue = getPropFromHeader(HEADER_FRAME_RATE_POS);
	delayvalue = getPropFromHeader(HEADER_DELAY_START_POS);
	reclengthvalue = getPropFromHeader(HEADER_RECORD_LENGTH_POS);
	
	//EWL Scan variables 
	
	ewlSCan_Mode = getPropFromHeader(HEADER_ewlSCan_Mode_POS);
	ewlStart = getPropFromHeader(HEADER_ewlStart_POS);
	ewlStop = getPropFromHeader(HEADER_ewlStop_POS);
	ewlStep = getPropFromHeader(HEADER_ewlStep_POS);
	ewlStepTime = getPropFromHeader(HEADER_ewlStepTime_POS);
	
	
	
	python480Init();
	Enable_Subsample();
	chip_id = spi_BB_Read(0x00);
	
	
	// Setup rest of Miniscope
	
	//setEWL(getPropFromHeader(HEADER_EWL_POS));
	//setExcitationLED(getPropFromHeader(HEADER_LED_POS), 1);	
	//python480SetGain(getPropFromHeader(HEADER_GAIN_POS));
	//python480SetFPS(getPropFromHeader(HEADER_FRAME_RATE_POS));
	//python480SetFPS(FRAME_RATE);
	
	// Set some parameters in config buffer to be written to SD card at end of recording
	// TODO: Add additional info in the config block to cover everything needed for offline processing
	setConfigBlockProp(CONFIG_BLOCK_WIDTH_POS, WIDTH / BINNING);
	setConfigBlockProp(CONFIG_BLOCK_HEIGHT_POS, HEIGHT / BINNING);
	setConfigBlockProp(CONFIG_BLOCK_FRAME_RATE_POS, getPropFromHeader(HEADER_FRAME_RATE_POS));
	setConfigBlockProp(CONFIG_BLOCK_BUFFER_SIZE_POS, BUFFER_BLOCK_LENGTH * SD_BLOCK_SIZE);
	setConfigBlockProp(CONFIG_BLOCK_NUM_BUFFERS_RECORDED_POS, 0);
	setConfigBlockProp(CONFIG_BLOCK_NUM_BUFFERS_DROPPED_POS,0);
	
	sd_mmc_init_write_blocks(0, CONFIG_BLOCK, 1);
	sd_mmc_start_write_blocks(configBlock, 1); // We will re-write this block at the end of recording too
	sd_mmc_wait_end_of_write_blocks(false);
	
	
	//setEWL(0x33);  //test value. Should we map the 0x01 to 0xFF as a 0-100 scale?
	
	// Enables DMA Transfer complete interrupt. Should be put in better place
	DMAC->Channel[CONF_PCC_DMA_CHANNEL].CHINTENSET.reg = DMAC_CHINTENSET_TCMPL;
	
	// Sets the callback for when each DMA buffer is full
	camera_async_register_callback(&CAMERA_0, pcc_dma_cb);
	
	// This should already be done in init but trying here as well
	PCC->MR.reg = PCC_MR_CID(0x3) | PCC_MR_ISIZE(CONF_PCC_ISIZE) | CONF_PCC_FRSTS << PCC_MR_FRSTS_Pos
	       | CONF_PCC_HALFS << PCC_MR_HALFS_Pos | CONF_PCC_ALWYS << PCC_MR_ALWYS_Pos
	       | CONF_PCC_SCALE << PCC_MR_SCALE_Pos | PCC_MR_DSIZE(CONF_PCC_DSIZE);
	
	
	// These PCC interrupts aren't needed for DMA functioning	   
	//PCC->IDR.reg = 2;
	//PCC->IER.reg = 3;
	
	//deviceState = DEVICE_STATE_START_RECORDING;
	while (1) {
		if (deviceState & DEVICE_STATE_START_RECORDING) {
			startRecording();
		}
		if (deviceState & DEVICE_STATE_RECORDING) {
			recording();
			//tempPCC[2] = SDHC0->HC1R.reg;
			//tempPCC[0] = PCC->MR.reg;
			//tempPCC[1] = PCC->ISR.reg;
			//tempPCC[2] = PCC->RHR.reg;	
		}
		if (deviceState & DEVICE_STATE_STOP_RECORDING) {
			stopRecording();
		}
	}
}

