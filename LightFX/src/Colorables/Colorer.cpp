#include "Colorables/Colorer.h"

using namespace LightFx;
using namespace LightFx::Colorables;

// Called when we should update the fade value
void Colorer::OnTick(uint64_t tick, milliseconds elapsedTime)
{
    // Update our time line
    TimelineObject::OnTick(tick, elapsedTime);

    // Do the color update
    Pixel color = OnColorSelf(tick, elapsedTime);

    // Update the colorables
    {
        std::lock_guard<std::mutex> lock(m_colorablesLock);
        for (auto colorable : m_colorables)
        {
            if (auto strongPtr = colorable.lock())
            {
                strongPtr->SetColor(color);
            }
        }
    }
}

// Called when we should add a drawable
void Colorer::AddColorable(IColorableWeakPtr colorable)
{
    std::lock_guard<std::mutex> lock(m_colorablesLock);
    m_colorables.insert(m_colorables.end(), colorable);
}

// Called when we should remove a drawable
void Colorer::RemoveColorable(IColorableWeakPtr colorable)
{
    std::lock_guard<std::mutex> lock(m_colorablesLock);

    if (auto searchFor = colorable.lock())
    {
        auto it = m_colorables.begin();
        while (it != m_colorables.end())
        {
            if (auto colorableStr = (*it).lock())
            {
                if (colorableStr == searchFor)
                {
                    m_colorables.erase(it);
                    break;
                }
            }
        }
    }
}