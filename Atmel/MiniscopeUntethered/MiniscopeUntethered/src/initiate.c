#include <asf.h>
#include "initiate.h"
#include "definitions.h"



void TWIHS_init()
{	
	//Make sure you have the correct TWIHS
	twihs_options_t twihsOpt;
	twihsOpt.master_clk = sysclk_get_cpu_hz()/2; //make sure this is the correct clock to be checking
	twihsOpt.speed = 100000; //100kHz
	
	matrix_set_system_io(matrix_get_system_io() | CCFG_SYSIO_SYSIO4 | CCFG_SYSIO_SYSIO5);
	
	ioport_set_pin_mode(TWCK_PIN,TWCK_MODE);
	ioport_disable_pin(TWCK_PIN);
	
	ioport_set_pin_mode(TWD_PIN,TWD_MODE);
	ioport_disable_pin(TWD_PIN);

	pmc_enable_periph_clk(ID_TWIHS1);

	twihs_master_init(TWIHS1,&twihsOpt);
}

void SPI_BitBang_init()
{
	pmc_enable_periph_clk(ID_PIOB);
	matrix_set_system_io(matrix_get_system_io() | CCFG_SYSIO_SYSIO4 | CCFG_SYSIO_SYSIO5);
	
	ioport_set_pin_dir(SPI_BB_MOSI, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(SPI_BB_MOSI, 0);
	
	ioport_set_pin_dir(SPI_BB_MISO, IOPORT_DIR_INPUT);
	ioport_set_pin_level(SPI_BB_MISO, 0);
	
	ioport_set_pin_dir(SPI_BB_SCK, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(SPI_BB_SCK, 0);
	
	ioport_set_pin_dir(SPI_BB_SS, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(SPI_BB_SS, 1);
}



// ========== NOT IN USE ========= //
void PWM_Init()
{
	// Power Management Controller (PMC) initiates the peripheral clock (PCLK) derived from master clock (MCK) for power width modulator (PWM)
	// <--> CPU clock (CCLK/HCLK): Generally faster (comes from on-board PLL or external clock/oscillator)
	// @ ID_PWM0: Peripheral ID Definition - Pulse Width Modulation 0
	pmc_enable_periph_clk(ID_PWM0);

	// matrix_set_system_io: implements a multi-layer AHB, that enables parallel access paths between
	//						 multiple AHB masters and slaves in a system, thus increasing the overall
	//						 bandwidth. The MATRIX interconnects 13 AHB masters to 9 AHB slaves.
	// @matrix_get_system_io: Detect the type of MCU and get the MATRIX base address
	//						  @return Bitmask OR of SYSIOx. (bitmask: data that is used for bitwise operations)
	// @CCFG_SYSIO_SYSIO12: System I/O Configuration register. configures I/O lines in System I/O mode (such as
	//					   JTAG, ERASE, USB, etc.) or as general purpose I/O lines. Enabling or disabling the corresponding I/O
	//					   lines in peripheral mode or in PIO mode (PIO_PER or PIO_PDR registers) in the PIO controller has no
	//					   effect. However, the direction (input or output), pull-up, pull-down and other mode control is still managed
	//					   by the PIO controller. (0x1u << 12, so 2^12)
	//					   SYSIO12: PB12 or ERASE Assignment
	//								(=0) ERASE function selected.
	//								(=1) PB12 function selected.
	matrix_set_system_io(matrix_get_system_io() | CCFG_SYSIO_SYSIO12);	// Bitwise OR		// So what's the value of SYSIO12? When did I assign it a value?
	ioport_set_pin_mode(PWM_LED_PIN, PWM_LED_MODE);						// Sets GPIO PIN to PWM Peripheral
	ioport_disable_pin(PWM_LED_PIN);									// why are we disabling this pin? Are we waiting to actually start?

	pwm_channel_disable(PWM0, PWM_LED_CHANNEL);
	
	pwm_clock_t clock_setting = {
		.ul_clka = PWM_FREQUENCY * PWM_PERIOD_VALUE,					// Clock A is...freq*period Hz??
		.ul_clkb = 0,													// Clock B is turned off
		.ul_mck = sysclk_get_cpu_hz()/2									// (Master Clock freq in Hz) Might need or not need to divide by 2 to get the correct clock
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
	pwm_channel_enable(PWM0, PWM_LED_CHANNEL);
}

/**
	SPI_master_init: Initialize SPI as master.
 */
/*
void SPI_master_init(void)
{
	// Configure an SPI peripheral
	spi_enable_clock(SPI0);
	spi_disable(SPI0);
	spi_reset(SPI0);
	spi_set_lastxfer(SPI0);
	spi_set_master_mode(SPI0);
	spi_disable_mode_fault_detect(SPI0);
	spi_set_peripheral_chip_select_value(SPI0, SPI_CHIP_PCS);
	spi_set_clock_polarity(SPI0, SPI_CHIP_SEL, SPI_CLK_POLARITY);
	spi_set_clock_phase(SPI0, SPI_CHIP_SEL, SPI_CLK_PHASE);
	spi_set_bits_per_transfer(SPI0, SPI_CHIP_SEL, SPI_CSR_BITS_8_BIT);
	spi_set_baudrate_div(SPI0, SPI_CHIP_SEL, (sysclk_get_peripheral_hz() / gs_ul_spi_clock));
	spi_set_transfer_delay(SPI0, SPI_CHIP_SEL, SPI_DLYBS, SPI_DLYBCT);
	spi_enable(SPI0);
}
*/

/*
// ==========  ANOTHER SPI ========== //
void spi_master_init(Spi *p_spi)
{
	spi_enable_clock(p_spi);
	spi_reset(p_spi);
	spi_set_master_mode(p_spi);
	spi_disable_mode_fault_detect(p_spi);
	spi_disable_loopback(p_spi);
	spi_set_peripheral_chip_select_value(p_spi, spi_get_pcs(DEFAULT_CHIP_ID));
	spi_set_fixed_peripheral_select(p_spi);
	spi_disable_peripheral_select_decode(p_spi);
	spi_set_delay_between_chip_select(p_spi, CONFIG_SPI_MASTER_DELAY_BCS);
}

void spi_master_setup_device(Spi *p_spi, struct spi_device *device, spi_flags_t flags, uint32_t baud_rate, board_spi_select_id_t sel_id)
{
	spi_set_transfer_delay(p_spi, device->id, CONFIG_SPI_MASTER_DELAY_BS, CONFIG_SPI_MASTER_DELAY_BCT);

	spi_set_bits_per_transfer(p_spi, device->id, CONFIG_SPI_MASTER_BITS_PER_TRANSFER);
	spi_set_baudrate_div(p_spi, device->id, spi_calc_baudrate_div(baud_rate, sysclk_get_peripheral_hz()));

	spi_configure_cs_behavior(p_spi, device->id, SPI_CS_KEEP_LOW);

	spi_set_clock_polarity(p_spi, device->id, flags >> 1);
	spi_set_clock_phase(p_spi, device->id, ((flags & 0x1) ^ 0x1));
}
*/


