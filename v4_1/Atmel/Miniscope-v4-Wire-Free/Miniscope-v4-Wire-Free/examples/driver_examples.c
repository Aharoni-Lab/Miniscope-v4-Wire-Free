/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

/**
 * Example of using ADC_0 to generate waveform.
 */
void ADC_0_example(void)
{
	uint8_t buffer[2];

	adc_sync_enable_channel(&ADC_0, 0);

	while (1) {
		adc_sync_read_channel(&ADC_0, 0, buffer, 2);
	}
}

/**
 * It's just demo for usage and assume that
 * the frame size is very small, in actually application,
 * the frame size  should be big enough for a frame.
 */
uint32_t frame_buf[CONF_PCC_DMA_FRAME_SIZE];

/**
 * Example of using CAMERA_0.
 */

static void capture_cb(struct camera_async_descriptor *const descr, uint32_t ch)
{
	if (ch == 0) {
		// Application can process data in frame_buf.
		camera_async_capture_start(&CAMERA_0, 0, frame_buf);
	}
}
/**
 * Application example.
 */
void CAMERA_0_example(void)
{
	camera_async_register_callback(&CAMERA_0, capture_cb);
	camera_async_enable(&CAMERA_0);
	camera_async_capture_start(&CAMERA_0, 0, frame_buf);
}

/**
 * Example of using SPI_0 to write "Hello World" using the IO abstraction.
 */
static uint8_t example_SPI_0[12] = "Hello World!";

void SPI_0_example(void)
{
	struct io_descriptor *io;
	spi_m_sync_get_io_descriptor(&SPI_0, &io);

	spi_m_sync_enable(&SPI_0);
	io_write(io, example_SPI_0, 12);
}

/**
 * Example of using PWM_0.
 */
void PWM_0_example(void)
{
	pwm_set_parameters(&PWM_0, 10000, 5000);
	pwm_enable(&PWM_0);
}
