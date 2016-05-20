#pragma once

#include <chrono>
#include <memory>
#include <thread>
#include <mutex>

#include "Common.h"

namespace LightFx
{
    DECLARE_SMARTPOINTER(ITimerCallback);
    class ITimerCallback
    {
    public:
        virtual void OnTimerTick(milliseconds elapsedTime) = 0;
    };

    DECLARE_SMARTPOINTER(Timer);
    class Timer
    {
    public:
        Timer(ITimerCallbackWeakPtr callback, milliseconds cycleTimeMs) :
            m_callback(callback),
            m_isActive(false),
            m_cycleTime(cycleTimeMs)
        {}

        ~Timer()
        {
            m_isActive = false;
            m_timerThread->join();
        }

        bool Start();
        void Stop();

    private:

        void TimerLoop();

        ITimerCallbackWeakPtr m_callback;
        std::unique_ptr<std::thread> m_timerThread;
        bool m_isActive;
        std::mutex m_threadMutex;
        milliseconds m_cycleTime;
        std::chrono::high_resolution_clock::time_point m_lastTickTime;
    };
}
