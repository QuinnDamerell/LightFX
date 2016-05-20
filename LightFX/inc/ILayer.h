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

        // Updates the layer if the panel size changes. This will be called at least once
        // before OnDraw is called.
        virtual void UpdatePanelSize(uint64_t height, uint64_t width) = 0;

        // Called when the layer should draw.
        // Args:
        //    tick - the current tick count
        //    elapsedTimeMs - the time since the last draw
        //    backBuffer - the current back buffer, what everyone has drawn before this call.
        // Returns
        //    nullptr - If returned nothing else will happen. It is assumed the layer doesn't need to draw or it has
        //         manually edited the back buffer
        //    BitmapPtr - If a bitmap is returned it will be blended on the back buffer.
        virtual BitmapPtr OnDraw(uint64_t tickCount, milliseconds elapsedTime, Bitmap& backBuffer) = 0;
    };
}