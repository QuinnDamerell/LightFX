
#include "Drawables/Drawable.h"

using namespace LightFx;
using namespace LightFx::Drawables;


// Called when size is set.
void Drawable::SetSize(uint64_t height, uint64_t width)
{
    // Create a new bitmap of the correct size.
    m_bitmap = std::make_shared<Bitmap>(height, width);
}

// Returns the width
uint64_t Drawable::GetWitdh()
{
    return m_bitmap->GetWidth();
}

// Returns the height
uint64_t Drawable::GetHeight()
{
    return m_bitmap->GetHeight();
}

// Adds a drawable to the drawable
void Drawable::AddDrawable(IDrawablePtr drawable, int64_t zIndex)
{
    std::lock_guard<std::mutex> lock(m_drawableCollectionLock);

    // Start with an iterator
    auto insertPosition = m_drawableCollection.begin();

    // Loop until we find an element that is larger than us or the end.
    while (insertPosition != m_drawableCollection.end() && ((*insertPosition).second < zIndex))
    {
        insertPosition++;
    }

    // Add the drawable
    m_drawableCollection.insert(insertPosition, DrawableZIndexPair(drawable, zIndex));

    // Set the size of the drawable
    drawable->SetSize(m_bitmap->GetHeight(), m_bitmap->GetWidth());
}

void Drawable::OnDraw(uint64_t tick, milliseconds elapsedTime, BitmapPtr backBuffer)
{
    // Update our fader if we have one first. We don't want to skip out
    // from an intensity of 0 if it actually shouldn't be.
    if (auto fader = GetFader())
    {
        fader->OnTick(tick, elapsedTime);
    }

    // If we aren't visible don't bother drawing. We will keep track of how much time
    // we missed so we can report it correctly when we draw again.
    if (GetIntensity() < 0.001)
    {
        m_ignoredDrawTime += elapsedTime;
        return;
    }

    // Check if we need to report any time.
    if (m_ignoredDrawTime.count() != 0)
    {
        elapsedTime += m_ignoredDrawTime;
        m_ignoredDrawTime = milliseconds(0);
    }

    // First clear out bitmap
    m_bitmap->Clear();

    // Draw our children
    {
        // Grab the panel lock
        std::lock_guard<std::mutex> lock(m_drawableCollectionLock);

        // Loop though all of the layers from bottom to top and ask them to draw.
        for (auto drawablePair : m_drawableCollection)
        {
            // Ask the drawable to draw.
            drawablePair.first->OnDraw(tick, elapsedTime, m_bitmap);
        }
    }

    // Now draw ourself
    OnDrawSelf(tick, elapsedTime);

    // Last, add our bitmap to the back buffer
    backBuffer->BlendInBitmap(m_bitmap, GetIntensity());
}
