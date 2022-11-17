#include "ITicker.h"
#include "IGPIO.h"
#include "IPlatform.h"

class TestRunner {
public:
    template <typename Ticker, typename GPIO, typename Platform>
    static void runTestCase(Ticker&& ticker, 
                            GPIO&& gpio, 
                            Platform&& platform) 
    {
        // ticker->attach(100, [&]() {
        //     static bool toggle = true;
        //     static uint8_t nextPin = 0;

        //     toggle = (toggle && nextPin == gpio->numPins()) ? !toggle : toggle;
        //     toggle = (!toggle && nextPin == 0) ? !toggle : toggle;

        //     nextPin = (toggle) ? nextPin + 1 : nextPin - 1;

        //     gpio->set(nextPin, toggle);
        // });

        platform.run();
    }
};
