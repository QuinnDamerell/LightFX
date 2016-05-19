#pragma once

#include <stdint.h>
#include <vector>
#include <mutex>

#include "Common.h"
#include "IDrivable.h"
#include "Bitmap.h"
#include "OutputBitmap.h"
#include "ILayer.h"

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
        public IDrivable
    {

    public:
        Panel(uint64_t height, uint64_t width);

        //
        // Render Logic

        // Called when the panel should render
        void OnTick(uint64_t tick, uint64_t elapsedTimeMs) override;

        // Returns the current bitmap as a pixel array.
        void GetPixelArray();

        // Sets who will be notified when the render is complete
        void SetPanelRenderedCallback(IPanelRenderedCallbackWeakPtr callback)
        {
            m_renderedCallback = callback;
        }

        // Returns an output bitmap from the current bitmap
        OutputBitmapPtr GetOutputBitmap()
        {
            return std::make_shared<OutputBitmap>(m_bitmap);
        }

        //
        // Layer Logic
        void AddLayer(ILayerPtr layerToAdd, int64_t zIndex);

    protected:

        //
        // Render logic

        // This is our main bitmap used for rendering the panel
        Bitmap m_bitmap;

        // This is a temp bitmap which is given to layers to draw to if they want to be composited.
        Bitmap m_compositeBitmap;

        // The callback to fire when a render is complete
        IPanelRenderedCallbackWeakPtr m_renderedCallback;

        // 
        // Layer logic
        std::mutex m_layerCollectionLock;
        std::vector<std::pair<int64_t, ILayerPtr>> m_layerCollection;
    };
}
