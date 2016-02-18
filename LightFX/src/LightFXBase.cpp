
#include <iostream>
#include "LightFXBase.h"

void LightFxBase::StartAnimation(uint16_t cycleTimeMs)
{
    // Setup and start the timer.
    m_animationTimer.reset(new Timer(shared_from_this(), cycleTimeMs));
    m_animationTimer->Start();
}

void LightFxBase::StopAnimation()
{
    m_animationTimer->Stop();
}

void LightFxBase::OnTimerTick(uint64_t elapsedTime)
{
    std::cout << elapsedTime;
}

