#pragma once

#include <stdint.h>

#include "Common.h"
#include "Timer.h"

DECLARE_SMARTPOINTER(LightFxBase);
class LightFxBase :
    public std::enable_shared_from_this<LightFxBase>,
    public ITimerCallback
{
public:
    LightFxBase() {}
    ~LightFxBase() {}

    void StartAnimation(uint16_t cycleTimeMs);

    void StopAnimation();



private:

    // Fired when the animation timer fires.
    void OnTimerTick(uint64_t elapsedTime);

    TimerUniquePtr m_animationTimer;
};
