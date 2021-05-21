/* Auto-generated config file hpl_pcc_config.h */
#ifndef HPL_PCC_CONFIG_H
#define HPL_PCC_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Basic Configuration

// <o> Data Size
//<i> Defines the number of the data once read.
// <0x0=>1 DATA
// <0x1=>2 DATA
// <0x2=>4 DATA
// <id> pcc_dsize
#ifndef CONF_PCC_DSIZE
#define CONF_PCC_DSIZE 0x2
#endif

// <q> Scale Data
//<i> Defines sample the sensor data up-scaled to 16 bits or not when input data is not 8 bit.
// <id> pcc_scale
#ifndef CONF_PCC_SCALE
#define CONF_PCC_SCALE 0x0
#endif

// <q> Always Sampling
//<i> Defines sample the sensor data comply with the sensor data enable signals or not.
// <id> pcc_alwys
#ifndef CONF_PCC_ALWYS
#define CONF_PCC_ALWYS 0x0
#endif

// <q> Half Sampling
//<i> Defines sample the sensor data only every other time or not.
// <id> pcc_halfs
#ifndef CONF_PCC_HALFS
#define CONF_PCC_HALFS 0x1
#endif

// <q> First Sample
//<i> Defines sample the even or odd sensor data.
// <id> pcc_frsts
#ifndef CONF_PCC_FRSTS
#define CONF_PCC_FRSTS 0x0
#endif

// <o> Input Data Size
//<i> Defines the input sensor data bit width.
// <0x0=>8 bits
// <0x1=>10 bits
// <0x2=>12 bits
// <0x3=>14 bits
// <id> pcc_isize
#ifndef CONF_PCC_ISIZE
#define CONF_PCC_ISIZE 0x0
#endif

//<o> DMA Channel <0-15>
//<i> Defines DMA channel to be used
//<id> pcc_dma_channel
#define CONF_PCC_DMA_CHANNEL 0x0

//<o> DMA Frame size <1-2000000>
//<i> Defines DMA transfer frame size
//<id> pcc_dma_frame_size
#define CONF_PCC_DMA_FRAME_SIZE 64
// </h>

// <<< end of configuration section >>>

#endif // HPL_PCC_CONFIG_H
