#pragma once

#include <memory>
#include <array>

#include "IGPIO.h"

static const int NUM_OF_PINS = 10;

class FauxGPIO {
private:
    // GPIOs are hardware IO and thus are finite physical "things",
    // therefore we are defining its interface as a singleton here.
    static std::shared_ptr<FauxGPIO> _instance;

    std::array<bool, NUM_OF_PINS> m_pinArray; 
    void dumpPins();
    FauxGPIO();

public:
    static std::shared_ptr<FauxGPIO> getInstance();
    virtual ~FauxGPIO() {}
    void set(int pinNumber, bool value);
    int numPins();
    
};
