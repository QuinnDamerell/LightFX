#include "Colorables/CrossfadeColorer.h"

using namespace LightFx;
using namespace LightFx::Colorables;

Pixel CrossfadeColorer::OnColorSelf(uint64_t tick, milliseconds elapsedTime)
{
    // Interpolate the color and return it 
    return InterpolateColor(m_fromColor, m_toColor);
}

// Returns an interpolated value between from and to based on progress.
Pixel CrossfadeColorer::InterpolateColor(Pixel from, Pixel to)
{
    double progress = GetProgress();
    Pixel output;
    output.R = to.R + (from.R - to.R) * progress;
    output.G = to.G + (from.G - to.G) * progress;
    output.B = to.B + (from.B - to.B) * progress;
    return output;
}