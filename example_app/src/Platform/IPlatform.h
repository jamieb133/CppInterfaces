#pragma once

#include <functional>

using MainFunction = std::function<void()>;

class IPlatform {
public:
    virtual void run(MainFunction& user_main_routine) = 0;
    virtual void run(MainFunction&& user_main_routine) = 0;
    virtual void run() = 0;
};
