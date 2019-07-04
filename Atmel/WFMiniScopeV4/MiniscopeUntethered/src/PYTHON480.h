/*
 * PYTHON480.h
 *
 * Created: 7/21/2018 7:51:30 PM
 *  Author: DBAharoni
 */ 


#ifndef PYTHON480_H_
#define PYTHON480_H_

#include <asf.h>
#include "SPI_BB_PYTHON480.h"

#define DISABLE_PLL

// Power off --> low-power standby --> standby1 --> intermediate standby --> standby2 -->idle --> running
//		power up seq	  enable clk mgmt1	enable clk mgmt2	req reg uploads	  softpower  enable seq

// configure clock management blocks, activate clock generation and distribution circuits
void EnableClockMngmnt1();


// Enable all internal clock distribution
void EnableClockMngmnt2();


// Reserved register settings uploads
void RequiredUploads();


// internal blocks are enabled and prepared to start processing the image data stream
void SoftPowerUp();


// Idle state to running state
void EnableSeq();


// Running state to idle state
void DisableSeq();



/************************************************************************/
/*                              NOT IN USE                              */
/************************************************************************/
void NoTransfer();


void Transfer();


// function to enable E-black calibration images
// enables electrical black image
void Eblack();


// function to enable E-gray calibration images
// enables electrical gray image
void Egray();


// function to (re)enable normal image mode
// (re-)enables 'normal' image capture
void DisableE();


#endif /* PYTHON480_H_ */