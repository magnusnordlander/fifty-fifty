//
// Created by Magnus Nordlander on 2021-03-28.
//

#include "WifiDebugViewController.h"
#include <WiFi.h>

void WifiDebugViewController::render(U8G2 display) {
    display.setFont(u8g2_font_5x8_tr);

    uint8_t buf[WL_MAC_ADDR_LENGTH];
    char full[32];

    snprintf(full, sizeof(full), "Status: %d", WiFi.status());
    display.drawStr(0,8, full);

    snprintf(full, sizeof(full), "SSID: %s", WiFi.SSID());
    display.drawStr(0,17, full);

    WiFi.BSSID(buf);
    snprintf(full, sizeof(full), "BSSID: %02X:%02X:%02X:%02X:%02X:%02X", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);
    display.drawStr(0,26, full);

    snprintf(full, sizeof(full), "RSSI: %ld", WiFi.RSSI());
    display.drawStr(0,35, full);

    IPAddress ip = WiFi.localIP();
    snprintf(full, sizeof(full), "IP: %d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
    display.drawStr(0,44, full);

    WiFi.macAddress(buf);
    snprintf(full, sizeof(full), "MAC: %02X:%02X:%02X:%02X:%02X:%02X", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5]);
    display.drawStr(0,53, full);
}

void WifiDebugViewController::handleButtonEvent(ButtonEvent event) {
    if (event == BUTTON_LET_UP) {
        this->navigationController->pop();
    }
}