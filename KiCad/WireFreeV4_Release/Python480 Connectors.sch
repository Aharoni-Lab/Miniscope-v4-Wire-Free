EESchema Schematic File Version 4
LIBS:WireFreeV4_Release-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 6
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 7500 5350 0    50   ~ 0
Data output - only using 8 out of 10
Entry Wire Line
	6200 4900 6300 5000
Entry Wire Line
	6200 4900 6300 5000
Entry Wire Line
	6200 5000 6300 5100
Entry Wire Line
	6200 5000 6300 5100
Entry Wire Line
	6200 5100 6300 5200
Entry Wire Line
	6200 5200 6300 5300
Entry Wire Line
	6200 5300 6300 5400
Entry Wire Line
	6200 5400 6300 5500
Entry Wire Line
	6200 5500 6300 5600
Entry Wire Line
	6200 5600 6300 5700
Text Label 6350 5350 0    50   ~ 0
img_d[0..7]
Text Label 5850 4900 0    50   ~ 0
img_d0
Wire Wire Line
	5800 4900 6200 4900
Wire Wire Line
	5800 5000 6200 5000
Wire Wire Line
	5800 5100 6200 5100
Wire Wire Line
	5800 5300 6200 5300
Wire Wire Line
	5800 5400 6200 5400
Wire Wire Line
	5800 5500 6200 5500
Wire Wire Line
	5800 5600 6200 5600
Connection ~ 6300 5350
Text HLabel 6800 5350 2    50   Output ~ 0
img_d[0..7]
Wire Wire Line
	5800 5200 6200 5200
Text Label 5850 5000 0    50   ~ 0
img_d1
Text Label 5850 5100 0    50   ~ 0
img_d2
Text Label 5850 5200 0    50   ~ 0
img_d3
Text Label 5850 5300 0    50   ~ 0
img_d4
Text Label 5850 5400 0    50   ~ 0
img_d5
Text Label 5850 5500 0    50   ~ 0
img_d6
Text Label 5850 5600 0    50   ~ 0
img_d7
Wire Bus Line
	6300 5350 6800 5350
Text HLabel 1975 4775 0    50   Output ~ 0
CLK_OUT
Text HLabel 1975 5475 0    50   Output ~ 0
FRAME_VALID
Text HLabel 1975 5575 0    50   Output ~ 0
LINE_VALID
Wire Wire Line
	2825 4175 3175 4175
$Comp
L power:Earth #PWR043
U 1 1 5CA4EDF4
P 2825 4175
F 0 "#PWR043" H 2825 3925 50  0001 C CNN
F 1 "Earth" H 2825 4025 50  0001 C CNN
F 2 "" H 2825 4175 50  0001 C CNN
F 3 "~" H 2825 4175 50  0001 C CNN
	1    2825 4175
	0    1    1    0   
$EndComp
Wire Wire Line
	2825 4275 3175 4275
$Comp
L power:+1V8 #PWR044
U 1 1 5CA4FD6F
P 2825 4275
F 0 "#PWR044" H 2825 4125 50  0001 C CNN
F 1 "+1V8" V 2840 4403 50  0000 L CNN
F 2 "" H 2825 4275 50  0001 C CNN
F 3 "" H 2825 4275 50  0001 C CNN
	1    2825 4275
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3175 4375 2825 4375
Text Label 2825 4375 0    50   ~ 0
img_d0
Wire Wire Line
	2825 4575 3175 4575
Wire Wire Line
	2825 4675 3175 4675
Wire Wire Line
	3175 5975 2825 5975
Wire Wire Line
	3175 6075 2825 6075
Wire Wire Line
	2825 4875 3175 4875
Wire Wire Line
	2825 4975 3175 4975
Wire Wire Line
	3175 5075 2825 5075
Wire Wire Line
	3175 5375 2825 5375
Wire Wire Line
	2825 5275 3175 5275
Wire Wire Line
	2825 5175 3175 5175
Text Label 2825 4575 0    50   ~ 0
img_d1
Text Label 2825 4675 0    50   ~ 0
img_d3
Text Label 2825 4875 0    50   ~ 0
img_d4
Text Label 2825 4975 0    50   ~ 0
img_d5
Text Label 2825 5075 0    50   ~ 0
img_d7
Text Label 2825 5175 0    50   ~ 0
img_d6
Text Label 2825 5275 0    50   ~ 0
img_d8
Text Label 2825 5375 0    50   ~ 0
img_d9
NoConn ~ 2825 5375
NoConn ~ 2825 5275
$Comp
L power:+3V3 #PWR046
U 1 1 5CA68D90
P 2825 5975
F 0 "#PWR046" H 2825 5825 50  0001 C CNN
F 1 "+3V3" V 2840 6103 50  0000 L CNN
F 2 "" H 2825 5975 50  0001 C CNN
F 3 "" H 2825 5975 50  0001 C CNN
	1    2825 5975
	0    -1   -1   0   
$EndComp
$Comp
L power:Earth #PWR047
U 1 1 5CA69189
P 2825 6075
F 0 "#PWR047" H 2825 5825 50  0001 C CNN
F 1 "Earth" H 2825 5925 50  0001 C CNN
F 2 "" H 2825 6075 50  0001 C CNN
F 3 "~" H 2825 6075 50  0001 C CNN
	1    2825 6075
	0    1    1    0   
$EndComp
Wire Wire Line
	1975 4775 3175 4775
Wire Wire Line
	1975 5475 3175 5475
Wire Wire Line
	1975 5575 3175 5575
Wire Wire Line
	2825 4475 3175 4475
Text Label 2825 4475 0    50   ~ 0
img_d2
$Comp
L power:+BATT #PWR045
U 1 1 5CA68C2B
P 2825 5875
F 0 "#PWR045" H 2825 5725 50  0001 C CNN
F 1 "+BATT" V 2840 6002 50  0000 L CNN
F 2 "" H 2825 5875 50  0001 C CNN
F 3 "" H 2825 5875 50  0001 C CNN
	1    2825 5875
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2825 5875 3175 5875
Wire Wire Line
	3175 5775 2825 5775
Wire Wire Line
	3175 5675 2825 5675
NoConn ~ 2825 5675
NoConn ~ 2825 5775
Text Label 2825 5675 0    50   ~ 0
I2C_SDA1
Text Label 2825 5775 0    50   ~ 0
I2C_SCL1
$Comp
L Connector_Generic:Conn_01x28 J2
U 1 1 5D422865
P 3375 5475
F 0 "J2" H 3455 5467 50  0000 L CNN
F 1 "Conn_01x28" H 3455 5376 50  0000 L CNN
F 2 ".Connector:B2B_Flex_28_Dual_Row_38milx24mil_Pad_20mil" H 3375 5475 50  0001 C CNN
F 3 "~" H 3375 5475 50  0001 C CNN
	1    3375 5475
	1    0    0    -1  
$EndComp
Text HLabel 1875 6175 0    50   Input ~ 0
Status_LED
Text Notes 5900 2100 0    50   ~ 0
Python board has its own status LED - \noverlap with MCU board status LED
Wire Wire Line
	1875 6675 3175 6675
Wire Wire Line
	1875 6575 3175 6575
Wire Wire Line
	1875 6175 3175 6175
Wire Wire Line
	1875 6475 3175 6475
Wire Wire Line
	1875 6775 3175 6775
Wire Wire Line
	1875 6275 3175 6275
Wire Wire Line
	1875 6375 3175 6375
Wire Wire Line
	1875 6875 3175 6875
Text HLabel 1875 6475 0    50   Output ~ 0
MONITOR0
Text HLabel 1875 6875 0    50   Input ~ 0
SS_N
Text HLabel 1875 6375 0    50   Input ~ 0
MISO
Text HLabel 1875 6275 0    50   Input ~ 0
MOSI
Text HLabel 1875 6775 0    50   Input ~ 0
SCK
Text HLabel 1875 6575 0    50   Input ~ 0
TRIGGER0
Text HLabel 1875 6675 0    50   Input ~ 0
RESET_N
Wire Bus Line
	6300 5350 6300 5700
Wire Bus Line
	6300 5000 6300 5350
$EndSCHEMATC
