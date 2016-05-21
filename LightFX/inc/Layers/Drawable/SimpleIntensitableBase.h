#pragma once

#include <stdint.h>

#include "Common.h"
#include "Layers/Drawable/IIntensitable.h"
#include "Layers/Drawable/TimelineObject.h"

namespace LightFx
{
    namespace Layers
    {
        namespace Drawable
        {
            DECLARE_SMARTPOINTER(SimpleIntensitableBase);
            class SimpleIntensitableBase :
                public IIntensitable,
                public TimelineObject
            {

            protected:
                // We can only be created by base classes
                SimpleIntensitableBase()
                {}

                //
                // IIntensitable
                // 

                // Called when the intensitable should return a intensity.
                virtual double OnIntensity(uint64_t tickCount, milliseconds elapsedTime) = 0;
            };
        }
    }
}