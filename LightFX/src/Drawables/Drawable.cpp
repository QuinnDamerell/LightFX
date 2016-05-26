
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

    // Update the colorer if we have one
    if (auto colorer = GetColorer())
    {
        colorer->OnTick(tick, elapsedTime);
    }

    // First clear out bitmap
    m_bitmap->Clear();

    // Draw our children
    {
        // Grab the panel lock
        std::lock_guard<std::mutex> lock(m_drawableCollectionLock);

        // Loop through all of our children.
        auto iter = m_drawableCollection.begin();
        while (iter != m_drawableCollection.end())
        {
            // Check if any drawable should be cleaned up.
            IDrawablePtr child = iter->first;
            if (child->ShouldBeCleanedUp())
            {
                // If so remove them.
                iter = m_drawableCollection.erase(iter);
            }
            else
            {
                // Ask the drawable to draw.
                child->OnDraw(tick, elapsedTime, m_bitmap);
                iter++;
            }
        }
    }

    // Now draw ourself
    OnDrawSelf(tick, elapsedTime);

    // Last, add our bitmap to the back buffer
    backBuffer->BlendInBitmap(m_bitmap, GetIntensity());
}

// If set, when all of the time line objects on this drawable are done
// the drawable will be cleaned up.
void Drawable::CleanupWhenComplete(bool cleanup)
{
    m_cleanUpWhenComplete = cleanup;
}

// Indicates if all of the time line objects are complete or not.
bool Drawable::ShouldBeCleanedUp()
{
    // If we are being forced clean up now.
    if (m_forceCleanUp)
    {
        return true;
    }

    // We will only consider cleaning up if we have a fader
    if (auto fader = GetFader())
    {
        if (fader->IsComplete())
        {
            return m_cleanUpWhenComplete;
        }
    }
    return false;
}

// Gets the color
Pixel Drawable::GetColor()
{
    return m_color;
}

// Sets the intensity
void Drawable::SetColor(Pixel color)
{
    m_color = color;
}

// Sets a colorable object
void Drawable::SetColorer(Colorables::IColorerPtr colorer)
{
    if (m_colorer)
    {
        // If we had a colorer remove ourselves.
        m_colorer->RemoveColorable(std::dynamic_pointer_cast<IColorable>(shared_from_this()));
    }

    m_colorer = colorer;

    if (m_colorer)
    {
        // If we have a colorer send register ourselves
        m_colorer->AddColorable(std::dynamic_pointer_cast<IColorable>(shared_from_this()));
    }
}

// Gets the colorer if there is one
Colorables::IColorerPtr Drawable::GetColorer()
{
    return m_colorer;
}