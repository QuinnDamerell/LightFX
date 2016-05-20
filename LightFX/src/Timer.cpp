#include <chrono>
#include <ratio>

#include "Timer.h"

using namespace LightFx;

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

    // Set the time.
    m_lastTickTime = high_resolution_clock::now();

    while (m_isActive)
    {
        // Grab the time since the last tick.
        time_point startTime = high_resolution_clock::now();
        duration timeSinceRun = startTime - m_lastTickTime;
        m_lastTickTime = startTime;
        auto timeSinceRunMs = duration_cast<milliseconds>(timeSinceRun);

        // Try to lock the callback
        auto callback = m_callback.lock();
        if (callback)
        {
            callback->OnTimerTick(timeSinceRunMs);
        }

        // Sleep for the correct amount of time
        milliseconds sleepTime = m_cycleTime - duration_cast<milliseconds>(high_resolution_clock::now() - startTime);
        std::this_thread::sleep_for(sleepTime);
    }
}
