EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "One phone exchange"
Date "2022-04-22"
Rev ""
Comp ""
Comment1 ""
Comment2 "Mikhail Belkin (+79609615427 dltech174@gmail.com)"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_ST_STM32F1:STM32F103C8Tx U3
U 1 1 6262ABE9
P 5550 3950
F 0 "U3" H 6000 5400 50  0000 C CNN
F 1 "STM32F103C8Tx" V 5550 3950 50  0000 C CNN
F 2 "Package_QFP:LQFP-48_7x7mm_P0.5mm" H 4950 2550 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00161566.pdf" H 5550 3950 50  0001 C CNN
	1    5550 3950
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:XC6206PxxxMR U1
U 1 1 6262FD30
P 4600 1150
F 0 "U1" H 4750 900 50  0000 C CNN
F 1 "XC6206P33MR" H 4600 1300 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4600 1375 50  0001 C CIN
F 3 "https://www.torexsemi.com/file/xc6206/XC6206.pdf" H 4600 1150 50  0001 C CNN
	1    4600 1150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 62638A8E
P 7900 1250
F 0 "R9" H 7900 1100 50  0000 L CNN
F 1 "1k" V 7900 1250 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 7830 1250 50  0001 C CNN
F 3 "~" H 7900 1250 50  0001 C CNN
	1    7900 1250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R10
U 1 1 62638E2E
P 7900 1650
F 0 "R10" H 7900 1500 50  0000 L CNN
F 1 "75R" V 7900 1600 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 7830 1650 50  0001 C CNN
F 3 "~" H 7900 1650 50  0001 C CNN
	1    7900 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 1050 7900 1050
Wire Wire Line
	7900 1050 7900 1100
Wire Wire Line
	7850 1450 7900 1450
Wire Wire Line
	7900 1450 7900 1400
Wire Wire Line
	7900 1450 7900 1500
Connection ~ 7900 1450
$Comp
L Device:C C14
U 1 1 6263FF33
P 8050 1300
F 0 "C14" H 8050 1400 50  0000 L CNN
F 1 "10uF" V 8100 1050 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 8088 1150 50  0001 C CNN
F 3 "~" H 8050 1300 50  0001 C CNN
	1    8050 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 1850 7900 1800
Wire Wire Line
	7900 1850 8050 1850
Wire Wire Line
	8050 1850 8050 1450
Wire Wire Line
	8050 1150 8050 1050
Wire Wire Line
	8050 1050 7900 1050
Connection ~ 7900 1050
$Comp
L Amplifier_Operational:LM358 U2
U 1 1 62647ADF
P 7250 2400
F 0 "U2" H 7400 2550 50  0000 C CNN
F 1 "LM358" H 7200 2400 50  0000 C CNN
F 2 "Package_SO:SO-8_3.9x4.9mm_P1.27mm" H 7250 2400 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2904-n.pdf" H 7250 2400 50  0001 C CNN
	1    7250 2400
	-1   0    0    1   
$EndComp
$Comp
L Device:C C1
U 1 1 626621FE
P 4250 1350
F 0 "C1" H 4250 1450 50  0000 L CNN
F 1 "10uF" V 4300 1100 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4288 1200 50  0001 C CNN
F 3 "~" H 4250 1350 50  0001 C CNN
	1    4250 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 1200 4250 1150
Wire Wire Line
	4250 1150 4300 1150
Wire Wire Line
	4250 1500 4250 1600
Wire Wire Line
	4250 1600 4600 1600
Wire Wire Line
	4600 1600 4600 1450
$Comp
L Device:C C5
U 1 1 62663717
P 4950 1350
F 0 "C5" H 4950 1450 50  0000 L CNN
F 1 "10uF" V 5000 1100 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4988 1200 50  0001 C CNN
F 3 "~" H 4950 1350 50  0001 C CNN
	1    4950 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 1150 4950 1150
Wire Wire Line
	4950 1150 4950 1200
Wire Wire Line
	4600 1600 4950 1600
Wire Wire Line
	4950 1600 4950 1500
Connection ~ 4600 1600
$Comp
L power:GND #PWR0102
U 1 1 62668976
P 4250 1650
F 0 "#PWR0102" H 4250 1400 50  0001 C CNN
F 1 "GND" H 4255 1477 50  0000 C CNN
F 2 "" H 4250 1650 50  0001 C CNN
F 3 "" H 4250 1650 50  0001 C CNN
	1    4250 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 1650 4250 1600
Connection ~ 4250 1600
$Comp
L power:+5V #PWR0103
U 1 1 6267F78F
P 4250 1050
F 0 "#PWR0103" H 4250 900 50  0001 C CNN
F 1 "+5V" H 4265 1223 50  0000 C CNN
F 2 "" H 4250 1050 50  0001 C CNN
F 3 "" H 4250 1050 50  0001 C CNN
	1    4250 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 1150 4250 1050
Connection ~ 4250 1150
$Comp
L Transistor_FET:AO3400A Q1
U 1 1 6268E70E
P 7300 3950
F 0 "Q1" H 7400 4100 50  0000 L CNN
F 1 "AO3400A" H 7400 3800 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 7500 3875 50  0001 L CIN
F 3 "http://www.aosmd.com/pdfs/datasheet/AO3400A.pdf" H 7300 3950 50  0001 L CNN
	1    7300 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 2300 7600 2300
$Comp
L Device:R R7
U 1 1 626A5E6A
P 7700 2700
F 0 "R7" H 7700 2550 50  0000 L CNN
F 1 "10k" V 7700 2600 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 7630 2700 50  0001 C CNN
F 3 "~" H 7700 2700 50  0001 C CNN
	1    7700 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 2500 7700 2500
Wire Wire Line
	7700 2500 7700 2450
Wire Wire Line
	7700 2550 7700 2500
Connection ~ 7700 2500
$Comp
L Device:R R3
U 1 1 626B8CA2
P 7400 3500
F 0 "R3" H 7470 3546 50  0000 L CNN
F 1 "82R" V 7400 3400 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 7330 3500 50  0001 C CNN
F 3 "~" H 7400 3500 50  0001 C CNN
	1    7400 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 3750 7400 3700
Connection ~ 7400 3700
Wire Wire Line
	7400 3700 7400 3650
$Comp
L Device:C C13
U 1 1 626C6589
P 7950 3700
F 0 "C13" V 8000 3750 50  0000 L CNN
F 1 "1uF" V 7900 3750 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7988 3550 50  0001 C CNN
F 3 "~" H 7950 3700 50  0001 C CNN
	1    7950 3700
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 626CDABC
P 7700 2900
F 0 "#PWR0105" H 7700 2650 50  0001 C CNN
F 1 "GND" H 7700 2750 50  0000 C CNN
F 2 "" H 7700 2900 50  0001 C CNN
F 3 "" H 7700 2900 50  0001 C CNN
	1    7700 2900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 626CE22C
P 7400 4200
F 0 "#PWR0106" H 7400 3950 50  0001 C CNN
F 1 "GND" H 7400 4050 50  0000 C CNN
F 2 "" H 7400 4200 50  0001 C CNN
F 3 "" H 7400 4200 50  0001 C CNN
	1    7400 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 4200 7400 4150
Wire Wire Line
	7700 2900 7700 2850
$Comp
L power:+24V #PWR0107
U 1 1 626DCA19
P 8050 1000
F 0 "#PWR0107" H 8050 850 50  0001 C CNN
F 1 "+24V" H 8065 1173 50  0000 C CNN
F 2 "" H 8050 1000 50  0001 C CNN
F 3 "" H 8050 1000 50  0001 C CNN
	1    8050 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 1050 8050 1000
Connection ~ 8050 1050
$Comp
L power:+24V #PWR0108
U 1 1 626DE36A
P 7400 3300
F 0 "#PWR0108" H 7400 3150 50  0001 C CNN
F 1 "+24V" H 7400 3450 50  0000 C CNN
F 2 "" H 7400 3300 50  0001 C CNN
F 3 "" H 7400 3300 50  0001 C CNN
	1    7400 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 3350 7400 3300
$Comp
L Connector_Generic:Conn_01x02 J3
U 1 1 62710CB2
P 8450 3700
F 0 "J3" H 8530 3692 50  0000 L CNN
F 1 "LINE" H 8530 3601 50  0000 L CNN
F 2 "Connector_PinHeader_1.27mm:PinHeader_1x02_P1.27mm_Vertical" H 8450 3700 50  0001 C CNN
F 3 "~" H 8450 3700 50  0001 C CNN
	1    8450 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8250 3700 8150 3700
Wire Wire Line
	8150 1050 8050 1050
Wire Wire Line
	8100 3700 8150 3700
Connection ~ 8150 3700
$Comp
L power:GND #PWR0109
U 1 1 6271B51A
P 8200 3850
F 0 "#PWR0109" H 8200 3600 50  0001 C CNN
F 1 "GND" H 8205 3677 50  0000 C CNN
F 2 "" H 8200 3850 50  0001 C CNN
F 3 "" H 8200 3850 50  0001 C CNN
	1    8200 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 3850 8200 3800
Wire Wire Line
	8200 3800 8250 3800
Wire Wire Line
	8150 1050 8150 2100
Wire Wire Line
	6900 2400 6950 2400
Wire Wire Line
	8050 2100 8150 2100
Connection ~ 8150 2100
$Comp
L Device:R R1
U 1 1 62747EDB
P 6700 2400
F 0 "R1" V 6750 2200 50  0000 L CNN
F 1 "75" V 6700 2300 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 6630 2400 50  0001 C CNN
F 3 "~" H 6700 2400 50  0001 C CNN
	1    6700 2400
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 6274D071
P 6900 3950
F 0 "R2" V 6950 3750 50  0000 L CNN
F 1 "75" V 6900 3850 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 6830 3950 50  0001 C CNN
F 3 "~" H 6900 3950 50  0001 C CNN
	1    6900 3950
	0    1    1    0   
$EndComp
Wire Wire Line
	6850 2400 6900 2400
Connection ~ 6900 2400
Wire Wire Line
	7100 3950 7050 3950
$Comp
L Connector:USB_A J2
U 1 1 6277ABAB
P 8300 4850
F 0 "J2" H 8200 5200 50  0000 R CNN
F 1 "USB_A" H 8500 5200 50  0000 R CNN
F 2 "Connector_USB:USB_A_CNCTech_1001-011-01101_Horizontal" H 8450 4800 50  0001 C CNN
F 3 " ~" H 8450 4800 50  0001 C CNN
	1    8300 4850
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 6278047C
P 8400 5350
F 0 "#PWR0110" H 8400 5100 50  0001 C CNN
F 1 "GND" H 8400 5200 50  0000 C CNN
F 2 "" H 8400 5350 50  0001 C CNN
F 3 "" H 8400 5350 50  0001 C CNN
	1    8400 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8300 5250 8300 5300
Wire Wire Line
	8300 5300 8400 5300
Wire Wire Line
	8400 5300 8400 5250
Wire Wire Line
	8400 5300 8400 5350
Connection ~ 8400 5300
$Comp
L power:+5V #PWR0111
U 1 1 62789794
P 7950 4500
F 0 "#PWR0111" H 7950 4350 50  0001 C CNN
F 1 "+5V" H 7950 4650 50  0000 C CNN
F 2 "" H 7950 4500 50  0001 C CNN
F 3 "" H 7950 4500 50  0001 C CNN
	1    7950 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 4650 7950 4650
$Comp
L Device:R R8
U 1 1 6278F715
P 7800 4650
F 0 "R8" H 7800 4500 50  0000 L CNN
F 1 "100k" V 7800 4550 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 7730 4650 50  0001 C CNN
F 3 "~" H 7800 4650 50  0001 C CNN
	1    7800 4650
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0112
U 1 1 62791864
P 7800 4500
F 0 "#PWR0112" H 7800 4350 50  0001 C CNN
F 1 "+3.3V" H 7750 4650 50  0000 C CNN
F 2 "" H 7800 4500 50  0001 C CNN
F 3 "" H 7800 4500 50  0001 C CNN
	1    7800 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 4800 7800 4850
Wire Wire Line
	7800 4850 8000 4850
Wire Wire Line
	7950 4500 7950 4650
$Comp
L Device:R R4
U 1 1 627A0501
P 7600 4850
F 0 "R4" V 7650 4650 50  0000 L CNN
F 1 "75" V 7600 4750 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 7530 4850 50  0001 C CNN
F 3 "~" H 7600 4850 50  0001 C CNN
	1    7600 4850
	0    1    1    0   
$EndComp
$Comp
L Device:R R5
U 1 1 627A1093
P 7600 4950
F 0 "R5" V 7650 4750 50  0000 L CNN
F 1 "75" V 7600 4850 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 7530 4950 50  0001 C CNN
F 3 "~" H 7600 4950 50  0001 C CNN
	1    7600 4950
	0    1    1    0   
$EndComp
Wire Wire Line
	7750 4850 7800 4850
Connection ~ 7800 4850
Wire Wire Line
	7750 4950 8000 4950
$Comp
L power:+3.3V #PWR0113
U 1 1 627E57A2
P 5750 2350
F 0 "#PWR0113" H 5750 2200 50  0001 C CNN
F 1 "+3.3V" H 5765 2523 50  0000 C CNN
F 2 "" H 5750 2350 50  0001 C CNN
F 3 "" H 5750 2350 50  0001 C CNN
	1    5750 2350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 627E8448
P 5350 5550
F 0 "#PWR0114" H 5350 5300 50  0001 C CNN
F 1 "GND" H 5350 5400 50  0000 C CNN
F 2 "" H 5350 5550 50  0001 C CNN
F 3 "" H 5350 5550 50  0001 C CNN
	1    5350 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 5450 5350 5500
Wire Wire Line
	5350 5500 5450 5500
Wire Wire Line
	5350 5500 5350 5550
Wire Wire Line
	5650 5450 5650 5500
Wire Wire Line
	5550 5450 5550 5500
Connection ~ 5550 5500
Wire Wire Line
	5550 5500 5650 5500
Wire Wire Line
	5450 5450 5450 5500
Connection ~ 5450 5500
Wire Wire Line
	5450 5500 5550 5500
Wire Wire Line
	5350 2450 5350 2400
Wire Wire Line
	5350 2400 5450 2400
Wire Wire Line
	5750 2400 5750 2450
Wire Wire Line
	5750 2400 5750 2350
Connection ~ 5750 2400
Wire Wire Line
	5650 2450 5650 2400
Connection ~ 5650 2400
Wire Wire Line
	5650 2400 5750 2400
Wire Wire Line
	5550 2450 5550 2400
Connection ~ 5550 2400
Wire Wire Line
	5550 2400 5650 2400
Wire Wire Line
	5450 2450 5450 2400
Connection ~ 5450 2400
Wire Wire Line
	5450 2400 5550 2400
Connection ~ 5350 5500
Wire Wire Line
	6750 3950 6150 3950
Wire Wire Line
	6150 3750 6350 3750
Wire Wire Line
	6350 3750 6350 2400
Wire Wire Line
	6350 2400 6550 2400
$Comp
L Connector_Generic:Conn_01x03 J1
U 1 1 6283FF1B
P 6800 5150
F 0 "J1" H 6880 5192 50  0000 L CNN
F 1 "SWD" H 6880 5101 50  0000 L CNN
F 2 "local:3WIRE_PADS" H 6800 5150 50  0001 C CNN
F 3 "~" H 6800 5150 50  0001 C CNN
	1    6800 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 5050 6200 5050
Wire Wire Line
	6150 5150 6450 5150
Wire Wire Line
	6450 5150 6450 5250
Wire Wire Line
	6450 5250 6600 5250
$Comp
L power:GND #PWR0115
U 1 1 6284A124
P 6550 5300
F 0 "#PWR0115" H 6550 5050 50  0001 C CNN
F 1 "GND" H 6555 5127 50  0000 C CNN
F 2 "" H 6550 5300 50  0001 C CNN
F 3 "" H 6550 5300 50  0001 C CNN
	1    6550 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 5300 6550 5150
Wire Wire Line
	6550 5150 6600 5150
$Comp
L power:+3.3V #PWR0116
U 1 1 628533CF
P 4950 1050
F 0 "#PWR0116" H 4950 900 50  0001 C CNN
F 1 "+3.3V" H 4900 1200 50  0000 C CNN
F 2 "" H 4950 1050 50  0001 C CNN
F 3 "" H 4950 1050 50  0001 C CNN
	1    4950 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 1150 4950 1050
Connection ~ 4950 1150
NoConn ~ 6150 4050
NoConn ~ 6150 4150
NoConn ~ 6150 4250
NoConn ~ 6150 4350
NoConn ~ 6150 4450
NoConn ~ 6150 4550
NoConn ~ 6150 4750
NoConn ~ 6150 5250
NoConn ~ 4850 5250
NoConn ~ 4850 5150
NoConn ~ 4850 5050
NoConn ~ 4850 4950
NoConn ~ 4850 4850
NoConn ~ 4850 4750
NoConn ~ 4850 4650
NoConn ~ 4850 4550
NoConn ~ 4850 4350
NoConn ~ 4850 4250
NoConn ~ 4850 4150
NoConn ~ 4850 4050
NoConn ~ 4850 3950
NoConn ~ 4850 3850
NoConn ~ 4850 3750
NoConn ~ 4850 3550
NoConn ~ 4850 3450
NoConn ~ 4850 3350
$Comp
L Device:Crystal_Small Y1
U 1 1 628D826B
P 4550 3050
F 0 "Y1" H 4450 3100 50  0000 C CNN
F 1 "8M" H 4700 3100 50  0000 C CNN
F 2 "Crystal:Crystal_SMD_5032-2Pin_5.0x3.2mm" H 4550 3050 50  0001 C CNN
F 3 "~" H 4550 3050 50  0001 C CNN
	1    4550 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 3150 4400 3050
Wire Wire Line
	4400 3050 4450 3050
$Comp
L Device:C C2
U 1 1 628E83F2
P 4500 3350
F 0 "C2" H 4500 3450 50  0000 L CNN
F 1 "20pF" V 4550 3100 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 4538 3200 50  0001 C CNN
F 3 "~" H 4500 3350 50  0001 C CNN
	1    4500 3350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 628E9441
P 4700 3350
F 0 "C4" H 4700 3450 50  0000 L CNN
F 1 "20pF" V 4750 3100 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 4738 3200 50  0001 C CNN
F 3 "~" H 4700 3350 50  0001 C CNN
	1    4700 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 3050 4700 3050
Wire Wire Line
	4700 3200 4700 3050
Connection ~ 4700 3050
Wire Wire Line
	4700 3050 4850 3050
Wire Wire Line
	4400 3150 4500 3150
Wire Wire Line
	4500 3200 4500 3150
Connection ~ 4500 3150
Wire Wire Line
	4500 3150 4850 3150
$Comp
L power:GND #PWR0117
U 1 1 62903D28
P 4500 3650
F 0 "#PWR0117" H 4500 3400 50  0001 C CNN
F 1 "GND" H 4500 3500 50  0000 C CNN
F 2 "" H 4500 3650 50  0001 C CNN
F 3 "" H 4500 3650 50  0001 C CNN
	1    4500 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 3500 4500 3600
Wire Wire Line
	4500 3600 4700 3600
Wire Wire Line
	4700 3600 4700 3500
Connection ~ 4500 3600
Wire Wire Line
	4500 3600 4500 3650
$Comp
L Device:C C3
U 1 1 62913164
P 4650 2650
F 0 "C3" H 4650 2750 50  0000 L CNN
F 1 "0.1uF" V 4700 2400 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 4688 2500 50  0001 C CNN
F 3 "~" H 4650 2650 50  0001 C CNN
	1    4650 2650
	0    1    1    0   
$EndComp
Wire Wire Line
	4800 2650 4850 2650
$Comp
L power:GND #PWR0118
U 1 1 62919C4A
P 4350 2700
F 0 "#PWR0118" H 4350 2450 50  0001 C CNN
F 1 "GND" H 4350 2550 50  0000 C CNN
F 2 "" H 4350 2700 50  0001 C CNN
F 3 "" H 4350 2700 50  0001 C CNN
	1    4350 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 2700 4350 2650
Wire Wire Line
	4350 2650 4450 2650
$Comp
L Device:C C6
U 1 1 629317F8
P 5600 1300
F 0 "C6" H 5600 1400 50  0000 L CNN
F 1 "0.1uF" V 5650 1050 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 5638 1150 50  0001 C CNN
F 3 "~" H 5600 1300 50  0001 C CNN
	1    5600 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 629337DF
P 5800 1300
F 0 "C7" H 5800 1400 50  0000 L CNN
F 1 "0.1uF" V 5850 1050 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 5838 1150 50  0001 C CNN
F 3 "~" H 5800 1300 50  0001 C CNN
	1    5800 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C8
U 1 1 6293398C
P 6000 1300
F 0 "C8" H 6000 1400 50  0000 L CNN
F 1 "0.1uF" V 6050 1050 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 6038 1150 50  0001 C CNN
F 3 "~" H 6000 1300 50  0001 C CNN
	1    6000 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C9
U 1 1 62933B71
P 6200 1300
F 0 "C9" H 6200 1400 50  0000 L CNN
F 1 "0.1uF" V 6250 1050 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 6238 1150 50  0001 C CNN
F 3 "~" H 6200 1300 50  0001 C CNN
	1    6200 1300
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0119
U 1 1 629364A1
P 5600 1150
F 0 "#PWR0119" H 5600 1000 50  0001 C CNN
F 1 "+3.3V" H 5500 1300 50  0000 C CNN
F 2 "" H 5600 1150 50  0001 C CNN
F 3 "" H 5600 1150 50  0001 C CNN
	1    5600 1150
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0120
U 1 1 62936E5C
P 5800 1150
F 0 "#PWR0120" H 5800 1000 50  0001 C CNN
F 1 "+3.3V" H 5750 1300 50  0000 C CNN
F 2 "" H 5800 1150 50  0001 C CNN
F 3 "" H 5800 1150 50  0001 C CNN
	1    5800 1150
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0121
U 1 1 629371EB
P 6000 1150
F 0 "#PWR0121" H 6000 1000 50  0001 C CNN
F 1 "+3.3V" H 6000 1300 50  0000 C CNN
F 2 "" H 6000 1150 50  0001 C CNN
F 3 "" H 6000 1150 50  0001 C CNN
	1    6000 1150
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0122
U 1 1 629375DB
P 6200 1150
F 0 "#PWR0122" H 6200 1000 50  0001 C CNN
F 1 "+3.3V" H 6250 1300 50  0000 C CNN
F 2 "" H 6200 1150 50  0001 C CNN
F 3 "" H 6200 1150 50  0001 C CNN
	1    6200 1150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0123
U 1 1 62937C75
P 5600 1550
F 0 "#PWR0123" H 5600 1300 50  0001 C CNN
F 1 "GND" H 5600 1400 50  0000 C CNN
F 2 "" H 5600 1550 50  0001 C CNN
F 3 "" H 5600 1550 50  0001 C CNN
	1    5600 1550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0124
U 1 1 62938302
P 5800 1550
F 0 "#PWR0124" H 5800 1300 50  0001 C CNN
F 1 "GND" H 5800 1400 50  0000 C CNN
F 2 "" H 5800 1550 50  0001 C CNN
F 3 "" H 5800 1550 50  0001 C CNN
	1    5800 1550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0125
U 1 1 62938572
P 6000 1550
F 0 "#PWR0125" H 6000 1300 50  0001 C CNN
F 1 "GND" H 6000 1400 50  0000 C CNN
F 2 "" H 6000 1550 50  0001 C CNN
F 3 "" H 6000 1550 50  0001 C CNN
	1    6000 1550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0126
U 1 1 62938782
P 6200 1550
F 0 "#PWR0126" H 6200 1300 50  0001 C CNN
F 1 "GND" H 6200 1400 50  0000 C CNN
F 2 "" H 6200 1550 50  0001 C CNN
F 3 "" H 6200 1550 50  0001 C CNN
	1    6200 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 1450 5600 1550
Wire Wire Line
	5800 1550 5800 1450
Wire Wire Line
	6000 1550 6000 1450
Wire Wire Line
	6200 1550 6200 1450
$Comp
L Device:C C11
U 1 1 62984793
P 6900 2600
F 0 "C11" H 6900 2700 50  0000 L CNN
F 1 "0.1uF" V 6950 2350 50  0000 L CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 6938 2450 50  0001 C CNN
F 3 "~" H 6900 2600 50  0001 C CNN
	1    6900 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 2450 6900 2400
$Comp
L power:GND #PWR0127
U 1 1 6298BE69
P 6900 2800
F 0 "#PWR0127" H 6900 2550 50  0001 C CNN
F 1 "GND" H 6900 2650 50  0000 C CNN
F 2 "" H 6900 2800 50  0001 C CNN
F 3 "" H 6900 2800 50  0001 C CNN
	1    6900 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 2800 6900 2750
$Comp
L Amplifier_Operational:LM358 U2
U 3 1 629AC46C
P 5450 1350
F 0 "U2" H 5350 1550 50  0000 L CNN
F 1 "LM358" V 5450 1200 50  0000 L CNN
F 2 "Package_SO:SO-8_3.9x4.9mm_P1.27mm" H 5450 1350 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm2904-n.pdf" H 5450 1350 50  0001 C CNN
	3    5450 1350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0128
U 1 1 629B4D34
P 5350 1650
F 0 "#PWR0128" H 5350 1400 50  0001 C CNN
F 1 "GND" H 5350 1500 50  0000 C CNN
F 2 "" H 5350 1650 50  0001 C CNN
F 3 "" H 5350 1650 50  0001 C CNN
	1    5350 1650
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0129
U 1 1 629B5215
P 5350 1050
F 0 "#PWR0129" H 5350 900 50  0001 C CNN
F 1 "+3.3V" H 5350 1200 50  0000 C CNN
F 2 "" H 5350 1050 50  0001 C CNN
F 3 "" H 5350 1050 50  0001 C CNN
	1    5350 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 4950 6200 4950
Wire Wire Line
	7300 4950 7300 4850
Wire Wire Line
	7300 4850 7450 4850
Wire Wire Line
	7450 4950 7350 4950
Wire Wire Line
	7350 4950 7350 4900
Wire Wire Line
	7350 4900 7250 4900
Wire Wire Line
	7250 4900 7250 4850
Wire Wire Line
	7250 4850 6150 4850
Wire Wire Line
	7400 3700 7450 3700
$Comp
L Device:D_Schottky D2
U 1 1 62B30DA0
P 7600 3700
F 0 "D2" H 7600 3800 50  0000 C CNN
F 1 "1N5822" H 7600 3600 50  0000 C CNN
F 2 "Diode_SMD:D_SMA" H 7600 3700 50  0001 C CNN
F 3 "~" H 7600 3700 50  0001 C CNN
	1    7600 3700
	-1   0    0    1   
$EndComp
Wire Wire Line
	7750 3700 7800 3700
Connection ~ 7900 1850
Wire Wire Line
	8150 2100 8150 3700
Wire Wire Line
	6900 2150 6900 2400
Wire Wire Line
	7750 2100 7700 2100
$Comp
L Device:C C12
U 1 1 6273159D
P 7900 2100
F 0 "C12" V 7950 2150 50  0000 L CNN
F 1 "1uF" V 7950 1900 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7938 1950 50  0001 C CNN
F 3 "~" H 7900 2100 50  0001 C CNN
	1    7900 2100
	0    1    1    0   
$EndComp
Wire Wire Line
	7700 2150 7700 2100
$Comp
L Device:R R6
U 1 1 626A4832
P 7700 2300
F 0 "R6" H 7700 2150 50  0000 L CNN
F 1 "100k" V 7700 2200 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 7630 2300 50  0001 C CNN
F 3 "~" H 7700 2300 50  0001 C CNN
	1    7700 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 2150 6900 2150
Wire Wire Line
	7600 2300 7600 2150
Connection ~ 6900 1050
Wire Wire Line
	6900 1050 6900 1000
$Comp
L power:+5V #PWR0104
U 1 1 62682583
P 6900 1000
F 0 "#PWR0104" H 6900 850 50  0001 C CNN
F 1 "+5V" H 6915 1173 50  0000 C CNN
F 2 "" H 6900 1000 50  0001 C CNN
F 3 "" H 6900 1000 50  0001 C CNN
	1    6900 1000
	1    0    0    -1  
$EndComp
Connection ~ 6900 1850
Wire Wire Line
	6900 1900 6900 1850
$Comp
L power:GND #PWR0101
U 1 1 626672E5
P 6900 1900
F 0 "#PWR0101" H 6900 1650 50  0001 C CNN
F 1 "GND" H 6905 1727 50  0000 C CNN
F 2 "" H 6900 1900 50  0001 C CNN
F 3 "" H 6900 1900 50  0001 C CNN
	1    6900 1900
	1    0    0    -1  
$EndComp
Connection ~ 7050 1050
Wire Wire Line
	6900 1050 7050 1050
Wire Wire Line
	6900 1200 6900 1050
Connection ~ 7500 1850
Wire Wire Line
	6900 1850 6900 1500
Wire Wire Line
	7500 1850 6900 1850
Wire Wire Line
	7500 1850 7900 1850
Wire Wire Line
	7500 1800 7500 1850
$Comp
L Device:C C10
U 1 1 6263CADE
P 6900 1350
F 0 "C10" H 6900 1450 50  0000 L CNN
F 1 "10uF" V 6950 1100 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6938 1200 50  0001 C CNN
F 3 "~" H 6900 1350 50  0001 C CNN
	1    6900 1350
	1    0    0    -1  
$EndComp
Connection ~ 7550 1050
Connection ~ 7450 1050
Wire Wire Line
	7450 1050 7550 1050
Wire Wire Line
	7550 1200 7550 1050
Wire Wire Line
	7450 1050 7450 1200
Wire Wire Line
	7400 1050 7450 1050
Connection ~ 7050 1400
Wire Wire Line
	7050 1500 7050 1400
Wire Wire Line
	7100 1500 7050 1500
Wire Wire Line
	7050 1050 7100 1050
Wire Wire Line
	7050 1400 7050 1050
Wire Wire Line
	7100 1400 7050 1400
$Comp
L Device:L L1
U 1 1 6263A0B1
P 7250 1050
F 0 "L1" V 7350 900 50  0000 C CNN
F 1 "4.7mH" V 7350 1100 50  0000 C CNN
F 2 "Inductor_SMD:L_7.3x7.3_H3.5" H 7250 1050 50  0001 C CNN
F 3 "~" H 7250 1050 50  0001 C CNN
	1    7250 1050
	0    -1   -1   0   
$EndComp
$Comp
L Device:D_Schottky D3
U 1 1 6263937E
P 7700 1050
F 0 "D3" H 7700 1150 50  0000 C CNN
F 1 "1N5822" H 7700 950 50  0000 C CNN
F 2 "Diode_SMD:D_SMA" H 7700 1050 50  0001 C CNN
F 3 "~" H 7700 1050 50  0001 C CNN
	1    7700 1050
	-1   0    0    1   
$EndComp
$Comp
L local:ME2149 D1
U 1 1 6262E64F
P 7500 1500
F 0 "D1" H 7650 1750 50  0000 L CNN
F 1 "ME2149" H 7550 1250 50  0000 L CNN
F 2 "Package_SO:SO-8_3.9x4.9mm_P1.27mm" H 7500 1500 50  0001 C CNN
F 3 "" H 7500 1500 50  0001 C CNN
	1    7500 1500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0130
U 1 1 62BB73F7
P 6200 3850
F 0 "#PWR0130" H 6200 3600 50  0001 C CNN
F 1 "GND" H 6200 3700 50  0000 C CNN
F 2 "" H 6200 3850 50  0001 C CNN
F 3 "" H 6200 3850 50  0001 C CNN
	1    6200 3850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6150 3850 6200 3850
Wire Wire Line
	4850 2850 4450 2850
Wire Wire Line
	4450 2850 4450 2650
Connection ~ 4450 2650
Wire Wire Line
	4450 2650 4500 2650
Wire Wire Line
	4850 4450 4800 4450
Wire Wire Line
	4800 4450 4800 5750
Wire Wire Line
	4800 5750 6200 5750
Wire Wire Line
	6200 5750 6200 5050
Connection ~ 6200 5050
Wire Wire Line
	6200 5050 6600 5050
Wire Wire Line
	6200 4950 6200 4650
Wire Wire Line
	6200 4650 6150 4650
Connection ~ 6200 4950
Wire Wire Line
	6200 4950 7300 4950
$EndSCHEMATC
