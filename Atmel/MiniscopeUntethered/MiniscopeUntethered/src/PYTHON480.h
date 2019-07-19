/*
 *  PYTHON480.h
 *
 *  Created: 7/21/2018 7:51:30 PM
 *  Author: DBAharoni
 *  Edits: RWChang
 */ 


#ifndef PYTHON480_H_
#define PYTHON480_H_

#include <asf.h>
#include "SPI_BB_PYTHON480.h"

#define DISABLE_PLL


/************************************************************************/
/*                         Power Up Sequence                            */
/************************************************************************/

// Power off --> low-power standby --> standby1 --> intermediate standby --> standby2 -->idle --> running
//		power up seq	  enable clk mgmt1	enable clk mgmt2	req reg uploads	  softpower  enable seq


// configure clock management blocks, activate clock generation and distribution circuits
void Enable_Clock_Management1();


// Enable all internal clock distribution
void Enable_Clock_Management2();


// Reserved register settings uploads
void Required_Uploads();


// Internal blocks are enabled and prepared to start processing the image data stream
void Soft_PowerUp();


// Idle state to running state
void Enable_Seq();


// Running state to idle state
void Disable_Seq();


// Enable sub-sampling (only take every other pixel)
void Enable_Subsample();


// Determine Region of Interest (Configure the window to sample from)
void ROI_Configuration();


/************************************************************************/
/*                              NOT IN USE                              */
/************************************************************************/
void No_Transfer();


void Transfer();


// function to enable E-black calibration images
// enables electrical black image
void Enable_Black();


// function to enable E-gray calibration images
// enables electrical gray image
void Enable_Gray();


// function to (re)enable normal image mode
// (re-)enables 'normal' image capture
void DisableE();


#endif /* PYTHON480_H_ */