#include "ArduinoTicker.h"
#include "ITicker.h"
#include <Arduino.h>
#include <assert.h>

// Prescaler = 65536-16/256/frequency
const static uint16_t PRELOAD_2HZ = 34285;
const static uint16_t PRELOAD_50HZ = 0xfb1e;  //1111101100011110
const static uint16_t PRELOAD_100HZ = 0xfd8f; //1111110110001111
const static uint16_t PRELOAD_1KHZ = 0xffc1; //1111110110001111

const static uint16_t PRELOAD = PRELOAD_1KHZ;

static bool toggle = true;

static std::shared_ptr<ArduinoTicker> _instance = nullptr;
static bool _created = false;

extern void debugLoop();

ISR(TIMER1_OVF_vect) {
    if (_instance.get() != nullptr)
        _instance->decrementTick();
    TCNT1 = PRELOAD;
}

ArduinoTicker::ArduinoTicker(IPlatform& platform) : 
    m_debugToggle(false),
    m_platform(platform)
{
    pendingCallback = std::shared_ptr<CallbackInfo>(new CallbackInfo(0xffff, [](){}));
}

std::shared_ptr<ArduinoTicker> ArduinoTicker::getInstance() {
    assert(_created);
    return _instance;
}

void ArduinoTicker::createInstance(IPlatform& platform) {
    if (!_created) {
        // Start of critical section.
        noInterrupts(); // disable all interrupts

        // Init timer compare registers.
        TCCR1A = 0;
        TCCR1B = 0; 

        TCNT1 = PRELOAD;        // Preload timer.
        TCCR1B |= (1 << CS12);  // 256 prescaler.
        TIMSK1 |= (1 << TOIE1); // Enable timer overflow interrupt (ISR above).
    
        _instance = std::shared_ptr<ArduinoTicker>(new ArduinoTicker(platform));
        _created = true;

        // Re-enable all interrupts.
        interrupts();
    }
}

void ArduinoTicker::attach(int rate, 
                            TickerCallback callback) 
{
    pendingCallback = std::shared_ptr<CallbackInfo>(new CallbackInfo(rate, callback));
}

void ArduinoTicker::stop() {

}

bool ArduinoTicker::decrementTick() {
    static bool called = true;

    if (pendingCallback->ticksRemaining == 0) {
        // Notify platform that there is a pending callback and
        // reset the tick value.
        m_platform.defer(pendingCallback->callback);
        pendingCallback->ticksRemaining = pendingCallback->ticksPerPeriod;

        return true;
    }
    else {
        pendingCallback->ticksRemaining--;
        return false;
    }
}

void ArduinoTicker::wait(int millis) {
    delay(millis);
}
