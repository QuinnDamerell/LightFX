#pragma once

#include <stdint.h>

#include "Common.h"

namespace LightFx
{
    namespace Layers
    {
        namespace Drawable
        {
            DECLARE_SMARTPOINTER(IFadable);
            class IFadable
            {

            public:
                // Called when the fadable should return a fade
                virtual double OnFade(uint64_t tickCount, milliseconds elapsedTime) = 0;
            };
        }
    }
}