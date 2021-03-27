//
// Created by Magnus Nordlander on 2021-02-06.
//

#include "BaseViewController.h"

#include <utility>
#include <WiFi.h>
#include "Utils/freemem.h"

void BaseViewController::render(U8G2 display) {
    display.setFont(u8g2_font_ncenB08_tr);
    display.drawStr(16, 16, "Override me");
}

void BaseViewController::handleRotation(int encoderDiff) {

}

void BaseViewController::handleButtonEvent(ButtonEvent event) {
}

void BaseViewController::viewWillBePushed(NavigationController *) {

}

void BaseViewController::viewWasPushed(NavigationController * nav) {
    this->navigationController = nav;
}

void BaseViewController::viewWillBePopped(NavigationController *) {
    this->navigationController = nullptr;
}

void BaseViewController::viewWasPopped(NavigationController *) {

}

void BaseViewController::tick(U8G2 display) {
    this->redraw(std::move(display));
}

void BaseViewController::subviewWillBePushed(NavigationController *, BaseViewController *) {

}

void BaseViewController::subviewWasPushed(NavigationController *, BaseViewController *) {

}

void BaseViewController::subviewWasPopped(NavigationController *, BaseViewController *) {

}

void BaseViewController::redraw(U8G2 display) {
    display.clearBuffer();

    this->render(display);

    display.setFont(u8g2_font_5x8_tr);
    display.setDrawColor(2);

    uint8_t status = WiFiDrv::getConnectionStatus();
    if (status == WL_CONNECTED) {
        display.drawStr(110, 10, "W");
    }

    char snum[10];
    itoa(freeMemory(), snum, 10);

    display.drawStr(90, 60, snum);

    display.setContrast(0xFF);
    display.sendBuffer();
}