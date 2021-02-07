//
// Created by Magnus Nordlander on 2021-02-06.
//

#include "SsrState.h"

SsrState::SsrState(pin_size_t pin) {
    this->pin = pin;
    pinMode(pin, OUTPUT);
    digitalWrite(this->pin, LOW);
}

void SsrState::enable() const {
    digitalWrite(this->pin, HIGH);
}

void SsrState::disable() const {
    digitalWrite(this->pin, LOW);
}
