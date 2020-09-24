/**
 * \file
 *
 * \brief User board configuration template
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef CONF_BOARD_H
#define CONF_BOARD_H


// ---------- Watchdog ---------- //
#define CONF_BOARD_KEEP_WATCHDOG_AT_INIT


// ---------- SD Card ---------- //
#define CONF_BOARD_SD_MMC_HSMCI


// ---------- USART2 ---------- //
#define CONF_BOARD_USART_TXD
#define CONF_BOARD_USART_RXD


// ---------- TWIHS1 ---------- //
#define CONF_BOARD_TWIHS1


// ---------- SPI Bit-bang ---------- //
#define CONF_BOARD_SPI_BITBANG


#endif // CONF_BOARD_H
