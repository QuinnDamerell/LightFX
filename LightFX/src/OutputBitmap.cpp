#include "OutputBitmap.h"
#include "Pixel.h"

using namespace LightFx;

OutputBitmap::~OutputBitmap()
{
    // If we have an array free it.
    if (m_rawPixelArray)
    {
        delete m_rawPixelArray;
        m_rawPixelArray = nullptr;
    }
}

uint8_t* OutputBitmap::GetPixelArray()
{
    // If we already have the array return it.
    if (!m_rawPixelArray)
    {
        // We don't have it so we need to make it
        m_rawPixelArray = new uint8_t[static_cast<unsigned int>(GetPixelArrayLength())];

        // Flatten the bitmap to the array.
        uint64_t currentPos = 0;
        for (int x = 0; x < GetWidth(); x++)
        {
            for (int y = 0; y < GetHeight(); y++)
            {
                // For each pixel, compute the values
                Pixel pixel = m_inputBitmap.GetPixel(x, y);
                m_rawPixelArray[currentPos] = static_cast<uint8_t>(pixel.R * 255.0);
                currentPos++;
                m_rawPixelArray[currentPos] = static_cast<uint8_t>(pixel.G * 255.0);
                currentPos++;
                m_rawPixelArray[currentPos] = static_cast<uint8_t>(pixel.B * 255.0);
                currentPos++;
            }
        }
    }

    // Return the output
    return m_rawPixelArray;
}