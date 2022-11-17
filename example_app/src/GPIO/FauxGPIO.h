#pragma once

#include <memory>
#include <array>

#include "IGPIO.h"

static const int NUM_OF_PINS = 8;

class FauxGPIO : public IGPIO<FauxGPIO> {
private:
    std::array<bool, NUM_OF_PINS> m_pinArray; 
    void dumpPins();
public:
    FauxGPIO();
    virtual ~FauxGPIO() {}
    void set(uint8_t pinNumber, bool value);
    unsigned int numPins();
};
