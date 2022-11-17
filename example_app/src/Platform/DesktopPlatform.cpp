#include "DesktopPlatform.h"
#include <thread>

// lvalue
void DesktopPlatform::run(MainFunction& user_main_function) {
    while(true) {
        user_main_function();
        std::this_thread::yield();
    }
}

// rvalue
void DesktopPlatform::run(MainFunction&& user_main_function) {
    while(true) {
        user_main_function();
        std::this_thread::yield();
    }
}

// No user function supplied, just do busy loop.
void DesktopPlatform::run() {
    while(true) 
        std::this_thread::yield();
}
