/**
 * \file
 *
 * \brief SAME70 clock configuration.
 *
 * Copyright (c) 2015 Atmel Corporation. All rights reserved.
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef CONF_CLOCK_H_INCLUDED
#define CONF_CLOCK_H_INCLUDED

//Which CMOS imaging sensor are we using. Defined in conf_clock.h and sdImaging.h
#define NOIP1SN0480A
//#define MT9V032
//#define EV76C454_SUBSAMP
// #define EV76C541
// #define EV76C454


// ===== System Clock (MCK) Source Options
//#define CONFIG_SYSCLK_SOURCE        SYSCLK_SRC_SLCK_RC
//#define CONFIG_SYSCLK_SOURCE        SYSCLK_SRC_SLCK_XTAL
//#define CONFIG_SYSCLK_SOURCE        SYSCLK_SRC_SLCK_BYPASS
//#define CONFIG_SYSCLK_SOURCE        SYSCLK_SRC_MAINCK_4M_RC
//#define CONFIG_SYSCLK_SOURCE        SYSCLK_SRC_MAINCK_8M_RC
//#define CONFIG_SYSCLK_SOURCE        SYSCLK_SRC_MAINCK_12M_RC
//#define CONFIG_SYSCLK_SOURCE        SYSCLK_SRC_MAINCK_XTAL
//#define CONFIG_SYSCLK_SOURCE        SYSCLK_SRC_MAINCK_BYPASS
#define CONFIG_SYSCLK_SOURCE        SYSCLK_SRC_PLLACK
//#define CONFIG_SYSCLK_SOURCE        SYSCLK_SRC_UPLLCK

// ===== Processor Clock (HCLK) Prescaler Options   (Fhclk = Fsys / (SYSCLK_PRES))
#define CONFIG_SYSCLK_PRES          SYSCLK_PRES_1
//#define CONFIG_SYSCLK_PRES          SYSCLK_PRES_2
//#define CONFIG_SYSCLK_PRES          SYSCLK_PRES_4
//#define CONFIG_SYSCLK_PRES          SYSCLK_PRES_8
//#define CONFIG_SYSCLK_PRES          SYSCLK_PRES_16
//#define CONFIG_SYSCLK_PRES          SYSCLK_PRES_32
//#define CONFIG_SYSCLK_PRES          SYSCLK_PRES_64
//#define CONFIG_SYSCLK_PRES          SYSCLK_PRES_3

// ===== System Clock (MCK) Division Options     (Fmck = Fhclk / (SYSCLK_DIV))
#define CONFIG_SYSCLK_DIV				2

// ===== PLL0 (A) Options   (Fpll = (Fclk * PLL_mul) / PLL_div)
// Use mul and div effective values here.
#define CONFIG_PLL0_SOURCE				PLL_SRC_MAINCK_XTAL //PLL_SRC_MAINCK_12M_RC //PLL_SRC_MAINCK_XTAL

#ifdef NOIP1SN0480A
	#define CONFIG_PLL0_MUL				12
#endif

#ifdef EV76C454
	#define CONFIG_PLL0_MUL             24 // This was decreased from 25 to make CMOS clk = 48MHz. This means ARM is running at 144MHz not 150MHz
#endif

#ifdef EV76C541
	#define CONFIG_PLL0_MUL             12 // This was decreased from 25 to make CMOS clk = 48MHz. This means ARM is running at 72MHz not 150MHz
#endif

// #ifdef EV76C454_SUBSAMP
// 	#define CONFIG_PLL0_MUL             12 // This was decreased from 25 to make CMOS clk = 48MHz. This means ARM is running at 72MHz not 150MHz
// #endif


#define CONFIG_PLL0_DIV             1

// ===== UPLL (UTMI) Hardware fixed at 480 MHz.

// ===== USB Clock Source Options   (Fusb = FpllX / USB_div)
// Use div effective value here.
//#define CONFIG_USBCLK_SOURCE        USBCLK_SRC_PLL0
#define CONFIG_USBCLK_SOURCE        USBCLK_SRC_UPLL
#define CONFIG_USBCLK_DIV           1

// ===== Target frequency (Processor clock)
// - XTAL frequency: 12MHz
// - System clock source: PLLA
// - System clock prescaler: 1 (divided by 1)
// - System clock divider: 2 (divided by 2)
// - PLLA source: XTAL
// - PLLA output: XTAL * 25 / 1
// - Processor clock: 12 * 25 / 1 / 1 = 300MHz
// - System clock: 300 / 2 = 150MHz
// ===== Target frequency (USB Clock)
// - USB clock source: UPLL
// - USB clock divider: 1 (not divided)
// - UPLL frequency: 480MHz
// - USB clock: 480 / 1 = 480MHz

#endif /* CONF_CLOCK_H_INCLUDED */
