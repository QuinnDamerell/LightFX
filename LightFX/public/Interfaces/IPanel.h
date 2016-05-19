#pragma once

#include <stdint.h>
#include <string>

#include "Common.h"
#include "Pixel.h"

namespace LightFx
{
    DECLARE_SMARTPOINTER(IPanel);
    class IPanel
    {

    public:
        IPanel(uint64_t height, uint64_t width) :
            m_height(height),
            m_width(width)
        {
        }

       

    protected:
        // Keep the height and width.
        uint64_t m_height;
        uint64_t m_width; 
    };
}
