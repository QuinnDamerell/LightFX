#pragma once

#include <stdint.h>

#include "Common.h"
#include "Layers/Drawable/IColorable.h"
#include "Fadable/IFadable.h"
#include "Layers/Drawable/TimelineObject.h"
#include "Bitmap.h"

namespace LightFx
{
    namespace Layers
    {
        namespace Drawable
        {
            DECLARE_SMARTPOINTER(SimpleColorableBase);
            class SimpleColorableBase :
                public IColorable,
                public TimelineObject
            {
            public:

            protected:
                // We can only be created by base classes
             

                //
                // IColorable
                // 

                // Called when the colorable should return a color.
                virtual LightColor OnColor(uint64_t tickCount, milliseconds elapsedTime);

                //
                // Base functions
                //

                // Called by the base when the sub class should return a color
                virtual LightColor GetColor(uint64_t tickCount, milliseconds elapsedTime, double intensity) = 0;

            private:

            };
        }
    }
}