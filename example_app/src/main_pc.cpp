#include <memory>
#include <mutex>
#include <iostream>

#include "ITicker.h"
#include "IGPIO.h"

#include "FauxGPIO.h"
#include "SimpleTicker.h"
#include "DesktopPlatform.h"

int main() {
    DesktopPlatform platform;
     
    std::shared_ptr<SimpleTicker> ticker = std::make_shared<SimpleTicker>();
    auto gpio = std::make_shared<FauxGPIO>();

    std::cout << "hell world\n";

    ticker->attach(100, [&]() {
        static bool toggle = true;
        static uint8_t nextPin = 0;
        static auto gpio = std::make_shared<FauxGPIO>();

        gpio->set(nextPin, toggle);

        nextPin = (toggle) ? nextPin + 1 : nextPin - 1;
        toggle = (toggle && nextPin == gpio->numPins()) ? !toggle : toggle;
        toggle = (!toggle && nextPin == 0) ? !toggle : toggle;
    });

    platform.run();

    return 0;
}
