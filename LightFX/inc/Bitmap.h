#pragma once

#include <stdint.h>

#include "Common.h"
#include "Pixel.h"

namespace LightFx
{
    DECLARE_SMARTPOINTER(Bitmap);
    class Bitmap :
        IntensityObject
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

        // Sets a light color to the bitmap
        void SetLightColor(uint64_t x, uint64_t y, LightColor& value)
        {
            SetPixel(x, y, Pixel(value));
        }

        // Adds a color to the current value.
        void AddToPixelValue(uint64_t x, uint64_t y, Pixel& value);

        // Sets a light color to the bitmap
        void AddLightColorToPixel(uint64_t x, uint64_t y, LightColor& value)
        {
            AddToPixelValue(x, y, Pixel(value));
        }

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
            LightColor empty(0, 0, 0, 0);
            FillRect(empty);
        }

        // Blends a bitmap into this bitmap
        void BlendInBitmap(BitmapPtr composite);

        // Fills the entire bitmap
        void FillRect(LightColor& lightColor)
        {
            FillRect(lightColor, 0, 0, GetWidth(), GetHeight());
        }

        // Fills a region of the bitmap
        void FillRect(LightColor& lightColor, uint64_t top, uint64_t left, uint64_t right, uint64_t bottom);

    protected:
        // Keep the height and width.
        uint64_t m_height;
        uint64_t m_width;

        // Keeps the main bitmap we are drawing to.
        Pixel2DArray m_bitmap;
    };
}
