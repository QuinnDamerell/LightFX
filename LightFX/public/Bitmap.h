#pragma once

#include <stdint.h>

#include "Common.h"
#include "Pixel.h"

namespace LightFx
{
    DECLARE_SMARTPOINTER(Bitmap);
    class Bitmap
    {

    public:
        Bitmap(uint64_t height, uint64_t width);

        // Returns what the pixel current is.
        Pixel GetPixel(uint64_t x, uint64_t y)
        {
            return m_bitmap[x][y];
        }

        // Sets a pixel to a value.
        void SetPixel(uint64_t x, uint64_t y, Pixel value);

        uint64_t GetWidth()
        {
            return m_width;
        }

        uint64_t GetHeight()
        {
            return m_width;
        }

        // Clears the bitmap
        void Clear();

        // Blends a bitmap into this bitmap
        void BlendInBitmap(Bitmap& composite);

    protected:
        // Keep the height and width.
        uint64_t m_height;
        uint64_t m_width;

        // Keeps the main bitmap we are drawing to.
        Pixel2DArray m_bitmap;
    };
}
