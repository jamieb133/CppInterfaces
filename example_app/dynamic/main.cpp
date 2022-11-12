#include <atomic>
#include <memory>
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

#include "ITicker.h"
#include "IGPIO.h"

#include "FauxGPIO.h"
#include "SimpleTicker.h"
#include "BoostTicker.h"

static std::mutex s_mutex;

void runBlinkyExample(std::shared_ptr<ITicker> ticker,
                        std::shared_ptr<IGPIO> gpio,
                        std::chrono::milliseconds period) {
    
    // Blink all LEDs once and then exit.
    std::atomic_uint32_t remainingPins = gpio->numPins();
    bool toggle = true;

    ticker->attach(period, [&]() { 
        std::unique_lock<std::mutex> lock(s_mutex);
        if (remainingPins > 0) {
            gpio->set(remainingPins - 1, toggle);
            toggle = !toggle;
            if (toggle)
                remainingPins--;
        }
    });

    // Wait until all LEDs have blinked.
    while(remainingPins > 0) 
        std::this_thread::yield();
    
    ticker->stop();

    std::unique_lock<std::mutex> lock(s_mutex);
    std::cout << "Finished\n";
}

int main() {
    std::shared_ptr<ITicker> ticker;
    std::shared_ptr<IGPIO> gpio;

    std::cout << "// --- DYNAMIC EXAMPLE (SimpleTicker + FauxGPIO) --- //\n";
    ticker = std::make_shared<SimpleTicker>();
    gpio = FauxGPIO::getInstance();
    runBlinkyExample(ticker, gpio, std::chrono::milliseconds(100));

    std::cout << "\n// --- DYNAMIC EXAMPLE (BoostTicker + FauxGPIO) --- //\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    ticker = std::make_shared<BoostTicker>();
    gpio = FauxGPIO::getInstance();
    runBlinkyExample(ticker, gpio, std::chrono::milliseconds(100));

#ifdef MBED
    std::cout << "// --- DYNAMIC EXAMPLE (MbedTicker + MbedGPIO) --- //\n";
    std::shared_ptr<ITicker> ticker = std::make_shared<SimpleTicker>();
    std::shared_ptr<IGPIO> gpio = std::make_shared<FauxGPIO>();
    runBlinkyExample(ticker, gpio, std::chrono::milliseconds(500));
#endif

    return 0;
}
