/**
 * @file ITicker.h
 * @brief Provides definition of a Ticker interface, 
 *          a generic peridic callback provider.
 * 
 */

#pragma once

#include <functional>
#include <chrono>

using TickerCallback = std::function<void()>;

template <typename TickerImpl>
class ITicker {
public:
    ~ITicker() {}
    
    void attach(std::chrono::milliseconds alarm_time,
                            TickerCallback callback) {
        static_cast<TickerImpl*>(this)->attach(alarm_time, callback);
    }
    
    void stop() { 
        static_cast<TickerImpl>(this)->stop(); 
    }
};

// End of file.