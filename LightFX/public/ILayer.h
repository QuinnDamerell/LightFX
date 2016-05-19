#pragma once

#include <stdint.h>

#include "Common.h"
#include "Bitmap.h"

namespace LightFx
{
    DECLARE_SMARTPOINTER(ILayer);
    class ILayer
    {
    public:

        // Fired when the layer should draw.
        // This function is designed to support layers that wish to handle blending on their own or layers that want the blending
        // to be done for them. 
        //
        // BackBuffer - The currently rendered output from the layer under this layer. The layer can read from this and / or
        //     write directly to it.
        // CompositeBitmap - If the layer would like the output to be composited with the back buffer it should render to this
        //     bitmap. If this is drawn to and the function returns true the compositeBitmap will be rendered correctly to the backBuffer
        // Returns - If true the compositeBitmap will be rendered to the backBuffer, if false nothing else will be rendered.
        //
        virtual bool OnDraw(uint64_t tick, uint64_t elapsedTimeMs, Bitmap& backBuffer, Bitmap& compositeBitmap) = 0;
    };
}