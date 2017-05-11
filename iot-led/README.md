The files in this directory are Arduino code for the ESP8266. They are used in
the "Internet of Things LED" class that I teach.

Required hardware:

• Micro-controller: ESP8266 (ESP12 module, NodeMCU board), e.g.:
https://smile.amazon.com/gp/product/B01IK9GEQG/ref=oh_aui_detailpage_o01_s00?ie=UTF8&psc=1

• RGB LED: WS2812B, e.g.:
https://smile.amazon.com/gp/product/B01D1FFVOA/ref=oh_aui_detailpage_o01_s00?ie=UTF8&psc=1

• USB host to micro B cable, to power and program the ESP8266.

* A few hookup wires, to connect the ESP8266 to the LED, e.g.:
https://smile.amazon.com/gp/product/B00PBZMN7C/ref=oh_aui_detailpage_o01_s00?ie=UTF8&psc=1

• Soldering supplies, to connect the ESP8266 to the LED.

Required software:

* Arduino IDE:
http://www.arduino.org/downloads (version 1.6.8 is validated for use with the
ESP8266).

• ESP8266 board support for the Arduino IDE:
https://github.com/esp8266/Arduino/blob/master/README.md 

• Adafruit_NeoPixel Arduino library:
https://blog.adafruit.com/2015/06/30/updated-neopixel-support-for-esp8266-and-arduino-zero/ 

• USB serial port driver for Windows or Mac; see instructions at
https://www.pololu.com/docs/0J7/all. For Linux, the driver is already built in.
