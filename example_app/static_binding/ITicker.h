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
private:
    std::function<void(std::chrono::milliseconds, TickerCallback)> _attach;
    std::function<void(void)> _stop;

public:
    virtual ~ITicker() {}
    
    template <typename TickerImpl>
    ITicker(TickerImpl& impl) :
        _attach(std::bind(&TickerImpl::attach, &impl, std::placeholders::_1, std::placeholders::_2)), 
        _stop(std::bind(&TickerImpl::stop, &impl)) 
    {}

    void attach(std::chrono::milliseconds alarm_time,
                TickerCallback callback) {
        _attach(alarm_time, callback);
    }

    void stop() {
        _stop();
    }
};

// End of file.