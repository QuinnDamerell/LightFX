#pragma once

#include <stdint.h>
#include <vector>

#include "Common.h"
#include "Timer.h"
#include "IDrivable.h"

namespace LightFx
{
    DECLARE_SMARTPOINTER(ConstantRateDriver);
    class ConstantRateDriver : 
        public ITimerCallback,
        public std::enable_shared_from_this<ConstantRateDriver>
    {

    public:
        ConstantRateDriver()
        { }

        // Starts the timer
        void Start(uint64_t cycleTimeMs);

        // Stops the timer
        void Stop();

        // Adds a new thing to drive       
        void AddDriveable(IDrivableWeakPtr callback);

    protected:

        // Fired when the timer ticks
        void OnTimerTick(uint64_t elapsedTime) override;

        // The list of callbacks
        std::mutex m_callbacksLock;
        std::vector<IDrivableWeakPtr> m_callbacks;

        // The timer logic
        TimerUniquePtr m_timer;
        uint64_t m_callbackCount;
    };
}
#pragma once
