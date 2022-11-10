#pragma once

#include <memory>
#include <vector>
#include <queue>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "ITicker.h"

class BoostTicker {
private:
    struct CallbackInfo {
        TickerCallback callback;
        std::chrono::milliseconds rate;
    };

    std::atomic_bool m_terminate;
    std::shared_ptr<std::thread> m_ioThread;
    boost::shared_ptr<boost::asio::io_service> m_io;
    boost::shared_ptr<boost::thread> m_thread;
    std::queue<CallbackInfo> m_callbacks;

public:
    BoostTicker();
    virtual ~BoostTicker();

    // Interface method will be implemented.
    void attach(std::chrono::milliseconds rate, 
                TickerCallback callback);
    void stop();
};
