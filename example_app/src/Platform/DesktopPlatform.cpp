#include "DesktopPlatform.h"
#include <thread>

// lvalue
void DesktopPlatform::run(MainFunction& user_main_function) {
    m_running = true;
    while(m_running) {
        user_main_function();

        std::unique_lock<std::mutex> lock(m_mutex, std::defer_lock);
        if (lock.try_lock()
            && !m_deferredQueue.empty()) {
                auto cb = m_deferredQueue.front();
                cb();
                m_deferredQueue.pop();
            } 
        
        std::this_thread::yield();
    }
}

// rvalue
void DesktopPlatform::run(MainFunction&& user_main_function) {
    run(user_main_function);
}

// No user function supplied, just do busy loop.
void DesktopPlatform::run() {
    run([](){});
}
