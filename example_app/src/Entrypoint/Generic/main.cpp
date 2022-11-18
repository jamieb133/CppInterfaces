#include <memory>
#include <mutex>
#include <iostream>

#include "ITicker.h"
#include "IGPIO.h"

#include "FauxGPIO.h"
#include "SimpleTicker.h"
#include "DesktopPlatform.h"

#include "App_user.h"

int main() {
    DesktopPlatform platform;

    FauxGPIO gpio;
    SimpleTicker ticker(platform);

    App::run(ticker, gpio, platform);

    return 0;
}
