#include <iostream>
#include "FauxGPIO.h"

using namespace std;

FauxGPIO::FauxGPIO() {
    for (auto& p : m_pinArray)
        p = 0;
}

void FauxGPIO::set(uint8_t pinNumber, bool value) {
    if (pinNumber < m_pinArray.size() - 1)
        m_pinArray[pinNumber] = value;

    // Dump pins.
    cout << "FauxGPIO pin array (p" << std::to_string(pinNumber)
                << "=" << value <<  ") -> {";
    for (auto& p : m_pinArray) 
        cout << " (" << p << ")";
    cout << " }" << std::endl;
}

unsigned int FauxGPIO::numPins() {
    return static_cast<uint8_t>(m_pinArray.size());
}

