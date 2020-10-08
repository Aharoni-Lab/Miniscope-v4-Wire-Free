/**
 * \file
 *
 * \brief User board definition template
 *
 */

 /* This file is intended to contain definitions and configuration details for
 * features and devices that are available on the board, e.g., frequency and
 * startup time for an external crystal, external memory devices, LED and USART
 * pins.
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef USER_BOARD_H
#define USER_BOARD_H

#include <conf_board.h>

/*----------------------------------------------------------------------------*/
/**
 *  \page External oscillator settings
 *  This page lists several definition related to the board operating frequency
 *
 *  \section Definitions
 *  - \ref BOARD_FREQ_*
 *  - \ref BOARD_MCK
 */

// External oscillator frequency
#define BOARD_XOSC_HZ          12000000

// External oscillator type (Un-comment the appropriate type)
//!< External clock signal
//#define BOARD_XOSC_TYPE        XOSC_TYPE_EXTERNAL
//!< 32.768 kHz resonator on TOSC
//#define BOARD_XOSC_TYPE        XOSC_TYPE_32KHZ
//!< 0.4 to 16 MHz resonator on XTALS
#define BOARD_XOSC_TYPE        XOSC_TYPE_XTAL

/** External oscillator startup time */
#define BOARD_XOSC_STARTUP_US  500000

/*----------------------------------------------------------------------------*/
/**
 *  \page same70_xplained_pro_opfreq "SAME70-XPLD - Operating frequencies"
 *  This page lists several definition related to the board operating frequency
 *
 *  \section Definitions
 *  - \ref BOARD_FREQ_*
 *  - \ref BOARD_MCK
 */

/** Board oscillator settings */
#define BOARD_FREQ_SLCK_XTAL      (32768UL)
#define BOARD_FREQ_SLCK_BYPASS    (32768UL)		// Shouldn't be used
#define BOARD_FREQ_MAINCK_XTAL    (12000000UL)
#define BOARD_FREQ_MAINCK_BYPASS  (12000000UL)	// Shouldn't be used

/** board main clock xtal statup time */
#define BOARD_OSC_STARTUP_US      (15625UL)

/*----------------------------------------------------------------------------*/

/** USART2 pins definitions, PD15, PD16. */
#define USART2_RXD_GPIO   PIO_PD15_IDX
#define USART2_RXD_FLAGS  IOPORT_MODE_MUX_B
#define USART2_TXD_GPIO   PIO_PD16_IDX
#define USART2_TXD_FLAGS  IOPORT_MODE_MUX_B

/** TWIHS1 pins definition */
#define TWIHS1_DATA_GPIO   PIO_PA4_IDX
#define TWIHS1_DATA_FLAGS  (IOPORT_MODE_MUX_A)
#define TWIHS1_CLK_GPIO    PIO_PA5_IDX
#define TWIHS1_CLK_FLAGS   (IOPORT_MODE_MUX_A)


/** SPI bit-banging pins definition */		// For PYTHON480. ATSAME SPI package sucks
#define SPI_BB_MOSI		PIO_PD21_IDX
#define SPI_BB_MISO		PIO_PD20_IDX
#define SPI_BB_SCK		PIO_PD22_IDX
#define SPI_BB_SS		PIO_PD25_IDX


/** HSMCI pins definition */				// SD card module
#define PIN_HSMCI_MCCDA_GPIO          (PIO_PA28_IDX)
#define PIN_HSMCI_MCCDA_FLAGS         (IOPORT_MODE_MUX_C)
#define PIN_HSMCI_MCCK_GPIO           (PIO_PA25_IDX)
#define PIN_HSMCI_MCCK_FLAGS          (IOPORT_MODE_MUX_D)
#define PIN_HSMCI_MCDA0_GPIO          (PIO_PA30_IDX)
#define PIN_HSMCI_MCDA0_FLAGS         (IOPORT_MODE_MUX_C)
#define PIN_HSMCI_MCDA1_GPIO          (PIO_PA31_IDX)
#define PIN_HSMCI_MCDA1_FLAGS         (IOPORT_MODE_MUX_C)
#define PIN_HSMCI_MCDA2_GPIO          (PIO_PA26_IDX)
#define PIN_HSMCI_MCDA2_FLAGS         (IOPORT_MODE_MUX_C)
#define PIN_HSMCI_MCDA3_GPIO          (PIO_PA27_IDX)
#define PIN_HSMCI_MCDA3_FLAGS         (IOPORT_MODE_MUX_C)


/** PYTHON480 status pins definition */
#define RESET_N_PIN			PIO_PB1_IDX
#define MONITOR0_PIN		PIO_PA18_IDX
#define TRIGGER0_PIN		PIO_PB2_IDX


/** OTHER peripheral pins definition */
#define VREG_INT			PIO_PD17_IDX		// Voltage regulator interrupt input pin
#define LED_PIN				PIO_PD19_IDX		// Status LED
#define LED_ENT_PIN			PIO_PA19_IDX		// Excitation LED power on and off. I2C below decides the actual light intensity

/*----------------------------------------------------------------------------*/

#endif // USER_BOARD_H
