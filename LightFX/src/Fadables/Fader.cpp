#include "Fadables/Fader.h"

using namespace LightFx;
using namespace LightFx::Fadables;

// Called when we should update the fade value
void Fader::OnTick(uint64_t tick, milliseconds elapsedTime)
{
    // Update our timeline
    TimelineObject::OnTick(tick, elapsedTime);

    // Get the new fade value
    double newFadeValue = InterpolateValue(m_from, m_to);

    // Update the fadables
    {
        std::lock_guard<std::mutex> lock(m_drawablesLock);
        for (auto fadeable : m_drawables)
        {
            if (auto strongPtr = fadeable.lock())
            {
                strongPtr->SetIntensity(newFadeValue);
            }
        }
    }
}

// Called when we should add a drawable
void Fader::AddFadingDrawable(IIntensityObjectWeakPtr fadeable)
{
    std::lock_guard<std::mutex> lock(m_drawablesLock);
    m_drawables.insert(m_drawables.end(), fadeable);
}

// Called when we should remove a drawable
void Fader::RemoveFadingDrawable(IIntensityObjectWeakPtr fadeable)
{
    std::lock_guard<std::mutex> lock(m_drawablesLock);

    if (auto searchFor = fadeable.lock())
    {
        auto it = m_drawables.begin();
        while (it != m_drawables.end())
        {
            if (auto fadeable = (*it).lock())
            {
                if (fadeable == searchFor)
                {
                    m_drawables.erase(it);
                    break;
                }
            }
        }
    }    
}