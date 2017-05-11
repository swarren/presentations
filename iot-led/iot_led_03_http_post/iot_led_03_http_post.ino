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

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>

// CHANGE THIS to avoid conflicts with other students
#define WIFI_SSID "IOT_LED_SWARREN"
// Must be at least 8 characters
#define WIFI_PASS "IOT_LED_PASSWORD"
#define LED_PIN 12

Adafruit_NeoPixel led(1, LED_PIN, NEO_GRB + NEO_KHZ800);
ESP8266WebServer web_server(80);
bool led_on;

void handle_http_not_found() {
    web_server.send(404, "text/plain", "Not Found");
}

const char html_get_root[] = { "\
<html>\
<head>\
<title>LED Control</title>\
</head>\
<body>\
<form method=\"POST\" action=\"/\">\
<input type=\"submit\" value=\"Toggle\"/>\
</form>\
</body>\
</html>\
"
};

void handle_http_get_root() {
    Serial.println("HTTP GET /");
    web_server.send(200, "text/html", html_get_root);
}

void handle_http_post_root() {
    Serial.println("HTTP POST /");

    web_server.sendHeader("Location", "/");
    web_server.send(302, "text/plain", "");

    led_on = !led_on;
    uint32_t color = led_on ?
        Adafruit_NeoPixel::Color(0xff, 0xff, 0xff) :
        Adafruit_NeoPixel::Color(0x00, 0x00, 0x00);
    led.setPixelColor(0, color);
    led.show();
}

void setup() {
    Serial.begin(115200);
    delay(250);
    Serial.println("");
    Serial.println("Running");

    Serial.println("Setting up LED (off)");
    led.begin();
    led.setBrightness(15);
    led.show();

    Serial.println("Starting WiFi");
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(
        IPAddress(192, 168, 50, 1),
        IPAddress(192, 168, 50, 1),
        IPAddress(255, 255, 255, 0));
    WiFi.softAP(WIFI_SSID, WIFI_PASS);

    Serial.println("Starting HTTP server");
    web_server.onNotFound(handle_http_not_found);
    web_server.on("/", HTTP_GET, handle_http_get_root);
    web_server.on("/", HTTP_POST, handle_http_post_root);
    web_server.begin();
}

void loop() {
    web_server.handleClient();
}
