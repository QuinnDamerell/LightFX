#include "Colorables/RainbowColorer.h"

using namespace LightFx;
using namespace LightFx::Colorables;

Pixel RainbowColorer::OnColorSelf(uint64_t tick, milliseconds elapsedTime)
{
    // Update our time remaining. 
    m_cycleTimeRemaining -= elapsedTime;
    if (m_cycleTimeRemaining.count() < 0)
    {
        m_cycleTimeRemaining = m_fullCycleTime;
    }

    // Figure out how far we are
    double progress = static_cast<double>(m_cycleTimeRemaining.count()) / static_cast<double>(m_fullCycleTime.count());

    // Set the color    
    return GetRainbowColor(progress);
}