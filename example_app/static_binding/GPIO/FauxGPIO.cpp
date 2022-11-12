#include <iostream>
#include "FauxGPIO.h"

std::shared_ptr<FauxGPIO> FauxGPIO::_instance = nullptr;

//std::array<bool, NUM_OF_PINS> m_pinArray; 
FauxGPIO::FauxGPIO() {}

std::shared_ptr<FauxGPIO> FauxGPIO::getInstance() {
    if(_instance == nullptr) 
        _instance = std::shared_ptr<FauxGPIO>(new FauxGPIO());
    
    return _instance;
}

void FauxGPIO::set(int pinNumber, bool value) {
    if (pinNumber < m_pinArray.size() - 1)
        m_pinArray[pinNumber] = value;

    // Dump pins.
    std::cout << "FauxGPIO pin array (p" << pinNumber
                << "=" << value <<  ") -> {";
    for (auto& p : m_pinArray) 
        std::cout << " (" << p << ")";
    std::cout << " }" << std::endl;
}

int FauxGPIO::numPins() {
    return static_cast<int>(m_pinArray.size());
}

void FauxGPIO::dumpPins() {
    std::cout << "FauxGPIO pin array -> {";
    for (auto& p : m_pinArray) 
        std::cout << " (" << p << ")";
    std::cout << " }" << std::endl;
}
