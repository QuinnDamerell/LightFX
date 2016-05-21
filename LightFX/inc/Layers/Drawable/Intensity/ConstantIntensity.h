#pragma once

#include <stdint.h>

#include "Common.h"
#include "Layers/Drawable/IIntensitable.h"
#include "Layers/Drawable/SimpleIntensitableBase.h"
#include "Pixel.h"

namespace LightFx
{
    namespace Layers
    {
        namespace Drawable
        {
            DECLARE_SMARTPOINTER(ConstantIntensity);
            class ConstantIntensity :
                public SimpleIntensitableBase,
                public IntensityObject
            {

            public:
                ConstantIntensity(double intensity) :
                    IntensityObject(Intensity)
                { }

            protected:

                // Called by the base when the sub class should get a intensity
                double OnIntensity(uint64_t tickCount, milliseconds elapsedTime)
                {
                    return Intensity;
                }
            };
        }
    }
}