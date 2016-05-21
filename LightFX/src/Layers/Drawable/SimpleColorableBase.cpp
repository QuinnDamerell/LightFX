#include "Layers/Drawable/SimpleColorableBase.h"

using namespace LightFx;
using namespace LightFx::Layers::Drawable;

LightColor SimpleColorableBase::OnColor(uint64_t tickCount, milliseconds elapsedTime)
{
    // The default intensity
    double intensityValue = 1.0;

    // If we have a intensitable ask it for color
    if (m_intensitable)
    {
        intensityValue = m_intensitable->OnIntensity(tickCount, elapsedTime);
    }

    // Now call the base class to draw
    return GetColor(tickCount, elapsedTime, intensityValue);
}