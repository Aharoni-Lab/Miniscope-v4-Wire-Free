EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 2150 1925 0    50   ~ 0
D0
Text Label 2150 2025 0    50   ~ 0
D1
Text Label 2150 2125 0    50   ~ 0
D2
Text Label 2150 2425 0    50   ~ 0
D3
Text Label 2150 2525 0    50   ~ 0
D4
Text Label 2150 2625 0    50   ~ 0
D5
Text Label 2150 2725 0    50   ~ 0
D6
Text Label 2150 2825 0    50   ~ 0
D7
Text Label 2150 2925 0    50   ~ 0
FV
Text Label 2150 3325 0    50   ~ 0
MONITOR0
Text Label 2150 3625 0    50   ~ 0
LV
Text Label 2150 3725 0    50   ~ 0
PXL_CLK
Wire Wire Line
	3000 4325 2150 4325
Text Label 2150 4125 0    50   ~ 0
SD2
Text Label 2150 4225 0    50   ~ 0
SD3
Text Label 2150 4425 0    50   ~ 0
SD0
Text Label 2150 4525 0    50   ~ 0
SD1
Text Label 2150 4325 0    50   ~ 0
SDCMDA
Text Label 2150 4025 0    50   ~ 0
SDCLKA
Text Label 2150 4825 0    50   ~ 0
RESET_N
Text Label 2150 4925 0    50   ~ 0
TRIGGER0
Text Label 2150 5125 0    50   ~ 0
SDA
Text Label 2150 5225 0    50   ~ 0
SCL
Wire Wire Line
	3000 5625 2150 5625
Text Label 2150 5325 0    50   ~ 0
SWDIO
Text Label 2150 5425 0    50   ~ 0
SWDCLK
Text Label 2150 5525 0    50   ~ 0
XOUT
Text Label 2150 5625 0    50   ~ 0
XIN
Text Label 2150 3425 0    50   ~ 0
LED_ENT
Wire Wire Line
	3650 7425 3650 7500
$Comp
L power:GND #PWR?
U 1 1 5F8105E7
P 3650 7500
AR Path="/5F8105E7" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8105E7" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 3650 7250 50  0001 C CNN
F 1 "GND" H 3655 7327 50  0000 C CNN
F 2 "" H 3650 7500 50  0001 C CNN
F 3 "" H 3650 7500 50  0001 C CNN
	1    3650 7500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 4825 5400 4825
Wire Wire Line
	6250 4925 5400 4925
Wire Wire Line
	6250 5025 5400 5025
Wire Wire Line
	6250 5225 5400 5225
Text Label 6250 4825 2    50   ~ 0
MISO
Text Label 6250 4925 2    50   ~ 0
MOSI
Text Label 6250 5025 2    50   ~ 0
SCK
Text Label 6250 5225 2    50   ~ 0
SS_N
Wire Wire Line
	6250 4625 5400 4625
Wire Wire Line
	6250 4725 5400 4725
Text Label 6250 4625 2    50   ~ 0
IR_REV
Text Label 6250 4725 2    50   ~ 0
STATUS_LED
Wire Wire Line
	3600 1225 3600 725 
Wire Wire Line
	4000 1225 4100 1225
Connection ~ 4100 1225
Wire Wire Line
	4100 1225 4200 1225
$Comp
L power:+1V2 #PWR?
U 1 1 5F8105FD
P 3600 725
AR Path="/5F8105FD" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8105FD" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 3600 575 50  0001 C CNN
F 1 "+1V2" H 3615 898 50  0000 C CNN
F 2 "" H 3600 725 50  0001 C CNN
F 3 "" H 3600 725 50  0001 C CNN
	1    3600 725 
	1    0    0    -1  
$EndComp
Text Label 3600 1100 1    50   ~ 0
VDDCORE
Wire Wire Line
	4100 1225 4100 725 
$Comp
L power:+1V8 #PWR?
U 1 1 5F810605
P 4100 725
AR Path="/5F810605" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F810605" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 4100 575 50  0001 C CNN
F 1 "+1V8" H 4115 898 50  0000 C CNN
F 2 "" H 4100 725 50  0001 C CNN
F 3 "" H 4100 725 50  0001 C CNN
	1    4100 725 
	1    0    0    -1  
$EndComp
Text Label 4100 1050 1    50   ~ 0
VDDIO
Wire Wire Line
	4450 1225 4450 725 
Wire Wire Line
	4650 1225 4650 725 
Wire Wire Line
	4750 1225 4750 725 
Wire Wire Line
	4850 1225 4850 725 
Text Label 4450 1100 1    50   ~ 0
VDDOUT
$Comp
L power:+1V2 #PWR?
U 1 1 5F810611
P 4450 725
AR Path="/5F810611" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F810611" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 4450 575 50  0001 C CNN
F 1 "+1V2" H 4465 898 50  0000 C CNN
F 2 "" H 4450 725 50  0001 C CNN
F 3 "" H 4450 725 50  0001 C CNN
	1    4450 725 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 1225 4550 725 
Text Label 4550 1100 1    50   ~ 0
VDDIN
$Comp
L power:+1V8 #PWR?
U 1 1 5F810619
P 4550 725
AR Path="/5F810619" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F810619" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 4550 575 50  0001 C CNN
F 1 "+1V8" H 4565 898 50  0000 C CNN
F 2 "" H 4550 725 50  0001 C CNN
F 3 "" H 4550 725 50  0001 C CNN
	1    4550 725 
	1    0    0    -1  
$EndComp
Text Label 4650 1100 1    50   ~ 0
VDDPLL
Text Label 4750 1100 1    50   ~ 0
VDDUTMIC
Text Label 4850 1100 1    50   ~ 0
VDDUTMII
Text Label 4950 1100 1    50   ~ 0
VDDPLLUSB
$Comp
L power:+1V8 #PWR?
U 1 1 5F810623
P 4850 725
AR Path="/5F810623" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F810623" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 4850 575 50  0001 C CNN
F 1 "+1V8" H 4865 898 50  0000 C CNN
F 2 "" H 4850 725 50  0001 C CNN
F 3 "" H 4850 725 50  0001 C CNN
	1    4850 725 
	1    0    0    -1  
$EndComp
Connection ~ 3700 1225
Connection ~ 3600 1225
Wire Wire Line
	3700 1225 3600 1225
Wire Wire Line
	3800 1225 3700 1225
Connection ~ 4650 7425
Connection ~ 4550 7425
Wire Wire Line
	4550 7425 4450 7425
Wire Wire Line
	4450 7425 4200 7425
Connection ~ 4450 7425
Connection ~ 4200 7425
Wire Wire Line
	4200 7425 4100 7425
Wire Wire Line
	4100 7425 4000 7425
Connection ~ 4100 7425
Connection ~ 4000 7425
Wire Wire Line
	4000 7425 3900 7425
Wire Wire Line
	3900 7425 3650 7425
Connection ~ 3900 7425
Wire Wire Line
	4650 7425 4550 7425
Wire Wire Line
	4750 7425 4650 7425
Wire Wire Line
	3000 5525 2150 5525
Wire Wire Line
	3000 5425 2150 5425
Wire Wire Line
	3000 5325 2150 5325
Wire Wire Line
	3000 5225 2150 5225
Wire Wire Line
	3000 5125 2150 5125
Wire Wire Line
	3000 4925 2150 4925
Wire Wire Line
	3000 4825 2150 4825
Wire Wire Line
	3000 4525 2150 4525
Wire Wire Line
	3000 4425 2150 4425
Wire Wire Line
	3000 4225 2150 4225
Wire Wire Line
	3000 4125 2150 4125
Wire Wire Line
	3000 4025 2150 4025
Wire Wire Line
	3000 3725 2150 3725
Wire Wire Line
	3000 3625 2150 3625
Wire Wire Line
	3000 3325 2150 3325
Wire Wire Line
	3000 2925 2150 2925
Wire Wire Line
	3000 2825 2150 2825
Wire Wire Line
	3000 2725 2150 2725
Wire Wire Line
	3000 2625 2150 2625
Wire Wire Line
	3000 2525 2150 2525
Wire Wire Line
	3000 2425 2150 2425
Wire Wire Line
	3000 2125 2150 2125
Wire Wire Line
	3000 2025 2150 2025
Wire Wire Line
	3000 1925 2150 1925
$Comp
L .MCU:ATSAME70N21A-CN U?
U 1 1 5F810654
P 4250 4525
AR Path="/5F810654" Ref="U?"  Part="1" 
AR Path="/5F7DBD7F/5F810654" Ref="U?"  Part="1" 
F 0 "U?" H 4200 1536 50  0000 C CNN
F 1 "ATSAME70N21A-CN" H 4200 1445 50  0000 C CNN
F 2 ".Package_BGA:BGA_100_CP80_10X10_900X900X110B40L" H 4150 4425 50  0001 C CNN
F 3 "http://www.microchip.com/mymicrochip/filehandler.aspx?ddocname=en589960" H 4250 4525 50  0001 C CNN
	1    4250 4525
	1    0    0    -1  
$EndComp
Wire Wire Line
	25   225  425  225 
Text Label 25   225  0    50   ~ 0
VDDUTMIC
Wire Wire Line
	1025 225  1375 225 
Text Label 1025 225  0    50   ~ 0
VDDPLL
Wire Wire Line
	1625 425  2025 425 
Text Label 2075 225  0    50   ~ 0
VDDCORE
Text Label 2125 -375 0    50   ~ 0
VDDOUT
Text Label 950  -375 0    50   ~ 0
VDDIO
Wire Wire Line
	1225 850  1625 850 
Text Label 1275 850  0    50   ~ 0
VDDUTMII
Text Label 500  875  0    50   ~ 0
VDDIN
$Comp
L .Capacitor:GRM033R61A104ME15D C?
U 1 1 5F810667
P 25 975
AR Path="/5C92D296/5F810667" Ref="C?"  Part="1" 
AR Path="/5F810667" Ref="C?"  Part="1" 
AR Path="/5F7DBD7F/5F810667" Ref="C?"  Part="1" 
F 0 "C?" H 117 1021 50  0000 L CNN
F 1 "GRM033R61A104ME15D" H -365 1145 50  0001 L CNN
F 2 ".Capacitor:C_0201_0603Metric_L" H 85  1245 50  0001 C CNN
F 3 "http://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM033R61A104ME15-01.pdf" H 35  1045 50  0001 C CNN
F 4 "0.1uF" H 117 930 50  0000 L CNN "Note"
F 5 "0201" H 135 795 50  0001 C CNN "Size"
	1    25   975 
	1    0    0    -1  
$EndComp
$Comp
L .Capacitor:GRM033R61A104ME15D C?
U 1 1 5F81066F
P 25 325
AR Path="/5C92D296/5F81066F" Ref="C?"  Part="1" 
AR Path="/5F81066F" Ref="C?"  Part="1" 
AR Path="/5F7DBD7F/5F81066F" Ref="C?"  Part="1" 
F 0 "C?" H 117 371 50  0000 L CNN
F 1 "GRM033R61A104ME15D" H -365 495 50  0001 L CNN
F 2 ".Capacitor:C_0201_0603Metric_L" H 85  595 50  0001 C CNN
F 3 "http://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM033R61A104ME15-01.pdf" H 35  395 50  0001 C CNN
F 4 "0.1uF" H 117 280 50  0000 L CNN "Note"
F 5 "0201" H 135 145 50  0001 C CNN "Size"
	1    25   325 
	1    0    0    -1  
$EndComp
$Comp
L .Capacitor:GRM033R61A104ME15D C?
U 1 1 5F810677
P 1025 325
AR Path="/5C92D296/5F810677" Ref="C?"  Part="1" 
AR Path="/5F810677" Ref="C?"  Part="1" 
AR Path="/5F7DBD7F/5F810677" Ref="C?"  Part="1" 
F 0 "C?" H 1117 371 50  0000 L CNN
F 1 "GRM033R61A104ME15D" H 635 495 50  0001 L CNN
F 2 ".Capacitor:C_0201_0603Metric_L" H 1085 595 50  0001 C CNN
F 3 "http://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM033R61A104ME15-01.pdf" H 1035 395 50  0001 C CNN
F 4 "0.1uF" H 1117 280 50  0000 L CNN "Note"
F 5 "0201" H 1135 145 50  0001 C CNN "Size"
	1    1025 325 
	1    0    0    -1  
$EndComp
$Comp
L .Capacitor:GRM033R61A104ME15D C?
U 1 1 5F81067F
P 1225 950
AR Path="/5C92D296/5F81067F" Ref="C?"  Part="1" 
AR Path="/5F81067F" Ref="C?"  Part="1" 
AR Path="/5F7DBD7F/5F81067F" Ref="C?"  Part="1" 
F 0 "C?" H 1317 996 50  0000 L CNN
F 1 "GRM033R61A104ME15D" H 835 1120 50  0001 L CNN
F 2 ".Capacitor:C_0201_0603Metric_L" H 1285 1220 50  0001 C CNN
F 3 "http://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM033R61A104ME15-01.pdf" H 1235 1020 50  0001 C CNN
F 4 "0.1uF" H 1317 905 50  0000 L CNN "Note"
F 5 "0201" H 1335 770 50  0001 C CNN "Size"
	1    1225 950 
	1    0    0    -1  
$EndComp
$Comp
L .Capacitor:GRM033R61A104ME15D C?
U 1 1 5F810687
P 2025 325
AR Path="/5C92D296/5F810687" Ref="C?"  Part="1" 
AR Path="/5F810687" Ref="C?"  Part="1" 
AR Path="/5F7DBD7F/5F810687" Ref="C?"  Part="1" 
F 0 "C?" H 2117 371 50  0000 L CNN
F 1 "GRM033R61A104ME15D" H 1635 495 50  0001 L CNN
F 2 ".Capacitor:C_0201_0603Metric_L" H 2085 595 50  0001 C CNN
F 3 "http://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM033R61A104ME15-01.pdf" H 2035 395 50  0001 C CNN
F 4 "0.1uF" H 2117 280 50  0000 L CNN "Note"
F 5 "0201" H 2135 145 50  0001 C CNN "Size"
	1    2025 325 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1625 225  2025 225 
Connection ~ 2025 225 
Wire Wire Line
	2025 225  2425 225 
$Comp
L .Capacitor:GRM033R61A104ME15D C?
U 1 1 5F810692
P 1625 325
AR Path="/5C92D296/5F810692" Ref="C?"  Part="1" 
AR Path="/5F810692" Ref="C?"  Part="1" 
AR Path="/5F7DBD7F/5F810692" Ref="C?"  Part="1" 
F 0 "C?" H 1717 371 50  0000 L CNN
F 1 "GRM033R61A104ME15D" H 1235 495 50  0001 L CNN
F 2 ".Capacitor:C_0201_0603Metric_L" H 1685 595 50  0001 C CNN
F 3 "http://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM033R61A104ME15-01.pdf" H 1635 395 50  0001 C CNN
F 4 "0.1uF" H 1717 280 50  0000 L CNN "Note"
F 5 "0201" H 1735 145 50  0001 C CNN "Size"
	1    1625 325 
	1    0    0    -1  
$EndComp
$Comp
L .Capacitor:GRM033R61A104ME15D C?
U 1 1 5F81069A
P 25 -275
AR Path="/5C92D296/5F81069A" Ref="C?"  Part="1" 
AR Path="/5F81069A" Ref="C?"  Part="1" 
AR Path="/5F7DBD7F/5F81069A" Ref="C?"  Part="1" 
F 0 "C?" H 117 -229 50  0000 L CNN
F 1 "GRM033R61A104ME15D" H -365 -105 50  0001 L CNN
F 2 ".Capacitor:C_0201_0603Metric_L" H 85  -5  50  0001 C CNN
F 3 "http://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM033R61A104ME15-01.pdf" H 35  -205 50  0001 C CNN
F 4 "0.1uF" H 117 -320 50  0000 L CNN "Note"
F 5 "0201" H 135 -455 50  0001 C CNN "Size"
	1    25   -275
	1    0    0    -1  
$EndComp
Wire Wire Line
	25   -375 425  -375
Wire Wire Line
	25   -175 425  -175
$Comp
L .Capacitor:GRM033R61A104ME15D C?
U 1 1 5F8106A4
P 425 -275
AR Path="/5C92D296/5F8106A4" Ref="C?"  Part="1" 
AR Path="/5F8106A4" Ref="C?"  Part="1" 
AR Path="/5F7DBD7F/5F8106A4" Ref="C?"  Part="1" 
F 0 "C?" H 517 -229 50  0000 L CNN
F 1 "GRM033R61A104ME15D" H 35  -105 50  0001 L CNN
F 2 ".Capacitor:C_0201_0603Metric_L" H 485 -5  50  0001 C CNN
F 3 "http://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM033R61A104ME15-01.pdf" H 435 -205 50  0001 C CNN
F 4 "0.1uF" H 517 -320 50  0000 L CNN "Note"
F 5 "0201" H 535 -455 50  0001 C CNN "Size"
	1    425  -275
	1    0    0    -1  
$EndComp
Connection ~ 425  -375
Connection ~ 425  -175
Wire Wire Line
	425  -375 825  -375
Wire Wire Line
	425  -175 825  -175
$Comp
L .Capacitor:GRM033R61A104ME15D C?
U 1 1 5F8106B0
P 825 -275
AR Path="/5C92D296/5F8106B0" Ref="C?"  Part="1" 
AR Path="/5F8106B0" Ref="C?"  Part="1" 
AR Path="/5F7DBD7F/5F8106B0" Ref="C?"  Part="1" 
F 0 "C?" H 917 -229 50  0000 L CNN
F 1 "GRM033R61A104ME15D" H 435 -105 50  0001 L CNN
F 2 ".Capacitor:C_0201_0603Metric_L" H 885 -5  50  0001 C CNN
F 3 "http://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM033R61A104ME15-01.pdf" H 835 -205 50  0001 C CNN
F 4 "0.1uF" H 917 -320 50  0000 L CNN "Note"
F 5 "0201" H 935 -455 50  0001 C CNN "Size"
	1    825  -275
	1    0    0    -1  
$EndComp
Connection ~ 825  -375
Wire Wire Line
	825  -375 1175 -375
Connection ~ 825  -175
Wire Wire Line
	825  -175 1175 -175
$Comp
L .Capacitor:GRM033R61A104ME15D C?
U 1 1 5F8106BC
P 1625 -275
AR Path="/5C92D296/5F8106BC" Ref="C?"  Part="1" 
AR Path="/5F8106BC" Ref="C?"  Part="1" 
AR Path="/5F7DBD7F/5F8106BC" Ref="C?"  Part="1" 
F 0 "C?" H 1717 -229 50  0000 L CNN
F 1 "GRM033R61A104ME15D" H 1235 -105 50  0001 L CNN
F 2 ".Capacitor:C_0201_0603Metric_L" H 1685 -5  50  0001 C CNN
F 3 "http://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM033R61A104ME15-01.pdf" H 1635 -205 50  0001 C CNN
F 4 "0.1uF" H 1717 -320 50  0000 L CNN "Note"
F 5 "0201" H 1735 -455 50  0001 C CNN "Size"
	1    1625 -275
	1    0    0    -1  
$EndComp
$Comp
L .Capacitor:GRM033R60J105MEA2D C?
U 1 1 5F8106C4
P 2025 -275
AR Path="/5C92D296/5F8106C4" Ref="C?"  Part="1" 
AR Path="/5F8106C4" Ref="C?"  Part="1" 
AR Path="/5F7DBD7F/5F8106C4" Ref="C?"  Part="1" 
F 0 "C?" H 2117 -229 50  0000 L CNN
F 1 "GRM033R60J105MEA2D" H 1635 -105 50  0001 L CNN
F 2 ".Capacitor:C_0201_0603Metric_L" H 2135 -5  50  0001 C CNN
F 3 "http://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM033R60J105MEA2-02.pdf" H 2035 -205 50  0001 C CNN
F 4 "1uF" H 2117 -320 50  0000 L CNN "Note"
F 5 "0201" H 2135 -455 50  0001 C CNN "Size"
	1    2025 -275
	1    0    0    -1  
$EndComp
Wire Wire Line
	1625 -375 2025 -375
Wire Wire Line
	1625 -175 2025 -175
Connection ~ 2025 -375
Wire Wire Line
	2025 -375 2425 -375
Connection ~ 2025 -175
Wire Wire Line
	2025 -175 2425 -175
$Comp
L power:GND #PWR?
U 1 1 5F8106D0
P 25 1075
AR Path="/5F8106D0" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8106D0" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 25  825 50  0001 C CNN
F 1 "GND" H 30  902 50  0000 C CNN
F 2 "" H 25  1075 50  0001 C CNN
F 3 "" H 25  1075 50  0001 C CNN
	1    25   1075
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F8106D6
P 25 425
AR Path="/5F8106D6" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8106D6" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 25  175 50  0001 C CNN
F 1 "GND" H 30  252 50  0000 C CNN
F 2 "" H 25  425 50  0001 C CNN
F 3 "" H 25  425 50  0001 C CNN
	1    25   425 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F8106DC
P 1025 425
AR Path="/5F8106DC" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8106DC" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1025 175 50  0001 C CNN
F 1 "GND" H 1030 252 50  0000 C CNN
F 2 "" H 1025 425 50  0001 C CNN
F 3 "" H 1025 425 50  0001 C CNN
	1    1025 425 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F8106E2
P 1175 -175
AR Path="/5F8106E2" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8106E2" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1175 -425 50  0001 C CNN
F 1 "GND" H 1180 -348 50  0000 C CNN
F 2 "" H 1175 -175 50  0001 C CNN
F 3 "" H 1175 -175 50  0001 C CNN
	1    1175 -175
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F8106E8
P 2425 -175
AR Path="/5F8106E8" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8106E8" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 2425 -425 50  0001 C CNN
F 1 "GND" H 2430 -348 50  0000 C CNN
F 2 "" H 2425 -175 50  0001 C CNN
F 3 "" H 2425 -175 50  0001 C CNN
	1    2425 -175
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F8106EE
P 2025 425
AR Path="/5F8106EE" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8106EE" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 2025 175 50  0001 C CNN
F 1 "GND" H 2030 252 50  0000 C CNN
F 2 "" H 2025 425 50  0001 C CNN
F 3 "" H 2025 425 50  0001 C CNN
	1    2025 425 
	1    0    0    -1  
$EndComp
Connection ~ 2025 425 
$Comp
L power:GND #PWR?
U 1 1 5F8106F5
P 1225 1050
AR Path="/5F8106F5" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8106F5" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1225 800 50  0001 C CNN
F 1 "GND" H 1230 877 50  0000 C CNN
F 2 "" H 1225 1050 50  0001 C CNN
F 3 "" H 1225 1050 50  0001 C CNN
	1    1225 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	25   225  -50  225 
Connection ~ 25   225 
$Comp
L .Inductor:BLM18PG471SN1D L?
U 1 1 5F8106FE
P -150 225
AR Path="/5C92D296/5F8106FE" Ref="L?"  Part="1" 
AR Path="/5F8106FE" Ref="L?"  Part="1" 
AR Path="/5F7DBD7F/5F8106FE" Ref="L?"  Part="1" 
F 0 "L?" V -102 271 50  0001 L BNN
F 1 "BLM18PG471SN1D" H -100 75  50  0001 L CNN
F 2 ".Inductor:L_0603_1608Metric_L" H -100 525 50  0001 C CNN
F 3 "https://www.murata.com/en-us/products/productdata/8796738650142/ENFA0003.pdf" H -150 225 50  0001 C CNN
F 4 "0603" H 0   -25 50  0001 C CNN "Size"
	1    -150 225 
	0    -1   -1   0   
$EndComp
Wire Wire Line
	-250 225  -375 225 
Wire Wire Line
	1025 225  975  225 
Connection ~ 1025 225 
$Comp
L .Inductor:BLM18PG471SN1D L?
U 1 1 5F810708
P 875 225
AR Path="/5C92D296/5F810708" Ref="L?"  Part="1" 
AR Path="/5F810708" Ref="L?"  Part="1" 
AR Path="/5F7DBD7F/5F810708" Ref="L?"  Part="1" 
F 0 "L?" V 923 271 50  0001 L BNN
F 1 "BLM18PG471SN1D" H 925 75  50  0001 L CNN
F 2 ".Inductor:L_0603_1608Metric_L" H 925 525 50  0001 C CNN
F 3 "https://www.murata.com/en-us/products/productdata/8796738650142/ENFA0003.pdf" H 875 225 50  0001 C CNN
F 4 "0603" H 1025 -25 50  0001 C CNN "Size"
	1    875  225 
	0    -1   -1   0   
$EndComp
Wire Wire Line
	775  225  725  225 
$Comp
L power:+1V2 #PWR?
U 1 1 5F81070F
P -375 225
AR Path="/5F81070F" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F81070F" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H -375 75  50  0001 C CNN
F 1 "+1V2" H -360 398 50  0000 C CNN
F 2 "" H -375 225 50  0001 C CNN
F 3 "" H -375 225 50  0001 C CNN
	1    -375 225 
	1    0    0    -1  
$EndComp
$Comp
L power:+1V2 #PWR?
U 1 1 5F810715
P 725 225
AR Path="/5F810715" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F810715" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 725 75  50  0001 C CNN
F 1 "+1V2" H 740 398 50  0000 C CNN
F 2 "" H 725 225 50  0001 C CNN
F 3 "" H 725 225 50  0001 C CNN
	1    725  225 
	1    0    0    -1  
$EndComp
$Comp
L .Capacitor:GRM155R60J475ME87D C?
U 1 1 5F81071D
P 425 975
AR Path="/5C92D296/5F81071D" Ref="C?"  Part="1" 
AR Path="/5F81071D" Ref="C?"  Part="1" 
AR Path="/5F7DBD7F/5F81071D" Ref="C?"  Part="1" 
F 0 "C?" H 517 1021 50  0000 L CNN
F 1 "GRM155R60J475ME87D" H 35  1145 50  0001 L CNN
F 2 ".Capacitor:C_0402_1005Metric_L" H 535 1245 50  0001 C CNN
F 3 "" H 435 1045 50  0001 C CNN
F 4 "4.7uF" H 517 930 50  0000 L CNN "Note"
F 5 "0402" H 535 795 50  0001 C CNN "Size"
	1    425  975 
	1    0    0    -1  
$EndComp
$Comp
L .Oscillator:ABM8G-12.000MHZ-4Y-T3 Y?
U 1 1 5F810723
P 675 6900
AR Path="/5C92D296/5F810723" Ref="Y?"  Part="1" 
AR Path="/5F810723" Ref="Y?"  Part="1" 
AR Path="/5F7DBD7F/5F810723" Ref="Y?"  Part="1" 
F 0 "Y?" V 721 7066 50  0000 L CNN
F 1 "ABM8G-12.000MHZ-4Y-T3" V 975 6450 50  0000 L CNN
F 2 ".Oscillator:OSCCC320X250X100L80X100" H 625 6975 50  0001 C CNN
F 3 "https://abracon.com/Resonators/ABM8G.pdf" H 675 6900 50  0001 C CNN
	1    675  6900
	0    1    -1   0   
$EndComp
Wire Wire Line
	550  6900 425  6900
Wire Wire Line
	800  6900 950  6900
Wire Wire Line
	675  6800 675  6725
Wire Wire Line
	950  6900 950  7125
Wire Wire Line
	950  7125 425  7125
Wire Wire Line
	425  7125 425  6900
$Comp
L power:GND #PWR?
U 1 1 5F81072F
P 425 7125
AR Path="/5F81072F" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F81072F" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 425 6875 50  0001 C CNN
F 1 "GND" H 430 6952 50  0000 C CNN
F 2 "" H 425 7125 50  0001 C CNN
F 3 "" H 425 7125 50  0001 C CNN
	1    425  7125
	1    0    0    -1  
$EndComp
Connection ~ 425  7125
$Comp
L .Capacitor:GRM1555C1H120JA01D C?
U 1 1 5F810738
P 1075 7100
AR Path="/5C92D296/5F810738" Ref="C?"  Part="1" 
AR Path="/5F810738" Ref="C?"  Part="1" 
AR Path="/5F7DBD7F/5F810738" Ref="C?"  Part="1" 
F 0 "C?" H 1167 7146 50  0000 L CNN
F 1 "GRM1555C1H120JA01D" H 685 7270 50  0001 L CNN
F 2 ".Capacitor:C_0402_1005Metric_L" H 1135 7370 50  0001 C CNN
F 3 "http://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM033R61A104ME15-01.pdf" H 1085 7170 50  0001 C CNN
F 4 "12pF" H 1167 7055 50  0000 L CNN "Note"
F 5 "0402" H 1185 6920 50  0001 C CNN "Size"
	1    1075 7100
	1    0    0    1   
$EndComp
$Comp
L .Capacitor:GRM1555C1H120JA01D C?
U 1 1 5F810740
P 1425 7100
AR Path="/5C92D296/5F810740" Ref="C?"  Part="1" 
AR Path="/5F810740" Ref="C?"  Part="1" 
AR Path="/5F7DBD7F/5F810740" Ref="C?"  Part="1" 
F 0 "C?" H 1517 7146 50  0000 L CNN
F 1 "GRM1555C1H120JA01D" H 1035 7270 50  0001 L CNN
F 2 ".Capacitor:C_0402_1005Metric_L" H 1485 7370 50  0001 C CNN
F 3 "http://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM033R61A104ME15-01.pdf" H 1435 7170 50  0001 C CNN
F 4 "12pF" H 1517 7055 50  0000 L CNN "Note"
F 5 "0402" H 1535 6920 50  0001 C CNN "Size"
	1    1425 7100
	1    0    0    1   
$EndComp
Wire Wire Line
	675  7000 1075 7000
Wire Wire Line
	1425 6725 1425 7000
Wire Wire Line
	675  6725 1425 6725
$Comp
L power:GND #PWR?
U 1 1 5F810749
P 1075 7200
AR Path="/5F810749" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F810749" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1075 6950 50  0001 C CNN
F 1 "GND" H 1080 7027 50  0000 C CNN
F 2 "" H 1075 7200 50  0001 C CNN
F 3 "" H 1075 7200 50  0001 C CNN
	1    1075 7200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1075 7200 1425 7200
Connection ~ 1075 7200
Text Label 1000 6725 0    50   ~ 0
XOUT
Text Label 1000 7000 0    50   ~ 0
XIN
Wire Wire Line
	25   875  425  875 
Connection ~ 425  875 
Wire Wire Line
	425  875  675  875 
Connection ~ 25   1075
Wire Wire Line
	25   1075 425  1075
$Comp
L .Connector:0475710001 J?
U 1 1 5F810758
P 10125 5025
AR Path="/5C92D2A1/5F810758" Ref="J?"  Part="1" 
AR Path="/5F810758" Ref="J?"  Part="1" 
AR Path="/5F7DBD7F/5F810758" Ref="J?"  Part="1" 
F 0 "J?" H 10452 5015 50  0000 L CNN
F 1 "0475710001" H 10452 4924 50  0000 L CNN
F 2 ".Connector:0475710001" H 9925 5025 50  0001 C CNN
F 3 "https://www.molex.com/pdm_docs/sd/475710001_sd.pdf" H 9925 5025 50  0001 C CNN
	1    10125 5025
	1    0    0    -1  
$EndComp
Wire Wire Line
	9675 5475 9525 5475
Wire Wire Line
	9525 5825 10125 5825
Wire Wire Line
	10325 5825 10325 5675
Wire Wire Line
	9525 5475 9525 5825
Wire Wire Line
	10225 5675 10225 5825
Connection ~ 10225 5825
Wire Wire Line
	10225 5825 10325 5825
Wire Wire Line
	10125 5675 10125 5825
Connection ~ 10125 5825
Wire Wire Line
	10125 5825 10225 5825
Wire Wire Line
	9225 4775 9675 4775
Wire Wire Line
	9225 4875 9675 4875
Wire Wire Line
	9225 4975 9675 4975
Wire Wire Line
	9225 5075 9675 5075
NoConn ~ 9675 5275
NoConn ~ 9675 5375
$Comp
L power:+3V3 #PWR?
U 1 1 5F81076E
P 9375 4025
AR Path="/5C92D2A1/5F81076E" Ref="#PWR?"  Part="1" 
AR Path="/5F81076E" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F81076E" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 9375 3875 50  0001 C CNN
F 1 "+3V3" H 9390 4198 50  0000 C CNN
F 2 "" H 9375 4025 50  0001 C CNN
F 3 "" H 9375 4025 50  0001 C CNN
	1    9375 4025
	1    0    0    -1  
$EndComp
Wire Wire Line
	7625 4675 7275 4675
Wire Wire Line
	7625 4775 7275 4775
Wire Wire Line
	7625 4875 7275 4875
Wire Wire Line
	7625 4975 7275 4975
Text Label 7275 4675 0    50   ~ 0
SD0
Text Label 7275 4775 0    50   ~ 0
SD1
Text Label 7275 4875 0    50   ~ 0
SD2
Text Label 7275 4975 0    50   ~ 0
SD3
Wire Wire Line
	8275 4025 8275 4125
Connection ~ 7625 4025
Wire Wire Line
	7625 4025 7625 4475
Wire Wire Line
	8575 4125 8575 4025
Wire Wire Line
	9225 4675 9675 4675
$Comp
L .Capacitor:GRM033R61A104ME15D C?
U 1 1 5F810783
P 9575 4125
AR Path="/5C92D2A1/5F810783" Ref="C?"  Part="1" 
AR Path="/5F810783" Ref="C?"  Part="1" 
AR Path="/5F7DBD7F/5F810783" Ref="C?"  Part="1" 
F 0 "C?" H 9667 4171 50  0000 L CNN
F 1 "GRM033R61A104ME15D" H 9185 4295 50  0001 L CNN
F 2 ".Capacitor:C_0201_0603Metric_L" H 9635 4395 50  0001 C CNN
F 3 "http://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM033R61A104ME15-01.pdf" H 9585 4195 50  0001 C CNN
F 4 "0.1uF" H 9667 4080 50  0000 L CNN "Note"
F 5 "0201" H 9685 3945 50  0001 C CNN "Size"
	1    9575 4125
	1    0    0    -1  
$EndComp
$Comp
L .Capacitor:GRM033R61A104ME15D C?
U 1 1 5F81078B
P 9175 4125
AR Path="/5C92D2A1/5F81078B" Ref="C?"  Part="1" 
AR Path="/5F81078B" Ref="C?"  Part="1" 
AR Path="/5F7DBD7F/5F81078B" Ref="C?"  Part="1" 
F 0 "C?" H 9267 4171 50  0000 L CNN
F 1 "GRM033R61A104ME15D" H 8785 4295 50  0001 L CNN
F 2 ".Capacitor:C_0201_0603Metric_L" H 9235 4395 50  0001 C CNN
F 3 "http://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM033R61A104ME15-01.pdf" H 9185 4195 50  0001 C CNN
F 4 "0.1uF" H 9267 4080 50  0000 L CNN "Note"
F 5 "0201" H 9285 3945 50  0001 C CNN "Size"
	1    9175 4125
	1    0    0    -1  
$EndComp
$Comp
L .Capacitor:GRM033R61A104ME15D C?
U 1 1 5F810793
P 7775 4125
AR Path="/5C92D2A1/5F810793" Ref="C?"  Part="1" 
AR Path="/5F810793" Ref="C?"  Part="1" 
AR Path="/5F7DBD7F/5F810793" Ref="C?"  Part="1" 
F 0 "C?" H 7867 4171 50  0000 L CNN
F 1 "GRM033R61A104ME15D" H 7385 4295 50  0001 L CNN
F 2 ".Capacitor:C_0201_0603Metric_L" H 7835 4395 50  0001 C CNN
F 3 "http://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM033R61A104ME15-01.pdf" H 7785 4195 50  0001 C CNN
F 4 "0.1uF" H 7867 4080 50  0000 L CNN "Note"
F 5 "0201" H 7885 3945 50  0001 C CNN "Size"
	1    7775 4125
	1    0    0    -1  
$EndComp
Wire Wire Line
	7625 4025 7775 4025
Wire Wire Line
	8575 4025 9175 4025
Connection ~ 7775 4025
Wire Wire Line
	7775 4025 8275 4025
Text Label 7275 5175 0    50   ~ 0
SDCLKA
Text Label 7275 5075 0    50   ~ 0
SDCMDA
Wire Wire Line
	7625 5075 7275 5075
Wire Wire Line
	7625 5175 7275 5175
Wire Wire Line
	8325 5475 8425 5475
$Comp
L power:GND #PWR?
U 1 1 5F8107A2
P 7775 4225
AR Path="/5F8107A2" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8107A2" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 7775 3975 50  0001 C CNN
F 1 "GND" H 7780 4052 50  0000 C CNN
F 2 "" H 7775 4225 50  0001 C CNN
F 3 "" H 7775 4225 50  0001 C CNN
	1    7775 4225
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F8107A8
P 8325 5475
AR Path="/5F8107A8" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8107A8" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 8325 5225 50  0001 C CNN
F 1 "GND" H 8330 5302 50  0000 C CNN
F 2 "" H 8325 5475 50  0001 C CNN
F 3 "" H 8325 5475 50  0001 C CNN
	1    8325 5475
	1    0    0    -1  
$EndComp
Connection ~ 8325 5475
$Comp
L power:+1V8 #PWR?
U 1 1 5F8107AF
P 7625 4025
AR Path="/5C92D2A1/5F8107AF" Ref="#PWR?"  Part="1" 
AR Path="/5F8107AF" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8107AF" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 7625 3875 50  0001 C CNN
F 1 "+1V8" H 7640 4198 50  0000 C CNN
F 2 "" H 7625 4025 50  0001 C CNN
F 3 "" H 7625 4025 50  0001 C CNN
	1    7625 4025
	1    0    0    -1  
$EndComp
$Comp
L .Logic_Level_Translator:MAX13030EETE+ U?
U 1 1 5F8107B5
P 8375 4925
AR Path="/5C92D2A1/5F8107B5" Ref="U?"  Part="1" 
AR Path="/5F8107B5" Ref="U?"  Part="1" 
AR Path="/5F7DBD7F/5F8107B5" Ref="U?"  Part="1" 
F 0 "U?" H 8925 4500 50  0000 C CNN
F 1 "MAX13030EETE+" H 7900 4500 50  0000 C CNN
F 2 ".Package_QFN:QFN_17_P65_400X400X80L50X30T210L" H 8425 4925 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX13030E-MAX13035E.pdf" H 8425 4925 50  0001 C CNN
	1    8375 4925
	1    0    0    -1  
$EndComp
Connection ~ 9175 4025
Wire Wire Line
	9175 4025 9375 4025
$Comp
L power:GND #PWR?
U 1 1 5F8107BD
P 9175 4225
AR Path="/5F8107BD" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8107BD" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 9175 3975 50  0001 C CNN
F 1 "GND" H 9180 4052 50  0000 C CNN
F 2 "" H 9175 4225 50  0001 C CNN
F 3 "" H 9175 4225 50  0001 C CNN
	1    9175 4225
	1    0    0    -1  
$EndComp
Wire Wire Line
	9225 5175 9675 5175
$Comp
L power:GND #PWR?
U 1 1 5F8107C4
P 9575 4225
AR Path="/5F8107C4" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8107C4" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 9575 3975 50  0001 C CNN
F 1 "GND" H 9580 4052 50  0000 C CNN
F 2 "" H 9575 4225 50  0001 C CNN
F 3 "" H 9575 4225 50  0001 C CNN
	1    9575 4225
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F8107CA
P 10325 5825
AR Path="/5F8107CA" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8107CA" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 10325 5575 50  0001 C CNN
F 1 "GND" H 10330 5652 50  0000 C CNN
F 2 "" H 10325 5825 50  0001 C CNN
F 3 "" H 10325 5825 50  0001 C CNN
	1    10325 5825
	1    0    0    -1  
$EndComp
Connection ~ 10325 5825
Wire Wire Line
	9675 4025 9675 4575
Wire Wire Line
	9575 4025 9675 4025
Wire Wire Line
	9575 4025 9375 4025
Connection ~ 9575 4025
Connection ~ 9375 4025
$Comp
L power:+1V8 #PWR?
U 1 1 5F8107D6
P 10250 6950
AR Path="/5C92D2A9/5F8107D6" Ref="#PWR?"  Part="1" 
AR Path="/5F8107D6" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8107D6" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 10250 6800 50  0001 C CNN
F 1 "+1V8" H 10265 7123 50  0000 C CNN
F 2 "" H 10250 6950 50  0001 C CNN
F 3 "" H 10250 6950 50  0001 C CNN
	1    10250 6950
	1    0    0    -1  
$EndComp
$Comp
L .Connector:Conn_01x01 J?
U 1 1 5F8107DC
P 10800 6950
AR Path="/5C92D2A9/5F8107DC" Ref="J?"  Part="1" 
AR Path="/5F8107DC" Ref="J?"  Part="1" 
AR Path="/5F7DBD7F/5F8107DC" Ref="J?"  Part="1" 
F 0 "J?" H 10880 6992 50  0000 L CNN
F 1 "Conn_01x01" H 10880 6901 50  0000 L CNN
F 2 ".Connector:Conn_1x1_700_Circular_Pad" H 10800 6950 50  0001 C CNN
F 3 "~" H 10800 6950 50  0001 C CNN
	1    10800 6950
	1    0    0    -1  
$EndComp
$Comp
L .Connector:Conn_01x01 J?
U 1 1 5F8107E2
P 10800 7050
AR Path="/5C92D2A9/5F8107E2" Ref="J?"  Part="1" 
AR Path="/5F8107E2" Ref="J?"  Part="1" 
AR Path="/5F7DBD7F/5F8107E2" Ref="J?"  Part="1" 
F 0 "J?" H 10880 7092 50  0000 L CNN
F 1 "Conn_01x01" H 10880 7001 50  0000 L CNN
F 2 ".Connector:Conn_1x1_700_Circular_Pad" H 10800 7050 50  0001 C CNN
F 3 "~" H 10800 7050 50  0001 C CNN
	1    10800 7050
	1    0    0    -1  
$EndComp
$Comp
L .Connector:Conn_01x01 J?
U 1 1 5F8107E8
P 10800 7150
AR Path="/5C92D2A9/5F8107E8" Ref="J?"  Part="1" 
AR Path="/5F8107E8" Ref="J?"  Part="1" 
AR Path="/5F7DBD7F/5F8107E8" Ref="J?"  Part="1" 
F 0 "J?" H 10880 7192 50  0000 L CNN
F 1 "Conn_01x01" H 10880 7101 50  0000 L CNN
F 2 ".Connector:Conn_1x1_700_Circular_Pad" H 10800 7150 50  0001 C CNN
F 3 "~" H 10800 7150 50  0001 C CNN
	1    10800 7150
	1    0    0    -1  
$EndComp
$Comp
L .Connector:Conn_01x01 J?
U 1 1 5F8107EE
P 10800 7250
AR Path="/5C92D2A9/5F8107EE" Ref="J?"  Part="1" 
AR Path="/5F8107EE" Ref="J?"  Part="1" 
AR Path="/5F7DBD7F/5F8107EE" Ref="J?"  Part="1" 
F 0 "J?" H 10880 7292 50  0000 L CNN
F 1 "Conn_01x01" H 10880 7201 50  0000 L CNN
F 2 ".Connector:Conn_1x1_700_Circular_Pad" H 10800 7250 50  0001 C CNN
F 3 "~" H 10800 7250 50  0001 C CNN
	1    10800 7250
	1    0    0    -1  
$EndComp
Wire Wire Line
	10300 7150 10600 7150
Wire Wire Line
	10600 7050 10300 7050
Wire Wire Line
	10250 6950 10600 6950
Wire Wire Line
	10300 7250 10600 7250
Text Notes 10150 6600 0    50   ~ 0
SWD Programming Connections
$Comp
L power:GND #PWR?
U 1 1 5F8107F9
P 10300 7250
AR Path="/5F8107F9" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8107F9" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 10300 7000 50  0001 C CNN
F 1 "GND" H 10305 7077 50  0000 C CNN
F 2 "" H 10300 7250 50  0001 C CNN
F 3 "" H 10300 7250 50  0001 C CNN
	1    10300 7250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 3425 2150 3425
Wire Notes Line
	9800 6450 11550 6450
Wire Notes Line
	9800 7450 9800 6450
Wire Notes Line
	9800 7450 11550 7450
Wire Notes Line
	7050 6075 10800 6075
Wire Notes Line
	10800 6075 10800 3775
Wire Notes Line
	10800 3775 7050 3775
Wire Notes Line
	7050 3775 7050 6075
Text Notes 7075 6050 0    50   ~ 0
Level Shifter & SD Card Slot
Text Notes 275  6550 0    50   ~ 0
Clock
Wire Notes Line
	225  6450 225  7450
Wire Notes Line
	225  7450 1725 7450
Wire Notes Line
	1725 7450 1725 6450
Wire Notes Line
	1725 6450 225  6450
Text Label 10300 7050 0    50   ~ 0
SWDIO
Text Label 10300 7150 0    50   ~ 0
SWDCLK
$Comp
L Connector_Generic:Conn_01x04 J?
U 1 1 5F81080F
P 8600 6950
AR Path="/5F81080F" Ref="J?"  Part="1" 
AR Path="/5F7DBD7F/5F81080F" Ref="J?"  Part="1" 
F 0 "J?" H 8518 7267 50  0000 C CNN
F 1 "Conn_01x04" H 8518 7176 50  0000 C CNN
F 2 ".Connector:1x4_USB" H 8600 6950 50  0001 C CNN
F 3 "~" H 8600 6950 50  0001 C CNN
	1    8600 6950
	-1   0    0    -1  
$EndComp
Wire Notes Line
	9650 6350 9650 7600
Wire Notes Line
	8175 7600 9650 7600
Wire Notes Line
	8175 6350 9650 6350
$Comp
L .Regulator_Switching:MAX77651AEWV+ U?
U 2 1 5F810818
P 8250 675
AR Path="/5F810818" Ref="U?"  Part="2" 
AR Path="/5F7DBD7F/5F810818" Ref="U?"  Part="2" 
F 0 "U?" H 9050 1062 60  0000 C CNN
F 1 "MAX77650CEWV+T" H 9050 956 60  0000 C CNN
F 2 ".Package_BGA:MAX77651AEWV&plus_" H 9150 915 60  0001 C CNN
F 3 "" H 8250 675 60  0000 C CNN
	2    8250 675 
	1    0    0    -1  
$EndComp
Wire Wire Line
	9850 675  9850 775 
Connection ~ 9850 775 
Wire Wire Line
	9850 775  9850 875 
Connection ~ 9850 875 
Wire Wire Line
	9850 875  9850 1000
$Comp
L power:GND #PWR?
U 1 1 5F810823
P 9850 1000
AR Path="/5F810823" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F810823" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 9850 750 50  0001 C CNN
F 1 "GND" H 9855 827 50  0000 C CNN
F 2 "" H 9850 1000 50  0001 C CNN
F 3 "" H 9850 1000 50  0001 C CNN
	1    9850 1000
	1    0    0    -1  
$EndComp
Text Notes 8225 6475 0    50   ~ 0
UART
$Comp
L power:VBUS #PWR?
U 1 1 5F81082A
P 9250 6850
AR Path="/5F81082A" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F81082A" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 9250 6700 50  0001 C CNN
F 1 "VBUS" H 9265 7023 50  0000 C CNN
F 2 "" H 9250 6850 50  0001 C CNN
F 3 "" H 9250 6850 50  0001 C CNN
	1    9250 6850
	1    0    0    -1  
$EndComp
Text Label 9250 6950 2    50   ~ 0
TXD2
Text Label 9250 7050 2    50   ~ 0
RXD2
$Comp
L power:GND #PWR?
U 1 1 5F810832
P 9250 7150
AR Path="/5F810832" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F810832" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 9250 6900 50  0001 C CNN
F 1 "GND" H 9255 6977 50  0000 C CNN
F 2 "" H 9250 7150 50  0001 C CNN
F 3 "" H 9250 7150 50  0001 C CNN
	1    9250 7150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9250 7150 8800 7150
Wire Wire Line
	8800 7050 9250 7050
Wire Wire Line
	8800 6950 9250 6950
Wire Wire Line
	8800 6850 9250 6850
$Comp
L power:VBUS #PWR?
U 1 1 5F81083C
P 6700 850
AR Path="/5F81083C" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F81083C" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 6700 700 50  0001 C CNN
F 1 "VBUS" H 6715 1023 50  0000 C CNN
F 2 "" H 6700 850 50  0001 C CNN
F 3 "" H 6700 850 50  0001 C CNN
	1    6700 850 
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR?
U 1 1 5F810842
P 6700 2575
AR Path="/5F810842" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F810842" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 6700 2425 50  0001 C CNN
F 1 "+BATT" H 6715 2748 50  0000 C CNN
F 2 "" H 6700 2575 50  0001 C CNN
F 3 "" H 6700 2575 50  0001 C CNN
	1    6700 2575
	1    0    0    -1  
$EndComp
$Comp
L .Capacitor:GRM155R60J475ME87D C?
U 1 1 5F81084A
P 6700 2675
AR Path="/5F81084A" Ref="C?"  Part="1" 
AR Path="/5F7DBD7F/5F81084A" Ref="C?"  Part="1" 
F 0 "C?" H 6792 2721 50  0000 L CNN
F 1 "GRM155R60J475ME87D" H 6310 2845 50  0001 L CNN
F 2 ".Capacitor:C_0402_1005Metric_L" H 6810 2945 50  0001 C CNN
F 3 "" H 6710 2745 50  0001 C CNN
F 4 "4.7uF" H 6792 2630 50  0000 L CNN "Note"
F 5 "0402" H 6810 2495 50  0001 C CNN "Size"
	1    6700 2675
	1    0    0    -1  
$EndComp
Connection ~ 6700 2575
$Comp
L power:GND #PWR?
U 1 1 5F810851
P 6700 2775
AR Path="/5F810851" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F810851" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 6700 2525 50  0001 C CNN
F 1 "GND" H 6705 2602 50  0000 C CNN
F 2 "" H 6700 2775 50  0001 C CNN
F 3 "" H 6700 2775 50  0001 C CNN
	1    6700 2775
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F810857
P 6700 1050
AR Path="/5F810857" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F810857" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 6700 800 50  0001 C CNN
F 1 "GND" H 6705 877 50  0000 C CNN
F 2 "" H 6700 1050 50  0001 C CNN
F 3 "" H 6700 1050 50  0001 C CNN
	1    6700 1050
	1    0    0    -1  
$EndComp
$Comp
L power:+1V8 #PWR?
U 1 1 5F81085D
P 8150 2375
AR Path="/5F81085D" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F81085D" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 8150 2225 50  0001 C CNN
F 1 "+1V8" V 8050 2450 50  0000 C CNN
F 2 "" H 8150 2375 50  0001 C CNN
F 3 "" H 8150 2375 50  0001 C CNN
	1    8150 2375
	0    -1   -1   0   
$EndComp
Text Label 7675 2175 0    50   ~ 0
SCL
Wire Wire Line
	8150 2975 7675 2975
Text Label 7675 2975 0    50   ~ 0
SDA
Wire Wire Line
	8150 2175 7675 2175
Wire Wire Line
	8250 675  8100 675 
$Comp
L .Capacitor:CL03A105KP3NSNC C?
U 1 1 5F81086A
P 8100 775
AR Path="/5F81086A" Ref="C?"  Part="1" 
AR Path="/5F7DBD7F/5F81086A" Ref="C?"  Part="1" 
F 0 "C?" H 8192 821 50  0000 L CNN
F 1 "CL03A105KP3NSNC" H 7710 945 50  0001 L CNN
F 2 ".Capacitor:C_0201_0603Metric_L" H 8160 1045 50  0001 C CNN
F 3 "https://media.digikey.com/pdf/Data%20Sheets/Samsung%20PDFs/CL_Series_MLCC_ds.pdf" H 8110 845 50  0001 C CNN
F 4 "1uF" H 8192 730 50  0000 L CNN "Note"
F 5 "0201" H 8210 595 50  0001 C CNN "Size"
	1    8100 775 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F810870
P 8100 875
AR Path="/5F810870" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F810870" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 8100 625 50  0001 C CNN
F 1 "GND" H 8105 702 50  0000 C CNN
F 2 "" H 8100 875 50  0001 C CNN
F 3 "" H 8100 875 50  0001 C CNN
	1    8100 875 
	1    0    0    -1  
$EndComp
Connection ~ 6700 850 
$Comp
L .Capacitor:GRM188R61E475KE11D C?
U 1 1 5F810879
P 6700 950
AR Path="/5F810879" Ref="C?"  Part="1" 
AR Path="/5F7DBD7F/5F810879" Ref="C?"  Part="1" 
F 0 "C?" H 6792 996 50  0000 L CNN
F 1 "GRM188R61E475KE11D" H 6310 1120 50  0001 L CNN
F 2 ".Capacitor:C_0603_1608Metric_L" H 6810 1220 50  0001 C CNN
F 3 "https://www.murata.com/~/media/webrenewal/support/library/catalog/products/capacitor/mlcc/c02e.ashx?la=en-us" H 6710 1020 50  0001 C CNN
F 4 "4.7uF" H 6792 905 50  0000 L CNN "Note"
F 5 "0603" H 6810 770 50  0001 C CNN "Size"
	1    6700 950 
	1    0    0    -1  
$EndComp
$Comp
L power:VS #PWR?
U 1 1 5F81087F
P 8150 1875
AR Path="/5F81087F" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F81087F" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 7950 1725 50  0001 C CNN
F 1 "VS" V 8168 2003 50  0000 L CNN
F 2 "" H 8150 1875 50  0001 C CNN
F 3 "" H 8150 1875 50  0001 C CNN
	1    8150 1875
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9950 2375 10175 2375
$Comp
L .Capacitor:CL10A226KQ8NRNE C?
U 1 1 5F810888
P 10175 2475
AR Path="/5F810888" Ref="C?"  Part="1" 
AR Path="/5F7DBD7F/5F810888" Ref="C?"  Part="1" 
F 0 "C?" H 10267 2521 50  0000 L CNN
F 1 "CL10A226KQ8NRNE" H 9785 2645 50  0001 L CNN
F 2 ".Capacitor:C_0603_1608Metric_L" H 10235 2745 50  0001 C CNN
F 3 "https://media.digikey.com/pdf/Data%20Sheets/Samsung%20PDFs/CL10A226KQ8NRNE_Spec_5-2-19.pdf" H 10185 2545 50  0001 C CNN
F 4 "22uF" H 10267 2430 50  0000 L CNN "Note"
F 5 "0603" H 10285 2295 50  0001 C CNN "Size"
	1    10175 2475
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F81088E
P 10175 2575
AR Path="/5F81088E" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F81088E" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 10175 2325 50  0001 C CNN
F 1 "GND" H 10180 2402 50  0000 C CNN
F 2 "" H 10175 2575 50  0001 C CNN
F 3 "" H 10175 2575 50  0001 C CNN
	1    10175 2575
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F810894
P 9950 3075
AR Path="/5F810894" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F810894" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 9950 2825 50  0001 C CNN
F 1 "GND" H 9955 2902 50  0000 C CNN
F 2 "" H 9950 3075 50  0001 C CNN
F 3 "" H 9950 3075 50  0001 C CNN
	1    9950 3075
	1    0    0    -1  
$EndComp
Wire Wire Line
	9950 2175 10525 2175
Wire Wire Line
	9950 2075 10525 2075
Wire Wire Line
	9950 1975 11375 1975
$Comp
L .Capacitor:GRM155R60J106ME15D C?
U 1 1 5F81089F
P 10950 2175
AR Path="/5F81089F" Ref="C?"  Part="1" 
AR Path="/5F7DBD7F/5F81089F" Ref="C?"  Part="1" 
F 0 "C?" H 11042 2221 50  0000 L CNN
F 1 "GRM155R60J106ME15D" H 10560 2345 50  0001 L CNN
F 2 ".Capacitor:C_0402_1005Metric_L" H 11060 2445 50  0001 C CNN
F 3 "https://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM155R60J106ME15-01.pdf" H 10960 2245 50  0001 C CNN
F 4 "10uF" H 11042 2130 50  0000 L CNN "Note"
F 5 "0402" H 11060 1995 50  0001 C CNN "Size"
	1    10950 2175
	1    0    0    -1  
$EndComp
$Comp
L .Capacitor:GRM155R60J106ME15D C?
U 1 1 5F8108A7
P 11375 2075
AR Path="/5F8108A7" Ref="C?"  Part="1" 
AR Path="/5F7DBD7F/5F8108A7" Ref="C?"  Part="1" 
F 0 "C?" H 11467 2121 50  0000 L CNN
F 1 "GRM155R60J106ME15D" H 10985 2245 50  0001 L CNN
F 2 ".Capacitor:C_0402_1005Metric_L" H 11485 2345 50  0001 C CNN
F 3 "https://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM155R60J106ME15-01.pdf" H 11385 2145 50  0001 C CNN
F 4 "10uF" H 11467 2030 50  0000 L CNN "Note"
F 5 "0402" H 11485 1895 50  0001 C CNN "Size"
	1    11375 2075
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F8108AD
P 10950 2275
AR Path="/5F8108AD" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8108AD" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 10950 2025 50  0001 C CNN
F 1 "GND" H 10955 2102 50  0000 C CNN
F 2 "" H 10950 2275 50  0001 C CNN
F 3 "" H 10950 2275 50  0001 C CNN
	1    10950 2275
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F8108B3
P 11375 2175
AR Path="/5F8108B3" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8108B3" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 11375 1925 50  0001 C CNN
F 1 "GND" H 11380 2002 50  0000 C CNN
F 2 "" H 11375 2175 50  0001 C CNN
F 3 "" H 11375 2175 50  0001 C CNN
	1    11375 2175
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 2575 8150 2575
Wire Wire Line
	8150 2775 7625 2775
Wire Wire Line
	8150 2875 7625 2875
$Comp
L .Inductor:MLF1005G1R5JTD25 L?
U 1 1 5F8108BE
P 7250 2825
AR Path="/5F8108BE" Ref="L?"  Part="1" 
AR Path="/5F7DBD7F/5F8108BE" Ref="L?"  Part="1" 
F 0 "L?" H 7206 2779 50  0000 R CNN
F 1 "MLF1005G1R5JTD25" H 7300 2675 50  0001 L CNN
F 2 "Inductor_SMD:L_0402_1005Metric" H 7300 3125 50  0001 C CNN
F 3 "https://product.tdk.com/info/en/catalog/datasheets/inductor_automotive_standard_mlf1005_en.pdf" H 7250 2825 50  0001 C CNN
F 4 "1.5uH" H 7206 2870 50  0000 R CNN "Note"
F 5 "0402" H 7400 2575 50  0001 C CNN "Size"
	1    7250 2825
	-1   0    0    1   
$EndComp
Wire Wire Line
	7250 2725 7625 2725
Wire Wire Line
	7625 2725 7625 2775
Wire Wire Line
	7250 2925 7625 2925
Wire Wire Line
	7625 2925 7625 2875
Text Label 7625 2875 0    50   ~ 0
BST
Wire Wire Line
	8150 1575 7800 1575
$Comp
L .Capacitor:GRM033R70J332KA01D C?
U 1 1 5F8108CC
P 7800 1475
AR Path="/5F8108CC" Ref="C?"  Part="1" 
AR Path="/5F7DBD7F/5F8108CC" Ref="C?"  Part="1" 
F 0 "C?" H 7892 1521 50  0000 L CNN
F 1 "GRM033R70J332KA01D" H 7410 1645 50  0001 L CNN
F 2 ".Capacitor:C_0201_0603Metric_L" H 7860 1745 50  0001 C CNN
F 3 "https://www.murata.com/~/media/webrenewal/support/library/catalog/products/capacitor/mlcc/c02e.ashx?la=en-us" H 7810 1545 50  0001 C CNN
F 4 "3300pF" H 7892 1430 50  0000 L CNN "Note"
F 5 "0201" H 7910 1295 50  0001 C CNN "Size"
	1    7800 1475
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 1375 7800 1225
Text Label 7800 1225 3    50   ~ 0
BST
Text Notes 9950 1875 0    50   ~ 0
Keep MCU powered down
NoConn ~ 9950 1875
Text Notes 8850 2350 0    50   ~ 0
<-Could save\nbattery if \nconnected to\nMCU
$Comp
L power:VS #PWR?
U 1 1 5F8108D7
P 8150 2075
AR Path="/5F8108D7" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8108D7" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 7950 1925 50  0001 C CNN
F 1 "VS" V 8168 2203 50  0000 L CNN
F 2 "" H 8150 2075 50  0001 C CNN
F 3 "" H 8150 2075 50  0001 C CNN
	1    8150 2075
	0    -1   -1   0   
$EndComp
Text Notes 10875 2625 0    50   ~ 0
Connected unused SBB to SBB#\np. 68
Text Notes 8775 1800 0    50   ~ 0
DNL Resistor\n<-p. 70
Wire Wire Line
	6700 850  7625 850 
$Comp
L power:+3V3 #PWR?
U 1 1 5F8108E0
P 10950 2075
AR Path="/5F8108E0" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8108E0" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 10950 1925 50  0001 C CNN
F 1 "+3V3" H 10965 2248 50  0000 C CNN
F 2 "" H 10950 2075 50  0001 C CNN
F 3 "" H 10950 2075 50  0001 C CNN
	1    10950 2075
	1    0    0    -1  
$EndComp
$Comp
L power:+1V8 #PWR?
U 1 1 5F8108E6
P 11375 1975
AR Path="/5F8108E6" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8108E6" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 11375 1825 50  0001 C CNN
F 1 "+1V8" H 11390 2148 50  0000 C CNN
F 2 "" H 11375 1975 50  0001 C CNN
F 3 "" H 11375 1975 50  0001 C CNN
	1    11375 1975
	1    0    0    -1  
$EndComp
Connection ~ 11375 1975
Text Notes 9950 1675 0    50   ~ 0
Not using the LDO
$Comp
L power:GND #PWR?
U 1 1 5F8108EE
P 6600 1750
AR Path="/5F8108EE" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8108EE" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 6600 1500 50  0001 C CNN
F 1 "GND" H 6605 1577 50  0000 C CNN
F 2 "" H 6600 1750 50  0001 C CNN
F 3 "" H 6600 1750 50  0001 C CNN
	1    6600 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7625 850  7625 1675
Wire Wire Line
	7625 1675 8150 1675
Wire Wire Line
	7000 1975 7300 1975
Wire Wire Line
	7000 1750 7000 1975
$Comp
L .Resistor:RC0201FR-07100KL R?
U 1 1 5F8108FA
P 7300 1875
AR Path="/5F8108FA" Ref="R?"  Part="1" 
AR Path="/5F7DBD7F/5F8108FA" Ref="R?"  Part="1" 
F 0 "R?" H 7368 1921 50  0000 L CNN
F 1 "RC0201FR-07100KL" H 7330 1685 50  0001 L CNN
F 2 ".Resistor:R_0201_0603Metric_ERJ_L" H 7230 1795 50  0001 C CNN
F 3 "https://www.yageo.com/upload/media/product/productsearch/datasheet/rchip/PYu-RC_Group_51_RoHS_L_11.pdf" H 7300 1875 50  0001 C CNN
F 4 "100K" H 7368 1830 50  0000 L CNN "Note"
F 5 "0201" H 7530 2095 50  0001 C CNN "Size"
	1    7300 1875
	1    0    0    -1  
$EndComp
Connection ~ 7300 1975
Wire Wire Line
	7300 1975 8150 1975
$Comp
L power:VS #PWR?
U 1 1 5F810902
P 7300 1775
AR Path="/5F810902" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F810902" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 7100 1625 50  0001 C CNN
F 1 "VS" H 7317 1948 50  0000 C CNN
F 2 "" H 7300 1775 50  0001 C CNN
F 3 "" H 7300 1775 50  0001 C CNN
	1    7300 1775
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 4325 6250 4325
Wire Wire Line
	5400 4425 6250 4425
Text Label 6250 4325 2    50   ~ 0
RXD2
Text Label 6250 4425 2    50   ~ 0
TXD2
Text Notes 5950 4225 0    50   ~ 0
USART module
NoConn ~ 9950 1575
Text Notes 10500 675  0    50   ~ 0
4mil spacing normally, 3mil for this chip. .3mm vias
Text Notes 9950 1575 0    50   ~ 0
Should I use this monitor pin? (Connect to ADC)
NoConn ~ 9950 1675
Text Notes 10325 1225 0    50   ~ 0
Use version C, power MCU with SBB0: 1.8V then drive SBB1: 1.0V to 3.3V
Connection ~ 10950 2075
Wire Wire Line
	10525 2175 10525 2075
Connection ~ 10525 2075
Wire Wire Line
	10525 2075 10950 2075
Wire Wire Line
	9950 2675 9950 2775
Connection ~ 9950 2775
Wire Wire Line
	9950 2875 9950 3075
Wire Wire Line
	9950 2775 9950 2875
Connection ~ 9950 2875
$Comp
L .Regulator_Switching:MAX77651AEWV+ U?
U 1 1 5F81091B
P 8150 1575
AR Path="/5F81091B" Ref="U?"  Part="1" 
AR Path="/5F7DBD7F/5F81091B" Ref="U?"  Part="1" 
F 0 "U?" H 9050 1962 60  0000 C CNN
F 1 "MAX77650CEWV+T" H 9050 1856 60  0000 C CNN
F 2 ".Package_BGA:MAX77651AEWV&plus_" H 9050 1815 60  0001 C CNN
F 3 "" H 8150 1575 60  0000 C CNN
	1    8150 1575
	1    0    0    -1  
$EndComp
NoConn ~ 8150 2275
NoConn ~ 8150 3075
Wire Wire Line
	9950 1775 10950 1775
Text Label 10950 1775 2    50   ~ 0
V_INT
NoConn ~ 8150 2675
Wire Wire Line
	4950 725  4950 1225
$Comp
L power:+1V8 #PWR?
U 1 1 5F810927
P 4950 725
AR Path="/5F810927" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F810927" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 4950 575 50  0001 C CNN
F 1 "+1V8" H 4965 898 50  0000 C CNN
F 2 "" H 4950 725 50  0001 C CNN
F 3 "" H 4950 725 50  0001 C CNN
	1    4950 725 
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R?
U 1 1 5F81092D
P 8050 1775
AR Path="/5F81092D" Ref="R?"  Part="1" 
AR Path="/5F7DBD7F/5F81092D" Ref="R?"  Part="1" 
F 0 "R?" V 7845 1775 50  0000 C CNN
F 1 "DNL" V 7936 1775 50  0000 C CNN
F 2 ".Resistor:R_0201_0603Metric_ERJ_L" H 8050 1775 50  0001 C CNN
F 3 "~" H 8050 1775 50  0001 C CNN
	1    8050 1775
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F810933
P 7950 1775
AR Path="/5F810933" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F810933" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 7950 1525 50  0001 C CNN
F 1 "GND" H 7955 1602 50  0000 C CNN
F 2 "" H 7950 1775 50  0001 C CNN
F 3 "" H 7950 1775 50  0001 C CNN
	1    7950 1775
	0    1    1    0   
$EndComp
Wire Notes Line
	11550 6450 11550 7450
Wire Notes Line
	8175 7600 8175 6350
Wire Notes Line
	6275 3500 11950 3500
Wire Notes Line
	11950 3500 11950 100 
Wire Notes Line
	11950 100  6275 100 
Wire Notes Line
	6275 100  6275 3500
Wire Notes Line
	-775 -750 -775 1450
Wire Notes Line
	-775 1450 2800 1450
Wire Notes Line
	2800 1450 2800 -750
Wire Notes Line
	2800 -750 -775 -750
Text Notes 6325 200  0    50   ~ 0
Voltage Regulator
Text Notes -700 -625 0    50   ~ 0
MCU Decouple Capacitors
$Comp
L .Jumper:Jumper_2_Bridged JP?
U 1 1 5F810945
P 6800 1750
AR Path="/5F810945" Ref="JP?"  Part="1" 
AR Path="/5F7DBD7F/5F810945" Ref="JP?"  Part="1" 
F 0 "JP?" H 6800 1945 50  0000 C CNN
F 1 "Jumper_2_Bridged" H 6800 1854 50  0000 C CNN
F 2 "Connector_PinHeader_1.27mm:PinHeader_1x02_P1.27mm_Vertical" H 6800 1750 50  0001 C CNN
F 3 "~" H 6800 1750 50  0001 C CNN
	1    6800 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 4525 6250 4525
Text Label 6250 4525 2    50   ~ 0
V_INT
$Comp
L Connector_Generic:Conn_01x27 J?
U 1 1 5F853FC0
P 275 4075
AR Path="/5F853FC0" Ref="J?"  Part="1" 
AR Path="/5F7DBD7F/5F853FC0" Ref="J?"  Part="1" 
F 0 "J?" H 193 2550 50  0000 C CNN
F 1 "Conn_01x27" H 193 2641 50  0000 C CNN
F 2 ".Connector:B2B_Flex_27_Single_Row_200x1000_Pad_400P" H 275 4075 50  0001 C CNN
F 3 "~" H 275 4075 50  0001 C CNN
	1    275  4075
	-1   0    0    1   
$EndComp
Wire Wire Line
	475  2875 1125 2875
Wire Wire Line
	475  2975 1125 2975
Wire Wire Line
	475  3075 1125 3075
Wire Wire Line
	475  3175 1125 3175
Wire Wire Line
	475  3275 1125 3275
Wire Wire Line
	475  3375 1125 3375
Wire Wire Line
	475  3475 1125 3475
Wire Wire Line
	475  3575 1125 3575
Wire Wire Line
	475  3675 1125 3675
Wire Wire Line
	475  3775 1125 3775
Wire Wire Line
	475  3875 1125 3875
Wire Wire Line
	475  3975 1125 3975
Wire Wire Line
	475  4075 1125 4075
Wire Wire Line
	475  4175 1125 4175
Wire Wire Line
	475  4275 1125 4275
Wire Wire Line
	475  4475 1125 4475
Wire Wire Line
	475  4575 1125 4575
Wire Wire Line
	475  4675 1125 4675
Wire Wire Line
	475  4775 1125 4775
Wire Wire Line
	475  4875 1125 4875
Wire Wire Line
	475  5075 1125 5075
Wire Wire Line
	475  5175 1125 5175
Text Label 1125 2975 2    50   ~ 0
PXL_CLK
Text Label 1125 3075 2    50   ~ 0
STATUS_LED
Text Label 1125 3175 2    50   ~ 0
MISO
Text Label 1125 3275 2    50   ~ 0
SCK
Text Label 1125 3375 2    50   ~ 0
MOSI
Text Label 1125 3475 2    50   ~ 0
MONITOR0
Text Label 1125 3575 2    50   ~ 0
D5
Text Label 1125 3675 2    50   ~ 0
TRIGGER0
Text Label 1125 3775 2    50   ~ 0
D3
Text Label 1125 3875 2    50   ~ 0
RESET_N
Text Label 1125 3975 2    50   ~ 0
D4
Text Label 1125 4075 2    50   ~ 0
D1
Text Label 1125 4175 2    50   ~ 0
SS_N
Text Label 1125 4275 2    50   ~ 0
D0
Text Label 1125 4475 2    50   ~ 0
D2
Text Label 1125 4575 2    50   ~ 0
FV
Text Label 1125 4675 2    50   ~ 0
IR_REV
Text Label 1125 4775 2    50   ~ 0
SCL
Text Label 1125 4875 2    50   ~ 0
D6
Text Label 1125 5075 2    50   ~ 0
D7
Text Label 1125 5175 2    50   ~ 0
SDA
Text Label 1125 2775 2    50   ~ 0
LED_ENT
Text Label 1125 2875 2    50   ~ 0
LV
Wire Notes Line
	-25  5700 1650 5700
Wire Notes Line
	1650 2350 -25  2350
Wire Notes Line
	-25  2350 -25  5700
Text Notes 1000 2475 0    50   ~ 0
To CMOS Board
Wire Wire Line
	1125 2775 475  2775
Wire Notes Line
	1650 2350 1650 5700
$Comp
L power:+3V3 #PWR?
U 1 1 5F8C0D56
P 1125 4375
AR Path="/5F8C0D56" Ref="#PWR?"  Part="1" 
AR Path="/5F6618FE/5F8C0D56" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8946C7/5F8C0D56" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1125 4225 50  0001 C CNN
F 1 "+3V3" V 1140 4503 50  0000 L CNN
F 2 "" H 1125 4375 50  0001 C CNN
F 3 "" H 1125 4375 50  0001 C CNN
	1    1125 4375
	0    1    1    0   
$EndComp
$Comp
L power:+1V8 #PWR?
U 1 1 5F8C0D5C
P 1125 4975
AR Path="/5F8C0D5C" Ref="#PWR?"  Part="1" 
AR Path="/5F6618FE/5F8C0D5C" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8946C7/5F8C0D5C" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1125 4825 50  0001 C CNN
F 1 "+1V8" V 1140 5103 50  0000 L CNN
F 2 "" H 1125 4975 50  0001 C CNN
F 3 "" H 1125 4975 50  0001 C CNN
	1    1125 4975
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F8C0D62
P 1125 5275
AR Path="/5F8C0D62" Ref="#PWR?"  Part="1" 
AR Path="/5F6618FE/5F8C0D62" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8946C7/5F8C0D62" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1125 5025 50  0001 C CNN
F 1 "GND" V 1130 5147 50  0000 R CNN
F 2 "" H 1125 5275 50  0001 C CNN
F 3 "" H 1125 5275 50  0001 C CNN
	1    1125 5275
	0    -1   -1   0   
$EndComp
$Comp
L power:+BATT #PWR?
U 1 1 5F8C0D68
P 1125 5375
AR Path="/5F8C0D68" Ref="#PWR?"  Part="1" 
AR Path="/5F6618FE/5F8C0D68" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8946C7/5F8C0D68" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1125 5225 50  0001 C CNN
F 1 "+BATT" V 1140 5503 50  0000 L CNN
F 2 "" H 1125 5375 50  0001 C CNN
F 3 "" H 1125 5375 50  0001 C CNN
	1    1125 5375
	0    1    1    0   
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 5F8C0D6E
P 1125 4375
AR Path="/5F8C0D6E" Ref="#PWR?"  Part="1" 
AR Path="/5F6618FE/5F8C0D6E" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8946C7/5F8C0D6E" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1125 4225 50  0001 C CNN
F 1 "+3V3" V 1140 4503 50  0000 L CNN
F 2 "" H 1125 4375 50  0001 C CNN
F 3 "" H 1125 4375 50  0001 C CNN
	1    1125 4375
	0    1    1    0   
$EndComp
$Comp
L power:+1V8 #PWR?
U 1 1 5F8C0D74
P 1125 4975
AR Path="/5F8C0D74" Ref="#PWR?"  Part="1" 
AR Path="/5F6618FE/5F8C0D74" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8946C7/5F8C0D74" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1125 4825 50  0001 C CNN
F 1 "+1V8" V 1140 5103 50  0000 L CNN
F 2 "" H 1125 4975 50  0001 C CNN
F 3 "" H 1125 4975 50  0001 C CNN
	1    1125 4975
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5F8C0D7A
P 1125 5275
AR Path="/5F8C0D7A" Ref="#PWR?"  Part="1" 
AR Path="/5F6618FE/5F8C0D7A" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8946C7/5F8C0D7A" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1125 5025 50  0001 C CNN
F 1 "GND" V 1130 5147 50  0000 R CNN
F 2 "" H 1125 5275 50  0001 C CNN
F 3 "" H 1125 5275 50  0001 C CNN
	1    1125 5275
	0    -1   -1   0   
$EndComp
$Comp
L power:+BATT #PWR?
U 1 1 5F8C0D80
P 1125 5375
AR Path="/5F8C0D80" Ref="#PWR?"  Part="1" 
AR Path="/5F6618FE/5F8C0D80" Ref="#PWR?"  Part="1" 
AR Path="/5F7DBD7F/5F8946C7/5F8C0D80" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1125 5225 50  0001 C CNN
F 1 "+BATT" V 1140 5503 50  0000 L CNN
F 2 "" H 1125 5375 50  0001 C CNN
F 3 "" H 1125 5375 50  0001 C CNN
	1    1125 5375
	0    1    1    0   
$EndComp
Text HLabel 1125 2775 2    50   Output ~ 0
LED_ENT
Text HLabel 1125 2875 2    50   Input ~ 0
LV
Text HLabel 1125 2975 2    50   Input ~ 0
PXL_CLK
Text HLabel 1125 3075 2    50   Output ~ 0
STATUS_LED
Text HLabel 1125 3175 2    50   Input ~ 0
MISO
Text HLabel 1125 3275 2    50   Output ~ 0
SCK
Text HLabel 1125 3375 2    50   Output ~ 0
MOSI
Text HLabel 1125 3475 2    50   Input ~ 0
MONITOR0
Text HLabel 1125 3575 2    50   Input ~ 0
D5
Text HLabel 1125 3675 2    50   Output ~ 0
TRIGGER0
Text HLabel 1125 3775 2    50   Input ~ 0
D3
Text HLabel 1125 3875 2    50   Input ~ 0
RESET_N
Text HLabel 1125 3975 2    50   Input ~ 0
D4
Text HLabel 1125 4075 2    50   Input ~ 0
D1
Text HLabel 1125 4175 2    50   Output ~ 0
SS_N
Text HLabel 1125 4275 2    50   Input ~ 0
D0
Text HLabel 1125 4475 2    50   Input ~ 0
D2
Text HLabel 1125 4575 2    50   Input ~ 0
FV
Text HLabel 1125 4675 2    50   Output ~ 0
IR_REV
Text HLabel 1125 4775 2    50   Output ~ 0
SCL
Text HLabel 1125 4875 2    50   Input ~ 0
D6
Text HLabel 1125 5075 2    50   Input ~ 0
D7
Text HLabel 1125 5175 2    50   BiDi ~ 0
SDA
Wire Wire Line
	475  5375 1125 5375
Connection ~ 1125 5375
Wire Wire Line
	475  5275 1125 5275
Connection ~ 1125 5275
Wire Wire Line
	475  4975 1125 4975
Connection ~ 1125 4975
Wire Wire Line
	475  4375 1125 4375
Connection ~ 1125 4375
$EndSCHEMATC
