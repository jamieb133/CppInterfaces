#include "App.h"

template <class Ticker, class GPIO>
void App::run(Ticker& ticker,
            GPIO& gpio,
            IPlatform& platform) 
{

    bool toggle = false;
    bool started = false;
    int count = 0;
    const int rate = 500; // ms
    const int duration = 10; // s
    const int totalIters = duration * 1000 / rate;

    std::cout << "\n\n\n\n\n\n\n\n\n\n // --- Entered App::run() --- //\n";

    // Toggle pin 7 (LED on Uno) for 5 seconds and then shutdown
    ticker.attach(rate, [&]() {
        // Start when we're ready.
        if (!started)
            return;

        gpio.set(7, toggle);
        toggle = !toggle;

        if (count++ == totalIters)
            platform.shutdown();
    });

    // Let's make the user responsible for running the platform.
    platform.run([&]() {
        // This is our main busy loop, just poll a value.
        static int nextCount = count + 2;
        started = true;
        if (count == nextCount) {
            nextCount = count + 2;
            std::cout << "Reading count value in busy loop (" 
                        << count 
                        << " / " 
                        << totalIters 
                        << ")\n";
        }
    });
}
