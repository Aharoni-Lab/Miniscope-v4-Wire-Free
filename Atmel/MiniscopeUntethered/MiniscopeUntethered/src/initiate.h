#ifndef INITIATE_H_
#define INITIATE_H_

/**
	SPI_BitBang_init: initiate SPI communication with PYTHON480 CMOS image sensor.
*/
void SPI_BitBang_init();


/**
	TWIHS_init: initiate I2C communication for electro-wetting lens and excitation LED. I'm assuming this kickstarts the actual PWM
*/
void TWIHS_init();



// ========== BELOW NOT IN USE ========== //

pwm_channel_t g_pwm_channel_led;	//Holds PWM channel information

/* SPI clock default setting (Hz). */
static uint32_t gs_ul_spi_clock = 500000;

/* Chip select. */
#define SPI_CHIP_SEL 0
#define SPI_CHIP_PCS spi_get_pcs(SPI_CHIP_SEL)

/* Clock polarity. */
#define SPI_CLK_POLARITY 0

/* Clock phase. */
#define SPI_CLK_PHASE 0

/* Delay before SPCK. */
#define SPI_DLYBS 0x40			// in # of MCK clocks

/* Delay between consecutive transfers. */
#define SPI_DLYBCT 0x10			// in # of MCK clocks


/**
	SPI_master_init: Initialize SPI as master.
 */
void SPI_master_init(void);


/**
	PWM_Init: initiate PWM for the excitation LED
*/
void PWM_Init();


#endif /* INITIATE_H_ */