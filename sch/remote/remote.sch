EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "IR remote USB stick"
Date "2022-01-23"
Rev ""
Comp ""
Comment1 ""
Comment2 "Mikhail Belkin (dltech174@gmail.com, +7-960-961-54-27)"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:Crystal Y1
U 1 1 60BB7B29
P 4200 2850
F 0 "Y1" H 4250 3000 50  0000 C CNN
F 1 "8M" H 4150 3000 50  0000 C CNN
F 2 "Crystal:Crystal_SMD_5032-2Pin_5.0x3.2mm" H 4200 2850 50  0001 C CNN
F 3 "" H 4200 2850 50  0001 C CNN
	1    4200 2850
	0    1    1    0   
$EndComp
$Comp
L Device:C C1
U 1 1 60BBCAE9
P 3900 2700
F 0 "C1" H 3900 2800 50  0000 L CNN
F 1 "22p" H 3900 2600 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 3938 2550 50  0001 C CNN
F 3 "" H 3900 2700 50  0001 C CNN
	1    3900 2700
	0    1    1    0   
$EndComp
$Comp
L Device:C C2
U 1 1 60BBD52B
P 3900 3000
F 0 "C2" H 3900 3100 50  0000 L CNN
F 1 "22p" H 3900 2900 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 3938 2850 50  0001 C CNN
F 3 "" H 3900 3000 50  0001 C CNN
	1    3900 3000
	0    1    1    0   
$EndComp
Wire Wire Line
	4450 2800 4400 2800
Wire Wire Line
	4400 2800 4400 2700
Wire Wire Line
	4400 2700 4200 2700
Wire Wire Line
	4450 2900 4400 2900
Wire Wire Line
	4400 2900 4400 3000
Wire Wire Line
	4400 3000 4200 3000
Wire Wire Line
	4200 2700 4050 2700
Connection ~ 4200 2700
Wire Wire Line
	4200 3000 4050 3000
Connection ~ 4200 3000
$Comp
L power:GND #PWR0103
U 1 1 60BC5327
P 3650 3050
F 0 "#PWR0103" H 3650 2800 50  0001 C CNN
F 1 "GND" H 3655 2877 50  0000 C CNN
F 2 "" H 3650 3050 50  0001 C CNN
F 3 "" H 3650 3050 50  0001 C CNN
	1    3650 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 3000 3650 3050
Wire Wire Line
	3650 3000 3750 3000
Wire Wire Line
	3650 2700 3750 2700
Wire Wire Line
	3650 2700 3650 3000
Connection ~ 3650 3000
$Comp
L Device:C C5
U 1 1 60BCC99C
P 8350 3750
F 0 "C5" H 8350 3850 50  0000 L CNN
F 1 "0.1uF" H 8350 3650 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 8388 3600 50  0001 C CNN
F 3 "" H 8350 3750 50  0001 C CNN
	1    8350 3750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 60BCEBAF
P 8350 3950
F 0 "#PWR0104" H 8350 3700 50  0001 C CNN
F 1 "GND" H 8350 3800 50  0000 C CNN
F 2 "" H 8350 3950 50  0001 C CNN
F 3 "" H 8350 3950 50  0001 C CNN
	1    8350 3950
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0105
U 1 1 60BCF857
P 8350 3550
F 0 "#PWR0105" H 8350 3400 50  0001 C CNN
F 1 "+3.3V" H 8350 3700 50  0000 C CNN
F 2 "" H 8350 3550 50  0001 C CNN
F 3 "" H 8350 3550 50  0001 C CNN
	1    8350 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 60BD3987
P 8600 3750
F 0 "C6" H 8600 3850 50  0000 L CNN
F 1 "0.1uF" H 8600 3650 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 8638 3600 50  0001 C CNN
F 3 "" H 8600 3750 50  0001 C CNN
	1    8600 3750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 60BD398D
P 8600 3950
F 0 "#PWR0106" H 8600 3700 50  0001 C CNN
F 1 "GND" H 8600 3800 50  0000 C CNN
F 2 "" H 8600 3950 50  0001 C CNN
F 3 "" H 8600 3950 50  0001 C CNN
	1    8600 3950
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0107
U 1 1 60BD3993
P 8600 3550
F 0 "#PWR0107" H 8600 3400 50  0001 C CNN
F 1 "+3.3V" H 8600 3700 50  0000 C CNN
F 2 "" H 8600 3550 50  0001 C CNN
F 3 "" H 8600 3550 50  0001 C CNN
	1    8600 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 60BD4708
P 8850 3750
F 0 "C7" H 8850 3850 50  0000 L CNN
F 1 "0.1uF" H 8850 3650 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 8888 3600 50  0001 C CNN
F 3 "" H 8850 3750 50  0001 C CNN
	1    8850 3750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 60BD470E
P 8850 3950
F 0 "#PWR0108" H 8850 3700 50  0001 C CNN
F 1 "GND" H 8850 3800 50  0000 C CNN
F 2 "" H 8850 3950 50  0001 C CNN
F 3 "" H 8850 3950 50  0001 C CNN
	1    8850 3950
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0109
U 1 1 60BD4714
P 8850 3550
F 0 "#PWR0109" H 8850 3400 50  0001 C CNN
F 1 "+3.3V" H 8850 3700 50  0000 C CNN
F 2 "" H 8850 3550 50  0001 C CNN
F 3 "" H 8850 3550 50  0001 C CNN
	1    8850 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C9
U 1 1 60BD5497
P 9100 3750
F 0 "C9" H 9100 3850 50  0000 L CNN
F 1 "0.1uF" H 9100 3650 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 9138 3600 50  0001 C CNN
F 3 "" H 9100 3750 50  0001 C CNN
	1    9100 3750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 60BD549D
P 9100 3950
F 0 "#PWR0110" H 9100 3700 50  0001 C CNN
F 1 "GND" H 9100 3800 50  0000 C CNN
F 2 "" H 9100 3950 50  0001 C CNN
F 3 "" H 9100 3950 50  0001 C CNN
	1    9100 3950
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0111
U 1 1 60BD54A3
P 9100 3550
F 0 "#PWR0111" H 9100 3400 50  0001 C CNN
F 1 "+3.3V" H 9100 3700 50  0000 C CNN
F 2 "" H 9100 3550 50  0001 C CNN
F 3 "" H 9100 3550 50  0001 C CNN
	1    9100 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 3600 9100 3550
Wire Wire Line
	9100 3900 9100 3950
Wire Wire Line
	8850 3900 8850 3950
Wire Wire Line
	8600 3900 8600 3950
Wire Wire Line
	8350 3900 8350 3950
Wire Wire Line
	8350 3600 8350 3550
Wire Wire Line
	8600 3550 8600 3600
Wire Wire Line
	8850 3550 8850 3600
$Comp
L power:+3.3V #PWR0112
U 1 1 60BE41C5
P 5100 1700
F 0 "#PWR0112" H 5100 1550 50  0001 C CNN
F 1 "+3.3V" H 5050 1850 50  0000 C CNN
F 2 "" H 5100 1700 50  0001 C CNN
F 3 "" H 5100 1700 50  0001 C CNN
	1    5100 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 1800 4800 1750
Wire Wire Line
	4800 1750 4900 1750
Wire Wire Line
	5100 1750 5100 1800
Wire Wire Line
	4900 1800 4900 1750
Connection ~ 4900 1750
Wire Wire Line
	4900 1750 5000 1750
Wire Wire Line
	5000 1800 5000 1750
Connection ~ 5000 1750
Wire Wire Line
	5000 1750 5100 1750
Wire Wire Line
	5100 1750 5100 1700
Connection ~ 5100 1750
$Comp
L power:GND #PWR0113
U 1 1 60BE8B74
P 5100 5500
F 0 "#PWR0113" H 5100 5250 50  0001 C CNN
F 1 "GND" H 5100 5350 50  0000 C CNN
F 2 "" H 5100 5500 50  0001 C CNN
F 3 "" H 5100 5500 50  0001 C CNN
	1    5100 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 5400 4800 5450
Wire Wire Line
	4800 5450 4900 5450
Wire Wire Line
	5100 5450 5100 5500
Wire Wire Line
	5100 5400 5100 5450
Connection ~ 5100 5450
Wire Wire Line
	5000 5400 5000 5450
Connection ~ 5000 5450
Wire Wire Line
	5000 5450 5100 5450
Wire Wire Line
	4900 5400 4900 5450
Connection ~ 4900 5450
Wire Wire Line
	4900 5450 5000 5450
$Comp
L power:GND #PWR0114
U 1 1 60BFBFA2
P 7500 3350
F 0 "#PWR0114" H 7500 3100 50  0001 C CNN
F 1 "GND" H 7500 3200 50  0000 C CNN
F 2 "" H 7500 3350 50  0001 C CNN
F 3 "" H 7500 3350 50  0001 C CNN
	1    7500 3350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 60C02E98
P 4000 2400
F 0 "#PWR0115" H 4000 2150 50  0001 C CNN
F 1 "GND" V 4005 2272 50  0000 R CNN
F 2 "" H 4000 2400 50  0001 C CNN
F 3 "" H 4000 2400 50  0001 C CNN
	1    4000 2400
	0    1    1    0   
$EndComp
$Comp
L Device:C C3
U 1 1 60C06DEC
P 4200 2200
F 0 "C3" H 4200 2300 50  0000 L CNN
F 1 "0.1uF" H 4200 2100 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 4238 2050 50  0001 C CNN
F 3 "" H 4200 2200 50  0001 C CNN
	1    4200 2200
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0116
U 1 1 60C0A725
P 4000 2200
F 0 "#PWR0116" H 4000 1950 50  0001 C CNN
F 1 "GND" V 4005 2072 50  0000 R CNN
F 2 "" H 4000 2200 50  0001 C CNN
F 3 "" H 4000 2200 50  0001 C CNN
	1    4000 2200
	0    1    1    0   
$EndComp
Wire Wire Line
	4050 2200 4000 2200
Wire Wire Line
	4350 2200 4450 2200
Wire Wire Line
	4000 2400 4450 2400
$Comp
L power:+3.3V #PWR0117
U 1 1 60C17286
P 4400 2550
F 0 "#PWR0117" H 4400 2400 50  0001 C CNN
F 1 "+3.3V" H 4250 2600 50  0000 C CNN
F 2 "" H 4400 2550 50  0001 C CNN
F 3 "" H 4400 2550 50  0001 C CNN
	1    4400 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 2600 4400 2600
Wire Wire Line
	4400 2600 4400 2550
NoConn ~ 4450 4500
NoConn ~ 4450 4600
NoConn ~ 4450 4700
NoConn ~ 4450 4800
NoConn ~ 5550 4400
NoConn ~ 5550 4300
Text Label 5600 4700 0    50   ~ 0
DP
Entry Wire Line
	5800 4600 5900 4700
Entry Wire Line
	5800 4700 5900 4800
Wire Wire Line
	5550 4600 5800 4600
Wire Wire Line
	5550 4700 5800 4700
Entry Bus Bus
	4100 5650 4200 5750
Entry Bus Bus
	5900 5650 6000 5750
Text Label 5600 4600 0    50   ~ 0
DM
Text Label 6400 4450 0    50   ~ 0
IR
$Comp
L power:GND #PWR0118
U 1 1 60CB8790
P 7050 4700
F 0 "#PWR0118" H 7050 4450 50  0001 C CNN
F 1 "GND" H 7050 4550 50  0000 C CNN
F 2 "" H 7050 4700 50  0001 C CNN
F 3 "" H 7050 4700 50  0001 C CNN
	1    7050 4700
	1    0    0    -1  
$EndComp
Entry Wire Line
	6300 3050 6400 2950
Entry Wire Line
	6300 4550 6400 4450
Connection ~ 8300 2550
Wire Wire Line
	8300 2550 8300 2500
$Comp
L power:+3.3V #PWR0119
U 1 1 60BDEA7C
P 8300 2500
F 0 "#PWR0119" H 8300 2350 50  0001 C CNN
F 1 "+3.3V" H 8250 2650 50  0000 C CNN
F 2 "" H 8300 2500 50  0001 C CNN
F 3 "" H 8300 2500 50  0001 C CNN
	1    8300 2500
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0120
U 1 1 60BDCB44
P 9750 2500
F 0 "#PWR0120" H 9750 2350 50  0001 C CNN
F 1 "+5V" H 9800 2650 50  0000 C CNN
F 2 "" H 9750 2500 50  0001 C CNN
F 3 "" H 9750 2500 50  0001 C CNN
	1    9750 2500
	1    0    0    -1  
$EndComp
Connection ~ 9250 2900
Wire Wire Line
	9250 2950 9250 2900
Connection ~ 9000 2900
Wire Wire Line
	9000 2900 9250 2900
Wire Wire Line
	9250 2900 9250 2850
Connection ~ 8650 2900
Wire Wire Line
	9000 2900 9000 2850
Wire Wire Line
	8650 2900 9000 2900
Wire Wire Line
	8650 2900 8650 2850
Wire Wire Line
	8300 2900 8650 2900
Wire Wire Line
	8300 2850 8300 2900
$Comp
L power:GND #PWR0121
U 1 1 60BA3E87
P 9250 2950
F 0 "#PWR0121" H 9250 2700 50  0001 C CNN
F 1 "GND" H 9255 2777 50  0000 C CNN
F 2 "" H 9250 2950 50  0001 C CNN
F 3 "" H 9250 2950 50  0001 C CNN
	1    9250 2950
	1    0    0    -1  
$EndComp
Connection ~ 9000 2550
Wire Wire Line
	9000 2550 9250 2550
Wire Wire Line
	8950 2550 9000 2550
Wire Wire Line
	8350 2550 8300 2550
$Comp
L Device:C C8
U 1 1 60B9D265
P 9000 2700
F 0 "C8" H 9000 2800 50  0000 L CNN
F 1 "0.1uF" H 9000 2600 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 9038 2550 50  0001 C CNN
F 3 "" H 9000 2700 50  0001 C CNN
	1    9000 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C10
U 1 1 60B9CD1A
P 9250 2700
F 0 "C10" H 9250 2800 50  0000 L CNN
F 1 "10uF" H 9250 2600 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 9288 2550 50  0001 C CNN
F 3 "" H 9250 2700 50  0001 C CNN
	1    9250 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 60B9CA4E
P 8300 2700
F 0 "C4" H 8300 2800 50  0000 L CNN
F 1 "10uF" H 8300 2600 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 8338 2550 50  0001 C CNN
F 3 "" H 8300 2700 50  0001 C CNN
	1    8300 2700
	1    0    0    -1  
$EndComp
Entry Bus Bus
	6300 5650 6400 5750
$Comp
L Connector_Generic:Conn_01x03 J1
U 1 1 60BDE5E6
P 7300 3700
F 0 "J1" H 7380 3742 50  0000 L CNN
F 1 "swd" H 7380 3651 50  0000 L CNN
F 2 "local:3WIRE_PADS" H 7300 3700 50  0001 C CNN
F 3 "~" H 7300 3700 50  0001 C CNN
	1    7300 3700
	1    0    0    -1  
$EndComp
Text Label 6400 3600 0    50   ~ 0
SWCLK
Text Label 6400 3800 0    50   ~ 0
SWDIO
Entry Wire Line
	6300 3700 6400 3600
Entry Wire Line
	6300 3900 6400 3800
$Comp
L power:GND #PWR0122
U 1 1 60BEBAA9
P 7050 3850
F 0 "#PWR0122" H 7050 3600 50  0001 C CNN
F 1 "GND" H 7050 3700 50  0000 C CNN
F 2 "" H 7050 3850 50  0001 C CNN
F 3 "" H 7050 3850 50  0001 C CNN
	1    7050 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 3850 7050 3700
Wire Wire Line
	7050 3700 7100 3700
Text Label 5550 4900 0    50   ~ 0
SWCLK
Text Label 5550 4800 0    50   ~ 0
SWDIO
Entry Wire Line
	5800 4800 5900 4900
Entry Wire Line
	5800 4900 5900 5000
Wire Wire Line
	5550 4900 5800 4900
Wire Wire Line
	5800 4800 5550 4800
$Comp
L Device:R R4
U 1 1 60BAA748
P 9550 2550
F 0 "R4" V 9450 2500 50  0000 L CNN
F 1 "10" V 9550 2500 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 9480 2550 50  0001 C CNN
F 3 "" H 9550 2550 50  0001 C CNN
	1    9550 2550
	0    1    1    0   
$EndComp
Wire Wire Line
	9250 2550 9400 2550
Connection ~ 9250 2550
Wire Wire Line
	9750 2550 9750 2500
Wire Wire Line
	9700 2550 9750 2550
Wire Wire Line
	6400 3800 7100 3800
Wire Wire Line
	6400 3600 7100 3600
Wire Wire Line
	6400 4450 7100 4450
NoConn ~ 5550 3600
Entry Wire Line
	6300 2950 6400 2850
NoConn ~ 4450 3800
NoConn ~ 4450 3900
NoConn ~ 4450 4000
NoConn ~ 4450 4100
Entry Wire Line
	4100 4500 4200 4400
Entry Wire Line
	5800 3700 5900 3800
NoConn ~ 4450 3100
NoConn ~ 4450 3200
NoConn ~ 4450 3300
$Comp
L power:GND #PWR0123
U 1 1 60D66AD7
P 4450 5500
F 0 "#PWR0123" H 4450 5250 50  0001 C CNN
F 1 "GND" H 4450 5350 50  0000 C CNN
F 2 "" H 4450 5500 50  0001 C CNN
F 3 "" H 4450 5500 50  0001 C CNN
	1    4450 5500
	1    0    0    -1  
$EndComp
NoConn ~ 4450 4900
$Comp
L local:XC6206-33 U2
U 1 1 61038F36
P 8650 2550
F 0 "U2" H 8650 2792 50  0000 C CNN
F 1 "XC6206-33" H 8650 2701 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 8650 2550 50  0001 C CNN
F 3 "" H 8750 2300 50  0001 C CNN
	1    8650 2550
	1    0    0    -1  
$EndComp
$Comp
L Interface_Optical:TSOP17xx U3
U 1 1 61EC21C1
P 7500 4450
F 0 "U3" H 7750 4750 50  0000 C CNN
F 1 "TSOP17xx" H 7300 4750 50  0000 C CNN
F 2 "OptoDevice:Vishay_CAST-3Pin" H 7450 4075 50  0001 C CNN
F 3 "http://www.micropik.com/PDF/tsop17xx.pdf" H 8150 4750 50  0001 C CNN
	1    7500 4450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7400 3250 7400 3300
Wire Wire Line
	7400 3300 7500 3300
Wire Wire Line
	7500 3300 7500 3350
Wire Wire Line
	7500 3300 7500 3250
Connection ~ 7500 3300
Wire Wire Line
	7050 4700 7050 4650
Wire Wire Line
	7050 4650 7100 4650
$Comp
L power:+3.3V #PWR0124
U 1 1 61F0D446
P 7050 4200
F 0 "#PWR0124" H 7050 4050 50  0001 C CNN
F 1 "+3.3V" H 6900 4300 50  0000 C CNN
F 2 "" H 7050 4200 50  0001 C CNN
F 3 "" H 7050 4200 50  0001 C CNN
	1    7050 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 4200 7050 4250
Wire Wire Line
	7050 4250 7100 4250
$Comp
L Device:C C11
U 1 1 61EC7AE6
P 9350 3750
F 0 "C11" H 9350 3850 50  0000 L CNN
F 1 "10uF" H 9350 3650 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 9388 3600 50  0001 C CNN
F 3 "" H 9350 3750 50  0001 C CNN
	1    9350 3750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0125
U 1 1 61ECBB49
P 9350 3950
F 0 "#PWR0125" H 9350 3700 50  0001 C CNN
F 1 "GND" H 9350 3800 50  0000 C CNN
F 2 "" H 9350 3950 50  0001 C CNN
F 3 "" H 9350 3950 50  0001 C CNN
	1    9350 3950
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0126
U 1 1 61ECC1C7
P 9350 3550
F 0 "#PWR0126" H 9350 3400 50  0001 C CNN
F 1 "+3.3V" H 9350 3700 50  0000 C CNN
F 2 "" H 9350 3550 50  0001 C CNN
F 3 "" H 9350 3550 50  0001 C CNN
	1    9350 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9350 3600 9350 3550
Wire Wire Line
	9350 3950 9350 3900
$Comp
L Connector_Generic:Conn_01x03 J2
U 1 1 61ED3CCD
P 7300 5100
F 0 "J2" H 7380 5142 50  0000 L CNN
F 1 "power_sw" H 7380 5051 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Horizontal" H 7300 5100 50  0001 C CNN
F 3 "~" H 7300 5100 50  0001 C CNN
	1    7300 5100
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:DTD114E Q1
U 1 1 61ED5A25
P 6800 5450
F 0 "Q1" H 6600 5600 50  0000 L CNN
F 1 "DTD114E" H 6500 5250 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 6800 5450 50  0001 L CNN
F 3 "" H 6800 5450 50  0001 L CNN
	1    6800 5450
	1    0    0    -1  
$EndComp
$Comp
L Connector:USB_A J3
U 1 1 61ECB861
P 7400 2850
F 0 "J3" H 7170 2839 50  0000 R CNN
F 1 "USB_A" H 7170 2748 50  0000 R CNN
F 2 "Connector_USB:USB_A_CNCTech_1001-011-01101_Horizontal" H 7550 2800 50  0001 C CNN
F 3 " ~" H 7550 2800 50  0001 C CNN
	1    7400 2850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7100 2650 7050 2650
Wire Wire Line
	6950 2500 6950 2400
$Comp
L power:+3.3V #PWR0102
U 1 1 6105D4FC
P 6950 2400
F 0 "#PWR0102" H 6950 2250 50  0001 C CNN
F 1 "+3.3V" H 6900 2550 50  0000 C CNN
F 2 "" H 6950 2400 50  0001 C CNN
F 3 "" H 6950 2400 50  0001 C CNN
	1    6950 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 2400 7050 2650
Wire Wire Line
	6950 2850 7100 2850
Connection ~ 6950 2850
Wire Wire Line
	6950 2800 6950 2850
Wire Wire Line
	6850 2950 7100 2950
Wire Wire Line
	6850 2850 6950 2850
Wire Wire Line
	6400 2950 6550 2950
Wire Wire Line
	6400 2850 6550 2850
$Comp
L Device:R R1
U 1 1 60BAF3EA
P 6700 2850
F 0 "R1" V 6600 2800 50  0000 L CNN
F 1 "50" V 6700 2800 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 6630 2850 50  0001 C CNN
F 3 "" H 6700 2850 50  0001 C CNN
	1    6700 2850
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 60BAF8CE
P 6700 2950
F 0 "R2" V 6800 2900 50  0000 L CNN
F 1 "50" V 6700 2900 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 6630 2950 50  0001 C CNN
F 3 "" H 6700 2950 50  0001 C CNN
	1    6700 2950
	0    1    1    0   
$EndComp
Text Label 6400 2850 0    50   ~ 0
DP
Text Label 6400 2950 0    50   ~ 0
DM
$Comp
L power:+5V #PWR0101
U 1 1 60BA6D79
P 7050 2400
F 0 "#PWR0101" H 7050 2250 50  0001 C CNN
F 1 "+5V" H 7100 2550 50  0000 C CNN
F 2 "" H 7050 2400 50  0001 C CNN
F 3 "" H 7050 2400 50  0001 C CNN
	1    7050 2400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 60B98022
P 6950 2650
F 0 "R3" H 6800 2700 50  0000 L CNN
F 1 "4.7k" V 6950 2550 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 6880 2650 50  0001 C CNN
F 3 "" H 6950 2650 50  0001 C CNN
	1    6950 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 5200 6900 5200
Wire Wire Line
	6900 5250 6900 5200
$Comp
L power:+5V #PWR0127
U 1 1 61F0A331
P 6700 4950
F 0 "#PWR0127" H 6700 4800 50  0001 C CNN
F 1 "+5V" H 6750 5100 50  0000 C CNN
F 2 "" H 6700 4950 50  0001 C CNN
F 3 "" H 6700 4950 50  0001 C CNN
	1    6700 4950
	1    0    0    -1  
$EndComp
$Comp
L Device:D_Schottky D1
U 1 1 61F0C630
P 6900 5000
F 0 "D1" H 7000 5050 50  0000 C CNN
F 1 "1N5822" H 6850 4900 50  0000 C CNN
F 2 "Diode_SMD:D_SMA" H 6900 5000 50  0001 C CNN
F 3 "~" H 6900 5000 50  0001 C CNN
	1    6900 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 5000 7050 5000
Wire Wire Line
	6750 5000 6700 5000
Wire Wire Line
	6700 5000 6700 4950
Wire Wire Line
	6900 5650 6900 5700
Wire Wire Line
	6900 5700 7050 5700
Wire Wire Line
	7050 5700 7050 5100
Wire Wire Line
	7050 5100 7100 5100
$Comp
L power:GND #PWR0128
U 1 1 61F213A3
P 7050 5750
F 0 "#PWR0128" H 7050 5500 50  0001 C CNN
F 1 "GND" H 7050 5600 50  0000 C CNN
F 2 "" H 7050 5750 50  0001 C CNN
F 3 "" H 7050 5750 50  0001 C CNN
	1    7050 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 5750 7050 5700
Connection ~ 7050 5700
Entry Wire Line
	6300 5550 6400 5450
Wire Wire Line
	6400 5450 6550 5450
Text Label 5600 3500 0    50   ~ 0
IR
Text Label 5600 4500 0    50   ~ 0
DP
NoConn ~ 4450 5000
Text Label 4250 4400 0    50   ~ 0
PWR
Wire Wire Line
	5550 3700 5800 3700
NoConn ~ 5550 3800
NoConn ~ 4450 3700
Text Label 6400 5450 0    50   ~ 0
PWR
Text Label 4200 4300 0    50   ~ 0
SWDIO
Wire Wire Line
	4450 4300 4200 4300
$Comp
L local:STM32F103C8Tx_usb U1
U 1 1 60B9067D
P 5000 3600
F 0 "U1" H 5400 5350 50  0000 C CNN
F 1 "STM32F103C8Tx_usb" V 5400 4850 50  0000 C CNN
F 2 "Package_QFP:LQFP-48_7x7mm_P0.5mm" V 4975 4600 50  0001 R TNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00161566.pdf" H 5100 3600 50  0001 C CNN
	1    5000 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 4400 4450 4400
Wire Wire Line
	5550 3500 5800 3500
Text Label 5600 3700 0    50   ~ 0
GND
Text Label 4200 5450 0    50   ~ 0
GND
Wire Wire Line
	4200 5450 4450 5450
Wire Wire Line
	4450 5450 4450 5500
NoConn ~ 4450 3600
NoConn ~ 4450 3500
NoConn ~ 4450 4200
NoConn ~ 5550 5000
NoConn ~ 5550 4200
NoConn ~ 5550 4100
NoConn ~ 5550 4000
NoConn ~ 5550 3900
Entry Wire Line
	4100 5350 4200 5450
Entry Wire Line
	5800 3500 5900 3600
Entry Wire Line
	4100 4400 4200 4300
Entry Wire Line
	5800 4500 5900 4600
Wire Wire Line
	5550 4500 5800 4500
Wire Bus Line
	4150 5750 6450 5750
Wire Bus Line
	4100 4350 4100 5700
Wire Bus Line
	6300 2900 6300 5700
Wire Bus Line
	5900 3550 5900 5700
$EndSCHEMATC
