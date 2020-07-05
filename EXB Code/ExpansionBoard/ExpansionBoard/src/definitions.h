#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_


// ========== FROM WIRELESS ========== //
#define PXLCLK_MASK				PIO_PA14X1_PIODCEN1
#define PXLCLK_ID				PIO_PA14_IDX

#define DAT0_MASK				PIO_PA3X1_PIODC0
#define DAT0_ID					PIO_PA3_IDX
#define DAT1_MASK				PIO_PA4X1_PIODC1
#define DAT1_ID					PIO_PA4_IDX
#define DAT2_MASK				PIO_PA5X1_PIODC2
#define DAT2_ID					PIO_PA5_IDX
#define DAT3_MASK				PIO_PA9X1_PIODC3
#define DAT3_ID					PIO_PA9_IDX

#define CONFIG_WL				PIO_PA10_IDX



// ========== TO SERIALIZER ========== //
#define CLK_SER					PIO_PA17_IDX		// Unnecessary?
#define PIXEL_CLK				PIO_PD24_IDX

#define DOUT_1					PIO_PD12_IDX
#define DOUT_2					PIO_PD13_IDX
#define DOUT_3					PIO_PD14_IDX
#define DOUT_4					PIO_PD15_IDX
#define DOUT_5					PIO_PD16_IDX
#define DOUT_6					PIO_PD17_IDX
#define DOUT_7					PIO_PD18_IDX
#define DOUT_8					PIO_PD19_IDX

#define LINE_VAL				PIO_PD21_IDX
#define FRAME_VAL				PIO_PD22_IDX

#define TWD_PIN					PIO_PB4_IDX
#define TWD_MODE				IOPORT_MODE_MUX_A
#define TWCK_PIN				PIO_PB5_IDX
#define TWCK_MODE				IOPORT_MODE_MUX_A

#endif	// DEFINITIONS_H_