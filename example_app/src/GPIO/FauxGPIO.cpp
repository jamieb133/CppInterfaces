#include <iostream>
#include "FauxGPIO.h"

#ifdef ARDUINO
#include <ArduinoSTL.h>
#endif

FauxGPIO::FauxGPIO() {
    for (auto& p : m_pinArray)
        p = 0;
}

void FauxGPIO::set(uint8_t pinNumber, bool value) {
    if (pinNumber < m_pinArray.size())
        m_pinArray[pinNumber] = value;

    // Dump pins.
    std::cout << "FauxGPIO pin array (p" << pinNumber
                << "=" << value <<  ") -> {";
    for (auto& p : m_pinArray) 
        std::cout << " (" << p << ")";
    std::cout << " }" << std::endl;
}

unsigned int FauxGPIO::numPins() {
    return static_cast<uint8_t>(m_pinArray.size());
}

