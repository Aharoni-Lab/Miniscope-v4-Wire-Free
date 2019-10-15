/*
 * definitions.h
 *
 * Created: 6/11/2019 12:23:41 AM
 *  Author: RWChang
 */ 


#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_



// =========== PYTHON480 =========== //
#define RESET_N_PIN			PIO_PB1_IDX
#define MONITOR0_PIN		PIO_PA18_IDX
#define TRIGGER0_PIN		PIO_PB2_IDX


// =========== BIT-BANGING SPI (ATSAME70N21) =========== //		// For PYTHON480. ATSAME SPI package sucks
#define SPI_BB_MOSI		PIO_PD21_IDX
#define SPI_BB_MISO		PIO_PD20_IDX
#define SPI_BB_SCK		PIO_PD22_IDX
#define SPI_BB_SS		PIO_PD25_IDX



// =========== OTHER =========== //
#define LED_PIN				PIO_PD19_IDX		// Status LED

#define LED_ENT_PIN			PIO_PA19_IDX		// Excitation LED power on and off. I2C below decides the actual light intensity


// =========== I2C =========== //			
#define TWCK_PIN		PIO_PB5_IDX			// This is SCK
#define TWCK_MODE		IOPORT_MODE_MUX_A	// I2C goes to the LED driver and electro-wetting lens
#define TWD_PIN			PIO_PB4_IDX			// This is SDA
#define TWD_MODE		IOPORT_MODE_MUX_A	// Talks through I2C (So that it can add more components later)


// =========== I2C COMMANDS =========== //
// No 0x00 values
#define SET_LED1_VALUE	0x01
#define SET_LED2_VALUE	0x02


// =========== TEST PINS =========== //
#define TEST_PIN_1	PIO_PA3_IDX
#define TEST_PIN_2	PIO_PB4_IDX
#define TEST_PIN_3	PIO_PA4_IDX
#define TEST_PIN_4	PIO_PD3_IDX
#define TEST_PIN_5	PIO_PD4_IDX
#define TEST_PIN_6	PIO_PD6_IDX
#define TEST_PIN_7	PIO_PD7_IDX
#define TEST_PIN_8	PIO_PD8_IDX


// =========== WIRED EXPANSION BOARD BITBANG PINS =========== //
#define WXB_CLK		PIO_PA25_IDX
#define WXB_PIN_1	PIO_PA31_IDX
#define WXB_PIN_2	PIO_PA26_IDX
#define WXB_PIN_3	PIO_PA27_IDX
#define WXB_PIN_4	PIO_PA30_IDX
#define WXB_CONFIG	PIO_PA28_IDX



/************************************************************************/
/*                           Not Used Anymore                           */
/************************************************************************/

// =========== SOURCE CLOCK =========== //
#define SCK1_PIN		IOPORT_CREATE_PIN(PIOA, 17)


// =========== POWER WIDTH MODULATION ========== //
// FROM MINISCOPEUNTETHERED (PWM stuff) --> For V4, we're using the I2C for this to talk to a potentiometer, so check its datasheet
#define PWM_LED_PIN		 PIO_PA0_IDX		// Turns on the LED for phosphorus illumination
#define PWM_LED_MODE	 IOPORT_MODE_MUX_A	// IOPORT_MODE_MUX_A = 0
#define PWM_LED_CHANNEL  PWM_CHANNEL_0		// PWM_CHANNEL_0 = 0
#define PWM_FREQUENCY	 1000				// Refer to PWM_init()
#define PWM_PERIOD_VALUE 255
#define INIT_DUTY_VALUE  5					// Percentage high per period



#endif /* DEFINITIONS_H_ */