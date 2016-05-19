#include "Panel.h"

using namespace LightFx;

Panel::Panel(uint64_t height, uint64_t width) :
    m_bitmap(height, width),
    m_compositeBitmap(height, width)
{ }

void Panel::OnTick(uint64_t tick, uint64_t elapsedTimeMs)
{
    {
        // Grab the panel lock
        std::lock_guard<std::mutex> lock(m_layerCollectionLock);

        // Clear the back buffer
        m_bitmap.Clear();

        // Loop though all of the layers from bottom to top and ask them to draw.
        for (auto layerPair : m_layerCollection)
        {
            // Clear the composite buffer.
            m_compositeBitmap.Clear();

            // Ask the layer to draw. If they return true we need to blend the composite bitmap 
            // to the back buffer.
            if (layerPair.second->OnDraw(tick, elapsedTimeMs, m_bitmap, m_compositeBitmap))
            {
                // We need to blend the m_compositeBitmap to the m_bitmap
                m_bitmap.BlendInBitmap(m_compositeBitmap);
            }
        }
    }

    // Now that we have drawn, report that we have an update to the panel
    if (auto callback = m_renderedCallback.lock())
    {
        callback->OnPanelRendered();
    }
}

void Panel::AddLayer(ILayerPtr layerToAdd, int64_t zIndex)
{
    std::lock_guard<std::mutex> lock(m_layerCollectionLock);

    // Start with an iterator
    auto insertPosition = m_layerCollection.begin();

    // Loop until we find an element that is larger than us or the end.
    while (insertPosition != m_layerCollection.end() && ((*insertPosition).first < zIndex))
    {
        insertPosition++;
    }

    // Add the layer
    m_layerCollection.insert(insertPosition, std::pair<int64_t, ILayerPtr>(zIndex, layerToAdd));
}
