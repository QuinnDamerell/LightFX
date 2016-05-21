#include <algorithm>

#include "Bitmap.h"

using namespace LightFx;

Bitmap::Bitmap(uint64_t height, uint64_t width) :
    IntensityObject(1),
    m_height(height),
    m_width(width)
{
    // Create the panel
    m_bitmap.resize(static_cast<size_t>(m_width));
    for (int i = 0; i < m_width; i++)
    {
        m_bitmap[i].resize(static_cast<size_t>(m_height));
    }
}

void Bitmap::SetPixel(uint64_t x, uint64_t y, Pixel& value)
{
    m_bitmap[static_cast<size_t>(x)][static_cast<size_t>(y)].B = value.B;
    m_bitmap[static_cast<size_t>(x)][static_cast<size_t>(y)].G = value.G;
    m_bitmap[static_cast<size_t>(x)][static_cast<size_t>(y)].R = value.R;
}


void Bitmap::AddToPixelValue(uint64_t x, uint64_t y, Pixel& value)
{
    Pixel& currentColor = m_bitmap[static_cast<size_t>(x)][static_cast<size_t>(y)];
    m_bitmap[static_cast<size_t>(x)][static_cast<size_t>(y)].R = std::min(1.0, currentColor.R + value.R); 
    m_bitmap[static_cast<size_t>(x)][static_cast<size_t>(y)].G = std::min(1.0, currentColor.G + value.G);
    m_bitmap[static_cast<size_t>(x)][static_cast<size_t>(y)].B = std::min(1.0, currentColor.B + value.B); 
}

void Bitmap::BlendInBitmap(BitmapPtr blendBitmap)
{
    // Make sure our bitmaps are the size
    if (GetHeight() != blendBitmap->GetHeight() ||
        GetWidth() != blendBitmap->GetWidth())
    {
        throw std::invalid_argument("Bitmaps must be the same size to blend.");
    }

    for (int x = 0; x < m_width; x++)
    {
        for (int y = 0; y < m_height; y++)
        {
            Pixel blendedPixel;
            Pixel localValue = m_bitmap[x][y];
            Pixel compositeValue = blendBitmap->GetPixel(x, y);
            double blendIntensity = blendBitmap->Intensity;

            // For this blend we are trying to emulate light. So we will use light as intensity and only add the 
            // color values together.
            blendedPixel.R = std::min(1.0, ((compositeValue.R * blendIntensity) + localValue.R));
            blendedPixel.G = std::min(1.0, ((compositeValue.G * blendIntensity) + localValue.G));
            blendedPixel.B = std::min(1.0, ((compositeValue.B * blendIntensity) + localValue.B));

            // Set the new color
            SetPixel(x, y, blendedPixel);
        }
    }
}

void Bitmap::FillRect(LightColor& lightColor, uint64_t top, uint64_t left, uint64_t right, uint64_t bottom)
{
    // Do a quick bound check
    if (top > bottom || left > right || right > GetWidth() || bottom > GetHeight())
    {
        throw std::invalid_argument("Args out of bounds");
    }

    // Flatten the LightColor
    Pixel pixel(lightColor);

    // Start at the left and go to right
    for (uint64_t x = left; x < right; x++)
    {
        // And start at the top and go to bottom
        for (uint64_t y = top; y < bottom; y++)
        {
            SetPixel(x, y, pixel);
        }
    }
}

