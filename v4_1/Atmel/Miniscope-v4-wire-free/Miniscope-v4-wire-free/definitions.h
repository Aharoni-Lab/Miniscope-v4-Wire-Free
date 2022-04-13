/*
 * definitions.h
 *
 * Created: 5/27/2021 1:30:55 PM
 *  Author: dbaha
 */ 


#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

// ------ OTHER STUFF ------------------------
#define MS_SUCCESS						1
#define MS_ERROR						0
// -------------------------------------------

// ---------- Device State Definitions -------
#define DEVICE_STATE_IDLE				1<<1
#define DEVICE_STATE_START_RECORDING	1<<2
#define DEVICE_STATE_RECORDING			1<<3
#define DEVICE_STATE_STOP_RECORDING		1<<4
#define DEVICE_STATE_CHARGING			1<<5
#define DEVICE_STATE_CONFIG_LOADED		1<<6
#define DEVICE_STATE_ERROR				1<<7
#define DEVICE_STATE_LOW_VOLTAGE		1<<8
#define DEVICE_STATE_START_RECORDING_WAITING	1<<9
#define DEVICE_STATE_SDCARD_WRITE_ERROR			1<<10
#define DEVICE_STATE_SDCARD_INIT_WRITE_ERROR	1<<11
// -------------------------------------------

// ----------- Buffer Definitions ------------
#define BUFFER_BLOCK_LENGTH		40 // can be edited by user to optimize speed
#define NUM_BUFFERS				8   // can be edited by user to optimize speed
#define BLOCK_SIZE_IN_WORDS		128 // (512 bytes) / (4 byte word size)

// Buffer Header position definitions
#define BUFFER_HEADER_LENGTH					10

#define BUFFER_HEADER_HEADER_LENGTH_POS			0
#define BUFFER_HEADER_LINKED_LIST_POS			1
#define BUFFER_HEADER_FRAME_NUM_POS				2
#define BUFFER_HEADER_BUFFER_COUNT_POS			3
#define BUFFER_HEADER_FRAME_BUFFER_COUNT_POS	4
#define BUFFER_HEADER_WRITE_BUFFER_COUNT_POS	5
#define BUFFER_HEADER_DROPPED_BUFFER_COUNT_POS	6
#define BUFFER_HEADER_TIMESTAMP_POS				7
#define BUFFER_HEADER_DATA_LENGTH_POS			8
#define BUFFER_HEADER_WRITE_TIMESTAMP_POS		9

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
#define NB_BUFFER_WRITES_PER_CHUNK	20 // Can be edited by user to optimize speed
 
 
#define HEADER_BLOCK				STARTING_BLOCK - 2
#define CONFIG_BLOCK				STARTING_BLOCK - 1

#define SD_BLOCK_SIZE					512 //Number of bytes in a single block (sector)

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
#define HEADER_FRAME_RATE_POS		8
// -------------------------------------------
 
// ------- Image Sensor Definitions ----------
#define FRAME_RATE					10
#define WIDTH						608
#define HEIGHT						608
#define BINNING						2

#define NUM_PIXELS					((WIDTH * HEIGHT) / (BINNING * BINNING))

// -------------------------------------------

#endif /* DEFINITIONS_H_ */