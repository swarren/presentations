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
Text Notes 600  1150 0    60   ~ 0
A     B     X\n0     0     0\n0     1     1\n1     0     1\n1     1     1
$Comp
L 74LS32 U2
U 1 1 52030283
P 1450 800
F 0 "U2" H 1450 850 60  0000 C CNN
F 1 "74LS32" H 1450 750 60  0000 C CNN
F 2 "" H 1450 800 60  0001 C CNN
F 3 "" H 1450 800 60  0001 C CNN
	1    1450 800 
	1    0    0    -1  
$EndComp
Text Label 700  700  0    60   ~ 0
A
Text Label 700  900  0    60   ~ 0
B
Text Label 2150 800  0    60   ~ 0
X
Wire Wire Line
	2300 800  2050 800 
Wire Wire Line
	600  900  850  900 
Wire Wire Line
	600  700  850  700 
$EndSCHEMATC
