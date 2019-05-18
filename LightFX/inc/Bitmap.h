#pragma once

#include <stdint.h>
#include <stdexcept>

#include "Common.h"
#include "Pixel.h"

namespace LightFx
{
    DECLARE_SMARTPOINTER(Bitmap);
    class Bitmap
    {
    public:
        Bitmap(int64_t height, int64_t width);

        //
        // Basic pixel logic 
        //

        // Returns what the pixel current is.
        Pixel& GetPixel(int64_t x, int64_t y)
        {
            return m_bitmap[static_cast<unsigned int>(x)][static_cast<unsigned int>(y)];
        }

        // Sets a pixel to a value.
        void SetPixel(int64_t x, int64_t y, Pixel& value);

        // Sets a light color to the bitmap
        void SetLightColor(int64_t x, int64_t y, LightColor& value)
        {
            Pixel pixel(value);
            SetPixel(x, y, pixel);
        }

        // Adds a color to the current value.
        void AddToPixelValue(int64_t x, int64_t y, Pixel& value);

        // Sets a light color to the bitmap
        void AddLightColorToPixel(int64_t x, int64_t y, LightColor& value)
        {
            Pixel pixel(value);
            AddToPixelValue(x, y, pixel);
        }

        inline int64_t GetWidth()
        {
            return m_width;
        }

        inline int64_t GetHeight()
        {
            return m_height;
        }

        // 
        // Basic operations
        //

        // Clears the bitmap
        void Clear()
        {
            Pixel empty(0, 0, 0);
            FillRect(empty);
        }

        // Blends a bitmap into this bitmap
        void BlendInBitmap(BitmapPtr composite, int64_t xPos, int64_t yPos, double intensity);

        // Fills the entire bitmap
        void FillRect(Pixel& pixel)
        {
            FillRect(pixel, 0, 0, GetWidth(), GetHeight());
        }

        // Fills a region of the bitmap
        void FillRect(Pixel& pixel, int64_t top, int64_t left, int64_t right, int64_t bottom);

    protected:
        // Keep the height and width.
        int64_t m_height;
        int64_t m_width;

        // Keeps the main bitmap we are drawing to.
        Pixel2DArray m_bitmap;
    };
}
