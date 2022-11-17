/**
 * @file ITicker.h
 * @brief Provides definition of a Ticker interface, 
 *          a generic peridic callback provider.
 * 
 */

#pragma once

#include <functional>
#include <vector>

using TickerCallback = std::function<void()>;
using TickerCallbackPtr = std::shared_ptr<TickerCallback>;

template <typename TickerImpl>
class ITicker {
public:
    virtual ~ITicker<TickerImpl>() {}
    void attach(int alarm_time_ms,
                            TickerCallback& callback) {
        static_cast<TickerImpl>(this)->attach(alarm_time_ms, callback);
    };

    void stop() {
        static_cast<TickerImpl>(this)->stop();
    }
                    
};

// End of file.
