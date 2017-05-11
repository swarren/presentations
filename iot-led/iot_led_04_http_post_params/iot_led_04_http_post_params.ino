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
Red: <input type=\"text\" name=\"red\" value=\"255\"/><br/>\
Green: <input type=\"text\" name=\"green\" value=\"255\"/><br/>\
Blue: <input type=\"text\" name=\"blue\" value=\"255\"/><br/>\
Brightness: <input type=\"text\" name=\"bright\" value=\"15\"/><br/>\
<input type=\"submit\" value=\"Set color\"/>\
</form>\
</body>\
</html>\
"
};

void handle_http_get_root() {
    Serial.println("HTTP GET /");
    web_server.send(200, "text/html", html_get_root);
}

int post_param_to_int(const char *param) {
    if (!web_server.hasArg(param)) {
        String s;
        s += "POST parameter missing: ";
        s += param;
        web_server.send(400, "text/plain", s);
        return -1;
    }

    String value_as_str = web_server.arg(param);
    if (value_as_str.length() < 1) {
        String s;
        s += "POST value empty: ";
        s += param;
        web_server.send(400, "text/plain", s);
        return -1;
    }
    char *end;
    unsigned long int value = strtoul(value_as_str.c_str(), &end, 10);
    if ((*end) || (value < 0) || (value > 255)) {
        String s;
        s += "POST value invalid: ";
        s += value_as_str;
        web_server.send(400, "text/plain", s);
        return -1;
    }

    return value;
}

void handle_http_post_root() {
    Serial.println("HTTP POST /");

    int red = post_param_to_int("red");
    if (red < 0)
        return;
    int green = post_param_to_int("green");
    if (green < 0)
        return;
    int blue = post_param_to_int("blue");
    if (blue < 0)
        return;
    int bright = post_param_to_int("bright");
    if (bright < 0)
        return;

    web_server.sendHeader("Location", "/");
    web_server.send(302, "text/plain", "");

    led.setBrightness(bright);
    uint32_t color =
        Adafruit_NeoPixel::Color(red, green, blue);
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
