#include <chrono>
#include <iostream>

#include "ConstantRateDriver.h"

using namespace LightFx;

// Starts the timer
void ConstantRateDriver::Start(milliseconds cycleTime)
{
    m_callbackCount = 0;
    ConstantRateDriverPtr thisss = GetSharedPtr<ConstantRateDriver>();
    m_timer.reset(new Timer(std::dynamic_pointer_cast<ITimerCallback>(shared_from_this()), cycleTime));
    m_timer->Start();
}

// Stops the timer
void ConstantRateDriver::Stop()
{
    if (m_timer)
    {
        m_timer->Stop();
    }
}

// Adds a new thing to drive       
void ConstantRateDriver::AddDriveable(IDrivableWeakPtr callback)
{
    // Add the new drivable to the list
    std::lock_guard<std::mutex> lock(m_callbacksLock);
    m_callbacks.insert(m_callbacks.end(), callback);
}

// Fired when the timer ticks
void ConstantRateDriver::OnTimerTick(milliseconds elapsedTime)
{
    // Lock the list and fire the callbacks
    std::lock_guard<std::mutex> lock(m_callbacksLock);

#ifdef PRINT_RENDER_TIME
    time_point now = high_res_clock::now();
#endif

    for (auto callback : m_callbacks)
    {
        if (auto callbackStrong = callback.lock())
        {
            callbackStrong->OnTick(m_callbackCount, elapsedTime);
        }
    }

#ifdef PRINT_RENDER_TIME
    time_point end = high_res_clock::now();
    duration diff = end - now;
    milliseconds diffMs = std::chrono::duration_cast<milliseconds>(diff);
    std::cout << "Render Time " << diffMs.count() << "ms\r\n";
#endif

    // Update the count
    m_callbackCount++;

    // todo clean up list
}