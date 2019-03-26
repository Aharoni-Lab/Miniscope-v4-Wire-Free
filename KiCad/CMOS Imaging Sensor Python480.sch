EESchema Schematic File Version 4
LIBS:MiniScope_V4-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 7
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 6800 1750 2    50   Input ~ 0
Vref_botplate
Text GLabel 3400 3600 0    50   Input ~ 0
RESET_N
Text GLabel 3400 3700 0    50   Input ~ 0
TRIGGER0
Text GLabel 3400 4300 0    50   Input ~ 0
LOCK_DETECT
Text GLabel 3400 4200 0    50   Input ~ 0
MONITOR2
Text GLabel 3400 4100 0    50   Input ~ 0
MONITOR1
Text GLabel 3400 4000 0    50   Input ~ 0
MONITOR0
Text GLabel 7250 4650 2    50   Output ~ 0
CMOS_Sensor
Text GLabel 10150 1600 2    50   Output ~ 0
Vref_botplate
$Comp
L Device:C_Small C?
U 1 1 5C8866BD
P 9850 1700
F 0 "C?" H 9942 1746 50  0001 L CNN
F 1 "4.7 uF" H 9942 1700 50  0000 L CNN
F 2 "" H 9850 1700 50  0001 C CNN
F 3 "~" H 9850 1700 50  0001 C CNN
	1    9850 1700
	1    0    0    -1  
$EndComp
$Comp
L pspice:INDUCTOR BLM18AG?
U 1 1 5C886764
P 9550 1600
F 0 "BLM18AG?" H 9550 1815 50  0000 C CNN
F 1 "600" H 9550 1724 50  0000 C CNN
F 2 "" H 9550 1600 50  0001 C CNN
F 3 "~" H 9550 1600 50  0001 C CNN
	1    9550 1600
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5C88A93E
P 8050 1800
F 0 "C?" H 8142 1846 50  0001 L CNN
F 1 "0.1 uF" H 8142 1800 50  0000 L CNN
F 2 "" H 8050 1800 50  0001 C CNN
F 3 "~" H 8050 1800 50  0001 C CNN
	1    8050 1800
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5C88AF6B
P 9000 1050
F 0 "C?" H 8908 1004 50  0001 R CNN
F 1 "0.1 uF" V 9100 1150 50  0000 R CNN
F 2 "" H 9000 1050 50  0001 C CNN
F 3 "~" H 9000 1050 50  0001 C CNN
	1    9000 1050
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:LMV321 U?
U 1 1 5C88B134
P 8900 1600
F 0 "U?" H 8950 1450 50  0000 L CNN
F 1 "LMV321" H 8900 1750 50  0000 L CNN
F 2 "" H 8900 1600 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/lmv324.pdf" H 8900 1600 50  0001 C CNN
	1    8900 1600
	1    0    0    1   
$EndComp
Wire Wire Line
	7650 1700 8050 1700
Wire Wire Line
	9800 1600 9850 1600
Wire Wire Line
	10150 1600 9850 1600
Connection ~ 9850 1600
Text Notes 2350 3100 0    50   ~ 0
SPI instead of I2C
Text Notes 1800 3700 0    50   ~ 0
Reset and start - 'commands'
Text Notes 2000 5750 0    50   ~ 0
Connect to a 68Mhz clock
Text Notes 6700 4850 0    50   ~ 0
Data output - only using 8 out of 10
Text Notes 6750 3300 0    50   ~ 0
LVDS receiver
Text Notes 6750 3550 0    50   ~ 0
LVDS receiver
Text Notes 6750 3800 0    50   ~ 0
LVDS receiver
Text Notes 8200 650  0    50   ~ 0
Seems like the high-frequency fluctuation filter
Connection ~ 5150 1250
Wire Wire Line
	5150 1250 4950 1250
Wire Wire Line
	5150 1450 4950 1450
$Comp
L Device:C_Small C?
U 1 1 5C89CC77
P 6200 900
F 0 "C?" V 6400 950 50  0001 R CNN
F 1 "100 nF" V 6300 750 50  0000 L CNN
F 2 "" H 6200 900 50  0001 C CNN
F 3 "~" H 6200 900 50  0001 C CNN
	1    6200 900 
	1    0    0    1   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5C89CCDE
P 6000 900
F 0 "C?" V 6200 950 50  0001 R CNN
F 1 "10 uF" V 6100 800 50  0000 L CNN
F 2 "" H 6000 900 50  0001 C CNN
F 3 "~" H 6000 900 50  0001 C CNN
	1    6000 900 
	1    0    0    1   
$EndComp
Wire Wire Line
	6000 800  6200 800 
$Comp
L Device:C_Small C?
U 1 1 5C89FCEB
P 6600 1850
F 0 "C?" V 6800 1900 50  0001 R CNN
F 1 "100 nF" V 6700 1700 50  0000 L CNN
F 2 "" H 6600 1850 50  0001 C CNN
F 3 "~" H 6600 1850 50  0001 C CNN
	1    6600 1850
	1    0    0    1   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5C89FD02
P 6400 1850
F 0 "C?" V 6600 1900 50  0001 R CNN
F 1 "10 uF" V 6500 1750 50  0000 L CNN
F 2 "" H 6400 1850 50  0001 C CNN
F 3 "~" H 6400 1850 50  0001 C CNN
	1    6400 1850
	1    0    0    1   
$EndComp
Text Notes 2550 2750 0    50   ~ 0
Low tolerance for VDD-pix: from 3.25 to 3.35
Text Notes 2050 2950 0    50   ~ 0
Label each wire on a bus\nsame name & # increments
$Comp
L Device:R_Small_US R?
U 1 1 5C8A3090
P 4200 6050
F 0 "R?" H 4268 6096 50  0001 L CNN
F 1 "47.7k" H 4268 6050 50  0000 L CNN
F 2 "" H 4200 6050 50  0001 C CNN
F 3 "~" H 4200 6050 50  0001 C CNN
	1    4200 6050
	1    0    0    -1  
$EndComp
Text GLabel 3400 3250 0    50   Input ~ 0
SCK
Text GLabel 3400 3150 0    50   Input ~ 0
MOSI
Text GLabel 3400 3050 0    50   Input ~ 0
MISO
Text GLabel 3400 2950 0    50   Input ~ 0
SS_N
NoConn ~ 6400 3100
NoConn ~ 6400 3200
NoConn ~ 6400 3400
NoConn ~ 6400 3500
NoConn ~ 6400 3650
NoConn ~ 6400 3750
Connection ~ 8050 1700
Wire Wire Line
	8050 1700 8600 1700
Wire Wire Line
	9000 950  8800 950 
Wire Wire Line
	8800 950  8800 1300
Wire Wire Line
	9200 1600 9300 1600
Wire Wire Line
	9200 1600 9200 700 
Wire Wire Line
	9200 700  8550 700 
Wire Wire Line
	8550 700  8550 1500
Wire Wire Line
	8550 1500 8600 1500
Connection ~ 9200 1600
Text GLabel 7250 5400 2    50   Output ~ 0
FRAME_VALID
Text GLabel 7250 5500 2    50   Output ~ 0
LINE_VALID
Text GLabel 7250 5300 2    50   Output ~ 0
CLK_OUT
Text Notes 1750 4150 0    50   ~ 0
Find out what monitors are for
Wire Wire Line
	6200 1000 6000 1000
Connection ~ 6200 1000
Wire Wire Line
	5850 800  6000 800 
Connection ~ 6000 800 
Wire Wire Line
	6400 1950 6600 1950
Wire Wire Line
	6600 1750 6400 1750
Wire Wire Line
	6800 1750 6600 1750
Connection ~ 6600 1750
Wire Wire Line
	5350 6750 5350 6550
Entry Wire Line
	6400 4200 6500 4300
Entry Wire Line
	6400 4200 6500 4300
Entry Wire Line
	6400 4300 6500 4400
Entry Wire Line
	6400 4300 6500 4400
Entry Wire Line
	6400 4400 6500 4500
Entry Wire Line
	6400 4500 6500 4600
Entry Wire Line
	6400 4600 6500 4700
Entry Wire Line
	6400 4700 6500 4800
Entry Wire Line
	6400 4800 6500 4900
Entry Wire Line
	6400 4900 6500 5000
Wire Bus Line
	6500 4650 7250 4650
Connection ~ 6500 4650
Text Label 6750 4650 0    50   ~ 0
d[0:7]
Text Label 6500 4300 0    50   ~ 0
d0
Text Label 6500 4400 0    50   ~ 0
d1
Text Label 6500 4500 0    50   ~ 0
d2
Text Label 6500 4600 0    50   ~ 0
d3
Text Label 6500 4700 0    50   ~ 0
d4
Text Label 6500 4800 0    50   ~ 0
d5
Text Label 6500 4900 0    50   ~ 0
d6
Text Label 6500 5000 0    50   ~ 0
d7
Text Notes 8150 1900 0    50   ~ 0
16V
Text Notes 9150 1100 0    50   ~ 0
16V
Text Notes 9950 1800 0    50   ~ 0
16V
Text GLabel 3400 5700 0    50   Input ~ 0
CLOCK
NoConn ~ 4350 4550
NoConn ~ 4350 4650
NoConn ~ 4350 4750
NoConn ~ 4350 4850
NoConn ~ 4350 4950
NoConn ~ 4350 5050
Wire Wire Line
	3400 3700 4350 3700
Wire Wire Line
	3400 3600 4350 3600
Wire Wire Line
	3400 2950 4350 2950
Wire Wire Line
	3400 3050 4350 3050
Wire Wire Line
	3400 3150 4350 3150
Wire Wire Line
	3400 3250 4350 3250
Wire Wire Line
	3400 5700 4350 5700
NoConn ~ 6400 5000
NoConn ~ 6400 5100
Connection ~ 5350 6550
Wire Wire Line
	4200 5950 4200 5850
Wire Wire Line
	4200 5850 4350 5850
Wire Wire Line
	3400 4000 4350 4000
Wire Wire Line
	3400 4100 4350 4100
Wire Wire Line
	3400 4200 4350 4200
Wire Wire Line
	3400 4300 4350 4300
Wire Wire Line
	5150 1250 5400 1250
Wire Wire Line
	5400 1250 5400 2300
Text Label 6200 2650 2    50   ~ 0
H6-Vrel_botplate
Wire Wire Line
	5350 6550 5400 6550
$Comp
L .Image_Sensor:NOIP1SN0480A U?
U 1 1 5C8B463E
P 5300 4300
F 0 "U?" H 5375 6478 50  0000 C CNN
F 1 "NOIP1SN0480A" H 5375 6387 50  0000 C CNN
F 2 ".Package_BGA:BGA88CP50_8X11_493X613X75B25" H 5200 6700 50  0001 C CNN
F 3 "https://www.onsemi.com/pub/Collateral/NOIP1SN0480A-D.PDF" H 5050 6350 50  0001 C CNN
	1    5300 4300
	1    0    0    -1  
$EndComp
Connection ~ 5300 6550
Wire Wire Line
	5300 6550 5350 6550
Connection ~ 5400 2300
Connection ~ 5400 6550
Connection ~ 5850 2300
Wire Wire Line
	6400 5400 7250 5400
Wire Wire Line
	6400 5500 7250 5500
Wire Wire Line
	6400 5300 7250 5300
Wire Wire Line
	4750 6550 4850 6550
Connection ~ 4850 6550
Wire Wire Line
	4850 6550 4950 6550
Connection ~ 4950 6550
Wire Wire Line
	4950 6550 5100 6550
Connection ~ 5100 6550
Wire Wire Line
	5100 6550 5200 6550
Connection ~ 5200 6550
Connection ~ 5550 6550
Wire Wire Line
	5550 6550 5650 6550
Connection ~ 5650 6550
Wire Wire Line
	5650 6550 5750 6550
Connection ~ 5750 6550
Wire Wire Line
	5750 6550 5850 6550
Connection ~ 5850 6550
Wire Wire Line
	5850 6550 5950 6550
Wire Wire Line
	5400 6550 5550 6550
Wire Wire Line
	5250 6550 5300 6550
Wire Wire Line
	4350 5300 4350 5400
Wire Wire Line
	5200 6550 5300 6550
Connection ~ 4350 5400
Wire Wire Line
	4350 5400 4350 5450
Connection ~ 4350 5450
Wire Wire Line
	4350 5450 4350 5500
Connection ~ 4350 5500
Wire Wire Line
	4350 5500 4350 5600
Wire Wire Line
	5450 2300 5400 2300
Wire Wire Line
	5300 2300 5400 2300
Wire Wire Line
	5400 2300 5500 2300
Wire Wire Line
	5850 2300 5950 2300
Wire Wire Line
	5750 2300 5850 2300
Wire Wire Line
	6400 1750 6100 1750
Wire Wire Line
	6100 1750 6100 2300
Connection ~ 6400 1750
NoConn ~ 6400 3900
NoConn ~ 6400 4000
Wire Wire Line
	3600 5450 4350 5450
$Comp
L power:+1V8 #PWR?
U 1 1 5C902A22
P 7650 1700
F 0 "#PWR?" H 7650 1550 50  0001 C CNN
F 1 "+1V8" H 7665 1873 50  0000 C CNN
F 2 "" H 7650 1700 50  0001 C CNN
F 3 "" H 7650 1700 50  0001 C CNN
	1    7650 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 800  5850 2300
$Comp
L pspice:INDUCTOR BLM18AG?
U 1 1 5C94DC90
P 6850 800
F 0 "BLM18AG?" H 6850 1015 50  0000 C CNN
F 1 "600" H 6850 924 50  0000 C CNN
F 2 "" H 6850 800 50  0001 C CNN
F 3 "~" H 6850 800 50  0001 C CNN
	1    6850 800 
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5C94DCD0
P 7200 800
F 0 "#PWR?" H 7200 650 50  0001 C CNN
F 1 "+3.3V" H 7215 973 50  0000 C CNN
F 2 "" H 7200 800 50  0001 C CNN
F 3 "" H 7200 800 50  0001 C CNN
	1    7200 800 
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7100 800  7200 800 
Wire Wire Line
	6200 800  6400 800 
Connection ~ 6200 800 
$Comp
L Device:C_Small C?
U 1 1 5C9690BE
P 6400 900
F 0 "C?" V 6600 950 50  0001 R CNN
F 1 "100 nF" V 6500 750 50  0000 L CNN
F 2 "" H 6400 900 50  0001 C CNN
F 3 "~" H 6400 900 50  0001 C CNN
	1    6400 900 
	1    0    0    1   
$EndComp
Connection ~ 6400 800 
Wire Wire Line
	6400 800  6600 800 
$Comp
L Device:C_Small C?
U 1 1 5C9690D7
P 6600 900
F 0 "C?" V 6800 950 50  0001 R CNN
F 1 "100 nF" V 6700 750 50  0000 L CNN
F 2 "" H 6600 900 50  0001 C CNN
F 3 "~" H 6600 900 50  0001 C CNN
	1    6600 900 
	1    0    0    1   
$EndComp
Connection ~ 6600 800 
Wire Wire Line
	6600 1000 6400 1000
Connection ~ 6400 1000
$Comp
L Device:C_Small C?
U 1 1 5C96D3D7
P 4950 1350
F 0 "C?" V 5150 1400 50  0001 R CNN
F 1 "100 nF" V 4850 1200 50  0000 L CNN
F 2 "" H 4950 1350 50  0001 C CNN
F 3 "~" H 4950 1350 50  0001 C CNN
	1    4950 1350
	1    0    0    1   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5C96D3EF
P 5150 1350
F 0 "C?" V 5350 1400 50  0001 R CNN
F 1 "10 uF" V 5050 1250 50  0000 L CNN
F 2 "" H 5150 1350 50  0001 C CNN
F 3 "~" H 5150 1350 50  0001 C CNN
	1    5150 1350
	1    0    0    1   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5C96D402
P 4750 1350
F 0 "C?" V 4950 1400 50  0001 R CNN
F 1 "100 nF" V 4650 1200 50  0000 L CNN
F 2 "" H 4750 1350 50  0001 C CNN
F 3 "~" H 4750 1350 50  0001 C CNN
	1    4750 1350
	1    0    0    1   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5C96D415
P 4550 1350
F 0 "C?" V 4750 1400 50  0001 R CNN
F 1 "100 nF" V 4450 1200 50  0000 L CNN
F 2 "" H 4550 1350 50  0001 C CNN
F 3 "~" H 4550 1350 50  0001 C CNN
	1    4550 1350
	1    0    0    1   
$EndComp
Wire Wire Line
	4950 1250 4750 1250
Connection ~ 4950 1250
Connection ~ 4750 1250
Wire Wire Line
	4750 1250 4550 1250
Wire Wire Line
	4550 1450 4750 1450
Connection ~ 4950 1450
Connection ~ 4750 1450
Wire Wire Line
	4750 1450 4950 1450
Wire Wire Line
	4850 1650 4850 2300
Wire Wire Line
	4650 2300 4750 2300
Connection ~ 4750 2300
Wire Wire Line
	4750 2300 4850 2300
Connection ~ 4850 2300
Wire Wire Line
	4850 2300 4950 2300
Connection ~ 4950 2300
Wire Wire Line
	4950 2300 5050 2300
$Comp
L Device:C_Small C?
U 1 1 5C984146
P 4600 1750
F 0 "C?" V 4800 1800 50  0001 R CNN
F 1 "10 uF" V 4500 1650 50  0000 L CNN
F 2 "" H 4600 1750 50  0001 C CNN
F 3 "~" H 4600 1750 50  0001 C CNN
	1    4600 1750
	1    0    0    1   
$EndComp
Connection ~ 4600 1650
Wire Wire Line
	4600 1650 4850 1650
$Comp
L Device:C_Small C?
U 1 1 5C98415B
P 4400 1750
F 0 "C?" V 4600 1800 50  0001 R CNN
F 1 "100 nF" V 4300 1600 50  0000 L CNN
F 2 "" H 4400 1750 50  0001 C CNN
F 3 "~" H 4400 1750 50  0001 C CNN
	1    4400 1750
	1    0    0    1   
$EndComp
Connection ~ 4400 1650
Wire Wire Line
	4400 1650 4600 1650
$Comp
L Device:C_Small C?
U 1 1 5C984170
P 4200 1750
F 0 "C?" V 4400 1800 50  0001 R CNN
F 1 "100 nF" V 4100 1600 50  0000 L CNN
F 2 "" H 4200 1750 50  0001 C CNN
F 3 "~" H 4200 1750 50  0001 C CNN
	1    4200 1750
	1    0    0    1   
$EndComp
Connection ~ 4200 1650
Wire Wire Line
	4200 1650 4400 1650
$Comp
L Device:C_Small C?
U 1 1 5C984185
P 4000 1750
F 0 "C?" V 4200 1800 50  0001 R CNN
F 1 "100 nF" V 3900 1600 50  0000 L CNN
F 2 "" H 4000 1750 50  0001 C CNN
F 3 "~" H 4000 1750 50  0001 C CNN
	1    4000 1750
	1    0    0    1   
$EndComp
Connection ~ 4000 1650
Wire Wire Line
	4000 1650 4200 1650
$Comp
L Device:C_Small C?
U 1 1 5C98419A
P 3800 1750
F 0 "C?" V 4000 1800 50  0001 R CNN
F 1 "100 nF" V 3700 1600 50  0000 L CNN
F 2 "" H 3800 1750 50  0001 C CNN
F 3 "~" H 3800 1750 50  0001 C CNN
	1    3800 1750
	1    0    0    1   
$EndComp
$Comp
L Device:C_Small C?
U 1 1 5C9841AD
P 3600 1750
F 0 "C?" V 3800 1800 50  0001 R CNN
F 1 "100 nF" V 3500 1600 50  0000 L CNN
F 2 "" H 3600 1750 50  0001 C CNN
F 3 "~" H 3600 1750 50  0001 C CNN
	1    3600 1750
	1    0    0    1   
$EndComp
Wire Wire Line
	3600 1650 3800 1650
Connection ~ 3800 1650
Wire Wire Line
	3800 1650 4000 1650
Wire Wire Line
	3600 1850 3800 1850
Connection ~ 3800 1850
Wire Wire Line
	3800 1850 4000 1850
Connection ~ 4000 1850
Wire Wire Line
	4000 1850 4200 1850
Connection ~ 4200 1850
Wire Wire Line
	4200 1850 4400 1850
Connection ~ 4400 1850
Wire Wire Line
	4400 1850 4600 1850
$Comp
L power:+1V8 #PWR?
U 1 1 5C98A63A
P 4550 1250
F 0 "#PWR?" H 4550 1100 50  0001 C CNN
F 1 "+1V8" H 4565 1423 50  0000 C CNN
F 2 "" H 4550 1250 50  0001 C CNN
F 3 "" H 4550 1250 50  0001 C CNN
	1    4550 1250
	-1   0    0    -1  
$EndComp
Connection ~ 4550 1250
Wire Wire Line
	6200 1000 6400 1000
$Comp
L power:+3.3V #PWR?
U 1 1 5C98A684
P 3600 1650
F 0 "#PWR?" H 3600 1500 50  0001 C CNN
F 1 "+3.3V" H 3615 1823 50  0000 C CNN
F 2 "" H 3600 1650 50  0001 C CNN
F 3 "" H 3600 1650 50  0001 C CNN
	1    3600 1650
	-1   0    0    -1  
$EndComp
Connection ~ 3600 1650
$Comp
L power:Earth #PWR?
U 1 1 5C98AA97
P 4600 1850
F 0 "#PWR?" H 4600 1600 50  0001 C CNN
F 1 "Earth" H 4600 1700 50  0001 C CNN
F 2 "" H 4600 1850 50  0001 C CNN
F 3 "~" H 4600 1850 50  0001 C CNN
	1    4600 1850
	1    0    0    -1  
$EndComp
Connection ~ 4600 1850
$Comp
L power:Earth #PWR?
U 1 1 5C98AACD
P 5150 1450
F 0 "#PWR?" H 5150 1200 50  0001 C CNN
F 1 "Earth" H 5150 1300 50  0001 C CNN
F 2 "" H 5150 1450 50  0001 C CNN
F 3 "~" H 5150 1450 50  0001 C CNN
	1    5150 1450
	1    0    0    -1  
$EndComp
Connection ~ 5150 1450
$Comp
L power:Earth #PWR?
U 1 1 5C98AB03
P 6000 1000
F 0 "#PWR?" H 6000 750 50  0001 C CNN
F 1 "Earth" H 6000 850 50  0001 C CNN
F 2 "" H 6000 1000 50  0001 C CNN
F 3 "~" H 6000 1000 50  0001 C CNN
	1    6000 1000
	1    0    0    -1  
$EndComp
Connection ~ 6000 1000
$Comp
L power:Earth #PWR?
U 1 1 5C98AB1B
P 6600 1950
F 0 "#PWR?" H 6600 1700 50  0001 C CNN
F 1 "Earth" H 6600 1800 50  0001 C CNN
F 2 "" H 6600 1950 50  0001 C CNN
F 3 "~" H 6600 1950 50  0001 C CNN
	1    6600 1950
	1    0    0    -1  
$EndComp
Connection ~ 6600 1950
$Comp
L power:Earth #PWR?
U 1 1 5C98AB33
P 8050 1900
F 0 "#PWR?" H 8050 1650 50  0001 C CNN
F 1 "Earth" H 8050 1750 50  0001 C CNN
F 2 "" H 8050 1900 50  0001 C CNN
F 3 "~" H 8050 1900 50  0001 C CNN
	1    8050 1900
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR?
U 1 1 5C991CCF
P 9000 1150
F 0 "#PWR?" H 9000 900 50  0001 C CNN
F 1 "Earth" H 9000 1000 50  0001 C CNN
F 2 "" H 9000 1150 50  0001 C CNN
F 3 "~" H 9000 1150 50  0001 C CNN
	1    9000 1150
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR?
U 1 1 5C991CE7
P 8800 1900
F 0 "#PWR?" H 8800 1650 50  0001 C CNN
F 1 "Earth" H 8800 1750 50  0001 C CNN
F 2 "" H 8800 1900 50  0001 C CNN
F 3 "~" H 8800 1900 50  0001 C CNN
	1    8800 1900
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR?
U 1 1 5C991CFF
P 9850 1800
F 0 "#PWR?" H 9850 1550 50  0001 C CNN
F 1 "Earth" H 9850 1650 50  0001 C CNN
F 2 "" H 9850 1800 50  0001 C CNN
F 3 "~" H 9850 1800 50  0001 C CNN
	1    9850 1800
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR?
U 1 1 5C991FBF
P 5350 6750
F 0 "#PWR?" H 5350 6500 50  0001 C CNN
F 1 "Earth" H 5350 6600 50  0001 C CNN
F 2 "" H 5350 6750 50  0001 C CNN
F 3 "~" H 5350 6750 50  0001 C CNN
	1    5350 6750
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR?
U 1 1 5C991FDF
P 4200 6150
F 0 "#PWR?" H 4200 5900 50  0001 C CNN
F 1 "Earth" H 4200 6000 50  0001 C CNN
F 2 "" H 4200 6150 50  0001 C CNN
F 3 "~" H 4200 6150 50  0001 C CNN
	1    4200 6150
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR?
U 1 1 5C991FF7
P 3600 5450
F 0 "#PWR?" H 3600 5200 50  0001 C CNN
F 1 "Earth" H 3600 5300 50  0001 C CNN
F 2 "" H 3600 5450 50  0001 C CNN
F 3 "~" H 3600 5450 50  0001 C CNN
	1    3600 5450
	1    0    0    -1  
$EndComp
Wire Bus Line
	6500 4300 6500 4650
Wire Bus Line
	6500 4650 6500 5000
$Comp
L power:+BATT #PWR?
U 1 1 5CA2EFDB
P 9000 950
F 0 "#PWR?" H 9000 800 50  0001 C CNN
F 1 "+BATT" H 9015 1123 50  0000 C CNN
F 2 "" H 9000 950 50  0001 C CNN
F 3 "" H 9000 950 50  0001 C CNN
	1    9000 950 
	1    0    0    -1  
$EndComp
Connection ~ 9000 950 
$EndSCHEMATC
