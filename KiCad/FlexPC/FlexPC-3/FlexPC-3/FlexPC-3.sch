EESchema Schematic File Version 4
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
L Connector_Generic:Conn_01x03 J2
U 1 1 5D82C8EE
P 7275 4150
F 0 "J2" H 7355 4192 50  0000 L CNN
F 1 "Conn_01x03" H 7355 4101 50  0000 L CNN
F 2 ".Connector:B2B_Flex_03_Dual_Row_38milx24mil_Hole_20mil" H 7275 4150 50  0001 C CNN
F 3 "~" H 7275 4150 50  0001 C CNN
	1    7275 4150
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J1
U 1 1 5D82D375
P 5700 4150
F 0 "J1" H 5618 4467 50  0000 C CNN
F 1 "Conn_01x03" H 5618 4376 50  0000 C CNN
F 2 ".Connector:B2B_Flex_03_Dual_Row_38milx24mil_Hole_20mil" H 5700 4150 50  0001 C CNN
F 3 "~" H 5700 4150 50  0001 C CNN
	1    5700 4150
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5900 4050 7075 4050
Wire Wire Line
	7075 4150 5900 4150
Wire Wire Line
	5900 4250 7075 4250
Text Label 6400 4050 0    50   ~ 0
Earth
Text Label 6300 4150 0    50   ~ 0
IR_Receiver
Text Label 6450 4250 0    50   ~ 0
3V3
$EndSCHEMATC
