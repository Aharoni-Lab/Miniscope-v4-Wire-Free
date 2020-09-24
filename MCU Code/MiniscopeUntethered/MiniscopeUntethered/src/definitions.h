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


// ========== VOLTAGE REGULATOR ========== //
#define VREG_INT		PIO_PD17_IDX


// =========== OTHERS =========== //
#define LED_PIN				PIO_PD19_IDX		// Status LED

#define LED_ENT_PIN			PIO_PA19_IDX		// Excitation LED power on and off. I2C below decides the actual light intensity


/************************************************************************/
/*                           Not Used Anymore                           */
/************************************************************************/

// =========== I2C COMMANDS =========== //
// No 0x00 values
// #define SET_LED1_VALUE	0x01
// #define SET_LED2_VALUE	0x02
// 
// 
// =========== SOURCE CLOCK =========== //
// #define SCK1_PIN		IOPORT_CREATE_PIN(PIOA, 17)
// 
// 
// =========== POWER WIDTH MODULATION ========== //
// FROM MINISCOPEUNTETHERED (PWM stuff) --> For V4, we're using the I2C for this to talk to a potentiometer, so check its datasheet
// #define PWM_LED_PIN		 PIO_PA0_IDX		// Turns on the LED for phosphorus illumination
// #define PWM_LED_MODE	 IOPORT_MODE_MUX_A	// IOPORT_MODE_MUX_A = 0
// #define PWM_LED_CHANNEL  PWM_CHANNEL_0		// PWM_CHANNEL_0 = 0
// #define PWM_FREQUENCY	 1000				// Refer to PWM_init()
// #define PWM_PERIOD_VALUE 255
// #define INIT_DUTY_VALUE  5					// Percentage high per period



#endif /* DEFINITIONS_H_ */