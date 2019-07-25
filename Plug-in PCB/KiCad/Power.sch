EESchema Schematic File Version 4
LIBS:SDCard-PCB-cache
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
L .Regulator_Linear:TLV7103318DSER U2
U 1 1 5D3F33D4
P 5750 3050
F 0 "U2" H 5850 3392 50  0000 C CNN
F 1 "TLV7103318DSER" H 5850 3301 50  0000 C CNN
F 2 ".Package_SON:SON_6_P50_150X150X80L50X25L" H 5750 3350 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/tlv711.pdf" H 5750 3050 50  0001 C CNN
	1    5750 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 2950 5375 2950
Wire Wire Line
	5375 2950 5375 3050
Wire Wire Line
	5375 3150 5450 3150
Wire Wire Line
	5450 3050 5375 3050
Connection ~ 5375 3050
Wire Wire Line
	5375 3050 5375 3150
Wire Wire Line
	4950 3050 5100 3050
Connection ~ 5100 3050
Wire Wire Line
	5100 3050 5375 3050
Wire Wire Line
	5100 3500 5450 3500
Wire Wire Line
	5850 3500 5850 3350
Wire Wire Line
	5450 3600 5450 3500
Connection ~ 5450 3500
Wire Wire Line
	5450 3500 5850 3500
$Comp
L power:+3.3V #PWR0134
U 1 1 5CC4B63F
P 6725 2875
F 0 "#PWR0134" H 6725 2725 50  0001 C CNN
F 1 "+3.3V" H 6740 3048 50  0000 C CNN
F 2 "" H 6725 2875 50  0001 C CNN
F 3 "" H 6725 2875 50  0001 C CNN
	1    6725 2875
	1    0    0    -1  
$EndComp
$Comp
L power:+1V8 #PWR0135
U 1 1 5CC4B9F6
P 6500 3050
F 0 "#PWR0135" H 6500 2900 50  0001 C CNN
F 1 "+1V8" H 6515 3223 50  0000 C CNN
F 2 "" H 6500 3050 50  0001 C CNN
F 3 "" H 6500 3050 50  0001 C CNN
	1    6500 3050
	-1   0    0    1   
$EndComp
Wire Wire Line
	6250 3050 6325 3050
Wire Wire Line
	6500 3050 6825 3050
Connection ~ 6500 3050
Wire Wire Line
	6250 2950 6325 2950
Wire Wire Line
	6725 2950 6725 2875
Wire Wire Line
	6725 2950 7200 2950
Connection ~ 6725 2950
Wire Wire Line
	7200 2950 7200 3000
Wire Wire Line
	6825 3100 6825 3050
Wire Wire Line
	5100 3375 5100 3500
Wire Wire Line
	5100 3050 5100 3175
$Comp
L .Device:C_Small C19
U 1 1 5CE194B8
P 5100 3275
F 0 "C19" H 5192 3321 50  0000 L CNN
F 1 "GRM033R61A105ME15D" H 5192 3230 50  0001 L CNN
F 2 ".Capacitor:C_0201_0603Metric_L" H 5100 3275 50  0001 C CNN
F 3 "~" H 5100 3275 50  0001 C CNN
F 4 "1uF" H 5192 3230 50  0000 L CNN "Note"
F 5 "0201" H 5100 3275 50  0001 C CNN "Size"
	1    5100 3275
	1    0    0    -1  
$EndComp
$Comp
L .Device:C_Small C20
U 1 1 5D3F8902
P 6825 3200
F 0 "C20" H 6917 3246 50  0000 L CNN
F 1 "GRM033R61A105ME15D" H 6917 3155 50  0001 L CNN
F 2 ".Capacitor:C_0201_0603Metric_L" H 6825 3200 50  0001 C CNN
F 3 "~" H 6825 3200 50  0001 C CNN
F 4 "1uF" H 6917 3155 50  0000 L CNN "Note"
F 5 "0201" H 6825 3200 50  0001 C CNN "Size"
	1    6825 3200
	1    0    0    -1  
$EndComp
$Comp
L .Device:C_Small C21
U 1 1 5D3F33DC
P 7200 3100
F 0 "C21" H 7292 3146 50  0000 L CNN
F 1 "GRM033R61A105ME15D" H 7292 3055 50  0001 L CNN
F 2 ".Capacitor:C_0201_0603Metric_L" H 7200 3100 50  0001 C CNN
F 3 "~" H 7200 3100 50  0001 C CNN
F 4 "1uF" H 7292 3055 50  0000 L CNN "Note"
F 5 "0201" H 7200 3100 50  0001 C CNN "Size"
	1    7200 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6825 3300 6825 3400
Wire Wire Line
	7200 3200 7200 3275
$Comp
L power:+5V #PWR0138
U 1 1 5D3F20DA
P 4950 3050
F 0 "#PWR0138" H 4950 2900 50  0001 C CNN
F 1 "+5V" H 4965 3223 50  0000 C CNN
F 2 "" H 4950 3050 50  0001 C CNN
F 3 "" H 4950 3050 50  0001 C CNN
	1    4950 3050
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR0120
U 1 1 5D5F87C6
P 5450 3600
F 0 "#PWR0120" H 5450 3350 50  0001 C CNN
F 1 "Earth" H 5450 3450 50  0001 C CNN
F 2 "" H 5450 3600 50  0001 C CNN
F 3 "~" H 5450 3600 50  0001 C CNN
	1    5450 3600
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR0122
U 1 1 5D5F897F
P 6825 3400
F 0 "#PWR0122" H 6825 3150 50  0001 C CNN
F 1 "Earth" H 6825 3250 50  0001 C CNN
F 2 "" H 6825 3400 50  0001 C CNN
F 3 "~" H 6825 3400 50  0001 C CNN
	1    6825 3400
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR0125
U 1 1 5D5F8B3E
P 7200 3275
F 0 "#PWR0125" H 7200 3025 50  0001 C CNN
F 1 "Earth" H 7200 3125 50  0001 C CNN
F 2 "" H 7200 3275 50  0001 C CNN
F 3 "~" H 7200 3275 50  0001 C CNN
	1    7200 3275
	1    0    0    -1  
$EndComp
$Comp
L .Connector:Conn_01x01 J18
U 1 1 5D3DB94D
P 6325 2750
F 0 "J18" V 6289 2662 50  0000 R CNN
F 1 "Conn_01x01" V 6198 2662 50  0000 R CNN
F 2 "Connector_PinHeader_1.27mm:PinHeader_1x01_P1.27mm_Vertical" H 6325 2750 50  0001 C CNN
F 3 "~" H 6325 2750 50  0001 C CNN
	1    6325 2750
	0    -1   -1   0   
$EndComp
Connection ~ 6325 2950
Wire Wire Line
	6325 2950 6725 2950
$Comp
L .Connector:Conn_01x01 J19
U 1 1 5D3DC2A8
P 6325 3250
F 0 "J19" V 6197 3330 50  0000 L CNN
F 1 "Conn_01x01" V 6288 3330 50  0000 L CNN
F 2 "Connector_PinHeader_1.27mm:PinHeader_1x01_P1.27mm_Vertical" H 6325 3250 50  0001 C CNN
F 3 "~" H 6325 3250 50  0001 C CNN
	1    6325 3250
	0    1    1    0   
$EndComp
Connection ~ 6325 3050
Wire Wire Line
	6325 3050 6500 3050
$EndSCHEMATC