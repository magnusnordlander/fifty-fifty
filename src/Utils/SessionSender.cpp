//
// Created by Magnus Nordlander on 2021-03-28.
//

#include "SessionSender.h"
#include <WiFiClient.h>
#include <sstream>
#include <WiFi.h>
#include <iomanip>
#include "secrets.h"
#include <avr/dtostrf.h>

WiFiClient client;

#define LONGSIZ 10
#define SHORTSIZ 5
#define LINESIZ LONGSIZ*2+3
#define SENDBUFSIZ 22 + 4*(LONGSIZ+1) + 4*(SHORTSIZ+1) + 11 + 2*SHORTSIZ + 2 + 100*LINESIZ + 7

char buf[SENDBUFSIZ];

void initSessionSender() {
}

void sendSession(GrindSession gs, std::vector<MeasuringPoint> *measuringPoints) {
    if (client.connect("grindstravaganza.coffee", 80)) {

        char str[10];
        dtostrf(gs.settings->getScaleCalibration(), 8, 2, str);

        uint8_t mac[WL_MAC_ADDR_LENGTH];
        WiFi.macAddress(mac);

        snprintf(buf, sizeof(buf), "C0FFEE:1:%02x%02x%02x%02x%02x%02x:%lu:%lu:%ld:%lu:%d:%d:%d:%d:%s:%d:%d\n",
            mac[0], mac[1], mac[2], mac[3], mac[4], mac[5],
            gs.startTime, gs.endTime, gs.tareValue, gs.temporaryTarget,
            gs.settings->getGrindTargetTime(), gs.settings->getPurgeTargetTime(),
            gs.settings->getGrindTargetWeight(), gs.settings->getProductivity(),
            str, gs.settings->getReactionTime(),
            gs.type
        );

        char line[LINESIZ];
        for (auto & measuringPoint : *measuringPoints) {
            snprintf(line, sizeof(line), "%lu:%ld\n", measuringPoint.microtime, measuringPoint.measuringPoint);
            strcat(buf, line);
        }

        strcat(buf, "EEFFC0\n");

 /*       Serial.print("Str siz: ");
        Serial.println(strlen(buf));
        Serial.println(buf); */

        client.print("POST /report HTTP/1.1\r\n");
        client.print("Host: grindstravaganza.coffee\r\n");
        client.print("Content-Type: text/plain\r\n");
        client.print("Authorization: ");
        client.print(GRINDSTRAVAGANZA_AUTH);
        client.print("\r\n");
        client.print("Content-Length: ");
        client.print(strlen(buf));
//        client.print("6");
        client.print("\r\n");
        client.print("Connection: close\r\n");
        client.print("\r\n");
//        client.print("foobar");
        client.print(buf);
    }

    client.stop();
}
