#pragma once

#include "ITicker.h"
#include <memory>
#include <vector>
#include <queue>
#include <Arduino.h>

class ArduinoTicker : public ITicker<ArduinoTicker> {
public:
    static std::shared_ptr<ArduinoTicker> _instance;
    static bool _created;
    bool m_debugToggle;
    
    // Physical timer polls at 100Hz.
    struct CallbackInfo {
        uint32_t ticksPerPeriod, ticksRemaining;
        TickerCallback callback;
        CallbackInfo(int rate, 
                    TickerCallback cb) :
            ticksPerPeriod(static_cast<uint32_t>(1000.0f / static_cast<int>(1.0f / (static_cast<float>(rate) / 1000.0f)))),
            ticksRemaining(ticksPerPeriod),
            callback(cb)
        {}
        CallbackInfo() :
            ticksPerPeriod(0),
            ticksRemaining(0),
            callback([]() {})
        {}

        void operator() () {
            callback();
        }
    };
    
    CallbackInfo pendingCallback;
    bool m_pending;

public:
    static std::shared_ptr<ArduinoTicker> getInstance();
    static void createInstance();
    virtual ~ArduinoTicker() {}
    ArduinoTicker();

    // Interface method will be implemented.
    void attach(int rate, 
                TickerCallback callback);

    void stop();

    void debug(int i, TickerCallback cb) {

        while(1) {
            cb();
        }
    }

    bool decrementTick();
};
