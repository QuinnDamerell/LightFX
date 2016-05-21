#pragma once

#include <stdint.h>

#include "Common.h"
#include "Pixel.h"

namespace LightFx
{
    namespace Layers
    {
        namespace Drawable
        {
            DECLARE_SMARTPOINTER(IColorable);
            class IColorable
            {

            public:
                // Called when the color should return a color
                virtual LightColor OnColor(uint64_t tickCount, milliseconds elapsedTime) = 0;
            };
        }
    }
}