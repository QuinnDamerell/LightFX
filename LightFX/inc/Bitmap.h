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

        //
        // Basic pixel logic 
        //

        // Returns what the pixel current is.
        inline Pixel& GetPixel(uint64_t x, uint64_t y)
        {
            return m_bitmap[static_cast<unsigned int>(x)][static_cast<unsigned int>(y)];
        }

        // Sets a pixel to a value.
        inline void SetPixel(uint64_t x, uint64_t y, Pixel& value);

        inline uint64_t GetWidth()
        {
            return m_width;
        }

        inline uint64_t GetHeight()
        {
            return m_width;
        }

        // 
        // Basic operations
        //

        // Clears the bitmap
        void Clear()
        {
            Pixel empty(0, 0, 0, 0);
            FillRect(empty);
        }

        // Blends a bitmap into this bitmap
        void BlendInBitmap(BitmapPtr composite);

        // Fills the entire bitmap
        void FillRect(Pixel& pixelColor)
        {
            FillRect(pixelColor, 0, 0, GetWidth(), GetHeight());
        }

        // Fills a region of the bitmap
        void FillRect(Pixel& pixelColor, uint64_t top, uint64_t left, uint64_t right, uint64_t bottom);

    protected:
        // Keep the height and width.
        uint64_t m_height;
        uint64_t m_width;

        // Keeps the main bitmap we are drawing to.
        Pixel2DArray m_bitmap;
    };
}
