#pragma once

#include "IPlatform.h"
#include <queue>
#include <mutex>
#include <atomic>
#include <condition_variable>

class DesktopPlatform : public IPlatform {
private:
    std::mutex m_mutex;
    std::condition_variable m_cv;
    std::atomic_bool m_running;
    std::queue<std::function<void()>> m_deferredQueue;
public:
    void run(MainFunction&& user_main_routine);
    void run(MainFunction& user_main_routine);
    void run();

    void defer(std::function<void()> f) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_deferredQueue.push(f);
        m_cv.notify_one();
    }

    void shutdown() {
        m_running = false;
    }
};
