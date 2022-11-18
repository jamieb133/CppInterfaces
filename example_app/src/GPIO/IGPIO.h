/**
 * @file IGPIO.h
 * @brief Interface to a generic GPIO.
 * 
 */

#pragma once 

#include <stdint.h>

template <typename GPIOImpl>
class IGPIO {
public:
    virtual ~IGPIO() {}
    
    void set(uint8_t pinNumber, bool value) { 
        static_cast<GPIOImpl>(this)->set(pinNumber, value); 
    }
    
    unsigned int numPins() { 
        return static_cast<GPIOImpl>(this)->numPins(); 
    }
};
