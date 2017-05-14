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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, Emessage_xpRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPUpdateServer.h>

#define ARRAY_SIZE(_x_) ((sizeof (_x_)) / (sizeof ((_x_)[0])))

#define MESSAGE_0_PIN 5
#define MESSAGE_0     "Go Savena!"
#define MESSAGE_1_PIN 4
#define MESSAGE_1     "Go Mountain!"

#define WIFI_SSID "ScrollSign"
#define WIFI_PASS "YouShallNotScroll"

const uint32_t colors[] = {
    Adafruit_NeoPixel::Color(0xff, 0, 0),
    Adafruit_NeoPixel::Color(0xff, 0xff, 0),
    Adafruit_NeoPixel::Color(0, 0xff, 0),
    Adafruit_NeoPixel::Color(0, 0xff, 0xff),
    Adafruit_NeoPixel::Color(0xff, 0, 0xff),
    Adafruit_NeoPixel::Color(0xff, 0xff, 0xff),
};

ESP8266WebServer web_server(80);
ESP8266HTTPUpdateServer http_updater;

#define LED_TILE_W 2
#define LED_TILE_H 1
#define LED_WIDTH  32
#define LED_HEIGHT 8
#define LED_PIN    12
Adafruit_NeoMatrix leds = Adafruit_NeoMatrix(
    LED_WIDTH, LED_HEIGHT, LED_TILE_W, LED_TILE_H, LED_PIN,
    NEO_MATRIX_TOP | NEO_MATRIX_LEFT | NEO_MATRIX_COLUMNS | NEO_MATRIX_ZIGZAG,
    NEO_GRB | NEO_KHZ800);

String web_message("Go Mountain Kids - Go Savena - Go Josie -");
String message;
uint16_t message_width;
int message_xp;
int color_index;
int scroll_delay = 75;
bool no_scroll;

void set_message(const String &new_message) {
    int16_t x1, y1;
    uint16_t h;

    message = new_message;
    message.concat(" ");
    leds.getTextBounds(const_cast<char *>(message.c_str()),
        0, 0, &x1, &y1, &message_width, &h);
    message_xp = 0;
}

enum msg_id {
    MSG_ID_UNKNOWN,
    MSG_ID_0,
    MSG_ID_1,
    MSG_ID_WEB,
};
enum msg_id last_msg_id = MSG_ID_UNKNOWN;
void eval_msg() {
    enum msg_id new_msg_id;
    if (digitalRead(MESSAGE_0_PIN) == 0)
        new_msg_id = MSG_ID_0;
    else if (digitalRead(MESSAGE_1_PIN) == 0)
        new_msg_id = MSG_ID_1;
    else
        new_msg_id = MSG_ID_WEB;

    if (new_msg_id == last_msg_id)
        return;
    last_msg_id = new_msg_id;

    String new_message;
    switch (new_msg_id) {
    case MSG_ID_0:
        new_message = MESSAGE_0;
        break;
    case MSG_ID_1:
        new_message = MESSAGE_1;
        break;
    default:
        new_message = web_message;
        break;
    }
    set_message(new_message);
}

void set_web_message(const String &new_message) {
    web_message = new_message;
    if (last_msg_id == MSG_ID_WEB)
        set_message(web_message);
}

void handle_http_not_found() {
    web_server.send(404, "text/plain", "Not Found");
}

const char html_get_root[] = { "\
<html>\
<head>\
<title>LED Sign Control</title>\
</head>\
<body>\
<p>" __DATE__ " " __TIME__ "\
<form method=\"POST\" action=\"/message\">\
Message: <input type=\"text\" name=\"message\" value=\"MESSAGE_VALUE\"/><br/>\
<input type=\"submit\" value=\"Set message\"/>\
</form>\
<form method=\"POST\" action=\"/bright\">\
Brightness: <input type=\"text\" name=\"bright\" value=\"BRIGHT_VALUE\"/><br/>\
<input type=\"submit\" value=\"Set brightness\"/>\
</form>\
<form method=\"POST\" action=\"/no_scroll\">\
No scroll: <input type=\"checkbox\" name=\"no_scroll\" value=\"1\" NO_SCROLL_CHECKED/><br/>\
Color index: <input type=\"text\" name=\"color_index\" value=\"COLOR_INDEX_VALUE\"/><br/>\
<input type=\"submit\" value=\"Set no scroll\"/>\
</form>\
<form method=\"POST\" action=\"/scroll_delay\">\
Scroll Delay: <input type=\"text\" name=\"scroll_delay\" value=\"SCROLL_DELAY_VALUE\"/><br/>\
<input type=\"submit\" value=\"Set scroll delay\"/>\
</form>\
<p><a href=\"/update\">Update</a></p>\
</body>\
</html>\
"
};

void handle_http_get_root() {
    Serial.println("HTTP GET /");

    String s = html_get_root;
    s.replace("MESSAGE_VALUE", web_message);
    String bright_s(leds.getBrightness());
    s.replace("BRIGHT_VALUE", bright_s);
    String color_index_s(color_index);
    s.replace("COLOR_INDEX_VALUE", color_index_s);
    String no_scroll_s;
    if (no_scroll)
        no_scroll_s = "checked=\"checked\"";
    s.replace("NO_SCROLL_CHECKED", no_scroll_s);
    String scroll_delay_s(scroll_delay);
    s.replace("SCROLL_DELAY_VALUE", scroll_delay_s);
    web_server.send(200, "text/html", s);
}

long int post_param_to_int(const char *param, long int minval, long int maxval) {
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
    long int value = strtol(value_as_str.c_str(), &end, 10);
    if ((*end) || (value < minval) || (value > maxval)) {
        String s;
        s += "POST value invalid: ";
        s += value_as_str;
        web_server.send(400, "text/plain", s);
        return -1;
    }

    return value;
}

void handle_http_post_bright() {
    Serial.println("HTTP POST /bright");

    int new_bright = post_param_to_int("bright", 0, 255);
    if (new_bright < 0)
        return;

    leds.setBrightness(new_bright);

    web_server.sendHeader("Location", "/");
    web_server.send(302, "text/plain", "");
}

void handle_http_post_message() {
    Serial.println("HTTP POST /message");

    if (!web_server.hasArg("message")) {
        web_server.send(400, "text/plain", "POST parameter missing: message");
        return;
    }

    String new_message = web_server.arg("message");
    new_message.trim();
    if (new_message.length() < 1) {
        web_server.send(400, "text/plain", "POST value empty: message");
        return;
    }

    set_web_message(new_message);

    web_server.sendHeader("Location", "/");
    web_server.send(302, "text/plain", "");
}

void handle_http_post_no_scroll() {
    Serial.println("HTTP POST /no_scroll");

    if (!web_server.hasArg("no_scroll")) {
        no_scroll = false;
    } else {
        int new_color_index = post_param_to_int("color_index", 0, ARRAY_SIZE(colors));
        if (new_color_index < 0)
            new_color_index = 0;
        no_scroll = true;
        message_xp = 0;
        color_index = new_color_index;
    }

    web_server.sendHeader("Location", "/");
    web_server.send(302, "text/plain", "");
}

void handle_http_post_scroll_delay() {
    Serial.println("HTTP POST /scroll_delay");

    int new_scroll_delay = post_param_to_int("scroll_delay", 25, 1000);
    if (new_scroll_delay < 0)
        return;

    scroll_delay = new_scroll_delay;

    web_server.sendHeader("Location", "/");
    web_server.send(302, "text/plain", "");
}

void setup() {
    Serial.begin(115200);
    delay(250);
    Serial.println("");
    Serial.println("Running");

    Serial.println("Settig up message GPIOs");
    pinMode(MESSAGE_0_PIN, INPUT_PULLUP);
    pinMode(MESSAGE_1_PIN, INPUT_PULLUP);

    Serial.println("Setting up LEDs");
    leds.begin();
    leds.setBrightness(10);
    leds.fillScreen(0);
    leds.show();
    leds.setTextWrap(false);

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
    web_server.on("/bright", HTTP_POST, handle_http_post_bright);
    web_server.on("/message", HTTP_POST, handle_http_post_message);
    web_server.on("/no_scroll", HTTP_POST, handle_http_post_no_scroll);
    web_server.on("/scroll_delay", HTTP_POST, handle_http_post_scroll_delay);
    http_updater.setup(&web_server);
    web_server.begin();
}

void loop() {
    web_server.handleClient();

    static unsigned long t_leds_updated;
    unsigned long t_now = millis();
    if ((t_now - t_leds_updated) < scroll_delay)
        return;
    t_leds_updated = t_now;

    eval_msg();

    leds.setPassThruColor();
    leds.fillScreen(0);
    leds.setCursor(message_xp, 0);
    leds.setPassThruColor(colors[color_index]);
    leds.printf(message.c_str());
    leds.setPassThruColor(colors[(color_index + 1) % ARRAY_SIZE(colors)]);
    leds.printf(message.c_str());
    leds.show();
    if (!no_scroll) {
        message_xp--;
        if (message_xp < -message_width) {
            message_xp = -1;
            color_index++;
            color_index %= ARRAY_SIZE(colors);
        }
    }
}
