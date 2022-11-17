#include "IPlatform.h"
#include "ArduinoPlatform.h"
#include <Arduino.h>
#include <assert.h>

// Declared weak in Arduino.h to allow user redefinitions.
int atexit(void (* /*func*/ )()) { return 0; }

// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant() { }

void setupUSB() __attribute__((weak));
void setupUSB() { }

std::shared_ptr<ArduinoPlatform> ArduinoPlatform::_instance = nullptr;
bool ArduinoPlatform::_created = false;

std::shared_ptr<ArduinoPlatform> ArduinoPlatform::getInstance() {
    // Empty setup function if user forgets to create the instance.
    if (_instance == nullptr)
        createInstance([](){});
    
    return _instance;
}

void ArduinoPlatform::createInstance(std::function<void()>& user_setup) {
    // Prepare to die if already created...
    assert(!_created);
    _instance = std::shared_ptr<ArduinoPlatform>(new ArduinoPlatform(user_setup));
    _created = true;
}

void ArduinoPlatform::createInstance(std::function<void()> user_setup) {
    // Prepare to die if already created...
    assert(!_created);
    _instance = std::shared_ptr<ArduinoPlatform>(new ArduinoPlatform(user_setup));
    _created = true;
}

void ArduinoPlatform::createInstance() {
    // Prepare to die if already created...
    assert(!_created);
    _instance = std::shared_ptr<ArduinoPlatform>(new ArduinoPlatform());
    _created = true;
}

ArduinoPlatform::ArduinoPlatform(std::function<void()>& user_setup) {
    init();
    initVariant();
#if defined(USBCON)
    USBDevice.attach();
#endif
    Serial.begin(9600);
    user_setup();
}

ArduinoPlatform::ArduinoPlatform() {
    init();
    initVariant();
#if defined(USBCON)
    USBDevice.attach();
#endif
    Serial.begin(9600);
}

void ArduinoPlatform::run(std::function<void()>& user_main_routine) {
    while(true) {
        user_main_routine();
        if (serialEventRun) 
            serialEventRun();
    }
}

void ArduinoPlatform::run(std::function<void()>&& user_main_routine) {
    while(true) {
        user_main_routine();
        if (serialEventRun) 
            serialEventRun();
    }
}

void ArduinoPlatform::run() {
    while(true) {
        if (serialEventRun) 
            serialEventRun();
    }
}
