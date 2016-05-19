#pragma once

#include <stdint.h>

#include "Common.h"
#include "ILayer.h"
#include "Pixel.h"

namespace LightFx
{
    DECLARE_SMARTPOINTER(SolidColorLayer);
    class SolidColorLayer : 
        public ILayer
    {

    public:

        bool OnDraw(uint64_t tick, uint64_t elapsedTimeMs, Bitmap& backBuffer, Bitmap& compositeBitmap)
        {
            for (int x = 0; x < compositeBitmap.GetWidth(); x++)
            {
                for (int y = 0; y < compositeBitmap.GetHeight(); y++)
                {
                    compositeBitmap.SetPixel(x, y, m_solidColor);
                }
            }
            return true;
        }

        void SetColor(Pixel color)
        {
            m_solidColor = color;
        }

        Pixel m_solidColor;
    };
}