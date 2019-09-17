EESchema Schematic File Version 4
LIBS:FlexPC-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L Connector_Generic:Conn_01x20 J2
U 1 1 5D43C2DA
P 5325 3150
F 0 "J2" H 5243 1925 50  0000 C CNN
F 1 "Conn_01x20" H 5243 2016 50  0000 C CNN
F 2 ".Connector:B2B_Flex_20_Dual_Row_38milx24mil_Hole_10milx20mil" H 5325 3150 50  0001 C CNN
F 3 "~" H 5325 3150 50  0001 C CNN
	1    5325 3150
	1    0    0    1   
$EndComp
Text Label 6450 4150 0    50   ~ 0
Status_LED
Wire Wire Line
	6450 4150 6950 4150
$Comp
L Connector_Generic:Conn_01x08 J3
U 1 1 5D49AF58
P 7150 4550
F 0 "J3" H 7068 3925 50  0000 C CNN
F 1 "Conn_01x08" H 7068 4016 50  0000 C CNN
F 2 ".Connector:B2B_Flex_08_Dual_Row_38milx24mil_Hole_10milx20mil" H 7150 4550 50  0001 C CNN
F 3 "~" H 7150 4550 50  0001 C CNN
	1    7150 4550
	1    0    0    1   
$EndComp
Text Label 6450 4250 0    50   ~ 0
MOSI
Text Label 6450 4350 0    50   ~ 0
MISO
Text Label 6450 4450 0    50   ~ 0
MONITOR0
Text Label 6450 4550 0    50   ~ 0
TRIGGER0
Text Label 6450 4650 0    50   ~ 0
RESET_N
Text Label 6450 4750 0    50   ~ 0
SCK
Text Label 6450 4850 0    50   ~ 0
SS_N
Wire Wire Line
	6950 4850 6450 4850
Wire Wire Line
	6950 4750 6450 4750
Wire Wire Line
	6950 4650 6450 4650
Wire Wire Line
	6950 4550 6450 4550
Wire Wire Line
	6950 4450 6450 4450
Wire Wire Line
	6950 4350 6450 4350
Wire Wire Line
	6950 4250 6450 4250
$Comp
L Connector_Generic:Conn_01x23 J?
U 1 1 5D808083
P 3625 3250
F 0 "J?" H 3543 4567 50  0000 C CNN
F 1 "Conn_01x23" H 3543 4476 50  0000 C CNN
F 2 "" H 3625 3250 50  0001 C CNN
F 3 "~" H 3625 3250 50  0001 C CNN
	1    3625 3250
	-1   0    0    -1  
$EndComp
Text Label 4250 4450 0    50   ~ 0
TRIGGER0
Text Label 4400 4150 0    50   ~ 0
SS_N
Text Label 4450 4250 0    50   ~ 0
SCK
Text Label 4275 4350 0    50   ~ 0
RESET_N
Text Label 4225 4550 0    50   ~ 0
MONITOR0
Text Label 4425 4650 0    50   ~ 0
MISO
Text Label 4425 4750 0    50   ~ 0
MOSI
Text Label 4200 4850 0    50   ~ 0
Status_LED
Wire Wire Line
	3825 4850 4625 4850
Wire Wire Line
	3825 4750 4625 4750
Wire Wire Line
	3825 4650 4625 4650
Wire Wire Line
	3825 4550 4625 4550
Wire Wire Line
	3825 4450 4625 4450
Wire Wire Line
	3825 4350 4625 4350
Wire Wire Line
	3825 4250 4625 4250
Wire Wire Line
	3825 4150 4625 4150
Wire Wire Line
	3825 3550 5125 3550
Wire Wire Line
	3825 3450 5125 3450
Text Label 4225 3550 0    50   ~ 0
LINE_VALID
Text Label 4150 3450 0    50   ~ 0
FRAME_VALID
Wire Wire Line
	3825 3350 5125 3350
Text Label 4350 2350 0    50   ~ 0
img_d0
Text Label 4350 2450 0    50   ~ 0
img_d2
Text Label 4350 2550 0    50   ~ 0
img_d1
Text Label 4350 2650 0    50   ~ 0
img_d3
Text Label 4350 2750 0    50   ~ 0
CLK_OUT
Text Label 4350 2850 0    50   ~ 0
img_d4
Text Label 4350 2950 0    50   ~ 0
img_d5
Text Label 4350 3050 0    50   ~ 0
img_d7
Text Label 4350 3150 0    50   ~ 0
img_d6
Wire Wire Line
	3825 2350 5125 2350
Wire Wire Line
	3825 2450 5125 2450
Wire Wire Line
	3825 2550 5125 2550
Wire Wire Line
	3825 2650 5125 2650
Wire Wire Line
	3825 2750 5125 2750
Wire Wire Line
	3825 2850 5125 2850
Wire Wire Line
	3825 2950 5125 2950
Wire Wire Line
	3825 3050 5125 3050
Wire Wire Line
	3825 3150 5125 3150
Wire Wire Line
	3825 2150 5125 2150
Wire Wire Line
	3825 2250 5125 2250
Wire Wire Line
	3825 3250 5125 3250
Wire Wire Line
	3825 3850 5125 3850
Wire Wire Line
	3825 3950 5125 3950
Wire Wire Line
	3825 4050 5125 4050
Wire Wire Line
	3825 3750 5125 3750
Wire Wire Line
	3825 3650 5125 3650
$EndSCHEMATC
