#pragma once

#include <stdint.h>

#include "Common.h"
#include "Layers/Drawable/SimpleDrawableBase.h"
#include "Layers/Drawable/IColorable.h"

namespace LightFx
{
    namespace Layers
    {
        namespace Drawable
        {
            DECLARE_SMARTPOINTER(DrawablePixel);
            class DrawablePixel :
                public SimpleDrawableBase
            {

            public:
                DrawablePixel(uint64_t x, uint64_t y) :
                    m_x(x),
                    m_y(y)
                { }      

            protected:
                // Called by the base when the sub class should draw pixels
                void DrawPixels(uint64_t tickCount, milliseconds elapsedTime, BitmapPtr buffer, Pixel color)
                {
                    // Simply draw this one pixel
                    buffer->AddToPixelValue(m_x, m_y, color);
                }

            private:
                uint64_t m_x;
                uint64_t m_y;
            };
        }
    }
}