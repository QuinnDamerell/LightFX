#include <chrono>
#include <ratio>
#include "Timer.h"

bool Timer::Start()
{
    std::lock_guard<std::mutex> lock(m_threadMutex);

    if (m_isActive)
    {
        return false;
    }

    m_isActive = true;
    m_timerThread.reset(new std::thread(std::bind(&Timer::TimerLoop, this)));
    return true;
}

void Timer::Stop()
{
    m_isActive = false;
}

void Timer::TimerLoop()
{
    using namespace std::chrono;

    while (m_isActive)
    {
        // Grab the time since the last tick.
        high_resolution_clock::time_point startTime = high_resolution_clock::now();
        high_resolution_clock::duration timeSinceRun = startTime - m_lastTickTime;
        m_lastTickTime = startTime;
        auto timeSinceRunMs = duration_cast<milliseconds>(timeSinceRun);

        // Try to lock the callback
        auto callback = m_callback.lock();
        if (callback)
        {
            callback->OnTimerTick(timeSinceRunMs.count());
        }

        // Sleep for the correct amount of time
        milliseconds sleepTime = milliseconds(m_cycleTime) - duration_cast<milliseconds>(high_resolution_clock::now() - startTime);
        std::this_thread::sleep_for(sleepTime);
    }
}
