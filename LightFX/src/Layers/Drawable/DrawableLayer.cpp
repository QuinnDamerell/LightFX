#include "Layers/Drawable/DrawableLayer.h"
#include "Layers/Drawable/TimelineObject.h"

using namespace LightFx;
using namespace LightFx::Layers::Drawable;

BitmapPtr DrawableLayer::OnDraw(uint64_t tickCount, milliseconds elapsedTime, Bitmap& backBuffer)
{
    {
        // Grab the lock
        std::lock_guard<std::mutex> lock(m_drawableListMutex);

        // Clear our local bitmap
        m_bitmap->Clear();

        // Loop though all of the drawables we current have.
        auto drawableIt = m_drawableList.begin();
        while (drawableIt != m_drawableList.end())
        {
            // Check if the drawable is done
            TimelineObjectPtr timeLineObject = std::dynamic_pointer_cast<TimelineObject>((*drawableIt).second);

            if (timeLineObject && timeLineObject->ShouldCleanup())
            {
                // If it is done remove it from our list.
                drawableIt = m_drawableList.erase(drawableIt);
            }
            else
            {
                // Otherwise ask the drawable to draw
                (*drawableIt).second->OnDraw(tickCount, elapsedTime, m_bitmap);
                drawableIt++;
            }       
        }
    }

    // When done return our bitmap to be blended
    return m_bitmap;
}

void DrawableLayer::AddDrawable(IDrawablePtr drawable, uint64_t zIndex)
{
    std::lock_guard<std::mutex> lock(m_drawableListMutex);

    // Start with an iterator
    auto insertPosition = m_drawableList.begin();

    // Loop until we find an element that is larger than us or the end.
    while (insertPosition != m_drawableList.end() && ((*insertPosition).first < zIndex))
    {
        insertPosition++;
    }

    // Add the layer
    m_drawableList.insert(insertPosition, std::pair<int64_t, IDrawablePtr>(zIndex, drawable));
}

bool DrawableLayer::RemoveDrawable(IDrawablePtr drawable)
{
    std::lock_guard<std::mutex> lock(m_drawableListMutex);

    auto searchIt = m_drawableList.begin();
    while(searchIt != m_drawableList.begin())
    {
        if ((*searchIt).second == drawable)
        {
            m_drawableList.erase(searchIt);
            return true;
        }
    }

    return false;
}