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

class ITicker {
public:
    virtual ~ITicker() {}
    virtual void attach(std::chrono::milliseconds alarm_time,
                            TickerCallback callback) = 0;
    virtual void stop() = 0;
                       
};

// End of file.