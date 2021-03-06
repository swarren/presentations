/*
 * Copyright (c) 2017, Stephen Warren
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <Adafruit_NeoPixel.h>

#define LED_PIN 12

Adafruit_NeoPixel led(1, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
    Serial.begin(115200);
    delay(250);
    Serial.println("");
    Serial.println("Running");

    Serial.println("Setting up LED (off)");
    led.begin();
    led.setBrightness(15);
    led.show();
}

void loop() {
    uint32_t color;

    color = Adafruit_NeoPixel::Color(0xff, 0xff, 0xff);
    led.setPixelColor(0, color);
    led.show();
    delay(500);

    color = Adafruit_NeoPixel::Color(0x00, 0x00, 0x00);
    led.setPixelColor(0, color);
    led.show();
    delay(500);
}
