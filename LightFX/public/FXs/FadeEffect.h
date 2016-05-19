#pragma once

#include <stdint.h>
#include <string>
#include <chrono>

#include "Common.h"
#include "ILayer.h"

DECLARE_SMARTPOINTER(FadeEffect);
class FadeEffect :

{
public:
    FadeEffect(std::string layerName, LightFxColor from, LightFxColor to, char activePixelElements, high_res_clock::duration duration) :
        FxLayerBase(layerName),
        m_from(from),
        m_to(to),
        m_duration(duration),
        m_durationRemaining(duration),
        activePixelElements(activePixelElements)
    {}

    ~FadeEffect() {}

protected:

    // Called when we should return the pixels for this drawing pass.
    void RenderEffect(uint64_t drawPass, uint32_t elapsedTimeMs, LightFxPixel2DArrayPtr arrayPtr);

private:
    LightFxColor m_from;
    LightFxColor m_to;
    char activePixelElements;
    high_res_clock::duration m_duration;
    high_res_clock::duration m_durationRemaining;
};

