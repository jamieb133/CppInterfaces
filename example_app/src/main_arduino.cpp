#include "Platform/ArduinoPlatform.h"
#include "Tickers/ArduinoTicker.h"
#include "GPIO/ArduinoGPIO.h"
#include "TestRunner/TestRunner.h"

#include <Arduino.h>
#include <ArduinoSTL.h>

// Flash the led to trace stuff.
static inline void debugLoop() {
    while(1) {
        delay(100);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
    }
}

int main() {

    // Horrible raw pointers...
    ArduinoGPIO* gpio = new ArduinoGPIO();
    ArduinoTicker* ticker = new ArduinoTicker();

    ArduinoPlatform::createInstance();

    ticker->attach(50, [&]() {
        static bool toggle = true;
        static uint8_t nextPin = 0;

        toggle = (toggle && nextPin == gpio->numPins()) ? !toggle : toggle;
        toggle = (!toggle && nextPin == 0) ? !toggle : toggle;

        nextPin = (toggle) ? nextPin + 1 : nextPin - 1;

        gpio->set(nextPin, toggle);
    });

    //TestRunner::runTestCase(ticker, gpio, *ArduinoPlatform::getInstance());
    
    ArduinoPlatform::getInstance()->run();

    delete gpio;
    delete ticker;

    return 0;
}
