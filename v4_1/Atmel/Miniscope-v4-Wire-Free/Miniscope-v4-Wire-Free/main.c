#include <atmel_start.h>
#include "sd_mmc.h"

#include "definitions.h"
#include "hpl_dmac_config.h"
#include "hpl_pcc_config.h"

#include "python480.h"
#include "i2c_bb.h"

//#define DEBUG

// ------- SET WIRE-FREE DEVICE TYPE ----
#define MINISCOPE_V4_WF
// --------------------------------------

#define EWL_I2C_ADDR 0x23  //7 bit address!

// ------------ GLOBAL VARIABLES --------
volatile uint32_t dataBuffer[NUM_BUFFERS][BUFFER_BLOCK_LENGTH * BLOCK_SIZE_IN_WORDS]; //Allocate memory for DMA image buffers
volatile uint8_t headerBlock[SD_BLOCK_SIZE] = {0}; // Will hold the 512 bytes from the header block of sd card
volatile uint8_t configBlock[SD_BLOCK_SIZE] = {0}; // Will hold the device config information to be written to the starting block
	
volatile uint32_t currentBlock = STARTING_BLOCK;
volatile uint32_t initBlocksRemaining;

volatile uint32_t deviceState = DEVICE_STATE_IDLE;
volatile DmacDescriptor linkedList[NUM_BUFFERS];

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
volatile uint32_t numBlocks;

// Debugging and checking stuff
volatile uint16_t chip_id; // Reads the chip id from Python480 to make sure we can talk to it
volatile uint16_t regValue[2]; 
// --------------------------------------

// ----------- FUNCTIONS ----------------
uint8_t loadSDCardHeader(void);
uint32_t getPropFromHeader(uint8_t headerPos);
void setConfigBlockProp(uint8_t position, uint32_t value);
void setBufferHeader(uint32_t dataWordLength);

void imageSensorInit(void);
void linkedListInit(void);

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

void setBufferHeader(uint32_t dataWordLength) {
	uint32_t numBuffer = bufferCount % NUM_BUFFERS;
	dataBuffer[numBuffer][BUFFER_HEADER_HEADER_LENGTH_POS] = BUFFER_HEADER_LENGTH;
	dataBuffer[numBuffer][BUFFER_HEADER_FRAME_NUM_POS] = frameNum;
	dataBuffer[numBuffer][BUFFER_HEADER_BUFFER_COUNT_POS] = bufferCount;
	dataBuffer[numBuffer][BUFFER_HEADER_FRAME_BUFFER_COUNT_POS] = frameBufferCount;
	dataBuffer[numBuffer][BUFFER_HEADER_TIMESTAMP_POS] = getCurrentTimeMS() - startTimeMS;
	
	// TODO: Put the correct value for data length. This will change if it is a partially filled buffer
	// UBLEN in XDMAC_CUBC gets decremented by MBSIZE or CSIZE for each memory or chunk transfer. We can calculate from this
	dataBuffer[numBuffer][BUFFER_HEADER_DATA_LENGTH_POS] = dataWordLength * 4; // In bytes
}

static void millisecondTimer_cb(const struct timer_task *const timer_task)
{
	timeMS++;
}

static void checkBattVoltage_cb(const struct timer_task *const timer_task)
{
	uint8_t adcValue;
	// Uses ADC0 to check batt voltage
	adc_sync_read_channel(&ADC_0, 0, &adcValue, 1);
	battVolt = adcValue;
	
	// If under voltage, set device state to ...
	// Compare to 1.1V band gap
	// Battery voltage goes through a 1/5x voltage divider
	
	// Raise issue if voltage is under 3.4V
	// 3.4V = 158
	if (adcValue < 158) {
		// Low voltage problem
		deviceState |= DEVICE_STATE_LOW_VOLTAGE;
	}
}

static void battCharging_cb(void)
{
	bool pinState = gpio_get_pin_level(nCHRG);
	if (pinState == true) {
		// Not charging
		deviceState &= !(DEVICE_STATE_CHARGING);
	}
	else {
		// charging
		deviceState |= DEVICE_STATE_CHARGING;
	}
}

static void irReceive_cb(void)
{
	bool pinState = gpio_get_pin_level(IR_REC);
	if (pinState == true) {
		
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
		
	}
	else {
		setStatusLED(1);
	}
	
	if (pinState == true) {
		// beginning of new frame acquisition
		
	}
	/*
	else {
		if (deviceState == DEVICE_STATE_RECORDING || deviceState == DEVICE_STATE_STOP_RECORDING) {
			// At the end of frame the current buffer is likely only partially filled.
			// Disable DMA to flush DMA FIFO then start DMA again but with the next linked list
			
			imageCaptureDisable();
			imageCaptureDMAStop();
			
			setBufferHeader(BUFFER_BLOCK_LENGTH * BLOCK_SIZE_IN_WORDS - BUFFER_HEADER_LENGTH - (XDMAC->XDMAC_CHID[IMAGE_CAPTURE_XDMAC_CH].XDMAC_CUBC & XDMAC_CUBC_UBLEN_Msk));// Update buffer header
			frameBufferCount = 0;
			bufferCount++; // A buffer has been filled (likely partially) and is ready for writing to SD card
			frameNum++; // Zero-Indexed
			
			if (deviceState == DEVICE_STATE_RECORDING) { // Keep recording
				// Update Linked List
				
				imageCaptureDMAStart((uint32_t)&linkedList[bufferCount % NUM_BUFFERS]);
				imageCaptureEnable();
			}
			if (deviceState == DEVICE_STATE_STOP_RECORDING) {
				// Reset linked lists so we will be ready to start recording again in the future
				linkedListInit();
				deviceState &= !(DEVICE_STATE_RECORDING);
				deviceState &= !(DEVICE_STATE_STOP_RECORDING);
				deviceState |= DEVICE_STATE_IDLE;
			}
		}
		else if (deviceState == DEVICE_STATE_START_RECORDING_WAITING) {
			// We wait till !FV to enable recording so the first buffer starts at the beginning and not middle of a frame
			
			frameNum = 0;
			bufferCount = 0;
			frameBufferCount = 0;
			linkedListInit();
			imageCaptureDMAStart((uint32_t)&linkedList[0]); // Let's always start a new recording at the initialized Linked List 0
			imageCaptureEnable();
			deviceState &= !(DEVICE_STATE_START_RECORDING_WAITING);
			deviceState |= DEVICE_STATE_RECORDING;
		}
	}
	*/
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
		linkedList[i].BTCNT.reg = (BUFFER_BLOCK_LENGTH * BLOCK_SIZE_IN_WORDS);
		// We aren't actually using the STEPSIZE part of incrementing the destination address. 
		linkedList[i].BTCTRL.reg = DMAC_BTCTRL_STEPSIZE(0) | (CONF_DMAC_STEPSEL_0 << DMAC_BTCTRL_STEPSEL_Pos)						\
								| (CONF_DMAC_DSTINC_0 << DMAC_BTCTRL_DSTINC_Pos) | (CONF_DMAC_SRCINC_0 << DMAC_BTCTRL_SRCINC_Pos)	\
								| DMAC_BTCTRL_BEATSIZE(CONF_DMAC_BEATSIZE_0) | DMAC_BTCTRL_BLOCKACT(CONF_DMAC_BLOCKACT_0)            \
								| DMAC_BTCTRL_EVOSEL(CONF_DMAC_EVOSEL_0);
	
		linkedList[i].SRCADDR.reg = (uint32_t)(&PCC->RHR.reg);
		// Destination address when incrementing address needs to be the end address and not the start address.
		linkedList[i].DSTADDR.reg = (uint32_t)(&dataBuffer[i][BUFFER_HEADER_LENGTH]) + (BUFFER_BLOCK_LENGTH * BLOCK_SIZE_IN_WORDS) * 4;
	}
	// Set up initial DMA descriptor for DMA channel handling PCC. BTCNT is already setup in DMA init step
	_dma_set_source_address(CONF_PCC_DMA_CHANNEL, linkedList[0].SRCADDR.reg);
	_dma_set_destination_address(CONF_PCC_DMA_CHANNEL, linkedList[0].DSTADDR.reg);
	_dma_set_data_amount(CONF_PCC_DMA_CHANNEL, (BUFFER_BLOCK_LENGTH * BLOCK_SIZE_IN_WORDS));
	_dma_set_destination_address(CONF_PCC_DMA_CHANNEL, linkedList[0].DSTADDR.reg); // Overwrite destination address since set_data_amount function modifies this
	_dma_set_next_descriptor(CONF_PCC_DMA_CHANNEL, linkedList[0].DESCADDR.reg);
	
	// To turn on DMA channel: 
	// _dma_enable_transaction(CONF_PCC_DMA_CHANNEL, false);
}

void startRecording()
{
	writeFrameNum = 0;
	writeBufferCount = 0;
	droppedBufferCount = 0;
	droppedFrameCount = 0;
	framesToDrop = 0;
	
	// This gets the next set of blocks ready to be written into
	sd_mmc_init_write_blocks(0, currentBlock, BUFFER_BLOCK_LENGTH * NB_BUFFER_WRITES_PER_CHUNK); 
	initBlocksRemaining = BUFFER_BLOCK_LENGTH * NB_BUFFER_WRITES_PER_CHUNK;
		
	startTimeMS = getCurrentTimeMS();
	
	deviceState &= !(DEVICE_STATE_IDLE);
	deviceState &= !(DEVICE_STATE_START_RECORDING);
	deviceState |= DEVICE_STATE_START_RECORDING_WAITING;
}

void stopRecording()
{
	// TODO: Change status LEDs
	
	// TODO: Update currentBlock maybe to get ready for next recording??
	
	// Write end of recording info to a block
	// TODO: Add more meta data to this (frames dropped?, blocks written?, overall time, data starting block?)!
	configBlock[CONFIG_BLOCK_NUM_BUFFERS_RECORDED_POS] = writeBufferCount;
	configBlock[CONFIG_BLOCK_NUM_BUFFERS_DROPPED_POS] = droppedBufferCount;
	sd_mmc_init_write_blocks(0,STARTING_BLOCK, 1);
	sd_mmc_start_write_blocks(configBlock, 1);
	sd_mmc_wait_end_of_write_blocks(false);
	
	deviceState &= !(DEVICE_STATE_STOP_RECORDING);
	deviceState &= !(DEVICE_STATE_RECORDING);
	deviceState |= DEVICE_STATE_IDLE;
}

void recording()
{
	if (bufferCount > (writeBufferCount + droppedBufferCount)) {
		// This means there are filled buffer(s) ready to be written to SD card
		
		// We need to check if the writing to sd card of data buffers has fallen too far behind where we are at risk
		// of writing overwritten data. We need to detect this and decide what to do in this case
		if (bufferCount > (writeBufferCount + droppedBufferCount + NUM_BUFFERS)) {
			// We  are at risk of at least the current buffer that we want to write to SD card being overflown with new image data
			// We are going to just drop writing the rest of this frame
			
			// Let's figure out how many buffers need to be dropped
			droppedBufferCount += (NUM_BUFFERS - (writeBufferCount + droppedBufferCount) % NUM_BUFFERS);
		}
		else {
			// Actual writing of good buffers
			bufferToWrite = (uint32_t)(&dataBuffer[(writeBufferCount + droppedBufferCount) % NUM_BUFFERS]);
			numBlocks = (bufferToWrite[BUFFER_HEADER_DATA_LENGTH_POS] + (BUFFER_HEADER_LENGTH * 4) + (SD_BLOCK_SIZE - 1)) / SD_BLOCK_SIZE;
			
			bufferToWrite[BUFFER_HEADER_WRITE_BUFFER_COUNT_POS] = writeBufferCount;
			bufferToWrite[BUFFER_HEADER_DROPPED_BUFFER_COUNT_POS] = droppedBufferCount;
			
			if (numBlocks < initBlocksRemaining) {
				// There are enough init blocks for this write
				if (sd_mmc_start_write_blocks(bufferToWrite, numBlocks) != SD_MMC_OK)
					deviceState |= DEVICE_STATE_SDCARD_WRITE_ERROR;
				
				
				initBlocksRemaining -= numBlocks;
				currentBlock += numBlocks;
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
				
				currentBlock += numBlocks - initBlocksRemaining;
				initBlocksRemaining = (BUFFER_BLOCK_LENGTH * NB_BUFFER_WRITES_PER_CHUNK) - (numBlocks - initBlocksRemaining);
				
			}
			writeBufferCount++;
			sd_mmc_wait_end_of_write_blocks(false);
			
		}
		
		if (((getCurrentTimeMS() - startTimeMS) >= getPropFromHeader(HEADER_RECORD_LENGTH_POS) * 1000) & (getPropFromHeader(HEADER_RECORD_LENGTH_POS) != 0)){
			// Recording time has elapsed
			deviceState |= DEVICE_STATE_STOP_RECORDING; // Sets the flag to want to end current recording			
			
		}
		
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

// Bit Bang I2C: Done and working with the HV892 EWL driver
// Linked List: TODO
// Check callbacks working: TODO
// Finish building state machine: TODO
// Set up IR communication: TODO
// Set up EWL configuration and control: TODO
// Optimize power: TODO
// Setup wired USART data connection: TODO
// Enable push button cb to start recording: TODO
// Pushbutton to power up system from battery??: TODO
// Make sure lipo charge callback works: TODO
// Consider putting ADC value and deviceState in frame header: TODO

// ================================================================
int main(void)
{
	uint32_t lastTime = 0;
	bool lastMonitor0 = 0;
	bool thisMonitor0 = 0;
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();	
	// We need to change the PWM mode from MPWM to NPWM because we are using WO[0] as waveform output
	hri_tc_write_WAVE_reg(TC0, TC_WAVE_WAVEGEN_NPWM_Val);	
	// Enable the 3.3V regulator
	gpio_set_pin_level(EN_3V3, true);
	// Enable ADC for checking battery voltage
	adc_sync_enable_channel(&ADC_0, 0);
	
	
	setStatusLED(1);	
	
	
	
	I2C_BB_init();
	
	
	// Setup a timer to count in milliseconds
	TIMER_0_task1.interval = 1; // Need to check this value
	TIMER_0_task1.cb       = millisecondTimer_cb;
	TIMER_0_task1.mode     = TIMER_TASK_REPEAT;
	
	TIMER_0_task2.interval = 1000; // Units are in ms so 1000 should check every 1 second
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
	
	/*
	// Sets up a set of circularly linked list for camera DMA.
	linkedListInit(); 
	*/
	
	// Wait for SD Card and then load config from it
	//while (SD_MMC_OK != sd_mmc_check(0)) {}
	//if (loadSDCardHeader() == MS_SUCCESS)
		//deviceState |= DEVICE_STATE_CONFIG_LOADED;
	//else 
		//deviceState |= DEVICE_STATE_ERROR;
	
	// Setup Image Sensor
	// TODO: Work on minimizing power draw
	// Trigger pin gets init'ed as output low and shouldn't need to be adjusted
	gpio_set_pin_level(RESET_CMOS, 0); // Make sure N_RESET of the PYTHON480 is low for a bit before going high. Shouldn't be needed
	delay_ms(100);
	gpio_set_pin_level(RESET_CMOS, 1);
	delay_us(100); // minimum delay is 10us
	chip_id = spi_BB_Read(0x00); // can use this to make sure MCU can talk to Python480
	python480Init();
	
	
	/*
	// Setup rest of Miniscope
	setEWL(getPropFromHeader(HEADER_EWL_POS));
	setExcitationLED(getPropFromHeader(HEADER_LED_POS), false);	
	python480SetGain(getPropFromHeader(HEADER_GAIN_POS));
	python480SetFPS(getPropFromHeader(HEADER_FRAME_RATE_POS));
	*/
	
	//// Set some parameters in config buffer to be written to SD card at end of recording
	//setConfigBlockProp(CONFIG_BLOCK_WIDTH_POS, WIDTH);
	//setConfigBlockProp(CONFIG_BLOCK_HEIGHT_POS, HEIGHT);
	//setConfigBlockProp(CONFIG_BLOCK_FRAME_RATE_POS, getPropFromHeader(HEADER_FRAME_RATE_POS));
	//setConfigBlockProp(CONFIG_BLOCK_BUFFER_SIZE_POS, BUFFER_BLOCK_LENGTH * SD_BLOCK_SIZE);
	//
	//sd_mmc_init_write_blocks(0, CONFIG_BLOCK, 1);
	//sd_mmc_start_write_blocks(configBlock, 1); // We will re-write this block at the end of recording too
	//sd_mmc_wait_end_of_write_blocks(false);
	
	
	// Just a debugging point for turning on excitation LED
	setExcitationLED(5,1);
	
	while (1) {
		if (deviceState & DEVICE_STATE_START_RECORDING) {
			startRecording();
		}
		if (deviceState & DEVICE_STATE_RECORDING) {
			recording();
		}
		if (deviceState & DEVICE_STATE_STOP_RECORDING) {
			stopRecording();
		}
		
		setEWL(0x33);  //test value. Should we map the 0x01 to 0xFF as a 0-100 scale?
		
		//thisMonitor0 = gpio_get_pin_level(MONITOR0);
		//if ((lastMonitor0 != thisMonitor0) && lastMonitor0 == 0) {
			//
			//if (gpio_get_pin_level(LED_STATUS) == 1) {
				//setStatusLED(0);
			//}
			//else {
				//setStatusLED(1);
			//}
		//}
		//lastMonitor0 = thisMonitor0;
		
		//setStatusLED(gpio_get_pin_level(MONITOR0));
		
		// Used for debugging timers
		//if (timeMS%1000 == 0 && timeMS > (lastTime + 500)) {
			//lastTime = timeMS;
			//if (gpio_get_pin_level(LED_STATUS) == 1) {
				//setStatusLED(0);
				//
			//}
			//else {
				//setStatusLED(1);
			//}
		//// ----------------------------
		//}
	}
}
