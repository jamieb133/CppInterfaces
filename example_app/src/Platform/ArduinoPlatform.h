#pragma once

#include "IPlatform.h"
#include <functional>
#include <memory>
#include <queue>

class ArduinoPlatform : public IPlatform{
public:
    ArduinoPlatform(std::function<void()>& user_setup); 
    ArduinoPlatform(); 
    std::queue<std::function<void()>> m_deferredQueue;
    std::queue<int> m_notifications;
    bool m_running;
    const int MAX_QUEUE_SIZE = 10;

public:
    static std::shared_ptr<ArduinoPlatform> getInstance();
    static void createInstance(std::function<void()>& user_setup);
    static void createInstance(std::function<void()> user_setup);
    static void createInstance();
    void run(std::function<void()>& user_main);
    void run(std::function<void()>&& user_main);
    void run();
    void defer(std::function<void()> event);
    void shutdown();
};

using ArduinoPlatformPtr = std::shared_ptr<ArduinoPlatform>;
