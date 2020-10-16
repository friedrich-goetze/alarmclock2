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
L Connector_Generic:Conn_02x05_Odd_Even J_TARGET1
U 1 1 5EBB23A4
P 4550 3300
F 0 "J_TARGET1" H 4600 3717 50  0000 C CNN
F 1 "Conn_02x05_Odd_Even" H 4600 3626 50  0000 C CNN
F 2 "Connector_IDC:IDC-Header_2x05_P2.54mm_Vertical" H 4550 3300 50  0001 C CNN
F 3 "~" H 4550 3300 50  0001 C CNN
	1    4550 3300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5EBB4399
P 4600 4100
F 0 "#PWR02" H 4600 3850 50  0001 C CNN
F 1 "GND" H 4605 3927 50  0000 C CNN
F 2 "" H 4600 4100 50  0001 C CNN
F 3 "" H 4600 4100 50  0001 C CNN
	1    4600 4100
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR01
U 1 1 5EBB4873
P 4600 2100
F 0 "#PWR01" H 4600 1950 50  0001 C CNN
F 1 "+5V" H 4615 2273 50  0000 C CNN
F 2 "" H 4600 2100 50  0001 C CNN
F 3 "" H 4600 2100 50  0001 C CNN
	1    4600 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 3100 4150 3100
Wire Wire Line
	4150 3100 4150 4100
Wire Wire Line
	4150 4100 4600 4100
Wire Wire Line
	4600 4100 5000 4100
Wire Wire Line
	5000 4100 5000 3400
Wire Wire Line
	5000 3100 4850 3100
Connection ~ 4600 4100
Text Label 4350 3200 2    50   ~ 0
RX
Text Label 4850 3200 0    50   ~ 0
TX
NoConn ~ 4350 3300
Text Label 4850 3300 0    50   ~ 0
PGC
Text Label 4350 3400 2    50   ~ 0
PGD
Wire Wire Line
	4850 3400 5000 3400
Connection ~ 5000 3400
Wire Wire Line
	5000 3400 5000 3150
Wire Wire Line
	4350 3500 4050 3500
Wire Wire Line
	4050 3500 4050 3200
Wire Wire Line
	4050 2100 4600 2100
Text Label 4850 3500 0    50   ~ 0
MCLR
$Comp
L Connector:6P6C J_ICD1
U 1 1 5EBB5889
P 1700 3400
F 0 "J_ICD1" H 1757 3967 50  0000 C CNN
F 1 "6P6C" H 1757 3876 50  0000 C CNN
F 2 "__6p6c:6p6c" V 1700 3425 50  0001 C CNN
F 3 "~" V 1700 3425 50  0001 C CNN
	1    1700 3400
	1    0    0    -1  
$EndComp
NoConn ~ 2100 3600
Text Label 2100 3500 0    50   ~ 0
PGC
Text Label 2100 3400 0    50   ~ 0
PGD
Wire Wire Line
	2100 3300 3900 3300
Wire Wire Line
	3900 3300 3900 4100
Wire Wire Line
	3900 4100 4150 4100
Connection ~ 4150 4100
Wire Wire Line
	2100 3200 4050 3200
Connection ~ 4050 3200
Wire Wire Line
	4050 3200 4050 2100
Text Label 2100 3100 0    50   ~ 0
MCLR
Connection ~ 5000 3150
Wire Wire Line
	5000 3150 5000 3100
NoConn ~ 6850 3250
NoConn ~ 6850 3350
NoConn ~ 6850 3650
Wire Wire Line
	6850 3150 5000 3150
$Comp
L Connector_Generic:Conn_01x06 J_USART1
U 1 1 5EBB7CFC
P 7050 3350
F 0 "J_USART1" H 7130 3342 50  0000 L CNN
F 1 "Conn_01x06" H 7130 3251 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 7050 3350 50  0001 C CNN
F 3 "~" H 7050 3350 50  0001 C CNN
	1    7050 3350
	1    0    0    -1  
$EndComp
Text Label 6850 3450 2    50   ~ 0
RX
Text Label 6850 3550 2    50   ~ 0
TX
$EndSCHEMATC
