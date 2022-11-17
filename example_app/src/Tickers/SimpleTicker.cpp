#include "SimpleTicker.h"

SimpleTicker::SimpleTicker() {
    std::function<void()> f = [this]() {
        while(!m_terminate) {
            // Poll the time.
            if (!m_callbacks.empty()) {
                for (auto& callback : m_callbacks) {
                    if(now() >= callback.time) 
                        callback();
                }
            }
            else 
                std::this_thread::yield();
        }
    };

    m_timePollingThread = std::make_shared<std::thread>([this]() {
        while(!m_terminate) {
            // Poll the time.
            if (!m_callbacks.empty()) {
                for (auto& callback : m_callbacks) {
                    if(now() >= callback.time) 
                        callback();
                }
            }
            else 
                std::this_thread::yield();
        }
    });
}

SimpleTicker::~SimpleTicker() {
    m_terminate = true;
    if (m_timePollingThread->joinable())
        m_timePollingThread->join();
}

void SimpleTicker::attach(int rate, 
                            TickerCallback callback) 
{
    m_callbacks.push_back(CallbackInfo(callback, std::chrono::milliseconds(rate)));
}

void SimpleTicker::stop() {
    m_terminate = true;
    m_timePollingThread->join();
}
