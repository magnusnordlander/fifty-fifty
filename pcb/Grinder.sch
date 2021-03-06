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
Wire Wire Line
	10150 3150 10150 3250
Wire Wire Line
	10050 3150 10150 3150
Text GLabel 10150 1150 1    50   Output ~ 0
3V3
Text GLabel 9950 1150 1    50   Input ~ 0
VIN
Text GLabel 9550 1550 0    50   Input ~ 0
UEXT_RX
Text GLabel 9550 1650 0    50   Output ~ 0
UEXT_TX
Text GLabel 9550 1750 0    50   Output ~ 0
ENC_CLK
Text GLabel 9550 1850 0    50   Input ~ 0
ENC_DT
Text GLabel 9550 1950 0    50   Input ~ 0
ENC_SW
Text GLabel 9550 2550 0    50   Output ~ 0
UEXT_SSEL
Text GLabel 9550 2650 0    50   Output ~ 0
UEXT_MOSI
Text GLabel 9550 2750 0    50   Input ~ 0
UEXT_MISO
Text GLabel 9550 2850 0    50   Output ~ 0
UEXT_SCK
Text GLabel 10550 2150 2    50   Input ~ 0
MANUAL_SW
Text GLabel 10550 2250 2    50   Input ~ 0
ADC_DOUT
Text GLabel 10550 2350 2    50   Output ~ 0
ADC_CLK
Text GLabel 10550 2450 2    50   Output ~ 0
ADC_PDWN
Text GLabel 10550 2550 2    50   BiDi ~ 0
UEXT_SDA
Text GLabel 10550 2650 2    50   Output ~ 0
UEXT_SCL
Text GLabel 10550 2750 2    50   Output ~ 0
ADC_SPEED
Text GLabel 10550 2850 2    50   Output ~ 0
SSR_GATE
Wire Notes Line
	8850 3600 11200 3600
NoConn ~ 10550 1950
NoConn ~ 10550 1650
NoConn ~ 10550 1550
NoConn ~ 9550 2050
$Comp
L Connector_Generic:Conn_02x05_Odd_Even J4
U 1 1 60407D1C
P 10000 4250
F 0 "J4" H 10050 4667 50  0000 C CNN
F 1 "Conn_02x05_Odd_Even" H 10050 4576 50  0000 C CNN
F 2 "" H 10000 4250 50  0001 C CNN
F 3 "~" H 10000 4250 50  0001 C CNN
	1    10000 4250
	1    0    0    -1  
$EndComp
Text GLabel 9800 4050 0    50   Input ~ 0
3V3
Text GLabel 9800 4150 0    50   Input ~ 0
UEXT_TX
Text GLabel 9800 4250 0    50   Input ~ 0
UEXT_SCL
Text GLabel 9800 4350 0    50   Output ~ 0
UEXT_MISO
Text GLabel 9800 4450 0    50   Input ~ 0
UEXT_SCK
Text GLabel 10300 4150 2    50   Output ~ 0
UEXT_RX
Text GLabel 10300 4250 2    50   BiDi ~ 0
UEXT_SDA
Text GLabel 10300 4350 2    50   Input ~ 0
UEXT_MOSI
Text GLabel 10300 4450 2    50   Input ~ 0
UEXT_SSEL
Wire Wire Line
	10300 4050 10500 4050
Wire Wire Line
	10500 4050 10500 3750
Wire Wire Line
	10500 3750 10650 3750
$Comp
L Connector_Generic:Conn_01x06 J1
U 1 1 6040DD45
P 10050 5150
F 0 "J1" H 10130 5142 50  0000 L CNN
F 1 "Conn_01x06" H 10130 5051 50  0000 L CNN
F 2 "" H 10050 5150 50  0001 C CNN
F 3 "~" H 10050 5150 50  0001 C CNN
	1    10050 5150
	1    0    0    -1  
$EndComp
Text GLabel 9850 4950 0    50   Output ~ 0
VIN
Wire Wire Line
	9600 4950 9600 5050
Wire Wire Line
	9600 5050 9850 5050
Text GLabel 9850 5150 0    50   Input ~ 0
VIN
Text GLabel 9850 5250 0    50   Input ~ 0
SSR_DRAIN
Text GLabel 9850 5350 0    50   Output ~ 0
MANUAL_SW
Wire Wire Line
	9450 5450 9850 5450
Wire Notes Line
	8850 5750 11200 5750
Text GLabel 6900 1600 0    50   Input ~ 0
SSR_GATE
Wire Wire Line
	6900 1600 7200 1600
Wire Wire Line
	7200 1600 7200 1250
$Comp
L power:GND #PWR0101
U 1 1 60416649
P 7500 1450
F 0 "#PWR0101" H 7500 1200 50  0001 C CNN
F 1 "GND" H 7505 1277 50  0000 C CNN
F 2 "" H 7500 1450 50  0001 C CNN
F 3 "" H 7500 1450 50  0001 C CNN
	1    7500 1450
	1    0    0    -1  
$EndComp
Text GLabel 7500 1050 1    50   Output ~ 0
SSR_DRAIN
$Comp
L Device:LED D1
U 1 1 6041A767
P 7800 2000
F 0 "D1" H 7793 1745 50  0000 C CNN
F 1 "LED" H 7793 1836 50  0000 C CNN
F 2 "" H 7800 2000 50  0001 C CNN
F 3 "~" H 7800 2000 50  0001 C CNN
	1    7800 2000
	-1   0    0    1   
$EndComp
Wire Wire Line
	7200 1600 7200 2000
Wire Wire Line
	7200 2000 7350 2000
Connection ~ 7200 1600
$Comp
L Device:R R1
U 1 1 6041C2A2
P 7500 2000
F 0 "R1" V 7293 2000 50  0000 C CNN
F 1 "R" V 7384 2000 50  0000 C CNN
F 2 "" V 7430 2000 50  0001 C CNN
F 3 "~" H 7500 2000 50  0001 C CNN
	1    7500 2000
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 6041E26D
P 7650 2400
F 0 "R2" V 7443 2400 50  0000 C CNN
F 1 "100R" V 7534 2400 50  0000 C CNN
F 2 "" V 7580 2400 50  0001 C CNN
F 3 "~" H 7650 2400 50  0001 C CNN
	1    7650 2400
	0    1    1    0   
$EndComp
Wire Wire Line
	7200 2000 7200 2400
Wire Wire Line
	7200 2400 7500 2400
Connection ~ 7200 2000
Wire Wire Line
	7800 2400 8100 2400
Wire Notes Line
	6300 2700 8850 2700
$Comp
L Connector_Generic:Conn_01x05 J2
U 1 1 60424C4F
P 10050 6100
F 0 "J2" H 10130 6142 50  0000 L CNN
F 1 "Conn_01x05" H 10130 6051 50  0000 L CNN
F 2 "" H 10050 6100 50  0001 C CNN
F 3 "~" H 10050 6100 50  0001 C CNN
	1    10050 6100
	1    0    0    -1  
$EndComp
Text GLabel 9850 5900 0    50   Input ~ 0
ENC_CLK
Text GLabel 9850 6000 0    50   Output ~ 0
ENC_DT
Text GLabel 9850 6100 0    50   Output ~ 0
ENC_SW
Text GLabel 9850 6200 0    50   Input ~ 0
3V3
Wire Notes Line
	8850 500  8850 6500
$Comp
L power:GND #PWR0102
U 1 1 6041F150
P 8100 2400
F 0 "#PWR0102" H 8100 2150 50  0001 C CNN
F 1 "GND" H 8105 2227 50  0000 C CNN
F 2 "" H 8100 2400 50  0001 C CNN
F 3 "" H 8100 2400 50  0001 C CNN
	1    8100 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7950 2000 8100 2000
$Comp
L power:GND #PWR0103
U 1 1 6041D72B
P 8100 2000
F 0 "#PWR0103" H 8100 1750 50  0001 C CNN
F 1 "GND" H 8105 1827 50  0000 C CNN
F 2 "" H 8100 2000 50  0001 C CNN
F 3 "" H 8100 2000 50  0001 C CNN
	1    8100 2000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 604278BA
P 9850 6300
F 0 "#PWR0104" H 9850 6050 50  0001 C CNN
F 1 "GND" H 9855 6127 50  0000 C CNN
F 2 "" H 9850 6300 50  0001 C CNN
F 3 "" H 9850 6300 50  0001 C CNN
	1    9850 6300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 604107CC
P 10700 3250
F 0 "#PWR0105" H 10700 3000 50  0001 C CNN
F 1 "GND" H 10705 3077 50  0000 C CNN
F 2 "" H 10700 3250 50  0001 C CNN
F 3 "" H 10700 3250 50  0001 C CNN
	1    10700 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	10150 3250 10700 3250
$Comp
L power:GND #PWR0106
U 1 1 60410F49
P 10650 3750
F 0 "#PWR0106" H 10650 3500 50  0001 C CNN
F 1 "GND" H 10655 3577 50  0000 C CNN
F 2 "" H 10650 3750 50  0001 C CNN
F 3 "" H 10650 3750 50  0001 C CNN
	1    10650 3750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 60412307
P 9450 5450
F 0 "#PWR0107" H 9450 5200 50  0001 C CNN
F 1 "GND" H 9455 5277 50  0000 C CNN
F 2 "" H 9450 5450 50  0001 C CNN
F 3 "" H 9450 5450 50  0001 C CNN
	1    9450 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 4950 9450 4950
$Comp
L power:GND #PWR0110
U 1 1 60438670
P 9450 4950
F 0 "#PWR0110" H 9450 4700 50  0001 C CNN
F 1 "GND" H 9455 4777 50  0000 C CNN
F 2 "" H 9450 4950 50  0001 C CNN
F 3 "" H 9450 4950 50  0001 C CNN
	1    9450 4950
	1    0    0    -1  
$EndComp
$Comp
L Analog_ADC:ADS1232IPW U1
U 1 1 6043B349
P 4550 2900
F 0 "U1" H 4550 4181 50  0000 C CNN
F 1 "ADS1232IPW" H 4550 4090 50  0000 C CNN
F 2 "" H 4550 2900 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/ads1232.pdf" H 4550 2900 50  0001 C CNN
	1    4550 2900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 6043EB21
P 4900 4100
F 0 "#PWR0111" H 4900 3850 50  0001 C CNN
F 1 "GND" H 4905 3927 50  0000 C CNN
F 2 "" H 4900 4100 50  0001 C CNN
F 3 "" H 4900 4100 50  0001 C CNN
	1    4900 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 4000 4550 4100
Wire Wire Line
	4650 4000 4650 4100
Connection ~ 4650 4100
Wire Wire Line
	4750 4000 4750 4100
Wire Wire Line
	4650 4100 4750 4100
Connection ~ 4750 4100
Wire Wire Line
	4750 4100 4900 4100
Text GLabel 5250 2400 2    50   Output ~ 0
ADC_DOUT
Text GLabel 5250 2500 2    50   Input ~ 0
ADC_CLK
Text GLabel 5250 2600 2    50   Input ~ 0
ADC_PDWN
Text GLabel 5250 3500 2    50   Input ~ 0
ADC_SPEED
$Comp
L power:GND #PWR0113
U 1 1 60443630
P 5350 3100
F 0 "#PWR0113" H 5350 2850 50  0001 C CNN
F 1 "GND" H 5355 2927 50  0000 C CNN
F 2 "" H 5350 3100 50  0001 C CNN
F 3 "" H 5350 3100 50  0001 C CNN
	1    5350 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 3100 5350 3100
NoConn ~ 5250 2900
Text GLabel 4900 1400 1    50   Input ~ 0
3V3
Wire Wire Line
	4750 1800 4900 1800
Wire Wire Line
	4550 4100 4650 4100
Text GLabel 3850 2100 0    50   Input ~ 0
REFP
$Comp
L Connector_Generic:Conn_01x04 J3
U 1 1 6044BD7F
P 950 5800
F 0 "J3" H 868 6117 50  0000 C CNN
F 1 "Conn_01x04" H 868 6026 50  0000 C CNN
F 2 "" H 950 5800 50  0001 C CNN
F 3 "~" H 950 5800 50  0001 C CNN
	1    950  5800
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1900 6450 2050 6450
Wire Wire Line
	1900 6150 2050 6150
$Comp
L Device:R R6
U 1 1 604560C7
P 1750 6450
F 0 "R6" V 1543 6450 50  0000 C CNN
F 1 "100R" V 1634 6450 50  0000 C CNN
F 2 "" V 1680 6450 50  0001 C CNN
F 3 "~" H 1750 6450 50  0001 C CNN
	1    1750 6450
	0    1    1    0   
$EndComp
$Comp
L Device:R R5
U 1 1 60454B18
P 1750 6150
F 0 "R5" V 1543 6150 50  0000 C CNN
F 1 "100R" V 1634 6150 50  0000 C CNN
F 2 "" V 1680 6150 50  0001 C CNN
F 3 "~" H 1750 6150 50  0001 C CNN
	1    1750 6150
	0    1    1    0   
$EndComp
$Comp
L Device:C C2
U 1 1 60453F67
P 2050 6300
F 0 "C2" H 2165 6346 50  0000 L CNN
F 1 "10 nF" H 2165 6255 50  0000 L CNN
F 2 "" H 2088 6150 50  0001 C CNN
F 3 "~" H 2050 6300 50  0001 C CNN
	1    2050 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 6450 2650 6450
Connection ~ 2050 6450
Wire Wire Line
	2050 6150 2650 6150
Connection ~ 2050 6150
$Comp
L Device:C C3
U 1 1 60463801
P 3400 2450
F 0 "C3" H 3515 2496 50  0000 L CNN
F 1 "100 nF" H 3515 2405 50  0000 L CNN
F 2 "" H 3438 2300 50  0001 C CNN
F 3 "~" H 3400 2450 50  0001 C CNN
	1    3400 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 2300 3850 2300
Wire Wire Line
	3850 2300 3850 2400
Wire Wire Line
	3400 2600 3850 2600
Wire Wire Line
	3850 2600 3850 2500
Text GLabel 4350 1300 1    50   Input ~ 0
AVDD
$Comp
L Device:C C4
U 1 1 6046CE82
P 4500 1350
F 0 "C4" V 4248 1350 50  0000 C CNN
F 1 "100nF" V 4339 1350 50  0000 C CNN
F 2 "" H 4538 1200 50  0001 C CNN
F 3 "~" H 4500 1350 50  0001 C CNN
	1    4500 1350
	0    1    1    0   
$EndComp
Wire Wire Line
	4350 1300 4350 1350
Wire Wire Line
	4350 1350 4350 1800
Connection ~ 4350 1350
Wire Wire Line
	1550 5700 1150 5700
$Comp
L power:GND #PWR0116
U 1 1 604777B8
P 1650 5800
F 0 "#PWR0116" H 1650 5550 50  0001 C CNN
F 1 "GND" H 1655 5627 50  0000 C CNN
F 2 "" H 1650 5800 50  0001 C CNN
F 3 "" H 1650 5800 50  0001 C CNN
	1    1650 5800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1150 5800 1650 5800
NoConn ~ 10250 1150
$Comp
L Transistor_FET:2N7002 Q1
U 1 1 604B955D
P 7400 1250
F 0 "Q1" H 7604 1296 50  0000 L CNN
F 1 "2N7002" H 7604 1205 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 7600 1175 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/NDS7002A-D.PDF" H 7400 1250 50  0001 L CNN
	1    7400 1250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 6042B4D0
P 5300 1550
F 0 "#PWR0108" H 5300 1300 50  0001 C CNN
F 1 "GND" H 5305 1377 50  0000 C CNN
F 2 "" H 5300 1550 50  0001 C CNN
F 3 "" H 5300 1550 50  0001 C CNN
	1    5300 1550
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C5
U 1 1 6042CAF6
P 5150 1550
F 0 "C5" H 5265 1596 50  0000 L CNN
F 1 "100 nF" H 5265 1505 50  0000 L CNN
F 2 "" H 5188 1400 50  0001 C CNN
F 3 "~" H 5150 1550 50  0001 C CNN
	1    5150 1550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4900 1800 4900 1550
Wire Wire Line
	5000 1550 4900 1550
Connection ~ 4900 1550
Wire Wire Line
	4900 1550 4900 1400
$Comp
L power:GND #PWR0109
U 1 1 6043FD04
P 4150 6400
F 0 "#PWR0109" H 4150 6150 50  0001 C CNN
F 1 "GND" H 4155 6227 50  0000 C CNN
F 2 "" H 4150 6400 50  0001 C CNN
F 3 "" H 4150 6400 50  0001 C CNN
	1    4150 6400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 6044E4EE
P 4350 4000
F 0 "#PWR0112" H 4350 3750 50  0001 C CNN
F 1 "GND" H 4355 3827 50  0000 C CNN
F 2 "" H 4350 4000 50  0001 C CNN
F 3 "" H 4350 4000 50  0001 C CNN
	1    4350 4000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 6044EC52
P 4650 1350
F 0 "#PWR0114" H 4650 1100 50  0001 C CNN
F 1 "GND" H 4655 1177 50  0000 C CNN
F 2 "" H 4650 1350 50  0001 C CNN
F 3 "" H 4650 1350 50  0001 C CNN
	1    4650 1350
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:XC6206PxxxMR U2
U 1 1 6044F57F
P 7550 3950
F 0 "U2" H 7550 4192 50  0000 C CNN
F 1 "XC6206P502MR" H 7550 4101 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 7550 4175 50  0001 C CIN
F 3 "https://www.torexsemi.com/file/xc6206/XC6206.pdf" H 7550 3950 50  0001 C CNN
	1    7550 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 604536EF
P 7050 4100
F 0 "C6" H 7165 4146 50  0000 L CNN
F 1 "100 nF" H 7165 4055 50  0000 L CNN
F 2 "" H 7088 3950 50  0001 C CNN
F 3 "~" H 7050 4100 50  0001 C CNN
	1    7050 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 3950 7250 3950
$Comp
L power:GND #PWR0115
U 1 1 604540E3
P 7050 4250
F 0 "#PWR0115" H 7050 4000 50  0001 C CNN
F 1 "GND" H 7055 4077 50  0000 C CNN
F 2 "" H 7050 4250 50  0001 C CNN
F 3 "" H 7050 4250 50  0001 C CNN
	1    7050 4250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0117
U 1 1 60454817
P 7550 4250
F 0 "#PWR0117" H 7550 4000 50  0001 C CNN
F 1 "GND" H 7555 4077 50  0000 C CNN
F 2 "" H 7550 4250 50  0001 C CNN
F 3 "" H 7550 4250 50  0001 C CNN
	1    7550 4250
	1    0    0    -1  
$EndComp
Text GLabel 8350 3450 2    50   Output ~ 0
AVDD
Wire Wire Line
	7850 3950 8000 3950
$Comp
L Device:C C7
U 1 1 604574C2
P 8000 4100
F 0 "C7" H 8115 4146 50  0000 L CNN
F 1 "100 nF" H 8115 4055 50  0000 L CNN
F 2 "" H 8038 3950 50  0001 C CNN
F 3 "~" H 8000 4100 50  0001 C CNN
	1    8000 4100
	1    0    0    -1  
$EndComp
Connection ~ 8000 3950
Wire Wire Line
	8000 3950 8200 3950
$Comp
L power:GND #PWR0118
U 1 1 60458043
P 8000 4250
F 0 "#PWR0118" H 8000 4000 50  0001 C CNN
F 1 "GND" H 8005 4077 50  0000 C CNN
F 2 "" H 8000 4250 50  0001 C CNN
F 3 "" H 8000 4250 50  0001 C CNN
	1    8000 4250
	1    0    0    -1  
$EndComp
Text GLabel 3850 3700 0    50   Input ~ 0
REFN
Wire Notes Line
	500  4700 11200 4700
Wire Wire Line
	7500 5950 7650 5950
Wire Wire Line
	7500 5650 7650 5650
$Comp
L Device:R R4
U 1 1 6047EC05
P 7350 5950
F 0 "R4" V 7143 5950 50  0000 C CNN
F 1 "100R" V 7234 5950 50  0000 C CNN
F 2 "" V 7280 5950 50  0001 C CNN
F 3 "~" H 7350 5950 50  0001 C CNN
	1    7350 5950
	0    1    1    0   
$EndComp
$Comp
L Device:R R3
U 1 1 6047EC0B
P 7350 5650
F 0 "R3" V 7143 5650 50  0000 C CNN
F 1 "100R" V 7234 5650 50  0000 C CNN
F 2 "" V 7280 5650 50  0001 C CNN
F 3 "~" H 7350 5650 50  0001 C CNN
	1    7350 5650
	0    1    1    0   
$EndComp
$Comp
L Device:C C1
U 1 1 6047EC11
P 7650 5800
F 0 "C1" H 7765 5846 50  0000 L CNN
F 1 "10 nF" H 7765 5755 50  0000 L CNN
F 2 "" H 7688 5650 50  0001 C CNN
F 3 "~" H 7650 5800 50  0001 C CNN
	1    7650 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 5650 7150 5650
Wire Wire Line
	7200 5950 7150 5950
Text GLabel 7150 5650 0    50   Input ~ 0
AVDD
$Comp
L power:GND #PWR0119
U 1 1 604871AA
P 7150 5950
F 0 "#PWR0119" H 7150 5700 50  0001 C CNN
F 1 "GND" H 7155 5777 50  0000 C CNN
F 2 "" H 7150 5950 50  0001 C CNN
F 3 "" H 7150 5950 50  0001 C CNN
	1    7150 5950
	1    0    0    -1  
$EndComp
Text GLabel 8050 5650 2    50   Output ~ 0
REFP
Text GLabel 8050 5950 2    50   Output ~ 0
REFN
Wire Wire Line
	7650 5650 8050 5650
Connection ~ 7650 5650
Wire Wire Line
	7650 5950 8050 5950
Connection ~ 7650 5950
Wire Notes Line
	6300 6550 6950 6550
Wire Notes Line
	6300 500  6300 6550
Text GLabel 6800 3950 0    50   Input ~ 0
VIN
Wire Wire Line
	6800 3950 7050 3950
$Comp
L Jumper:Jumper_3_Open JP1
U 1 1 6043F561
P 8200 3450
F 0 "JP1" V 8246 3537 50  0000 L CNN
F 1 "Debug voltage" V 8155 3537 50  0000 L CNN
F 2 "" H 8200 3450 50  0001 C CNN
F 3 "~" H 8200 3450 50  0001 C CNN
	1    8200 3450
	0    -1   -1   0   
$EndComp
Connection ~ 7050 3950
Text GLabel 8200 3200 1    50   Input ~ 0
3V3
Wire Wire Line
	8200 3950 8200 3700
Text GLabel 5250 2100 2    50   Input ~ 0
ADC_GAIN0
Text GLabel 5250 2200 2    50   Input ~ 0
ADC_GAIN1
Text GLabel 5250 3600 2    50   Input ~ 0
ADC_A0
Text GLabel 5250 3700 2    50   Input ~ 0
ADC_TEMP
$Comp
L Jumper:SolderJumper_2_Bridged JP2
U 1 1 60479FD8
P 4650 6050
F 0 "JP2" H 4650 6255 50  0000 C CNN
F 1 "AINP2" H 4650 6164 50  0000 C CNN
F 2 "" H 4650 6050 50  0001 C CNN
F 3 "~" H 4650 6050 50  0001 C CNN
	1    4650 6050
	1    0    0    -1  
$EndComp
$Comp
L Jumper:SolderJumper_2_Bridged JP3
U 1 1 60483558
P 4650 6400
F 0 "JP3" H 4650 6605 50  0000 C CNN
F 1 "AINN2" H 4650 6514 50  0000 C CNN
F 2 "" H 4650 6400 50  0001 C CNN
F 3 "~" H 4650 6400 50  0001 C CNN
	1    4650 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 6400 4800 6400
Wire Wire Line
	4500 6400 4400 6400
Wire Wire Line
	4500 6050 4400 6050
Wire Wire Line
	4400 6050 4400 6400
Connection ~ 4400 6400
Wire Wire Line
	4400 6400 4150 6400
Connection ~ 10150 3150
$Comp
L MCU_Module:Arduino_Nano_v3.x A1
U 1 1 603FF1E0
P 10050 2150
F 0 "A1" H 10050 1061 50  0000 C CNN
F 1 "Arduino Nano 33 IoT" H 10050 970 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 10050 2150 50  0001 C CIN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 10050 2150 50  0001 C CNN
	1    10050 2150
	1    0    0    -1  
$EndComp
Text GLabel 9550 2250 0    50   Output ~ 0
ADC_A0
Text GLabel 9550 2150 0    50   Output ~ 0
ADC_TEMP
Text GLabel 1550 5700 2    50   Input ~ 0
AVDD
Wire Wire Line
	1600 6150 1600 5900
Wire Wire Line
	1600 5900 1150 5900
Wire Wire Line
	1600 6450 1500 6450
Wire Wire Line
	1500 6450 1500 6000
Wire Wire Line
	1500 6000 1150 6000
Text GLabel 2650 6150 2    50   Output ~ 0
AIN1_P
Text GLabel 2650 6450 2    50   Output ~ 0
AIN1_N
Wire Wire Line
	4800 6050 4900 6050
Text GLabel 4900 6050 2    50   Output ~ 0
AIN2_P
Text GLabel 4900 6400 2    50   Output ~ 0
AIN2_N
Wire Notes Line
	3550 4700 3550 7750
Text GLabel 3850 2900 0    50   Input ~ 0
AIN1_P
Text GLabel 3850 3000 0    50   Input ~ 0
AIN1_N
Text GLabel 3850 3200 0    50   Input ~ 0
AIN2_P
Text GLabel 3850 3300 0    50   Input ~ 0
AIN2_N
Text GLabel 9550 2450 0    50   Output ~ 0
ADC_GAIN1
Text GLabel 9550 2350 0    50   Output ~ 0
ADC_GAIN0
$EndSCHEMATC
