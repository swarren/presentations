EESchema Schematic File Version 2  date Sat 30 Nov 2013 10:56:57 PM MST
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
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 4 4
Title ""
Date "1 dec 2013"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Notes 600  1100 0    60   ~ 0
A     B     X\n0     0     0\n0     1     0\n1     0     0\n1     1     1
Text Label 700  850  0    60   ~ 0
B
Wire Wire Line
	600  850  850  850 
Wire Wire Line
	2300 750  2050 750 
Wire Wire Line
	600  650  850  650 
$Comp
L 74LS08 U1
U 1 1 520302F2
P 1450 750
F 0 "U1" H 1450 800 60  0000 C CNN
F 1 "74LS08" H 1450 700 60  0000 C CNN
F 2 "DIP14" H 1450 750 60  0001 C CNN
	1    1450 750 
	1    0    0    -1  
$EndComp
Text Label 700  650  0    60   ~ 0
A
Text Label 2150 750  0    60   ~ 0
X
$EndSCHEMATC
