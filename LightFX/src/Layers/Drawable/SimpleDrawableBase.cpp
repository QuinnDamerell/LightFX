#include "Layers/Drawable/SimpleDrawableBase.h"

using namespace LightFx;
using namespace LightFx::Layers::Drawable;

void SimpleDrawableBase::OnDraw(uint64_t tickCount, milliseconds elapsedTime, BitmapPtr buffer)
{
    // The default draw color
    Pixel drawColor(1, 1, 1, 1);

    // If we have a colorable ask it for color
    if (m_colorable)
    {
        drawColor = m_colorable->OnColor(tickCount, elapsedTime);
    }

    // Now call the base class to draw
    DrawPixels(tickCount, elapsedTime, buffer, drawColor);
}