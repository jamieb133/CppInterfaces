#include "ArduinoGPIO.h"
#include <Arduino.h>
#include <stdint.h>
#include <assert.h>

// There are actually 14 digital pins but for the purposes
// of the demo, we'll only use 8.
static const int NUMBER_OF_DIGITAL_PINS_UNO = 8; // pin 0 to pin 7.

static void inline setupPin(uint8_t pin) {
    uint8_t p = pin + 6U;
    pinMode(p, OUTPUT);

    // Waggle the pin after setting.
    uint32_t togs = 0x0f;
    while (togs > 0) {
        digitalWrite(p, HIGH);
        delay(10);
        digitalWrite(p, LOW);
        delay(10);
        --togs;
    }
}

static std::shared_ptr<ArduinoGPIO> _instance = nullptr;
static bool _created = false;

void ArduinoGPIO::createInstance() {
    if (!_created)
        _instance = std::shared_ptr<ArduinoGPIO>(new ArduinoGPIO());
    _created = true;
}

std::shared_ptr<ArduinoGPIO> ArduinoGPIO::getInstance() {
    assert(_created);
    return _instance;
}

ArduinoGPIO::ArduinoGPIO() {
    for (uint8_t i = 6U; i < NUMBER_OF_DIGITAL_PINS_UNO + 6U; i++)
        setupPin(i);
}

void ArduinoGPIO::set(uint8_t pinNumber, bool value) {
    // Offset by 6.
    digitalWrite(6U + pinNumber, static_cast<uint8_t>(value));
}

unsigned int ArduinoGPIO::numPins() {
    return NUMBER_OF_DIGITAL_PINS_UNO;
}
