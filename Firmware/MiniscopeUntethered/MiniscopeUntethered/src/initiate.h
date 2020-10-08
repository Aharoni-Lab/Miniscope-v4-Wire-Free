#ifndef INITIATE_H_
#define INITIATE_H_

/**
	SPI_BitBang_init: initiate SPI communication with PYTHON480 CMOS image sensor.
*/
void SPI_BitBang_init();


/**
	TWIHS_init: initiate I2C communication for electro-wetting lens and excitation LED.
*/
void TWIHS_init();


/**
	USART_init: initiate USART communication for USART-USB board communication
*/
void USART_init();

#endif /* INITIATE_H_ */