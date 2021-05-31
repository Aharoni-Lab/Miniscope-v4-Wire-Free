#include <atmel_start.h>

#include "definitions.h"
#include "hpl_dmac_config.h"
#include "hpl_pcc_config.h"

#include "python480.h"
#include "i2c_bb.h"

// ------- SET WIRE-FREE DEVICE TYPE ----
#define MINISCOPE_V4_WF
// --------------------------------------


// ------------ GLOBAL VARIABLES --------
volatile uint32_t dataBuffer[NUM_BUFFERS][BUFFER_BLOCK_LENGTH * BLOCK_SIZE_IN_WORDS]; //Allocate memory for DMA image buffers
volatile uint8_t headerBlock[SD_BLOCK_SIZE] = {0}; // Will hold the 512 bytes from the header block of sd card
volatile uint8_t configBlock[SD_BLOCK_SIZE] = {0}; // Will hold the device config information to be written to the starting block
	
volatile uint32_t currentBlock = STARTING_BLOCK;
volatile uint32_t initBlocksRemaining;

volatile uint8_t deviceState = DEVICE_STATE_IDLE;
volatile DmacDescriptor linkedList[NUM_BUFFERS];

volatile uint32_t frameNum = 0;
volatile uint32_t bufferCount = 0;
volatile uint32_t frameBufferCount = 0;

volatile uint32_t startTimeMS;
volatile uint32_t timeMS = 0;

static struct timer_task TIMER_0_task1, TIMER_0_task2;
// --------------------------------------

// ----------- FUNCTIONS ----------------
void imageSensorInit(void);
void linkedListInit(void);

void setExcitationLED(uint8_t value, bool enable);
void setEWL(uint8_t value);
void setStatusLED(bool value);

// call backs
static void millisecondTimer_cb(const struct timer_task *const timer_task);
static void checkBattVoltage_cb(const struct timer_task *const timer_task);
// --------------------------------------

static void millisecondTimer_cb(const struct timer_task *const timer_task)
{
	timeMS++;
}

static void checkBattVoltage_cb(const struct timer_task *const timer_task)
{
	// Uses ADC0 to check batt voltage
	
	// If undervoltage set device state to ...
}

void setExcitationLED(uint8_t value, bool enable)
{
	uint32_t period = 10000;
	
	if (value > 100)
		value = 100;
	uint32_t duty = (period * value ) / 100; // Might need to invert this
	
	pwm_set_parameters(&PWM_0, period, duty); // period and duty cycle
	pwm_enable(&PWM_0);
	
	gpio_set_pin_level(ENT_LED, enable);
}

void setEWL(uint8_t value)
{

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


int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	// Enable the 3.3V regulator
	gpio_set_pin_level(EN_3V3, true);

	I2C_BB_init();
	
	linkedListInit(); // Sets up a set of circularly linked list for camera DMA.
	
	// Setup a timer to count in milliseconds
	TIMER_0_task1.interval = 100; // Need to check this value
	TIMER_0_task1.cb       = millisecondTimer_cb;checkBattVoltage_cb
	TIMER_0_task1.mode     = TIMER_TASK_REPEAT;
	
	TIMER_0_task2.interval = 100000; // Need to check this value
	TIMER_0_task2.cb       = checkBattVoltage_cb
	TIMER_0_task2.mode     = TIMER_TASK_REPEAT;
	
	timer_add_task(&TIMER_0, &TIMER_0_task1);
	timer_add_task(&TIMER_0, &TIMER_0_task2);
	timer_start(&TIMER_0);
		
	// Wait for SD Card and then load config from it
	
	// Setup Image Sensor
	// TODO: Work on minimizing power draw
	python480Init();
	python480SetGain(1);
	python480SetFPS(20);
	
	// Setup rest of Miniscope
	setEWL(100);
	setExcitationLED(10, 0);
	
	while (1) {
	}
}
