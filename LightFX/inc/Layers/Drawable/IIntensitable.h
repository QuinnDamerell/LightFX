#pragma once

#include <stdint.h>

#include "Common.h"

namespace LightFx
{
    namespace Layers
    {
        namespace Drawable
        {
            DECLARE_SMARTPOINTER(IIntensitable);
            class IIntensitable
            {

            public:
                // Called when the intensitable should return a intensity
                virtual double OnIntensity(uint64_t tickCount, milliseconds elapsedTime) = 0;
            };
        }
    }
}