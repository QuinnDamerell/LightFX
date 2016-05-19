#pragma once

#include <stdint.h>
#include <string>
#include <chrono>
#include <random>

#include "Common.h"
#include "ILayer.h"
#include "FxLayerBase.h"
#include "FadeEffect.h"

DECLARE_SMARTPOINTER(RandomColorPeakFadeEffect);
class RandomColorPeakFadeEffect :
    public FxLayerBase
{
public:
    RandomColorPeakFadeEffect(std::string layerName);

    ~RandomColorPeakFadeEffect() {}

protected:

    // Called when we should return the pixels for this drawing pass.
    void RenderEffect(uint64_t drawPass, uint32_t elapsedTimeMs, LightFxPixel2DArrayPtr arrayPtr);

private:

    LightFxColor GetRandomColor(double value);

    std::vector<FadeEffectPtr> m_fadeEffectList;

    // Random engine
    std::default_random_engine m_randEngine;
};

