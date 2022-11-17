#include "IGPIO.h"
#include <ArduinoSTL.h>

class ArduinoGPIO : public IGPIO<ArduinoGPIO> {
private:
    static std::shared_ptr<ArduinoGPIO> _instance; 
    static bool _created;
public:
    // GPIOs are hardware IO and thus are finite physical "things",
    // therefore we are defining its interface as a singleton here.
    static void createInstance();
    static std::shared_ptr<ArduinoGPIO> getInstance();
    ArduinoGPIO();

    virtual ~ArduinoGPIO() {}
    void set(uint8_t pinNumber, bool value);
    unsigned int numPins();
};
