/*
 * definitions.h
 *
 * Created: 5/27/2021 1:30:55 PM
 *  Author: dbaha
 */ 


#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

// ---------- Device State Definitions -------
#define DEVICE_STATE_IDLE				0
#define DEVICE_STATE_START_RECORDING	1
#define DEVICE_STATE_RECORDING			2
#define DEVICE_STATE_STOP_RECORDING		3
// -------------------------------------------

// ----------- Buffer Definitions ------------
#define BUFFER_BLOCK_LENGTH		80 // can be edited by used to optimize speed
#define NUM_BUFFERS				4   // can be edited by used to optimize speed
#define BLOCK_SIZE_IN_WORDS		128 // (512 bytes) / (4 byte word size)

// Buffer Header position definitions
#define BUFFER_HEADER_LENGTH					9

#define BUFFER_HEADER_HEADER_LENGTH_POS			0
#define BUFFER_HEADER_LINKED_LIST_POS			1
#define BUFFER_HEADER_FRAME_NUM_POS				2
#define BUFFER_HEADER_BUFFER_COUNT_POS			3
#define BUFFER_HEADER_FRAME_BUFFER_COUNT_POS	4
#define BUFFER_HEADER_WRITE_BUFFER_COUNT_POS	5
#define BUFFER_HEADER_DROPPED_BUFFER_COUNT_POS	6
#define BUFFER_HEADER_TIMESTAMP_POS				7
#define BUFFER_HEADER_DATA_LENGTH_POS			8

// -------------------------------------------

// ------------ Config Block Definitions -----
#define CONFIG_BLOCK_WIDTH_POS					0
#define CONFIG_BLOCK_HEIGHT_POS					1
#define CONFIG_BLOCK_FRAME_RATE_POS				2
#define CONFIG_BLOCK_BUFFER_SIZE_POS			3
#define CONFIG_BLOCK_NUM_BUFFERS_RECORDED_POS	4
#define CONFIG_BLOCK_NUM_BUFFERS_DROPPED_POS	5
// -------------------------------------------

// -------------------------------------------
// -------------- SD Definitions -------------
#define STARTING_BLOCK				1024
#define NB_BUFFER_WRITES_PER_CHUNK	100 // Can be edited by user to optimize speed
 
 
#define HEADER_BLOCK				STARTING_BLOCK - 2
#define CONFIG_BLOCK				STARTING_BLOCK - 1

#define BLOCK_SIZE					512 //Number of bytes in a single block (sector)

// Write Key Protection Values
#define WRITE_KEY0					0x0D7CBA17
#define WRITE_KEY1					0x0D7CBA17
#define WRITE_KEY2					0x0D7CBA17
#define WRITE_KEY3					0x0D7CBA17

// SD Header Definitions
#define HEADER_GAIN_POS				4
#define HEADER_LED_POS				5
#define HEADER_EWL_POS				6
#define HEADER_RECORD_LENGTH_POS	7
#define HEADER_FRAME_RATE			8
// -------------------------------------------
 
// ------- Image Sensor Definitions ----------
#define FRAME_RATE					20
#define WIDTH						600
#define HEIGHT						600
#define BINNING						2

#define NUM_PIXELS					((WIDTH * HEIGHT) / (BINNING * BINNING))

// -------------------------------------------

#endif /* DEFINITIONS_H_ */