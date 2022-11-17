#pragma once

#include "IPlatform.h"
#include <functional>
#include <memory>

class ArduinoPlatform : public IPlatform{
public:
    ArduinoPlatform(std::function<void()>& user_setup); 
    ArduinoPlatform(); 
    static std::shared_ptr<ArduinoPlatform> _instance;
    static bool _created;

public:
    static std::shared_ptr<ArduinoPlatform> getInstance();
    static void createInstance(std::function<void()>& user_setup);
    static void createInstance(std::function<void()> user_setup);
    static void createInstance();
    void run(std::function<void()>& user_main);
    void run(std::function<void()>&& user_main);
    void run();
};

using ArduinoPlatformPtr = std::shared_ptr<ArduinoPlatform>;
