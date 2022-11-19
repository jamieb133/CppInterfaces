#include "Platform/ArduinoPlatform.h"
#include "Tickers/ArduinoTicker.h"
#include "GPIO/ArduinoGPIO.h"
#include "GPIO/FauxGPIO.h"

// The user's application code lives here.
#include "App_user.h"

#include <Arduino.h>
#include <ArduinoSTL.h>

// Flash the led really fast to indicate that we've finished.
void indicateFinished() {
    while(1) {
        delay(100);
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
    }
}

using Ticker = ITicker<ArduinoTicker>;
using GPIO = IGPIO<ArduinoGPIO>;

int main() {
    // Initialise our target platform.
    ArduinoPlatform::createInstance();
    auto platform = ArduinoPlatform::getInstance();

    // Driver setup.
    ArduinoGPIO::createInstance();
    ArduinoTicker::createInstance(*platform);

    auto ticker = ArduinoTicker::getInstance();
    auto gpio = ArduinoGPIO::getInstance();

    FauxGPIO fauxGpio;

    // Run the user app using the real GPIO.
    //App::run(*ticker, *gpio, *platform); 

    // Run the user app using the fake GPIO.   
    App::run(*ticker, fauxGpio, *platform);    

    // Completed.
    indicateFinished();

    return 0;
}
