#pragma once

#include <stdint.h>
#include <vector>
#include <mutex>

#include "Common.h"
#include "IDrivable.h"
#include "Bitmap.h"
#include "OutputBitmap.h"
#include "Drawables/Drawable.h"

namespace LightFx
{
    DECLARE_SMARTPOINTER(IPanelRenderedCallback);
    class IPanelRenderedCallback
    {
    public:
        virtual void OnPanelRendered() = 0;
    };

    DECLARE_SMARTPOINTER(Panel);
    class Panel : 
        public IDrivable,
        public Drawables::Drawable
    {

    public:
        Panel(int64_t height, int64_t width);

        //
        // Render Logic

        // Called when the panel should render
        void OnTick(uint64_t tick, milliseconds elapsedTime) override;

        // Sets who will be notified when the render is complete
        void SetPanelRenderedCallback(IPanelRenderedCallbackWeakPtr callback)
        {
            m_renderedCallback = callback;
        }

        // Returns an output bitmap from the current bitmap
        OutputBitmapPtr GetOutputBitmap()
        {
            return std::make_shared<OutputBitmap>(m_backBuffer);
        }

    protected:

        //
        // Render logic

        // This is our main bitmap used for rendering the panel
        BitmapPtr m_backBuffer;

        // The callback to fire when a render is complete
        IPanelRenderedCallbackWeakPtr m_renderedCallback;
    };
}
