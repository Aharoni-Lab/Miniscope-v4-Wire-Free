EESchema Schematic File Version 4
LIBS:WireFreeV4_Release-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 6
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:+1V8 #PWR016
U 1 1 5CA13D29
P 3900 2950
F 0 "#PWR016" H 3900 2800 50  0001 C CNN
F 1 "+1V8" H 3915 3123 50  0000 C CNN
F 2 "" H 3900 2950 50  0001 C CNN
F 3 "" H 3900 2950 50  0001 C CNN
	1    3900 2950
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR017
U 1 1 5CA13D91
P 3950 3250
F 0 "#PWR017" H 3950 3000 50  0001 C CNN
F 1 "Earth" H 3950 3100 50  0001 C CNN
F 2 "" H 3950 3250 50  0001 C CNN
F 3 "~" H 3950 3250 50  0001 C CNN
	1    3950 3250
	1    0    0    -1  
$EndComp
$Comp
L .Connector:Conn_01x01 J10
U 1 1 5CA161C4
P 4450 2950
F 0 "J10" H 4530 2992 50  0000 L CNN
F 1 "Conn_01x01" H 4530 2901 50  0000 L CNN
F 2 ".Connector:Conn_1x1_700_Circular_Pad" H 4450 2950 50  0001 C CNN
F 3 "~" H 4450 2950 50  0001 C CNN
	1    4450 2950
	1    0    0    -1  
$EndComp
$Comp
L .Connector:Conn_01x01 J11
U 1 1 5CA16203
P 4450 3050
F 0 "J11" H 4530 3092 50  0000 L CNN
F 1 "Conn_01x01" H 4530 3001 50  0000 L CNN
F 2 ".Connector:Conn_1x1_700_Circular_Pad" H 4450 3050 50  0001 C CNN
F 3 "~" H 4450 3050 50  0001 C CNN
	1    4450 3050
	1    0    0    -1  
$EndComp
$Comp
L .Connector:Conn_01x01 J12
U 1 1 5CA16222
P 4450 3150
F 0 "J12" H 4530 3192 50  0000 L CNN
F 1 "Conn_01x01" H 4530 3101 50  0000 L CNN
F 2 ".Connector:Conn_1x1_700_Circular_Pad" H 4450 3150 50  0001 C CNN
F 3 "~" H 4450 3150 50  0001 C CNN
	1    4450 3150
	1    0    0    -1  
$EndComp
$Comp
L .Connector:Conn_01x01 J13
U 1 1 5CA16277
P 4450 3250
F 0 "J13" H 4530 3292 50  0000 L CNN
F 1 "Conn_01x01" H 4530 3201 50  0000 L CNN
F 2 ".Connector:Conn_1x1_700_Circular_Pad" H 4450 3250 50  0001 C CNN
F 3 "~" H 4450 3250 50  0001 C CNN
	1    4450 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 3150 4250 3150
Wire Wire Line
	4250 3050 3950 3050
Wire Wire Line
	3900 2950 4250 2950
Wire Wire Line
	3950 3250 4250 3250
$Comp
L .Connector:Conn_01x01 J14
U 1 1 5CA26767
P 4450 4350
F 0 "J14" H 4530 4392 50  0000 L CNN
F 1 "Conn_01x01" H 4530 4301 50  0000 L CNN
F 2 ".Connector:Conn_1x1_700_Circular_Pad" H 4450 4350 50  0001 C CNN
F 3 "~" H 4450 4350 50  0001 C CNN
	1    4450 4350
	1    0    0    -1  
$EndComp
$Comp
L .Connector:Conn_01x01 J15
U 1 1 5CA267B7
P 4450 4450
F 0 "J15" H 4530 4492 50  0000 L CNN
F 1 "Conn_01x01" H 4530 4401 50  0000 L CNN
F 2 ".Connector:Conn_1x1_700_Circular_Pad" H 4450 4450 50  0001 C CNN
F 3 "~" H 4450 4450 50  0001 C CNN
	1    4450 4450
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR018
U 1 1 5CA268F4
P 4250 4350
F 0 "#PWR018" H 4250 4200 50  0001 C CNN
F 1 "+BATT" H 4265 4523 50  0000 C CNN
F 2 "" H 4250 4350 50  0001 C CNN
F 3 "" H 4250 4350 50  0001 C CNN
	1    4250 4350
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR019
U 1 1 5CA26FF1
P 4250 4450
F 0 "#PWR019" H 4250 4200 50  0001 C CNN
F 1 "Earth" H 4250 4300 50  0001 C CNN
F 2 "" H 4250 4450 50  0001 C CNN
F 3 "~" H 4250 4450 50  0001 C CNN
	1    4250 4450
	1    0    0    -1  
$EndComp
Text HLabel 3950 3150 0    50   Input ~ 0
SWDCLK
Text HLabel 3950 3050 0    50   Input ~ 0
SWDIO
Text HLabel 6725 3000 0    50   Input ~ 0
SDA
Text HLabel 6725 2900 0    50   Input ~ 0
SCL
Text HLabel 6725 2800 0    50   Input ~ 0
LED_ENT
$Comp
L power:Earth #PWR021
U 1 1 5D1A9DB7
P 6725 3100
F 0 "#PWR021" H 6725 2850 50  0001 C CNN
F 1 "Earth" H 6725 2950 50  0001 C CNN
F 2 "" H 6725 3100 50  0001 C CNN
F 3 "~" H 6725 3100 50  0001 C CNN
	1    6725 3100
	0    1    1    0   
$EndComp
$Comp
L power:+3V3 #PWR020
U 1 1 5D1AA0CA
P 6725 3200
F 0 "#PWR020" H 6725 3050 50  0001 C CNN
F 1 "+3V3" H 6740 3373 50  0000 C CNN
F 2 "" H 6725 3200 50  0001 C CNN
F 3 "" H 6725 3200 50  0001 C CNN
	1    6725 3200
	0    -1   -1   0   
$EndComp
Text Notes 6550 2600 0    50   ~ 0
To Python480 Board
Text Notes 3800 2600 0    50   ~ 0
SWD Programming Connections
Text Notes 4000 4050 0    50   ~ 0
Battery Power Input
$Comp
L Connector_Generic:Conn_01x05 J1
U 1 1 5D3F21DC
P 7450 3000
F 0 "J1" H 7530 3042 50  0000 L CNN
F 1 "Conn_01x05" H 7530 2951 50  0000 L CNN
F 2 ".Connector:B2B_Flex_05_Dual_Row_38milx24mil_Pad_20mil_copy" H 7450 3000 50  0001 C CNN
F 3 "~" H 7450 3000 50  0001 C CNN
	1    7450 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 2800 6725 2800
Wire Wire Line
	7250 2900 6725 2900
Wire Wire Line
	7250 3000 6725 3000
Wire Wire Line
	7250 3100 6725 3100
Wire Wire Line
	7250 3200 6725 3200
$EndSCHEMATC
