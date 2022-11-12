/**
 * @file IGPIO.h
 * @brief 
 * 
 */

#pragma once 

#include <functional>

class IGPIO {
private:
    std::function<void(int, bool)> _set;
    std::function<int(void)> _numPins;

public:
    virtual ~IGPIO() {}

    template <typename GPIOImpl>
    IGPIO(GPIOImpl& impl) : 
        _set(std::bind(&GPIOImpl::set, &impl, std::placeholders::_1, std::placeholders::_2)),
        _numPins(std::bind(&GPIOImpl::numPins, &impl))
    {}

    void set(int pinNumber, bool value) {
        _set(pinNumber, value);
    }

    int numPins() {
        return _numPins();
    }
};
