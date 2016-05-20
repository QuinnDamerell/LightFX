#pragma once

#include <stdint.h>

#include "Common.h"
#include "Layers/Drawable/IFadable.h"
#include "Layers/Drawable/TimelineObject.h"

namespace LightFx
{
    namespace Layers
    {
        namespace Drawable
        {
            DECLARE_SMARTPOINTER(SimpleFadableBase);
            class SimpleFadableBase :
                public IFadable,
                public TimelineObject
            {

            protected:
                // We can only be created by base classes
                SimpleFadableBase()
                {}

                //
                // IColorable
                // 

                // Called when the colorable should return a color.
                virtual double OnFade(uint64_t tickCount, milliseconds elapsedTime) = 0;
            };
        }
    }
}