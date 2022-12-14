#pragma once

#include "ITicker.h"
#include "IPlatform.h"

#include <atomic>
#include <memory>
#include <thread>
#include <vector>
#include <chrono>

class SimpleTicker : public ITicker<SimpleTicker> {
private:

    // Get instantaneous time since epoch.
    static inline std::chrono::milliseconds now() {
        return std::chrono::duration_cast<std::chrono::milliseconds>
                    (std::chrono::system_clock().now().time_since_epoch());
    }

    struct CallbackInfo {
        TickerCallback func;
        std::chrono::milliseconds time, period;
        void operator() () {
            func();
            time = now() + period;
        }
        CallbackInfo(TickerCallback cb, 
                        std::chrono::milliseconds t) : 
            func(cb), 
            time(now() + t), 
            period(t) {}
    };

    std::shared_ptr<std::thread> m_timePollingThread;
    std::atomic_bool m_terminate;
    std::vector<CallbackInfo> m_callbacks;
    IPlatform& m_platform;

public:
    SimpleTicker(IPlatform& targetPlatform);
    virtual ~SimpleTicker();

    // Interface method will be implemented.
    void attach(int rate, 
                TickerCallback callback);
    void stop();

    void wait(int millis);
};
