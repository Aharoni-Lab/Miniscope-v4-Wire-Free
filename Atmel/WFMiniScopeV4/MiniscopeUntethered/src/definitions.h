/*
 * definitions.h
 *
 * Created: 6/11/2019 12:23:41 AM
 *  Author: RWChang
 */ 


#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

// ATSAME SPI package sucks
// =========== BIT-BANGING SPI (ATSAME70N21) =========== //
#define SPI_BB_MOSI		PIO_PD21_IDX
#define SPI_BB_MISO		PIO_PD20_IDX
#define SPI_BB_SCK		PIO_PD22_IDX
#define SPI_BB_SS		PIO_PD25_IDX



// =========== OTHER =========== //
// #define LED_PORT			IOPORT_PIOD
// #define LED_DDR			DDRD
#define LED_PIN				PIO_PD1_IDX

// #define LED_ENT_PORT		IOPORT_PIOA		// This just turns the excitation LED on and off
// #define LED_ENT_DDR		DDRA			// I2C below decides the light intensity
#define LED_ENT_PIN			PIO_PA0_IDX
// #define LED_ENT2_PIN		PB1


// =========== I2C =========== //
// #define TWC_PORT		IOPORT_PIOB			// I2C goes to the LED driver and electro-wetting lens
// #define TWC_DDR		DDRB				// Talks through I2C (So that it can add more components later)
#define TWCK_PIN		PIO_PB5_IDX			// This is SCK
#define TWCK_MODE		IOPORT_MODE_MUX_A
#define TWD_PIN			PIO_PB4_IDX			// This is SDA		// PYTHON480 is SPI
#define TWD_MODE		IOPORT_MODE_MUX_A



// =========== PYTHON480 =========== //
// #define RESET_N_PORT		IOPORT_PIOB
// #define RESET_N_DDR		DDRB
#define RESET_N_PIN			PIO_PB1_IDX

// #define MONITOR_PORT		IOPORT_PIOA
// #define MONITOR_DDR		DDRA
#define MONITOR0_PIN		PIO_PA18_IDX

// #define TRIGGER0_PORT	IOPORT_PIOB
// #define TRIGGER0_DDR		DDRB
#define TRIGGER0_PIN		PIO_PB2_IDX


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
#define TEST_PIN_6	PIO_PB6_IDX
#define TEST_PIN_7	PIO_PA6_IDX
#define TEST_PIN_8	PIO_PB7_IDX


// =========== PLUG-IN BITBANG PINS =========== //
#define SD_CLK		PIO_PA25_IDX
#define SD_PIN_1	PIO_PA31_IDX
#define SD_PIN_2	PIO_PA26_IDX
#define SD_PIN_3	PIO_PA27_IDX
#define SD_PIN_4	PIO_PA30_IDX
#define SD_CONFIG	PIO_PA28_IDX


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

/*
// =========== SPI BITBANG (ATmega328P) =========== //		// This talks to PYTHON480
#define SPI_PORT        PORTD			// Determines default val when input & unconnected. When output, PIN = PORT
#define SPI_SS_PORT		PORTD			// Does this have to be separate?
#define SPI_DDR         DDRD			// DDR (data direction register) determines input(0)/output(1) for each of the 32 pin in the port.
#define SPI_SS_DDR		DDRD			// DDRD is 32 bit but wouldn't the pin direction be 1 bit?
#define MOSI            PIO_PD21		// IDX = index (...)
#define MISO            PIO_PD20		// can I write on the pin register?
#define SCK             PIO_PD22
#define SS              PIO_PD25
*/


#endif /* DEFINITIONS_H_ */