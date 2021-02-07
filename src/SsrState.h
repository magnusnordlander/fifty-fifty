//
// Created by Magnus Nordlander on 2021-02-06.
//

#ifndef GRINDER_SSRSTATE_H
#define GRINDER_SSRSTATE_H

#include <Arduino.h>

class SsrState {
public:
    explicit SsrState(pin_size_t pin);

    void enable() const;
    void disable() const;

private:
    pin_size_t pin;
};


#endif //GRINDER_SSRSTATE_H
