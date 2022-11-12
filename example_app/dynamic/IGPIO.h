/**
 * @file IGPIO.h
 * @brief 
 * 
 */

#pragma once 

class IGPIO {
public:
    virtual ~IGPIO() {}
    virtual void set(int pinNumber, bool value) = 0;
    virtual int numPins() = 0;
};
