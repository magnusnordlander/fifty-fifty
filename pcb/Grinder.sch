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
Connection ~ 10150 3150
Text GLabel 10150 1150 1    50   Output ~ 0
3V3
Text GLabel 9950 1150 1    50   Input ~ 0
5V
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
NoConn ~ 9550 2150
NoConn ~ 9550 2250
NoConn ~ 9550 2350
NoConn ~ 9550 2450
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
5V
Wire Wire Line
	9600 4950 9600 5050
Wire Wire Line
	9600 5050 9850 5050
Text GLabel 9850 5150 0    50   Input ~ 0
5V
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
F 1 "R" V 7534 2400 50  0000 C CNN
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
L Device:R R3
U 1 1 6042A9BF
P 7350 3250
F 0 "R3" H 7420 3296 50  0000 L CNN
F 1 "100R" H 7420 3205 50  0000 L CNN
F 2 "" V 7280 3250 50  0001 C CNN
F 3 "~" H 7350 3250 50  0001 C CNN
	1    7350 3250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 6042B426
P 7650 3250
F 0 "R4" H 7720 3296 50  0000 L CNN
F 1 "100R" H 7720 3205 50  0000 L CNN
F 2 "" V 7580 3250 50  0001 C CNN
F 3 "~" H 7650 3250 50  0001 C CNN
	1    7650 3250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 6042BDDB
P 7500 3750
F 0 "C1" V 7248 3750 50  0000 C CNN
F 1 "10nF" V 7339 3750 50  0000 C CNN
F 2 "" H 7538 3600 50  0001 C CNN
F 3 "~" H 7500 3750 50  0001 C CNN
	1    7500 3750
	0    1    1    0   
$EndComp
Wire Wire Line
	7350 3400 7350 3750
Wire Wire Line
	7650 3400 7650 3750
Text GLabel 7350 3100 1    50   Input ~ 0
5V
Wire Wire Line
	7650 2950 7650 3100
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
Text GLabel 7350 4000 3    50   Output ~ 0
5V_FILTERED
Wire Wire Line
	9600 4950 9450 4950
Wire Wire Line
	7350 3750 7350 4000
Connection ~ 7350 3750
Wire Wire Line
	7650 3750 7650 4000
Connection ~ 7650 3750
$Comp
L power:GNDA #PWR0108
U 1 1 604366AD
P 7650 4000
F 0 "#PWR0108" H 7650 3750 50  0001 C CNN
F 1 "GNDA" H 7655 3827 50  0000 C CNN
F 2 "" H 7650 4000 50  0001 C CNN
F 3 "" H 7650 4000 50  0001 C CNN
	1    7650 4000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 604376A5
P 7900 2950
F 0 "#PWR0109" H 7900 2700 50  0001 C CNN
F 1 "GND" H 7905 2777 50  0000 C CNN
F 2 "" H 7900 2950 50  0001 C CNN
F 3 "" H 7900 2950 50  0001 C CNN
	1    7900 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 2950 7900 2950
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
Wire Notes Line
	6300 4700 11200 4700
Wire Notes Line
	6300 500  6300 4700
$Comp
L Analog_ADC:ADS1232IPW U1
U 1 1 6043B349
P 4550 2550
F 0 "U1" H 4550 3831 50  0000 C CNN
F 1 "ADS1232IPW" H 4550 3740 50  0000 C CNN
F 2 "" H 4550 2550 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/ads1232.pdf" H 4550 2550 50  0001 C CNN
	1    4550 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 6043EB21
P 4900 3750
F 0 "#PWR0111" H 4900 3500 50  0001 C CNN
F 1 "GND" H 4905 3577 50  0000 C CNN
F 2 "" H 4900 3750 50  0001 C CNN
F 3 "" H 4900 3750 50  0001 C CNN
	1    4900 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 3650 4550 3750
Wire Wire Line
	4650 3650 4650 3750
Connection ~ 4650 3750
Wire Wire Line
	4750 3650 4750 3750
Wire Wire Line
	4650 3750 4750 3750
Connection ~ 4750 3750
Wire Wire Line
	4750 3750 4900 3750
Text GLabel 5250 2050 2    50   Output ~ 0
ADC_DOUT
Text GLabel 5250 2150 2    50   Input ~ 0
ADC_CLK
Text GLabel 5250 2250 2    50   Input ~ 0
ADC_PDWN
Text GLabel 5250 3150 2    50   Input ~ 0
ADC_SPEED
$Comp
L power:GND #PWR0112
U 1 1 604420F6
P 5350 3450
F 0 "#PWR0112" H 5350 3200 50  0001 C CNN
F 1 "GND" H 5355 3277 50  0000 C CNN
F 2 "" H 5350 3450 50  0001 C CNN
F 3 "" H 5350 3450 50  0001 C CNN
	1    5350 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 3350 5350 3350
Wire Wire Line
	5250 3250 5350 3250
Wire Wire Line
	5350 3250 5350 3350
Connection ~ 5350 3350
Wire Wire Line
	5350 3350 5350 3450
$Comp
L power:GND #PWR0113
U 1 1 60443630
P 5350 2750
F 0 "#PWR0113" H 5350 2500 50  0001 C CNN
F 1 "GND" H 5355 2577 50  0000 C CNN
F 2 "" H 5350 2750 50  0001 C CNN
F 3 "" H 5350 2750 50  0001 C CNN
	1    5350 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 2750 5350 2750
NoConn ~ 5250 2550
Text GLabel 5450 1300 2    50   Input ~ 0
3V3
Wire Wire Line
	5250 1850 5300 1850
Wire Wire Line
	5300 1850 5300 1750
Wire Wire Line
	5300 1300 5450 1300
Wire Wire Line
	5250 1750 5300 1750
Connection ~ 5300 1750
Wire Wire Line
	4750 1450 5300 1450
Wire Wire Line
	5300 1300 5300 1450
Connection ~ 5300 1450
Wire Wire Line
	5300 1450 5300 1750
NoConn ~ 3850 2850
NoConn ~ 3850 2950
Wire Wire Line
	4350 3650 4350 3750
Wire Wire Line
	4350 3750 4550 3750
Connection ~ 4550 3750
Wire Wire Line
	4550 3750 4650 3750
$Comp
L power:GNDA #PWR0114
U 1 1 6044AEA7
P 3850 3350
F 0 "#PWR0114" H 3850 3100 50  0001 C CNN
F 1 "GNDA" H 3855 3177 50  0000 C CNN
F 2 "" H 3850 3350 50  0001 C CNN
F 3 "" H 3850 3350 50  0001 C CNN
	1    3850 3350
	1    0    0    -1  
$EndComp
Text GLabel 3850 1750 0    50   Input ~ 0
5V_FILTERED
$Comp
L Connector_Generic:Conn_01x04 J3
U 1 1 6044BD7F
P 900 2400
F 0 "J3" H 818 2717 50  0000 C CNN
F 1 "Conn_01x04" H 818 2626 50  0000 C CNN
F 2 "" H 900 2400 50  0001 C CNN
F 3 "~" H 900 2400 50  0001 C CNN
	1    900  2400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3100 2750 3250 2750
Wire Wire Line
	3100 2450 3250 2450
$Comp
L Device:R R6
U 1 1 604560C7
P 2950 2750
F 0 "R6" V 2743 2750 50  0000 C CNN
F 1 "100R" V 2834 2750 50  0000 C CNN
F 2 "" V 2880 2750 50  0001 C CNN
F 3 "~" H 2950 2750 50  0001 C CNN
	1    2950 2750
	0    1    1    0   
$EndComp
$Comp
L Device:R R5
U 1 1 60454B18
P 2950 2450
F 0 "R5" V 2743 2450 50  0000 C CNN
F 1 "100R" V 2834 2450 50  0000 C CNN
F 2 "" V 2880 2450 50  0001 C CNN
F 3 "~" H 2950 2450 50  0001 C CNN
	1    2950 2450
	0    1    1    0   
$EndComp
$Comp
L Device:C C2
U 1 1 60453F67
P 3250 2600
F 0 "C2" H 3365 2646 50  0000 L CNN
F 1 "10 nF" H 3365 2555 50  0000 L CNN
F 2 "" H 3288 2450 50  0001 C CNN
F 3 "~" H 3250 2600 50  0001 C CNN
	1    3250 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 2750 3850 2750
Wire Wire Line
	3850 2750 3850 2650
Connection ~ 3250 2750
Wire Wire Line
	3250 2450 3850 2450
Wire Wire Line
	3850 2450 3850 2550
Connection ~ 3250 2450
$Comp
L Device:C C3
U 1 1 60463801
P 3400 2100
F 0 "C3" H 3515 2146 50  0000 L CNN
F 1 "100 nF" H 3515 2055 50  0000 L CNN
F 2 "" H 3438 1950 50  0001 C CNN
F 3 "~" H 3400 2100 50  0001 C CNN
	1    3400 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 1950 3850 1950
Wire Wire Line
	3850 1950 3850 2050
Wire Wire Line
	3400 2250 3850 2250
Wire Wire Line
	3850 2250 3850 2150
Wire Wire Line
	2800 2450 2750 2450
Wire Wire Line
	2750 2450 2750 2500
Wire Wire Line
	2750 2500 1100 2500
Wire Wire Line
	2800 2750 2750 2750
Wire Wire Line
	2750 2750 2750 2600
Wire Wire Line
	2750 2600 1100 2600
Text GLabel 4350 950  1    50   Input ~ 0
5V
$Comp
L power:GND #PWR0115
U 1 1 6046C41B
P 4750 1000
F 0 "#PWR0115" H 4750 750 50  0001 C CNN
F 1 "GND" H 4755 827 50  0000 C CNN
F 2 "" H 4750 1000 50  0001 C CNN
F 3 "" H 4750 1000 50  0001 C CNN
	1    4750 1000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 6046CE82
P 4500 1000
F 0 "C4" V 4248 1000 50  0000 C CNN
F 1 "100nF" V 4339 1000 50  0000 C CNN
F 2 "" H 4538 850 50  0001 C CNN
F 3 "~" H 4500 1000 50  0001 C CNN
	1    4500 1000
	0    1    1    0   
$EndComp
Wire Wire Line
	4750 1000 4650 1000
Wire Wire Line
	4350 950  4350 1000
Wire Wire Line
	4350 1000 4350 1450
Connection ~ 4350 1000
Wire Wire Line
	4350 1450 1500 1450
Wire Wire Line
	1500 1450 1500 2300
Wire Wire Line
	1500 2300 1100 2300
Connection ~ 4350 1450
$Comp
L power:GND #PWR0116
U 1 1 604777B8
P 1850 2250
F 0 "#PWR0116" H 1850 2000 50  0001 C CNN
F 1 "GND" H 1855 2077 50  0000 C CNN
F 2 "" H 1850 2250 50  0001 C CNN
F 3 "" H 1850 2250 50  0001 C CNN
	1    1850 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 2400 1600 2400
Wire Wire Line
	1600 2400 1600 2150
Wire Wire Line
	1600 2150 1850 2150
Wire Wire Line
	1850 2150 1850 2250
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
$EndSCHEMATC
