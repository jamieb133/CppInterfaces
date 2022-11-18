#pragma once

#include "ITicker.h"
#include "IGPIO.h"
#include "IPlatform.h"

namespace App {
    // User implements application code here.
    template <class Ticker, class GPIO>
    void run(Ticker& ticker, 
                GPIO& gpio,
                IPlatform& platform);
}
