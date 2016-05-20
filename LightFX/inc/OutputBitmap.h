#pragma once

#include <stdint.h>

#include "Common.h"
#include "Pixel.h"
#include "Bitmap.h"

namespace LightFx
{
    DECLARE_SMARTPOINTER(OutputBitmap);
    class OutputBitmap
    {

    public:
        OutputBitmap(Bitmap inputBitmap) :
            m_inputBitmap(inputBitmap),
            m_rawPixelArray(nullptr)
        { }

        ~OutputBitmap();

        uint64_t GetWidth()
        {
            return m_inputBitmap.GetWidth();
        }

        uint64_t GetHeight()
        {
            return m_inputBitmap.GetHeight();
        }

        uint64_t GetPixelArrayLength()
        {
            return GetHeight() * GetWidth() * 3;
        }

        uint8_t* GetPixelArray();       

    protected:
        // The backing bitmap
        Bitmap m_inputBitmap;

        // The array of the flattened bitmap.
        uint8_t* m_rawPixelArray;
    };
}
