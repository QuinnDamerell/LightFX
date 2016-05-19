#include <algorithm>

#include "Bitmap.h"

using namespace LightFx;


Bitmap::Bitmap(uint64_t height, uint64_t width) :
    m_height(height),
    m_width(width)
{
    // Create the panel
    m_bitmap.resize(m_width);
    for (int i = 0; i < m_width; i++)
    {
        m_bitmap[i].resize(m_height);
    }
}

void Bitmap::SetPixel(uint64_t x, uint64_t y, Pixel value)
{
    m_bitmap[x][y].A = value.A;
    m_bitmap[x][y].B = value.B;
    m_bitmap[x][y].G = value.G;
    m_bitmap[x][y].R = value.R;
}

void Bitmap::Clear()
{
    Pixel empty(0, 0, 0, 0);
    for (int x = 0; x < m_width; x++)
    {
        for (int y = 0; y < m_height; y++)
        {
            SetPixel(x, y, empty);
        }
    }
}

void Bitmap::BlendInBitmap(Bitmap& composite)
{
    // Make sure our bitmaps are the size
    if (GetHeight() != composite.GetHeight() ||
        GetWidth() != composite.GetWidth())
    {
        return;
    }

    for (int x = 0; x < m_width; x++)
    {
        for (int y = 0; y < m_height; y++)
        {
            Pixel blendedPixel;
            Pixel localValue = m_bitmap[x][y];
            Pixel compositeValue = composite.GetPixel(x, y);

            // I'm not quite sure how this blend should work...
            blendedPixel.R = std::min(1.0, ((compositeValue.R * compositeValue.A) + ((localValue.R * localValue.A) * (1.0 - compositeValue.A))));
            blendedPixel.G = std::min(1.0, ((compositeValue.G * compositeValue.A) + ((localValue.G * localValue.A) * (1.0 - compositeValue.A))));
            blendedPixel.B = std::min(1.0, ((compositeValue.B * compositeValue.A) + ((localValue.B * localValue.A) * (1.0 - compositeValue.A))));
            blendedPixel.A = std::max(localValue.A, compositeValue.A);

            // Set the new color
            SetPixel(x, y, blendedPixel);
        }
    }
}
