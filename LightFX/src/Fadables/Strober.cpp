#include "Fadables/Strober.h"

using namespace LightFx;
using namespace LightFx::Fadables;

// Called when we should update the fade value
void Strober::OnTick(uint64_t tick, milliseconds elapsedTime)
{
    // Update our timeline
    TimelineObject::OnTick(tick, elapsedTime);

    // Update the strobe time based on how much time passed.
    m_intervalCounter -= static_cast<int64_t>(elapsedTime.count());

    // If the counter is under the negative interval, reset.
    if(m_intervalCounter < -m_interval.count())
    {
        m_intervalCounter = m_interval.count();
    }

    //  Get the fade value.
    double newFadeValue = m_intervalCounter > 0 ? m_onValue : m_offValue;

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
void Strober::AddFadingDrawable(IIntensityObjectWeakPtr fadeable)
{
    std::lock_guard<std::mutex> lock(m_drawablesLock);
    m_drawables.insert(m_drawables.end(), fadeable);
}

// Called when we should remove a drawable
void Strober::RemoveFadingDrawable(IIntensityObjectWeakPtr fadeable)
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