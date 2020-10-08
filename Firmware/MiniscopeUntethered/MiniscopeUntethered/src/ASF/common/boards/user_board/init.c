/**
 * \file
 *
 * \brief User board initialization template
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>

/**
 * \brief Set peripheral mode for one single IOPORT pin.
 * It will configure port mode and disable pin mode (but enable peripheral).
 * \param pin IOPORT pin to configure
 * \param mode Mode masks to configure for the specified pin (\ref ioport_modes)
 */
#define ioport_set_pin_peripheral_mode(pin, mode) \
do {\
	ioport_set_pin_mode(pin, mode);\
	ioport_disable_pin(pin);\
} while (0)

void board_init(void)
{
	/* This function is meant to contain board-specific initialization code
	 * for, e.g., the I/O pins. The initialization can rely on application-
	 * specific board configuration, found in conf_board.h.
	 */
	#ifndef CONF_BOARD_KEEP_WATCHDOG_AT_INIT
	/* Disable the watchdog */
	WDT->WDT_MR = WDT_MR_WDDIS;
	#endif
	
	 #ifdef CONF_BOARD_SD_MMC_HSMCI
	 /* Configure HSMCI pins */
	 ioport_set_pin_peripheral_mode(PIN_HSMCI_MCCDA_GPIO, PIN_HSMCI_MCCDA_FLAGS);
	 ioport_set_pin_peripheral_mode(PIN_HSMCI_MCCK_GPIO, PIN_HSMCI_MCCK_FLAGS);
	 ioport_set_pin_peripheral_mode(PIN_HSMCI_MCDA0_GPIO, PIN_HSMCI_MCDA0_FLAGS);
	 ioport_set_pin_peripheral_mode(PIN_HSMCI_MCDA1_GPIO, PIN_HSMCI_MCDA1_FLAGS);
	 ioport_set_pin_peripheral_mode(PIN_HSMCI_MCDA2_GPIO, PIN_HSMCI_MCDA2_FLAGS);
	 ioport_set_pin_peripheral_mode(PIN_HSMCI_MCDA3_GPIO, PIN_HSMCI_MCDA3_FLAGS);
	 
	 /* Configure SD/MMC card detect pin */
// 	 ioport_set_pin_dir(SD_MMC_0_CD_GPIO, IOPORT_DIR_INPUT);
// 	 ioport_set_pin_mode(SD_MMC_0_CD_GPIO, SD_MMC_0_CD_FLAGS);
	 #endif
	 
	 #ifdef CONF_BOARD_TWIHS1
	 /* Configure TWIHS pins */
	 ioport_set_pin_peripheral_mode(TWIHS1_DATA_GPIO, TWIHS1_DATA_FLAGS);
	 ioport_set_pin_peripheral_mode(TWIHS1_CLK_GPIO, TWIHS1_CLK_FLAGS);
	 #endif
 
	 #ifdef CONF_BOARD_SPI_BITBANG
	 /* Going to bit-bang SPI */ 	
	 ioport_set_pin_dir(SPI_BB_MOSI, IOPORT_DIR_OUTPUT);
	 ioport_set_pin_level(SPI_BB_MOSI, 0);
	 ioport_set_pin_dir(SPI_BB_MISO, IOPORT_DIR_INPUT);
	 ioport_set_pin_level(SPI_BB_MISO, 0);
	 ioport_set_pin_dir(SPI_BB_SCK, IOPORT_DIR_OUTPUT);
	 ioport_set_pin_level(SPI_BB_SCK, 0);
	 ioport_set_pin_dir(SPI_BB_SS, IOPORT_DIR_OUTPUT);
	 ioport_set_pin_level(SPI_BB_SS, 1);
	 #endif
	 
	 #ifdef CONF_BOARD_USART_RXD
	 /* Configure USART RXD pin */
	 ioport_set_pin_peripheral_mode(USART2_RXD_GPIO, USART2_RXD_FLAGS);
	 #endif

	 #ifdef CONF_BOARD_USART_TXD
	 /* Configure USART TXD pin */
	 ioport_set_pin_peripheral_mode(USART2_TXD_GPIO, USART2_TXD_FLAGS);
	 #endif
}
