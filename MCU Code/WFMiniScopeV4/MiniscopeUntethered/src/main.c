/**
 * \file
 *
 * \brief Empty user application template
 *
 */

 //Untethered code for E2V Jade CMOS sensor
#include <asf.h>
#include "sdImaging.h"
#include "time_tick.h"

/************************************************************************/
/*                      PARALLEL INPUT OUTPUT                           */
/************************************************************************/
// #include "pio_handler.h"


// ----- GPIO Definitions
#define LED_PIN		PIO_PD1_IDX //Red LED on PCB

#define STANDBY_PIN PIO_PB0_IDX //For E2V Jade Sensor
#define RESETB_PIN	PIO_PB1_IDX //For E2V Jade Sensor
#define TRIG_PIN	PIO_PB2_IDX //For E2V Jade Sensor

#define ENT_PIN		PIO_PB12_IDX //LED Driver enable

// ----- DAC Stuff that can be removed once PWM is made
#define DACC_WPKEY	0x444143
#define DACC_PIN	PIO_PD0_IDX

// ----- PWM Stuff 
//PWM0 PWMC0_PWMH0 PA0 A
#define PWM_LED_PIN		 PIO_PA0_IDX
#define PWM_LED_MODE	 IOPORT_MODE_MUX_A
#define PWM_LED_CHANNEL  PWM_CHANNEL_0
#define PWM_FREQUENCY	 1000
#define PWM_PERIOD_VALUE 255	
#define INIT_DUTY_VALUE  5

// ---- TWI Definitions
#define TWCK_PIN	PIO_PB5_IDX
#define TWCK_MODE	IOPORT_MODE_MUX_A
#define TWD_PIN		PIO_PB4_IDX
#define TWD_MODE	IOPORT_MODE_MUX_A

// ----- Bit Bang Spi ----
#define SPI_BB_MOSI_PIN TWD_PIN
#define SPI_BB_SCK_PIN	TWCK_PIN

//------- DACC for Channel 1 ---------------------------
//void DACC_init();
//void DACC_updateOutput(uint32_t value,uint32_t channel);
//------------------------------------------------------

//------ TWIHS -----------------------------------------
//void TWIHS_init();
//------------------------------------------------------

volatile uint32_t time_ms;
volatile uint32_t tick_start;
volatile uint32_t sdCount = 0;
volatile uint32_t sdCount2 = 0;
volatile uint32_t valueLED = 0; //PWM duty value
volatile uint32_t test[128];

//Holds PWM channel information
pwm_channel_t g_pwm_channel_led;

void PWM_Init() {
	pmc_enable_periph_clk(ID_PWM0);

	matrix_set_system_io(matrix_get_system_io() | CCFG_SYSIO_SYSIO12);
	ioport_set_pin_mode(PWM_LED_PIN,PWM_LED_MODE); //Sets GPIO PIN to PWM Peripheral
	ioport_disable_pin(PWM_LED_PIN);

	pwm_channel_disable(PWM0, PWM_LED_CHANNEL);
	
	pwm_clock_t clock_setting = {
		.ul_clka = PWM_FREQUENCY * PWM_PERIOD_VALUE,
		.ul_clkb = 0,
		.ul_mck = sysclk_get_cpu_hz()/2 //Might need or not need to divide by 2 to get the correct clock
	};

	pwm_init(PWM0, &clock_setting);

	/* Initialize PWM channel for LED0 */
	/* Period is left-aligned */
	g_pwm_channel_led.alignment = PWM_ALIGN_LEFT;
	/* Output waveform starts at a high level */
	g_pwm_channel_led.polarity = PWM_HIGH;
	/* Use PWM clock A as source clock */
	g_pwm_channel_led.ul_prescaler = PWM_CMR_CPRE_CLKA;
	/* Period value of output waveform */
	g_pwm_channel_led.ul_period = PWM_PERIOD_VALUE;
	/* Duty cycle value of output waveform */
	g_pwm_channel_led.ul_duty = INIT_DUTY_VALUE;
	g_pwm_channel_led.channel = PWM_LED_CHANNEL;
	pwm_channel_init(PWM0, &g_pwm_channel_led);

	/* Disable channel counter event interrupt */
	pwm_channel_disable_interrupt(PWM0, PWM_LED_CHANNEL, 0);
	//Enable PWM output
	pwm_channel_enable(PWM0,PWM_LED_CHANNEL);
	
}
void DACC_init() {
	pmc_enable_periph_clk(ID_DACC);
	DACC->DACC_WPMR = DACC_WPKEY<<DACC_WPMR_WPKEY_Pos; //Disables write protection of DAC
	DACC->DACC_CR = DACC_CR_SWRST; //resets the DAC
	DACC->DACC_MR = DACC_MR_MAXS0_TRIG_EVENT|DACC_MR_WORD_DISABLED|DACC_MR_DIFF_DISABLED|DACC_MR_PRESCALER(0);//After reset DACC_MR is set to 0x0000
	DACC->DACC_TRIGR = 0x0000; //Puts DAC in free-running mode. Should already be set to 0x0000 after reset but doing it anyways
	DACC->DACC_CHER = DACC_CHER_CH1; //Enables channel 1 of DACC
	while ((DACC->DACC_CHSR & DACC_CHSR_DACRDY1) != DACC_CHSR_DACRDY1) {
		//wait for DAC channel to be ready to receive data
	}

}

void DACC_updateOutput(uint32_t value,uint32_t channel) {
	while ((DACC->DACC_ISR & DACC_ISR_TXRDY1) != DACC_ISR_TXRDY1) {
		//wait for DACC to be ready to receive new data
	}
	DACC->DACC_CDR[channel] = value&0x0FFF;
}

void TWIHS_init() { //Make sure you have correct TWIHS 
	twihs_options_t twihsOpt;
	twihsOpt.master_clk = sysclk_get_cpu_hz()/2; //make sure this is the correct clock to be checking
	twihsOpt.speed = 100000; //100KHz
	
	//matrix_set_system_io(matrix_get_system_io() | CCFG_SYSIO_SYSIO4 | CCFG_SYSIO_SYSIO5);
	//pmc_enable_periph_clk(ID_PIOB);
	//ioport_set_pin_dir(TWCK_PIN, IOPORT_DIR_INPUT);
	////ioport_set_pin_level(TWCK_PIN, 0);
	//ioport_set_pin_dir(TWD_PIN, IOPORT_DIR_INPUT);
	////ioport_set_pin_level(TWD_PIN, 0);
	//while(1) {
		////tick_start = time_tick_get();
		////while (time_tick_calc_delay(tick_start, time_tick_get()) <10) {}
		////ioport_toggle_pin_level(TWCK_PIN);
		////ioport_toggle_pin_level(TWD_PIN);
//
	//}

	matrix_set_system_io(matrix_get_system_io() | CCFG_SYSIO_SYSIO4 | CCFG_SYSIO_SYSIO5);
	ioport_set_pin_mode(TWCK_PIN,TWCK_MODE);
	ioport_disable_pin(TWCK_PIN);
	ioport_set_pin_mode(TWD_PIN,TWD_MODE);
	ioport_disable_pin(TWD_PIN);

	pmc_enable_periph_clk(ID_TWIHS1);

	twihs_master_init(TWIHS1,&twihsOpt);
	//twihs_enable_master_mode(TWIHS1);
}

void SPI_BitBag_init() {
	pmc_enable_periph_clk(ID_PIOB);
	matrix_set_system_io(matrix_get_system_io() | CCFG_SYSIO_SYSIO4 | CCFG_SYSIO_SYSIO5);
	ioport_set_pin_dir(SPI_BB_MOSI_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(SPI_BB_MOSI_PIN, 0);
	ioport_set_pin_dir(SPI_BB_SCK_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(SPI_BB_SCK_PIN, 0);
}

//////////////////////////////////////////////////
// **************** Test Pins ******************//
#define TEST_PIN_1	PIO_PA3_IDX
#define TEST_PIN_2	PIO_PB4_IDX
#define TEST_PIN_3	PIO_PA4_IDX
#define TEST_PIN_4	PIO_PD3_IDX
#define TEST_PIN_5	PIO_PD4_IDX
#define TEST_PIN_6	PIO_PB6_IDX
#define TEST_PIN_7	PIO_PA6_IDX
#define TEST_PIN_8	PIO_PB7_IDX
// **************** Test Pins ******************//
	
/************************************************************************/
/*                      Data  Bit-banging  Pins                         */
/************************************************************************/
#define SD_CLK		PIO_PA25_IDX
#define SD_PIN_1	PIO_PA31_IDX
#define SD_PIN_2	PIO_PA26_IDX
#define SD_PIN_3	PIO_PA27_IDX
#define SD_PIN_4	PIO_PA30_IDX
#define SD_CONFIG	PIO_PA28_IDX



int main (void)
{
	printf("Let's test if this will work.");
	uint32_t writeNum = 0;
	uint32_t writeFrameNum = 0;
//	WDT->WDT_MR = WDT_MR_WDDIS; //Disables WDT

	//SCB_EnableICache();
	//SCB_EnableDCache();
	
	// Interrupt Management Stuff
	/**
	* \brief Initialize interrupt vectors
	*
	* For NVIC the interrupt vectors are put in vector table. So nothing
	* to do to initialize them, except defined the vector function with
	* right name.
	*
	* This must be called prior to \ref irq_register_handler.
	*/
	
	irq_initialize_vectors();
	cpu_irq_enable();

	sysclk_init();
	board_init(); //Sets up sd card slot pins
	ioport_init(); //turns on all peripheral clocks. could remove this to save power

	//----- CMOS Sensor Stuff
	enableSourceClk(); //Turns on SCK1 from MCU to drive CMOS sensor
	//

	time_tick_init();
	PWM_Init(); // Not sure what this is for
	
	//DACC_init(); //The DAC cannot run at 1.8V. This needs to be replaced with PWM to drive the LED current source
	//DACC_updateOutput(0x0FFF,1);
	
	#ifdef EV76C541
		SPI_BitBag_init();
	#else
		TWIHS_init();
	#endif
	
	tick_start = time_tick_get();
	time_ms = time_tick_calc_delay(tick_start, time_tick_get());

	//----- Enable control of LED
	pmc_enable_periph_clk(ID_PIOD);
	ioport_set_pin_dir(LED_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(LED_PIN, 1);
	//-----
	
	
	//**************************************
	//             CMOS Sensor              //
	/*
	//----- Enable control of sensor control pins (Reset on, standby on, trigger off)
	pmc_enable_periph_clk(ID_PIOB);

	// Reset pin goes off and on
	ioport_set_pin_dir(RESETB_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(RESETB_PIN, 0); //not sure if this can stay high the whole time.

	tick_start = time_tick_get();
	while (time_tick_calc_delay(tick_start, time_tick_get()) <100) {} // wait again. Why do we keep doing this?
	
	ioport_set_pin_level(RESETB_PIN, 1);

	// Standby pin
	ioport_set_pin_dir(STANDBY_PIN, IOPORT_DIR_OUTPUT);
	#ifdef EV76C541
		ioport_set_pin_level(STANDBY_PIN, 1); // This line is used for SPI chip select
	#else
		ioport_set_pin_level(STANDBY_PIN, 0); //Should be low for CMOS to acquire. standby bit at address = 0x0F needs to be set low to run
	#endif

	// Trigger pin
	ioport_set_pin_dir(TRIG_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(TRIG_PIN, 0); //Should be high for CMOS to acquire or can be left 0 and controlled by TWI (address = 0x0F)
	//-----
	*/
	//               CMOS Sensor                //
	//******************************************//

	//******************************************//
	//                 SD Card                  //
	
	sd_mmc_init(); // Initiate SD card slot
	
	// ****SD Card Connection Error Check****
	/*
	sd_mmc_err_t err0;
	sd_mmc_err_t err1;
	sd_mmc_err_t err2;
	card_type_t slot0;
	card_type_t slot1;
	card_type_t slot2;
	int8_t num_slots;
	num_slots = sd_mmc_nb_slot();
	if (num_slots == 0) // num_slot gives 0x01
	{
		ioport_set_pin_level(LED_PIN, 0);
		delay_ms(200);
		ioport_set_pin_level(LED_PIN, 1);
		delay_ms(200);
	}
	
	err0 = sd_mmc_check(SD_SLOT_NB); // this is 0x01 - Card not initialized (0x03 when no card - Unusable card)
	err1 = sd_mmc_check(SD_SLOT_NB + 1); // this is 0x04 - Slot Unknown
	err2 = sd_mmc_check(SD_SLOT_NB + 2);		// this is 0x04 - Slot Unknown
	slot0 = sd_mmc_get_type(SD_SLOT_NB);	// 0x09 - ????? (0x00 when no card)
	slot1 = sd_mmc_get_type(SD_SLOT_NB + 1);// 0x00 - CARD_TYPE_UNKNOWN
	slot2 = sd_mmc_get_type(SD_SLOT_NB + 2);// 0x00
	if (slot0 == slot1 || slot0 == slot2)
	{
		ioport_set_pin_level(LED_PIN, 0);
		delay_ms(200);
		ioport_set_pin_level(LED_PIN, 1);
		delay_ms(200);
	}
	if (err0 == err1 || err0 == err2)
	{
		ioport_set_pin_level(LED_PIN, 0);
		delay_ms(200);
		ioport_set_pin_level(LED_PIN, 1);
		delay_ms(200);
	}
	*/
	// **** End SD Card Error Check ****
	
	// Continue with SD Card...
	// Check if connection is okay
	while (sd_mmc_check(SD_SLOT_NB) != SD_MMC_OK) {} // while the SD connection is NOT okay.. wait --> delete later when Plugin PCB
	
	uint32_t PCB;
	uint32_t SD;
	// Check SD Card Type
	if (sd_mmc_get_type(SD_SLOT_NB) == (CARD_TYPE_SD|CARD_TYPE_HC)) // Bitwise OR --> 9 = 8 + 1
	{
		ioport_set_pin_level(LED_PIN, 0); // If SDHC, turn LED off and on
		ioport_set_pin_level(LED_PIN, 1);
		PCB = 0;
		SD = 1;
		// set MCU = 0 and SD = 1. Do the SD card thing.
	}
	else
	{
		ioport_set_pin_level(LED_PIN, 0); // if not SDHC, turn off LED
		PCB = 1;
		SD = 0;
		// set MCU = 1 and SD = 0. Do the MCU thing.
	}
	
	// If SD card...
	if (SD == 1 && PCB == 0)
	{
		// Get SD card capacity
		uint32_t sdCapacity = sd_mmc_get_capacity(SD_SLOT_NB); //in KB
	
		if (sdCapacity == 0x00ed6600){ // 16GB
			ioport_set_pin_level(LED_PIN, 0);
			ioport_set_pin_level(LED_PIN, 1);
		}
	
		tick_start = time_tick_get();
		while (time_tick_calc_delay(tick_start, time_tick_get()) < 5000) {
			ioport_toggle_pin_level(LED_PIN);
			delay_ms(100);
		}

		// Let's see if this is it
		if (sd_mmc_is_write_protected(SD_SLOT_NB) == true){
		//This is a problem. Maybe turn off the LED
		}
		//-----

	
		//fills imageBuffer location with 0x11003344 a bunch of times
	
		fillBuffer(); // Used for initial testing of SD card writes
	
		/*
		@SD_Slot_NB: Slot number to use
		@Starting_Block: Start block number to be written = 1024(why??), 
		@NB_Blocks_Per_Frame: Total number of blocks to be written. = (total # pixels/subsample) / 512 (Number of bytes in a single block (sector))
		*/
		sd_mmc_init_write_blocks(SD_SLOT_NB,STARTING_BLOCK,NB_BLOCKS_PER_FRAME);
	
		//-------------Loop this by numWritesPerFrame
		/*params
		@imageBuffer: pointer to write buffer 
		@NB_Blocks_..: # of blocks to be written
		*/
		static uint32_t imageBuffer[NUM_PIXEL_WORDS+FRAME_FOOTER_LENGTH];
		sd_mmc_start_write_blocks(&imageBuffer[0],NB_BLOCKS_PER_FRAME);
	
		// Wait the end of write blocks of data (?)
		sd_mmc_wait_end_of_write_blocks(true);
		//-------------
	
		// What does this do..?
		while (1) {
			ioport_toggle_pin_level(LED_PIN);
			testPoint++;
			testPoint++;
			// delay_ms(1000);
			while (time_tick_calc_delay(tick_start, time_tick_get()) < 1000) {}
		}
	}

	// IF MCU Plugin PCB...
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
		
		
	}
	
	return 0;
}
