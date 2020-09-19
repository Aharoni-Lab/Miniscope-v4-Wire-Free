EESchema Schematic File Version 4
EELAYER 30 0
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
L dk_Interface-Controllers:FT232RQ-REEL U1
U 1 1 5F31BDA9
P 5850 3125
F 0 "U1" H 5650 3725 60  0000 C CNN
F 1 "FT232RQ-REEL" H 5625 3575 60  0000 C CNN
F 2 ".digikey-footprints:QFN-32-1EP_5x5mm" H 6050 3325 60  0001 L CNN
F 3 "https://www.ftdichip.com/Support/Documents/DataSheets/ICs/DS_FT232R.pdf" H 6050 3425 60  0001 L CNN
F 4 "768-1008-1-ND" H 6050 3525 60  0001 L CNN "Digi-Key_PN"
F 5 "FT232RQ-REEL" H 6050 3625 60  0001 L CNN "MPN"
F 6 "Integrated Circuits (ICs)" H 6050 3725 60  0001 L CNN "Category"
F 7 "Interface - Controllers" H 6050 3825 60  0001 L CNN "Family"
F 8 "https://www.ftdichip.com/Support/Documents/DataSheets/ICs/DS_FT232R.pdf" H 6050 3925 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/ftdi-future-technology-devices-international-ltd/FT232RQ-REEL/768-1008-1-ND/1836403" H 6050 4025 60  0001 L CNN "DK_Detail_Page"
F 10 "IC USB FS SERIAL UART 32-QFN" H 6050 4125 60  0001 L CNN "Description"
F 11 "FTDI, Future Technology Devices International Ltd" H 6050 4225 60  0001 L CNN "Manufacturer"
F 12 "Active" H 6050 4325 60  0001 L CNN "Status"
	1    5850 3125
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 3425 7000 3425
$Comp
L Connector_Generic:Conn_01x04 J1
U 1 1 5F32EBDF
P 1625 3950
F 0 "J1" H 1543 3525 50  0000 C CNN
F 1 "Conn_01x04" H 1543 3616 50  0000 C CNN
F 2 ".Connector:1x4_USB" H 1625 3950 50  0001 C CNN
F 3 "~" H 1625 3950 50  0001 C CNN
	1    1625 3950
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J2
U 1 1 5F3300F4
P 9775 3875
F 0 "J2" H 9855 3867 50  0000 L CNN
F 1 "Conn_01x04" H 9855 3776 50  0000 L CNN
F 2 ".Connector:1x4_USB" H 9775 3875 50  0001 C CNN
F 3 "~" H 9775 3875 50  0001 C CNN
	1    9775 3875
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 4825 5750 4825
Connection ~ 5650 4825
Wire Wire Line
	5650 4825 5550 4825
Connection ~ 5750 4825
Wire Wire Line
	5750 4825 5650 4825
$Comp
L power:GND #PWR01
U 1 1 5F331042
P 5550 4825
F 0 "#PWR01" H 5550 4575 50  0001 C CNN
F 1 "GND" H 5555 4652 50  0000 C CNN
F 2 "" H 5550 4825 50  0001 C CNN
F 3 "" H 5550 4825 50  0001 C CNN
	1    5550 4825
	1    0    0    -1  
$EndComp
Connection ~ 5550 4825
Wire Wire Line
	5150 4025 4725 4025
Wire Wire Line
	5150 4125 4725 4125
Text Label 4725 4025 0    50   ~ 0
USBD+
Text Label 4725 4125 0    50   ~ 0
USBD-
$Comp
L .Capacitor:GRM033R61A104ME15D C1
U 1 1 5F332BE7
P 7000 3525
F 0 "C1" H 7092 3571 50  0000 L CNN
F 1 "GRM033R61A104ME15D" H 6610 3695 50  0001 L CNN
F 2 ".Capacitor:C_0201_0603Metric_L" H 7060 3795 50  0001 C CNN
F 3 "http://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM033R61A104ME15-01.pdf" H 7010 3595 50  0001 C CNN
F 4 "0.1uF" H 7092 3480 50  0000 L CNN "Note"
F 5 "0201" H 7110 3345 50  0001 C CNN "Size"
	1    7000 3525
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5F332F89
P 7000 3625
F 0 "#PWR04" H 7000 3375 50  0001 C CNN
F 1 "GND" H 7005 3452 50  0000 C CNN
F 2 "" H 7000 3625 50  0001 C CNN
F 3 "" H 7000 3625 50  0001 C CNN
	1    7000 3625
	1    0    0    -1  
$EndComp
NoConn ~ 5150 4625
NoConn ~ 6150 3525
NoConn ~ 6150 3825
NoConn ~ 5150 3625
$Comp
L power:VBUS #PWR03
U 1 1 5F33422B
P 5750 3025
F 0 "#PWR03" H 5750 2875 50  0001 C CNN
F 1 "VBUS" H 5825 3200 50  0000 C CNN
F 2 "" H 5750 3025 50  0001 C CNN
F 3 "" H 5750 3025 50  0001 C CNN
	1    5750 3025
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 3625 6825 3625
Text Label 6825 3625 2    50   ~ 0
FT-WF-UTX
Text Label 4725 3225 0    50   ~ 0
FT-WF-URX
Wire Wire Line
	4725 3225 5150 3225
Wire Wire Line
	5150 4525 5000 4525
Wire Wire Line
	5000 4525 5000 4825
Wire Wire Line
	5000 4825 5550 4825
NoConn ~ 5150 4225
Text Notes 1250 3725 0    50   ~ 0
Or add CTS# and RTS#?
Text Notes 1525 3525 0    50   ~ 0
To WF
Text Notes 9650 3575 0    50   ~ 0
To PC
Wire Notes Line
	975  4900 3600 4900
Wire Notes Line
	3600 4900 3600 3050
Wire Notes Line
	3600 3050 975  3050
Wire Notes Line
	975  3050 975  4900
Wire Notes Line
	10750 2825 10750 5025
Wire Notes Line
	10750 5025 8175 5025
Wire Notes Line
	8175 5025 8175 2825
Wire Notes Line
	8175 2825 10750 2825
NoConn ~ 5150 3425
NoConn ~ 6150 3725
NoConn ~ 5150 3525
NoConn ~ 5150 3325
Wire Wire Line
	9575 3775 9100 3775
Wire Wire Line
	9575 3875 9100 3875
Wire Wire Line
	9575 3975 9100 3975
Wire Wire Line
	9575 4075 9100 4075
$Comp
L power:VBUS #PWR012
U 1 1 5F44B8B8
P 9100 3775
F 0 "#PWR012" H 9100 3625 50  0001 C CNN
F 1 "VBUS" H 9115 3948 50  0000 C CNN
F 2 "" H 9100 3775 50  0001 C CNN
F 3 "" H 9100 3775 50  0001 C CNN
	1    9100 3775
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR013
U 1 1 5F44BC86
P 9100 4075
F 0 "#PWR013" H 9100 3825 50  0001 C CNN
F 1 "GND" H 9105 3902 50  0000 C CNN
F 2 "" H 9100 4075 50  0001 C CNN
F 3 "" H 9100 4075 50  0001 C CNN
	1    9100 4075
	1    0    0    -1  
$EndComp
Text Label 9100 3875 0    50   ~ 0
USBD+
Text Label 9100 3975 0    50   ~ 0
USBD-
Wire Wire Line
	1825 3850 2475 3850
Wire Wire Line
	1825 4050 2475 4050
Wire Wire Line
	1825 3950 2475 3950
Wire Wire Line
	1825 4150 2475 4150
$Comp
L power:GND #PWR05
U 1 1 5F44D228
P 2475 4150
F 0 "#PWR05" H 2475 3900 50  0001 C CNN
F 1 "GND" H 2480 3977 50  0000 C CNN
F 2 "" H 2475 4150 50  0001 C CNN
F 3 "" H 2475 4150 50  0001 C CNN
	1    2475 4150
	1    0    0    -1  
$EndComp
$Comp
L power:VBUS #PWR02
U 1 1 5F44D505
P 2475 3850
F 0 "#PWR02" H 2475 3700 50  0001 C CNN
F 1 "VBUS" H 2490 4023 50  0000 C CNN
F 2 "" H 2475 3850 50  0001 C CNN
F 3 "" H 2475 3850 50  0001 C CNN
	1    2475 3850
	1    0    0    -1  
$EndComp
Text Label 2475 4050 2    50   ~ 0
FT-WF-UTX
Text Label 2475 3950 2    50   ~ 0
FT-WF-URX
$Comp
L .Regulator_Linear:TPS79718DCKR U2
U 1 1 5F467060
P 5650 5875
F 0 "U2" H 5650 6462 60  0000 C CNN
F 1 "TPS79718DCKR" H 5650 6356 60  0000 C CNN
F 2 ".Package_SOT:DCK5" H 5650 6315 60  0001 C CNN
F 3 "https://www.ti.com/lit/ds/symlink/tps797.pdf?HQS=TI-null-null-digikeymode-df-pf-null-wwe&ts=1598436675520" H 5650 6356 60  0001 C CNN
	1    5650 5875
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR09
U 1 1 5F467FBE
P 7000 3425
F 0 "#PWR09" H 7000 3275 50  0001 C CNN
F 1 "+3V3" H 7015 3598 50  0000 C CNN
F 2 "" H 7000 3425 50  0001 C CNN
F 3 "" H 7000 3425 50  0001 C CNN
	1    7000 3425
	1    0    0    -1  
$EndComp
Connection ~ 7000 3425
$Comp
L power:+3V3 #PWR06
U 1 1 5F468175
P 4850 5675
F 0 "#PWR06" H 4850 5525 50  0001 C CNN
F 1 "+3V3" H 4865 5848 50  0000 C CNN
F 2 "" H 4850 5675 50  0001 C CNN
F 3 "" H 4850 5675 50  0001 C CNN
	1    4850 5675
	1    0    0    -1  
$EndComp
NoConn ~ 4850 6075
Wire Wire Line
	6450 5675 7200 5675
$Comp
L power:+1V8 #PWR010
U 1 1 5F468C0C
P 7200 5675
F 0 "#PWR010" H 7200 5525 50  0001 C CNN
F 1 "+1V8" H 7215 5848 50  0000 C CNN
F 2 "" H 7200 5675 50  0001 C CNN
F 3 "" H 7200 5675 50  0001 C CNN
	1    7200 5675
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5F468E5B
P 6450 6075
F 0 "#PWR08" H 6450 5825 50  0001 C CNN
F 1 "GND" H 6455 5902 50  0000 C CNN
F 2 "" H 6450 6075 50  0001 C CNN
F 3 "" H 6450 6075 50  0001 C CNN
	1    6450 6075
	1    0    0    -1  
$EndComp
$Comp
L power:+1V8 #PWR07
U 1 1 5F469621
P 5650 3025
F 0 "#PWR07" H 5650 2875 50  0001 C CNN
F 1 "+1V8" H 5575 3200 50  0000 C CNN
F 2 "" H 5650 3025 50  0001 C CNN
F 3 "" H 5650 3025 50  0001 C CNN
	1    5650 3025
	1    0    0    -1  
$EndComp
$Comp
L .Capacitor:CC0201MRX5R4BB474 C2
U 1 1 5F46BA7F
P 7200 5775
F 0 "C2" H 7292 5821 50  0000 L CNN
F 1 "CC0201MRX5R4BB474" H 6810 5945 50  0001 L CNN
F 2 ".Capacitor:C_0201_0603Metric_L" H 7260 6045 50  0001 C CNN
F 3 "https://www.yageo.com/upload/media/product/productsearch/datasheet/mlcc/UPY-GPHC_X5R_4V-to-50V_26.pdf" H 7210 5845 50  0001 C CNN
F 4 "0.47uF" H 7292 5730 50  0000 L CNN "Note"
F 5 "0201" H 7310 5595 50  0001 C CNN "Size"
	1    7200 5775
	1    0    0    -1  
$EndComp
Connection ~ 7200 5675
$Comp
L power:GND #PWR011
U 1 1 5F46C490
P 7200 5875
F 0 "#PWR011" H 7200 5625 50  0001 C CNN
F 1 "GND" H 7205 5702 50  0000 C CNN
F 2 "" H 7200 5875 50  0001 C CNN
F 3 "" H 7200 5875 50  0001 C CNN
	1    7200 5875
	1    0    0    -1  
$EndComp
NoConn ~ 4850 5875
NoConn ~ 5150 4425
NoConn ~ 5150 4325
NoConn ~ 5150 3925
$Comp
L power:VBUS #PWR014
U 1 1 5F4702A2
P 9275 2150
F 0 "#PWR014" H 9275 2000 50  0001 C CNN
F 1 "VBUS" H 9290 2323 50  0000 C CNN
F 2 "" H 9275 2150 50  0001 C CNN
F 3 "" H 9275 2150 50  0001 C CNN
	1    9275 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9275 2150 9550 2150
Wire Wire Line
	9275 2150 9000 2150
Connection ~ 9275 2150
Wire Wire Line
	9100 3775 8825 3775
Connection ~ 9100 3775
$Comp
L .Capacitor:GRM033R71A103KA01D C3
U 1 1 5F4732EF
P 8825 3925
F 0 "C3" H 8917 3971 50  0000 L CNN
F 1 "GRM033R71A103KA01D" H 8435 4095 50  0001 L CNN
F 2 ".Capacitor:C_0201_0603Metric_L" H 8935 4195 50  0001 C CNN
F 3 "http://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM033R71A103KA01-01.pdf" H 8835 3995 50  0001 C CNN
F 4 "10nF" H 8917 3880 50  0000 L CNN "Note"
F 5 "0201" H 8935 3745 50  0001 C CNN "Size"
	1    8825 3925
	1    0    0    -1  
$EndComp
Wire Wire Line
	8825 3825 8825 3775
Wire Wire Line
	8825 4025 8825 4075
Wire Wire Line
	8825 4075 9100 4075
Connection ~ 9100 4075
$Comp
L .Capacitor:GRM033R61A104ME15D C4
U 1 1 5F476B66
P 9000 2250
F 0 "C4" H 9092 2296 50  0000 L CNN
F 1 "GRM033R61A104ME15D" H 8610 2420 50  0001 L CNN
F 2 ".Capacitor:C_0201_0603Metric_L" H 9060 2520 50  0001 C CNN
F 3 "http://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM033R61A104ME15-01.pdf" H 9010 2320 50  0001 C CNN
F 4 "0.1uF" H 9092 2205 50  0000 L CNN "Note"
F 5 "0201" H 9110 2070 50  0001 C CNN "Size"
	1    9000 2250
	1    0    0    -1  
$EndComp
$Comp
L .Capacitor:GRM033R71A103KA01D C5
U 1 1 5F47735A
P 9550 2250
F 0 "C5" H 9642 2296 50  0000 L CNN
F 1 "GRM033R71A103KA01D" H 9160 2420 50  0001 L CNN
F 2 ".Capacitor:C_0201_0603Metric_L" H 9660 2520 50  0001 C CNN
F 3 "http://search.murata.co.jp/Ceramy/image/img/A01X/G101/ENG/GRM033R71A103KA01-01.pdf" H 9560 2320 50  0001 C CNN
F 4 "10nF" H 9642 2205 50  0000 L CNN "Note"
F 5 "0201" H 9660 2070 50  0001 C CNN "Size"
	1    9550 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9000 2350 9275 2350
$Comp
L power:GND #PWR015
U 1 1 5F477B5A
P 9275 2350
F 0 "#PWR015" H 9275 2100 50  0001 C CNN
F 1 "GND" H 9280 2177 50  0000 C CNN
F 2 "" H 9275 2350 50  0001 C CNN
F 3 "" H 9275 2350 50  0001 C CNN
	1    9275 2350
	1    0    0    -1  
$EndComp
Connection ~ 9275 2350
Wire Wire Line
	9275 2350 9550 2350
Text Notes 5875 3000 0    50   ~ 0
Ferrite Bead?
Wire Wire Line
	5150 3725 4725 3725
$Comp
L .LED:LTST-C190CKT D?
U 1 1 5F663AD2
P 4575 3725
F 0 "D?" H 4575 4015 50  0000 C CNN
F 1 "LTST-C190CKT" H 4575 3924 50  0000 C CNN
F 2 ".LED:LED_SC80X160X65L40L" H 4555 3550 50  0001 C CNN
F 3 "https://media.digikey.com/pdf/Data%20Sheets/Lite-On%20PDFs/LTST-C190CKT.pdf" H 4575 3725 50  0001 C CNN
	1    4575 3725
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4425 3725 4150 3725
Wire Wire Line
	4150 3725 4150 3575
$Comp
L power:+1V8 #PWR?
U 1 1 5F665C86
P 4150 3575
F 0 "#PWR?" H 4150 3425 50  0001 C CNN
F 1 "+1V8" H 4165 3748 50  0000 C CNN
F 2 "" H 4150 3575 50  0001 C CNN
F 3 "" H 4150 3575 50  0001 C CNN
	1    4150 3575
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 3825 4725 3825
$Comp
L .LED:TLMY1000-GS08 D?
U 1 1 5F666A14
P 4575 3825
F 0 "D?" H 4575 4000 50  0000 C CNN
F 1 "TLMY1000-GS08" H 4550 3925 50  0000 C CNN
F 2 ".LED:LED_SC80X160X65L40L" H 4580 3630 50  0001 C CNN
F 3 "https://www.vishay.com/docs/83172/tlmo1000.pdf" H 4575 3825 50  0001 C CNN
	1    4575 3825
	-1   0    0    1   
$EndComp
Wire Wire Line
	4425 3825 4150 3825
Wire Wire Line
	4150 3825 4150 3725
Connection ~ 4150 3725
$EndSCHEMATC
