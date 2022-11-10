/**
 * @file IGPIO.h
 * @brief 
 * 
 */

#pragma once 

template<typename GPIOImpl>
class IGPIO {
public:
    virtual ~IGPIO() {}
    void set(int pinNumber, bool value) { static_cast<GPIOImpl*>(this)->set(pinNumber, value); }
    int numPins() { return static_cast<GPIOImpl*>(this)->numPins(); }
};
