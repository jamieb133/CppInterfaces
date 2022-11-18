#pragma once

#include "ITicker.h"
#include "IPlatform.h"
#include <memory>
#include <vector>
#include <queue>
#include <Arduino.h>

class ArduinoTicker : public ITicker<ArduinoTicker> {
public:
    bool m_debugToggle;
    IPlatform& m_platform;
    
    // Physical timer polls at 100Hz.
    struct CallbackInfo {
        uint32_t ticksPerPeriod, ticksRemaining;
        TickerCallback callback;
        CallbackInfo(const CallbackInfo& other) :
            ticksPerPeriod(other.ticksPerPeriod),
            ticksRemaining(other.ticksRemaining),
            callback(other.callback)
        {}
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
        void operator= (const CallbackInfo& other) {
            ticksPerPeriod = other.ticksPerPeriod;
            ticksRemaining = other.ticksRemaining;
            callback = other.callback;
        }
        void operator() () {
            callback();
        }
    };

    // struct CallbackInfo {
    //     uint32_t ticksPerPeriod, ticksRemaining;
    //     TickerCallback callback = [](){};
    // };
    
    std::shared_ptr<CallbackInfo> pendingCallback;
    bool m_pending;

public:
    static std::shared_ptr<ArduinoTicker> getInstance();
    static void createInstance(IPlatform&);
    virtual ~ArduinoTicker() {}
    ArduinoTicker(IPlatform& targetPlatform);

    // Interface method will be implemented.
    void attach(int rate, 
                TickerCallback callback);

    void stop();

    bool decrementTick();

    void wait(int);

};
