#pragma once

#include <stdint.h>

#include "Common.h"
#include "ILayer.h"
#include "Pixel.h"
#include "Bitmap.h"

namespace LightFx
{
    namespace Layers
    {    
        DECLARE_SMARTPOINTER(SolidColorLayer);
        class SolidColorLayer :
            public ILayer
        {

        public:

            // Called when the panel size is set.
            void UpdatePanelSize(uint64_t height, uint64_t width) override
            {
                m_bitmap = std::make_shared<Bitmap>(height, width);
                m_bitmap->FillRect(m_solidColor);
            }

            // When we are asked to call just return the bitmap
            BitmapPtr OnDraw(uint64_t tick, milliseconds elapsedTime, Bitmap& backBuffer) override
            {
                return m_bitmap;
            }

            // Sets the color of the solid.
            void SetColor(Pixel color)
            {
                m_solidColor = color;
                if (m_bitmap)
                {
                    m_bitmap->FillRect(m_solidColor);
                }
            }

            // Holds the current color
            Pixel m_solidColor;

            // Holds our bitmap we will draw to
            BitmapPtr m_bitmap;
        };
    }
}