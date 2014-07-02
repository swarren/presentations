EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:gates-ex1-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 4
Title ""
Date "29 jun 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 600  2050 0    60   ~ 0
A     B     SEL   X\n---------------\n0     0     0     0\n0     1     0     0\n1     0     0     0\n1     1     0     1\n---------------\n0     0     1     0\n0     1     1     1\n1     0     1     1\n1     1     1     1
$Comp
L 74LS08 U3
U 1 1 5203026B
P 1650 800
F 0 "U3" H 1650 850 60  0000 C CNN
F 1 "74LS08" H 1650 750 60  0000 C CNN
F 2 "" H 1650 800 60  0001 C CNN
F 3 "" H 1650 800 60  0001 C CNN
	1    1650 800 
	1    0    0    -1  
$EndComp
$Comp
L 74LS32 U5
U 1 1 5203026A
P 1650 1700
F 0 "U5" H 1650 1750 60  0000 C CNN
F 1 "74LS32" H 1650 1650 60  0000 C CNN
F 2 "" H 1650 1700 60  0001 C CNN
F 3 "" H 1650 1700 60  0001 C CNN
	1    1650 1700
	1    0    0    -1  
$EndComp
Text Label 700  700  0    60   ~ 0
A
Text Label 700  900  0    60   ~ 0
B
$Comp
L 74LS08 U4
U 1 1 52030269
P 2850 900
F 0 "U4" H 2850 950 60  0000 C CNN
F 1 "74LS08" H 2850 850 60  0000 C CNN
F 2 "" H 2850 900 60  0001 C CNN
F 3 "" H 2850 900 60  0001 C CNN
	1    2850 900 
	1    0    0    -1  
$EndComp
$Comp
L 74LS08 U6
U 1 1 52030268
P 2850 1600
F 0 "U6" H 2850 1650 60  0000 C CNN
F 1 "74LS08" H 2850 1550 60  0000 C CNN
F 2 "" H 2850 1600 60  0001 C CNN
F 3 "" H 2850 1600 60  0001 C CNN
	1    2850 1600
	1    0    0    -1  
$EndComp
$Comp
L 74HC04 U7
U 1 1 52030267
P 1500 1200
F 0 "U7" H 1650 1300 40  0000 C CNN
F 1 "74HC04" H 1700 1100 40  0000 C CNN
F 2 "" H 1500 1200 60  0001 C CNN
F 3 "" H 1500 1200 60  0001 C CNN
	1    1500 1200
	1    0    0    -1  
$EndComp
$Comp
L 74LS32 U8
U 1 1 52030266
P 4050 1250
F 0 "U8" H 4050 1300 60  0000 C CNN
F 1 "74LS32" H 4050 1200 60  0000 C CNN
F 2 "" H 4050 1250 60  0001 C CNN
F 3 "" H 4050 1250 60  0001 C CNN
	1    4050 1250
	1    0    0    -1  
$EndComp
Text Label 4750 1250 0    60   ~ 0
X
Text Label 600  1400 0    60   ~ 0
SEL
Wire Wire Line
	950  1600 1050 1600
Wire Wire Line
	950  700  950  1600
Wire Wire Line
	4900 1250 4650 1250
Wire Wire Line
	3450 900  3450 1150
Wire Wire Line
	2150 1000 2250 1000
Wire Wire Line
	2150 1200 2150 1000
Wire Wire Line
	1950 1200 2150 1200
Connection ~ 950  700 
Wire Wire Line
	1050 700  550  700 
Wire Wire Line
	1050 900  550  900 
Connection ~ 850  900 
Wire Wire Line
	2150 1400 550  1400
Wire Wire Line
	2150 1500 2150 1400
Wire Wire Line
	2250 1500 2150 1500
Wire Wire Line
	3450 1350 3450 1600
Wire Wire Line
	850  1800 850  900 
Wire Wire Line
	1050 1800 850  1800
Wire Wire Line
	1050 1400 1050 1200
Connection ~ 1050 1400
$EndSCHEMATC
