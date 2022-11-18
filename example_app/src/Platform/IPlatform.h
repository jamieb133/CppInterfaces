#pragma once

#include <functional>

using MainFunction = std::function<void()>;

class IPlatform {
public:
    // One of the run functions should start the system event loop.
    virtual void run(MainFunction& user_main_routine) = 0;
    virtual void run(MainFunction&& user_main_routine) = 0;
    virtual void run() = 0;

    virtual void shutdown() = 0;

    // This function should push a pending event to the platform's
    // event queue to be executed at some future point in the event
    // loop.
    virtual void defer(std::function<void()>) = 0;
};
