#include <memory>
#include <functional>
#include <thread>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind/bind.hpp>
#include <boost/thread.hpp>

#include "BoostTicker.h"

static void boostThreadWrapper(std::function<void()> func) {
    func();
}

// Pseudo-recursive timer callback.
static void callbackWrapper(const boost::system::error_code& e, 
                            BoostTicker* ticker,
                            TickerCallback callback, 
                            std::chrono::milliseconds period) {
    callback();
    ticker->attach(period, std::bind(callback));
}

BoostTicker::BoostTicker() : 
    m_terminate(false),
    m_io(boost::make_shared<boost::asio::io_service>()) 
{
    m_thread = boost::make_shared<boost::thread> ([&]() {
        while(!m_terminate) {
            if(!m_callbacks.empty()) {
                auto rate = m_callbacks.front().rate;
                auto callback = m_callbacks.front().callback;

                m_io->reset();
                boost::asio::deadline_timer timer(*m_io, boost::posix_time::milliseconds(rate.count()));
                timer.async_wait(boost::bind(&callbackWrapper, 
                                                boost::placeholders::_1, 
                                                this,
                                                callback,
                                                rate));
                m_callbacks.pop();
                m_io->run();
            }
        }

        m_io->stop();
    });
}

void BoostTicker::attach(std::chrono::milliseconds rate, 
            TickerCallback callback) {
    m_callbacks.push({
        .callback = callback,
        .rate = rate
    });
}

void BoostTicker::stop() {
    m_terminate = true;
}

BoostTicker::~BoostTicker() {
    m_terminate = true;
    if (m_thread->joinable())
        m_thread->join();
}