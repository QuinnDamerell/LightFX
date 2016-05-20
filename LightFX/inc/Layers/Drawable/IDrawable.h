#pragma once

#include <stdint.h>

#include "Common.h"
#include "Bitmap.h"

namespace LightFx
{
    namespace Layers
    {
        namespace Drawable
        {
            DECLARE_SMARTPOINTER(IDrawable);
            class IDrawable 
            {

            public:
                // Called when the drawable should draw something.
                virtual void OnDraw(uint64_t tickCount, milliseconds elapsedTime, BitmapPtr buffer) = 0;
            };
        }
    }
}