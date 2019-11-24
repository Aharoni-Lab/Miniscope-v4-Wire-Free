/*
 *  PYTHON480.h
 *
 *  Created: 7/21/2018 7:51:30 PM
 *  Author: DBAharoni
 *  Edits: RWChang
 */ 


#include "PYTHON480.h"


// Configure clock management blocks, activate clock generation and distribution circuits
void Enable_Clock_Management1() 
{
	SPI_Write(2, 0x0000);	// Monochrome sensor
	SPI_Write(17, 0x2113);	// Configure PLL
	SPI_Write(20, 0x0000);	// Configure clock management
	SPI_Write(26, 0x2280);	// Configure PLL lock detector
	SPI_Write(27, 0x3D2D);	// Configure PLL lock detector
	
	#ifdef DISABLE_PLL
		SPI_Write(32, 0x7014|0x0008);	// SPI_Write(32, 0x2004); PLL input clock
	#else
//		SPI_Write(32, 0x7014);			// SPI_Write(32, 0x2004); PLL input clock
		SPI_Write(32, 0x7014|0x0008);			// SPI_Write(32, 0x2004); PLL input clock
	#endif
	
	SPI_Write(8, 0x0000);	// Release PLL soft reset
	
	#ifdef DISABLE_PLL
		SPI_Write(16, 0x0007);			// Disable PLL
	#else
		SPI_Write(16, 0x0003);			// Enable PLL Andres says to make this 0x0007. I originally had it at 0x0004. Try 0x0003
	#endif
}

// Enable internal clock distribution
void Enable_Clock_Management2() 
{
	SPI_Write(9, 0x0000);	// Release clock generator Soft Reset

	// Why is it 0x7006 instead of 0x2006??
	#ifdef DISABLE_PLL
		SPI_Write(32, 0x7006|0x0008);		// SPI_Write(32, 0x7006); Enable logic clock. Changed this to 7006 to try
	#else
//		SPI_Write(32, 0x7006);				// SPI_Write(32, 0x7006); Enable logic clock. Changed this to 7006 to try
		SPI_Write(32, 0x7006|0x0008);				// SPI_Write(32, 0x7006); Enable logic clock. Changed this to 7006 to try
	#endif

	SPI_Write(34, 0x0001);	// Enable logic blocks
}

// Reserved register settings uploads
void Required_Uploads() 
{
	SPI_Write(2, 0x0000);
	SPI_Write(8, 0x0000);
	SPI_Write(9, 0x0000);
	SPI_Write(10, 0x0000);
	SPI_Write(20, 0x0000);
	// SPI_Write(24, 0x0001);
	SPI_Write(26, 0x2280);
	SPI_Write(27, 0x3D2D);
	
	#ifdef DISABLE_PLL
		SPI_Write(32, 0x7007|0x0008);
	#else
//		SPI_Write(32, 0x7007);
		SPI_Write(32, 0x7007|0x0008);
	#endif
	
	SPI_Write(34, 0x0001);
	SPI_Write(40, 0x0007);		// 3rd bit enables bias. This was set to 0 (0x003).
	SPI_Write(41, 0x085F);
	SPI_Write(42, 0x4103);
	SPI_Write(43, 0x0518);
	SPI_Write(48, 0x0001);
	SPI_Write(64, 0x0001);
	SPI_Write(65, 0x382A);		// Bias block. SPI_Write(65, 0x382B)
	SPI_Write(66, 0x53C8);
	SPI_Write(67, 0x0665);
	SPI_Write(68, 0x0085);
	SPI_Write(69, 0x0888);
	SPI_Write(70, 0x4800);
	SPI_Write(71, 0x8888);
	SPI_Write(72, 0x0117);
	// SPI_Write(112, 0x0007);
	SPI_Write(112, 0x0000);		// LVDS power-down config
	SPI_Write(128, 0x470A);		//SPI_Write(128, 0x470A); SPI_Write(128, 0x4714); black offset
	SPI_Write(129, 0x8001);
	// SPI_Write(130, 0x0001);	// Handles phase of pixel clock changed from 0x0001 to 0x0015

	// Test Pattern
	// SPI_Write(144,0x0003);

	SPI_Write(130, 0x0015);
	SPI_Write(192, 0x0801);		// Monitor select function
	SPI_Write(194, 0x03E4);		// reverse x and y enabled for demo kit compatibility
	SPI_Write(197, 0x0380);		// Num black lines SPI_Write(197, 0x030A);
	
	#ifdef DISABLE_PLL
		SPI_Write(199, 167);		// Exposure/Frame rate config, SPI_Write(199, 0x0299);	// Why is this not 666?? --> Python divides input clock by 4 and then uses PLL to multiply by 4 again
		SPI_Write(200, 5000);	// Frame length, SPI_Write(200, 0x0350);
		SPI_Write(201, 4900);	// SPI_Write(201, 2900); // Exposure time SPI_Write(201, 0x01F4);
	#else
		SPI_Write(199, 666);		// Exposure/Frame rate config, SPI_Write(199, 0x0299);
		SPI_Write(200, 3000);	// Frame length, SPI_Write(200, 0x0350);
		SPI_Write(201, 2900);	// SPI_Write(201, 2900); // Exposure time SPI_Write(201, 0x01F4);
	#endif
	
	SPI_Write(204, 0x00E1); 	// (gain 1x : 0x00E1 // gain 2x : 0x00E4 // gain 3.5x : 0x0024)
	SPI_Write(207, 0x0014);
	SPI_Write(214, 0x0100);
	SPI_Write(215, 0x101F);
	SPI_Write(216, 0x0000);
	SPI_Write(219, 0x0023);
	SPI_Write(220, 0x3C2B);
	SPI_Write(221, 0x2B4D);
	SPI_Write(224, 0x3E5E);
	SPI_Write(211, 0x0049);
	SPI_Write(216, 0x0000);
	SPI_Write(219, 0x0023);
	SPI_Write(220, 0x3C2B);
	SPI_Write(221, 0x2B4D);
	SPI_Write(230, 0x0299);
	SPI_Write(231, 0x0350);
	SPI_Write(232, 0x01F4);
	SPI_Write(235, 0x00E1);


	
	// PROGRAM SPACE //
	SPI_Write(384, 0xC800);
	SPI_Write(385, 0xFB1F);
	SPI_Write(386, 0xFB1F);
	SPI_Write(387, 0xFB12);
	SPI_Write(388, 0xF912);
	SPI_Write(389, 0xF903);
	SPI_Write(390, 0xF802);
	SPI_Write(391, 0xF30F);
	SPI_Write(392, 0xF30F);
	SPI_Write(393, 0xF30F);
	SPI_Write(394, 0xF30A);
	SPI_Write(395, 0xF101);
	SPI_Write(396, 0xF00A);
	SPI_Write(397, 0xF24B);
	SPI_Write(398, 0xF201);
	SPI_Write(399, 0xF226);
	SPI_Write(400, 0xF021);
	SPI_Write(401, 0xF001);
	SPI_Write(402, 0xF402);
	SPI_Write(403, 0xF007);
	SPI_Write(404, 0xF20F);
	SPI_Write(405, 0xF20F);
	SPI_Write(406, 0xF202);
	SPI_Write(407, 0xF006);
	SPI_Write(408, 0xEC08);
	SPI_Write(409, 0xC801);
	SPI_Write(410, 0xC800);

	SPI_Write(419, 0xC800);
	SPI_Write(420, 0xCC02);
	SPI_Write(421, 0xCC01);
	SPI_Write(422, 0xCC02);
	SPI_Write(423, 0xCC01);
	SPI_Write(424, 0xCC02);
	SPI_Write(425, 0xC805);
	SPI_Write(426, 0xC800);

	SPI_Write(427, 0x0030);
	SPI_Write(428, 0x207B);
	SPI_Write(429, 0x2071);
	SPI_Write(430, 0x0071);
	SPI_Write(431, 0x107F);
	SPI_Write(432, 0x1072);
	SPI_Write(433, 0x1074);
	SPI_Write(434, 0x0071);
	SPI_Write(435, 0x0031);
	SPI_Write(436, 0x21BB);
	SPI_Write(437, 0x20B1);
	SPI_Write(438, 0x00B1);
	SPI_Write(439, 0x10BF);
	SPI_Write(440, 0x10B2);
	SPI_Write(441, 0x10B4);
	SPI_Write(442, 0x00B1);
	SPI_Write(443, 0x0030);

	SPI_Write(444, 0x0030);
	SPI_Write(445, 0x217B);
	SPI_Write(446, 0x2071);
	SPI_Write(447, 0x0071);
	SPI_Write(448, 0x107F);
	SPI_Write(449, 0x1072);
	SPI_Write(450, 0x1074);
	SPI_Write(451, 0x0071);
	SPI_Write(452, 0x0031);
	SPI_Write(453, 0x21BB);
	SPI_Write(454, 0x20B1);
	SPI_Write(455, 0x00B1);
	SPI_Write(456, 0x10BF);
	SPI_Write(457, 0x10B2);
	SPI_Write(458, 0x10B4);
	SPI_Write(459, 0x00B1);
	SPI_Write(460, 0x0030);

	SPI_Write(461, 0x0030);
	SPI_Write(462, 0x217B);
	SPI_Write(463, 0x2071);
	SPI_Write(464, 0x0071);
	SPI_Write(465, 0x1071);
	SPI_Write(466, 0x0071);
	SPI_Write(467, 0x0031);
	SPI_Write(468, 0x21BB);
	SPI_Write(469, 0x20B1);
	SPI_Write(470, 0x00B1);
	SPI_Write(471, 0x10B3);
	SPI_Write(472, 0x10B1);
	SPI_Write(473, 0x00B1);
	SPI_Write(474, 0x003F);
	SPI_Write(475, 0x0032);
	SPI_Write(476, 0x0030);
}

// Internal blocks are enabled and prepared to start processing the image data stream
void Soft_PowerUp() 
{
	SPI_Write(10, 0x0000);		// Release soft reset state
	
	#ifdef DISABLE_PLL
		SPI_Write(32, 0x7007|0x0008);	// Enable analog clock
	#else
		SPI_Write(32, 0x7007);			// Enable analog clock
	#endif
	
	SPI_Write(40, 0x0007);		// Enable column multiplexer // 3rd bit endables bias. This was set to 0 (0x003).
	SPI_Write(42, 0x4113);		// SPI_Write(42, 0x4103); Configure image core
	SPI_Write(48, 0x0001);		// Enable AFE
	SPI_Write(64, 0x0001);		// Enable biasing block
	SPI_Write(72, 0x0127);		// SPI_Write(72, 0x0117); Enable charge pump.
	//SPI_Write(112, 0x0007);	// Enable LVDS transmitters
	SPI_Write(112, 0x0000);		// Enable LVDS transmitters
}

// Enable subsampling by taking every other pixel
void Enable_Subsample()
{
	SPI_Write(192, 0x0803 | 0x0080);	// Subsampling
	SPI_Write(194, 0x03E4 | 0x0C00);	// Subsampling mode in both x and y (Check VITA-compatibility)
}

// Window Configuration
void ROI_Configuration()
	{
		// Registers 195 & 256-265
		
		// ROI0 config0
		// * default: 0xC900 (x_start 0x00, x_end 0xC9)
		// goes from 0 - 201
		// mind the subsampling
		SPI_Write(256, 0xC405);		// Take 20 pixels off from each side (each bit = 4 pxs) // Is it 8 pixels since subsampling??
		
		// ROI0 config1
		// * default: 0x9700 (y_start 0x00, y_end 0x97)
		// goes from 0 - 151
		// mind the subsampling
		SPI_Write(257, 0x9502);		// take 8 pixels off from each side (each bit = 4 pxs)
		
		// Test on Oscilloscope:
		// SPI_Write(257, 0x5250);
		
		// RIO0 config_lsb0
		// The least significant configuration bits for x and y parameters are located in separate registers
		// (refer to registers 264?265). One may decide not to reconfigure these bits, in which case the
		// configuration granularity becomes 4 pixels for both x? and y?configurations.
		// * default 0xc4c4
		// bit 0: x_start0(0) - default 0 (ROI0 - x start config (bit0))
		// bit 2 
		// SPI_Write(264, val);
		
		
		// Active ROI selection (195 vs 228??)
		SPI_Write(228, 0x0000);		// Choose ROI0
	}



// ========== NOT IN USE ========== //
void No_Transfer() 
{
	SPI_Write(402, 0xF002);
}

void Transfer() 
{
	SPI_Write(402, 0xF402);
}

// Enable E-black calibration images. Enables electrical black image
void Enable_Black() 
{			
	SPI_Write(220, 0x3C2B);
	No_Transfer();

}

// Enable E-gray calibration images. Enables electrical gray image
void Enable_Gray()
{				
	No_Transfer();
	SPI_Write(220, 0x3C4D);
}

// (Re)enable normal image mode. (Re-)enables 'normal' image capture
void DisableE()
{				
	Transfer();
	SPI_Write(220, 0x3C2B);
}

// Power on sequencer and accepting/outputting pixel values
void EnableSeq () 
{
	SPI_Write(192,0x0803);
}

// Power off sequencer and accepting/outputting pixel values
void Disable_Seq () 
{
	SPI_Write(192,0x0802);
}