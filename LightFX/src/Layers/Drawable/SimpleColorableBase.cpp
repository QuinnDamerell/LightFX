#include "Layers/Drawable/SimpleColorableBase.h"

using namespace LightFx;
using namespace LightFx::Layers::Drawable;

Pixel SimpleColorableBase::OnColor(uint64_t tickCount, milliseconds elapsedTime)
{
    // The default alpha
    double alphaValue = 1.0;

    // If we have a colorable ask it for color
    if (m_fadable)
    {
        alphaValue = m_fadable->OnFade(tickCount, elapsedTime);
    }

    // Now call the base class to draw
    return GetColor(tickCount, elapsedTime, alphaValue);
}