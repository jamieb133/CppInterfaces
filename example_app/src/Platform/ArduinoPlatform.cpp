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

static std::shared_ptr<ArduinoPlatform> _instance = nullptr;
static bool _created = false;

extern void debugLoop();

std::shared_ptr<ArduinoPlatform> ArduinoPlatform::getInstance() {
    assert(_created);    
    return _instance;
}

void ArduinoPlatform::createInstance(std::function<void()>& user_setup) {
    // Prepare to die if already created...
    if (!_created);
        _instance = std::shared_ptr<ArduinoPlatform>(new ArduinoPlatform(user_setup));
    _created = true;
}

void ArduinoPlatform::createInstance(std::function<void()> user_setup) {
    if (!_created);
        _instance = std::shared_ptr<ArduinoPlatform>(new ArduinoPlatform(user_setup));
    _created = true;
}

void ArduinoPlatform::createInstance() {
    // Prepare to die if already created...
    if (!_created);
        _instance = std::shared_ptr<ArduinoPlatform>(new ArduinoPlatform());
    _created = true;
}

ArduinoPlatform::ArduinoPlatform(std::function<void()>& user_setup) :
    m_running(false)
{
    init();
    initVariant();
#if defined(USBCON)
    USBDevice.attach();
#endif
    Serial.begin(9600);
    user_setup();
}

ArduinoPlatform::ArduinoPlatform() :
    m_running(false)
{
    init();
    initVariant();
#if defined(USBCON)
    USBDevice.attach();
#endif
    Serial.begin(9600);
}

void ArduinoPlatform::run(std::function<void()>& user_main_routine) {
    m_running = true;

    while(m_running) {
        user_main_routine();

        if (m_deferredQueue.size() > 0) {
            auto cb = m_deferredQueue.front();
            cb();
            m_deferredQueue.pop();
        }

        if (serialEventRun) 
            serialEventRun();
    }

    std::cout << "Arduino platform finished\n";
}

void ArduinoPlatform::run(std::function<void()>&& user_main_routine) {
    run(user_main_routine);    
}

void ArduinoPlatform::run() {

    run([](){});
}

void ArduinoPlatform::defer(std::function<void()> f) {
    if (m_deferredQueue.size() < MAX_QUEUE_SIZE)
        m_deferredQueue.push(f);
}

void ArduinoPlatform::shutdown() {
    m_running = false;
}
