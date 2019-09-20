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
P 5175 2175
F 0 "J2" H 5093 950 50  0000 C CNN
F 1 "Conn_01x20" H 5093 1041 50  0000 C CNN
F 2 ".Connector:B2B_Flex_20_Dual_Row_38milx24mil_Hole_10milx20mil" H 5175 2175 50  0001 C CNN
F 3 "~" H 5175 2175 50  0001 C CNN
	1    5175 2175
	1    0    0    1   
$EndComp
Text Label 3625 3675 0    50   ~ 0
TRIGGER0
Text Label 3625 3375 0    50   ~ 0
SS_N
Text Label 3625 3475 0    50   ~ 0
SCK
Text Label 3625 3575 0    50   ~ 0
RESET_N
Text Label 3625 3775 0    50   ~ 0
MONITOR0
Text Label 3625 3875 0    50   ~ 0
MISO
Text Label 3625 3975 0    50   ~ 0
MOSI
Text Label 3625 2075 0    50   ~ 0
LINE_VALID
Text Label 3625 2175 0    50   ~ 0
FRAME_VALID
Text Label 3625 3075 0    50   ~ 0
img_d0
Text Label 3625 2975 0    50   ~ 0
img_d2
Text Label 3625 2875 0    50   ~ 0
img_d1
Text Label 3625 2775 0    50   ~ 0
img_d3
Text Label 3625 2675 0    50   ~ 0
CLK_OUT
Text Label 3625 2575 0    50   ~ 0
img_d4
Text Label 3625 2475 0    50   ~ 0
img_d5
Text Label 3625 2375 0    50   ~ 0
img_d7
Text Label 3625 2275 0    50   ~ 0
img_d6
$Comp
L Connector_Generic:Conn_01x22 J1
U 1 1 5D820ECA
P 3425 3075
F 0 "J1" H 3343 4292 50  0000 C CNN
F 1 "Conn_01x22" H 3343 4201 50  0000 C CNN
F 2 ".Connector:B2B_Flex_22_Dual_Row_38milx24mil_Hole_10milx20mil" H 3425 3075 50  0001 C CNN
F 3 "~" H 3425 3075 50  0001 C CNN
	1    3425 3075
	-1   0    0    -1  
$EndComp
Text Label 3625 3175 0    50   ~ 0
1V8
Text Label 3625 3275 0    50   ~ 0
GND
Text Label 3625 4075 0    50   ~ 0
3V3
$Comp
L Connector_Generic:Conn_01x14 J3
U 1 1 5D825428
P 5175 3975
F 0 "J3" H 5255 3967 50  0000 L CNN
F 1 "Conn_01x14" H 5255 3876 50  0000 L CNN
F 2 ".Connector:B2B_Flex_14_Dual_Row_38milx24mil_Hole_10milx20mil" H 5175 3975 50  0001 C CNN
F 3 "~" H 5175 3975 50  0001 C CNN
	1    5175 3975
	1    0    0    1   
$EndComp
Text Label 4975 4575 2    50   ~ 0
VBATT
Text Label 4975 4375 2    50   ~ 0
3V3
Text Label 4975 4275 2    50   ~ 0
MOSI
Text Label 4975 4175 2    50   ~ 0
MISO
Text Label 4975 4075 2    50   ~ 0
MONITOR0
Text Label 4975 3975 2    50   ~ 0
TRIGGER0
Text Label 4975 3875 2    50   ~ 0
RESET_N
Text Label 4975 3775 2    50   ~ 0
SCK
NoConn ~ 4975 3675
NoConn ~ 4975 3575
Text Label 4975 3475 2    50   ~ 0
SS_N
NoConn ~ 4975 3375
Text Label 4975 2975 2    50   ~ 0
1V8
Text Label 4975 2875 2    50   ~ 0
img_d0
Text Label 4975 2675 2    50   ~ 0
img_d1
Text Label 4975 2775 2    50   ~ 0
img_d2
Text Label 4975 2575 2    50   ~ 0
img_d3
Text Label 4975 2375 2    50   ~ 0
img_d4
Text Label 4975 2275 2    50   ~ 0
img_d5
Text Label 4975 2075 2    50   ~ 0
img_d6
Text Label 4975 2175 2    50   ~ 0
img_d7
Text Label 4975 1975 2    50   ~ 0
img_d8
Text Label 4975 1875 2    50   ~ 0
img_d9
Text Label 4975 2475 2    50   ~ 0
CLK_OUT
Text Label 4975 1775 2    50   ~ 0
FRAME_VALID
Text Label 4975 1675 2    50   ~ 0
LINE_VALID
NoConn ~ 4975 1575
NoConn ~ 4975 1475
NoConn ~ 4975 1375
NoConn ~ 4975 1275
NoConn ~ 4975 1175
Text Label 4975 3275 2    50   ~ 0
GND
NoConn ~ 4975 3075
Wire Wire Line
	3625 2075 3750 2075
Wire Wire Line
	3750 2075 3750 1675
Wire Wire Line
	3750 1675 4975 1675
Wire Wire Line
	3625 2175 3825 2175
Wire Wire Line
	3825 2175 3825 1775
Wire Wire Line
	3825 1775 4975 1775
Wire Wire Line
	3625 2275 3900 2275
Wire Wire Line
	3900 2275 3900 2075
Wire Wire Line
	3900 2075 4975 2075
Wire Wire Line
	3625 2375 3975 2375
Wire Wire Line
	3975 2375 3975 2175
Wire Wire Line
	3975 2175 4975 2175
Wire Wire Line
	3625 2475 4050 2475
Wire Wire Line
	4050 2475 4050 2275
Wire Wire Line
	4050 2275 4975 2275
Wire Wire Line
	3625 2575 4125 2575
Wire Wire Line
	4125 2575 4125 2375
Wire Wire Line
	4125 2375 4975 2375
Wire Wire Line
	3625 2675 4200 2675
Wire Wire Line
	4200 2675 4200 2475
Wire Wire Line
	4200 2475 4975 2475
Wire Wire Line
	3625 2775 4275 2775
Wire Wire Line
	4275 2775 4275 2575
Wire Wire Line
	4275 2575 4975 2575
Wire Wire Line
	3625 2875 4350 2875
Wire Wire Line
	4350 2875 4350 2675
Wire Wire Line
	4350 2675 4975 2675
Wire Wire Line
	3625 2975 4425 2975
Wire Wire Line
	4425 2975 4425 2775
Wire Wire Line
	4425 2775 4975 2775
Wire Wire Line
	3625 3075 4500 3075
Wire Wire Line
	4500 3075 4500 2875
Wire Wire Line
	4500 2875 4975 2875
Wire Wire Line
	3625 3175 4575 3175
Wire Wire Line
	4575 3175 4575 2975
Wire Wire Line
	4575 2975 4975 2975
Wire Wire Line
	3625 3275 4975 3275
Wire Wire Line
	3625 3375 4900 3375
Wire Wire Line
	4900 3375 4900 3475
Wire Wire Line
	4900 3475 4975 3475
Wire Wire Line
	3625 3475 4825 3475
Wire Wire Line
	4825 3475 4825 3775
Wire Wire Line
	4825 3775 4975 3775
Wire Wire Line
	3625 3575 4750 3575
Wire Wire Line
	4750 3575 4750 3875
Wire Wire Line
	4750 3875 4975 3875
Wire Wire Line
	3625 3675 4675 3675
Wire Wire Line
	4675 3675 4675 3975
Wire Wire Line
	4675 3975 4975 3975
Wire Wire Line
	3625 3775 4600 3775
Wire Wire Line
	4600 3775 4600 4075
Wire Wire Line
	4600 4075 4975 4075
Wire Wire Line
	3625 3875 4525 3875
Wire Wire Line
	4525 3875 4525 4175
Wire Wire Line
	4525 4175 4975 4175
Wire Wire Line
	3625 3975 4450 3975
Wire Wire Line
	4450 3975 4450 4275
Wire Wire Line
	4450 4275 4975 4275
Wire Wire Line
	3625 4075 4375 4075
Wire Wire Line
	4375 4075 4375 4375
Wire Wire Line
	4375 4375 4975 4375
Wire Wire Line
	3625 4175 4300 4175
Wire Wire Line
	4300 4175 4300 4475
Wire Wire Line
	4300 4475 4975 4475
NoConn ~ 4975 4575
NoConn ~ 4975 1875
NoConn ~ 4975 1975
Text Label 3625 4175 0    50   ~ 0
Status_LED
Text Label 4975 4475 2    50   ~ 0
Status_LED
$EndSCHEMATC
