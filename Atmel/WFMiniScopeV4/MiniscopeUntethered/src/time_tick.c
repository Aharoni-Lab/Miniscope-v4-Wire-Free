/**
 * \file
 *
 * \brief Time tick for SAM.
 *
 * Copyright (c) 2014-2015 Atmel Corporation. All rights reserved.
 *
*/

#include <asf.h>
#include "time_tick.h"


volatile uint32_t g_ms_ticks = 0;

/**
 * \brief Handler for Sytem Tick interrupt.
 *
 * Process System Tick Event
 * Increments the g_ms_ticks counter.
 */
void SysTick_Handler(void)
{
	++g_ms_ticks;
}

void time_tick_init(void)
{
	g_ms_ticks = 0;

	/* Configure SysTick */
	if (SysTick_Config(sysclk_get_cpu_hz() / TICK_US)) 
	{
		Assert(false);
	}
}

uint32_t time_tick_get(void)
{
	return g_ms_ticks;
}

uint32_t time_tick_calc_delay(uint32_t tick_start, uint32_t tick_end)
{
	if (tick_end >= tick_start) 
	{
		return (tick_end - tick_start) * (1000 / TICK_US);
	}
	
	else 
	{
		/* In the case of 32-bit couter number overflow */
		return (tick_end + (0xFFFFFFFF - tick_start)) * (1000 / TICK_US);
	}
}
