EESchema Schematic File Version 4
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
Text HLabel 3550 2450 0    50   Output ~ 0
CLK_OUT
Text HLabel 3550 3150 0    50   Output ~ 0
FRAME_VALID
Text HLabel 3550 3250 0    50   Output ~ 0
LINE_VALID
Text HLabel 6900 2800 0    50   Input ~ 0
RESET_N
Text HLabel 6900 2700 0    50   Input ~ 0
TRIGGER0
Text HLabel 6900 2900 0    50   Input ~ 0
SCK
Text HLabel 6900 2400 0    50   Input ~ 0
MOSI
Text HLabel 6900 2500 0    50   Input ~ 0
MISO
Text HLabel 6900 3200 0    50   Input ~ 0
SS_N
Text HLabel 6900 2600 0    50   Output ~ 0
MONITOR0
Wire Wire Line
	4400 1850 4750 1850
$Comp
L power:Earth #PWR0102
U 1 1 5CA4EDF4
P 4400 1850
F 0 "#PWR0102" H 4400 1600 50  0001 C CNN
F 1 "Earth" H 4400 1700 50  0001 C CNN
F 2 "" H 4400 1850 50  0001 C CNN
F 3 "~" H 4400 1850 50  0001 C CNN
	1    4400 1850
	0    1    1    0   
$EndComp
Wire Wire Line
	4400 1950 4750 1950
$Comp
L power:+1V8 #PWR0103
U 1 1 5CA4FD6F
P 4400 1950
F 0 "#PWR0103" H 4400 1800 50  0001 C CNN
F 1 "+1V8" V 4415 2078 50  0000 L CNN
F 2 "" H 4400 1950 50  0001 C CNN
F 3 "" H 4400 1950 50  0001 C CNN
	1    4400 1950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4750 2050 4400 2050
Text Label 4400 2050 0    50   ~ 0
img_d0
Wire Wire Line
	4400 2250 4750 2250
Wire Wire Line
	4400 2350 4750 2350
Wire Wire Line
	4750 3650 4400 3650
Wire Wire Line
	4750 3750 4400 3750
Wire Wire Line
	4400 2550 4750 2550
Wire Wire Line
	4400 2650 4750 2650
Wire Wire Line
	4750 2750 4400 2750
Wire Wire Line
	4750 3050 4400 3050
Wire Wire Line
	4400 2950 4750 2950
Wire Wire Line
	4400 2850 4750 2850
Text Label 4400 2250 0    50   ~ 0
img_d1
Text Label 4400 2350 0    50   ~ 0
img_d3
Text Label 4400 2550 0    50   ~ 0
img_d4
Text Label 4400 2650 0    50   ~ 0
img_d5
Text Label 4400 2750 0    50   ~ 0
img_d7
Text Label 4400 2850 0    50   ~ 0
img_d6
Text Label 4400 2950 0    50   ~ 0
img_d8
Text Label 4400 3050 0    50   ~ 0
img_d9
NoConn ~ 4400 3050
NoConn ~ 4400 2950
$Comp
L power:+3V3 #PWR0105
U 1 1 5CA68D90
P 4400 3650
F 0 "#PWR0105" H 4400 3500 50  0001 C CNN
F 1 "+3V3" V 4415 3778 50  0000 L CNN
F 2 "" H 4400 3650 50  0001 C CNN
F 3 "" H 4400 3650 50  0001 C CNN
	1    4400 3650
	0    -1   -1   0   
$EndComp
$Comp
L power:Earth #PWR0106
U 1 1 5CA69189
P 4400 3750
F 0 "#PWR0106" H 4400 3500 50  0001 C CNN
F 1 "Earth" H 4400 3600 50  0001 C CNN
F 2 "" H 4400 3750 50  0001 C CNN
F 3 "~" H 4400 3750 50  0001 C CNN
	1    4400 3750
	0    1    1    0   
$EndComp
Wire Wire Line
	7850 3400 8200 3400
Wire Wire Line
	7850 3300 8200 3300
Wire Wire Line
	7850 2300 8200 2300
Wire Wire Line
	8200 2100 7850 2100
$Comp
L power:+BATT #PWR0107
U 1 1 5CA83899
P 7850 2100
F 0 "#PWR0107" H 7850 1950 50  0001 C CNN
F 1 "+BATT" V 7865 2227 50  0000 L CNN
F 2 "" H 7850 2100 50  0001 C CNN
F 3 "" H 7850 2100 50  0001 C CNN
	1    7850 2100
	0    -1   -1   0   
$EndComp
$Comp
L power:+3V3 #PWR0108
U 1 1 5CA83E3B
P 7850 2300
F 0 "#PWR0108" H 7850 2150 50  0001 C CNN
F 1 "+3V3" V 7865 2428 50  0000 L CNN
F 2 "" H 7850 2300 50  0001 C CNN
F 3 "" H 7850 2300 50  0001 C CNN
	1    7850 2300
	0    -1   -1   0   
$EndComp
$Comp
L power:+1V8 #PWR0109
U 1 1 5CA89FAF
P 7850 3300
F 0 "#PWR0109" H 7850 3150 50  0001 C CNN
F 1 "+1V8" V 7865 3428 50  0000 L CNN
F 2 "" H 7850 3300 50  0001 C CNN
F 3 "" H 7850 3300 50  0001 C CNN
	1    7850 3300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6900 3200 8200 3200
Wire Wire Line
	6900 2500 8200 2500
Wire Wire Line
	6900 2400 8200 2400
Wire Wire Line
	6900 2900 8200 2900
Wire Wire Line
	6900 2600 8200 2600
Wire Wire Line
	3550 2450 4750 2450
Wire Wire Line
	3550 3150 4750 3150
Wire Wire Line
	3550 3250 4750 3250
Text HLabel 6900 3000 0    50   Input ~ 0
CLOCK
Text Notes 5550 3050 0    50   ~ 0
Connect to a 68Mhz clock
Wire Wire Line
	6900 3000 8200 3000
Wire Wire Line
	6900 2200 8200 2200
Text HLabel 6900 2200 0    50   Input ~ 0
LED
$Comp
L Connector_Generic:Conn_01x20 J6
U 1 1 5CADAE78
P 4950 2750
F 0 "J6" H 5030 2742 50  0000 L CNN
F 1 "Conn_01x20" H 5030 2651 50  0000 L CNN
F 2 ".Connector:B2B_Flex_20_Dual_Row_38milx24mil_Pad_20mil" H 4950 2750 50  0001 C CNN
F 3 "~" H 4950 2750 50  0001 C CNN
	1    4950 2750
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x14 J9
U 1 1 5CADC05E
P 8400 2700
F 0 "J9" H 8480 2692 50  0000 L CNN
F 1 "Conn_01x14" H 8480 2601 50  0000 L CNN
F 2 ".Connector:B2B_Flex_14_Dual_Row_38milx24mil_Pad_20mil" H 8400 2700 50  0001 C CNN
F 3 "~" H 8400 2700 50  0001 C CNN
	1    8400 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 2150 4750 2150
Text Label 4400 2150 0    50   ~ 0
img_d2
$Comp
L power:+BATT #PWR0104
U 1 1 5CA68C2B
P 4400 3550
F 0 "#PWR0104" H 4400 3400 50  0001 C CNN
F 1 "+BATT" V 4415 3677 50  0000 L CNN
F 2 "" H 4400 3550 50  0001 C CNN
F 3 "" H 4400 3550 50  0001 C CNN
	1    4400 3550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4400 3550 4750 3550
NoConn ~ 4750 3350
NoConn ~ 4750 3450
NoConn ~ 8200 3100
Text Notes 5700 1200 0    50   ~ 0
Hole or Pad?
Text Notes 5550 1300 0    50   ~ 0
Choosing pad for now
Wire Notes Line
	5400 1000 6500 1000
Wire Notes Line
	6550 1000 6550 1450
Wire Notes Line
	6550 1450 5450 1450
Wire Notes Line
	5400 1450 5400 1000
Wire Wire Line
	6900 2700 8200 2700
Wire Wire Line
	6900 2800 8200 2800
$Comp
L power:Earth #PWR0110
U 1 1 5CA8A424
P 7850 3400
F 0 "#PWR0110" H 7850 3150 50  0001 C CNN
F 1 "Earth" H 7850 3250 50  0001 C CNN
F 2 "" H 7850 3400 50  0001 C CNN
F 3 "~" H 7850 3400 50  0001 C CNN
	1    7850 3400
	0    1    1    0   
$EndComp
Wire Bus Line
	6300 5350 6300 5700
Wire Bus Line
	6300 5000 6300 5350
$EndSCHEMATC
