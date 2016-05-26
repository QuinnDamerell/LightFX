#include <algorithm>

#include "Bitmap.h"

using namespace LightFx;

Bitmap::Bitmap(int64_t height, int64_t width) :
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

void Bitmap::SetPixel(int64_t x, int64_t y, Pixel& value)
{
    m_bitmap[static_cast<size_t>(x)][static_cast<size_t>(y)].B = value.B;
    m_bitmap[static_cast<size_t>(x)][static_cast<size_t>(y)].G = value.G;
    m_bitmap[static_cast<size_t>(x)][static_cast<size_t>(y)].R = value.R;
}


void Bitmap::AddToPixelValue(int64_t x, int64_t y, Pixel& value)
{
    Pixel& currentColor = m_bitmap[static_cast<size_t>(x)][static_cast<size_t>(y)];
    m_bitmap[static_cast<size_t>(x)][static_cast<size_t>(y)].R = std::min(1.0, currentColor.R + value.R); 
    m_bitmap[static_cast<size_t>(x)][static_cast<size_t>(y)].G = std::min(1.0, currentColor.G + value.G);
    m_bitmap[static_cast<size_t>(x)][static_cast<size_t>(y)].B = std::min(1.0, currentColor.B + value.B); 
}

void Bitmap::BlendInBitmap(BitmapPtr blendBitmap, int64_t xPos, int64_t yPos, double intensity)
{
    // This bitmap can be a different size than use, we will just blend in whatever overlaps.
    for (int x = xPos; x < m_width; x++)
    {
        // Bounds check to make sure the blend bitmap is as big
        if (x >= xPos + blendBitmap->GetWidth())
        {
            // We are done.
            break;
        }


        for (int y = yPos; y < m_height; y++)
        {
            // Bounds check to make sure the blend bitmap is as big
            if (y >= yPos + blendBitmap->GetHeight())
            {
                // We are done.
                break;
            }

            Pixel blendedPixel;
            Pixel localValue = m_bitmap[x][y];
            Pixel compositeValue = blendBitmap->GetPixel(x - xPos, y - yPos);

            // For this blend we are trying to emulate light. So we will use light as intensity and only add the 
            // color values together.
            blendedPixel.R = std::min(1.0, ((compositeValue.R * intensity) + localValue.R));
            blendedPixel.G = std::min(1.0, ((compositeValue.G * intensity) + localValue.G));
            blendedPixel.B = std::min(1.0, ((compositeValue.B * intensity) + localValue.B));

            // Set the new color
            SetPixel(x, y, blendedPixel);
        }
    }
}

void Bitmap::FillRect(Pixel& pixel, int64_t top, int64_t left, int64_t right, int64_t bottom)
{
    // Do a quick bound check
    if (top > bottom || left > right || right > GetWidth() || bottom > GetHeight())
    {
        throw std::invalid_argument("Args out of bounds");
    }

    // Start at the left and go to right
    for (int64_t x = left; x < right; x++)
    {
        // And start at the top and go to bottom
        for (int64_t y = top; y < bottom; y++)
        {
            SetPixel(x, y, pixel);
        }
    }
}

