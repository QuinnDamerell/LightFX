#include "ConstantRateDriver.h"

using namespace LightFx;

// Starts the timer
void ConstantRateDriver::Start(uint64_t cycleTimeMs)
{
    m_callbackCount = 0;
    ConstantRateDriverPtr thisss = shared_from_this();
    m_timer.reset(new Timer(std::dynamic_pointer_cast<ITimerCallback>(shared_from_this()), cycleTimeMs));
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
    m_callbacks.insert(m_callbacks.begin(), callback);
}



// Fired when the timer ticks
void ConstantRateDriver::OnTimerTick(uint64_t elapsedTime)
{
    // Lock the list and fire the callbacks
    std::lock_guard<std::mutex> lock(m_callbacksLock);

    for (auto callback : m_callbacks)
    {
        if (auto callbackStrong = callback.lock())
        {
            callbackStrong->OnTick(m_callbackCount, elapsedTime);
        }
    }

    // Update the count
    m_callbackCount++;

    // todo clean up list
}