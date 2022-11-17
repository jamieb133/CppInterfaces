#include "ArduinoTicker.h"
#include "ITicker.h"
#include <Arduino.h>

// Prescaler = 65536-16/256/frequency
const static uint16_t PRELOAD_2HZ = 34285;
const static uint16_t PRELOAD_50HZ = 0xfb1e;  //1111101100011110
const static uint16_t PRELOAD_100HZ = 0xfd8f; //1111110110001111
const static uint16_t PRELOAD_1KHZ = 0xffc1; //1111110110001111

const static uint16_t PRELOAD = PRELOAD_1KHZ;

const static int MAX_SIZE = 5;

std::shared_ptr<ArduinoTicker> ArduinoTicker::_instance = nullptr;
bool ArduinoTicker::_created = false;

static bool toggle = true;

static ArduinoTicker* pTicker = nullptr;

ISR(TIMER1_OVF_vect) {
    pTicker->decrementTick();
    TCNT1 = PRELOAD;
}

ArduinoTicker::ArduinoTicker() : 
    m_pending(false),
    m_debugToggle(false)
{
    // Start of critical section.
    noInterrupts(); // disable all interrupts

    // Init timer compare registers.
    TCCR1A = 0;
    TCCR1B = 0; 

    TCNT1 = PRELOAD;        // Preload timer.
    TCCR1B |= (1 << CS12);  // 256 prescaler.
    TIMSK1 |= (1 << TOIE1); // Enable timer overflow interrupt (ISR above).
 
    // Re-enable all interrupts.
    interrupts();

    std::shared_ptr<CallbackInfo> cb = std::shared_ptr<CallbackInfo>(new CallbackInfo(0xffff, [](){}));
    pendingCallback = *cb;
}

std::shared_ptr<ArduinoTicker> ArduinoTicker::getInstance() {
    if (!_created) 
        createInstance();
    
    return _instance;
}

void ArduinoTicker::createInstance() {
    if (!_created) {
        std::shared_ptr<ArduinoTicker>(new ArduinoTicker());
    }
    _created = true;
}

void ArduinoTicker::attach(int rate, 
                            TickerCallback callback) 
{
    pTicker = this;
    CallbackInfo cb(rate, callback);
    pendingCallback = cb;
    m_pending = true;
}


void ArduinoTicker::stop() {

}

bool ArduinoTicker::decrementTick() {
    static bool called = true;

#ifdef GPIO_DEBUG
    digitalWrite(13U, static_cast<uint8_t>(toggle));
    toggle = !toggle;
#endif 

    if (pendingCallback.ticksRemaining == 0) {
#ifdef GPIO_DEBUG
        digitalWrite(12U, static_cast<uint8_t>(called));
        called = !called;
#endif
        pendingCallback.ticksRemaining = pendingCallback.ticksPerPeriod;
        pendingCallback.callback();
        return true;
    }
    else {
        pendingCallback.ticksRemaining--;
        return false;
    }
}
