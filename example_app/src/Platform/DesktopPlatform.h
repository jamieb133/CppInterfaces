#pragma once

#include "IPlatform.h"

class DesktopPlatform : public IPlatform {
public:
    void run(MainFunction&& user_main_routine);
    void run(MainFunction& user_main_routine);
    void run();
};
