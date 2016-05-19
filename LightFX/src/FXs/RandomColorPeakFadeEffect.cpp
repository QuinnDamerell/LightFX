
#include <cmath>
#include "FXs\RandomColorPeakFadeEffect.h"

RandomColorPeakFadeEffect::RandomColorPeakFadeEffect(std::string layerName) :
    FxLayerBase(layerName)
{

    //  std::default_random_engine generator;
    //  std::uniform_int_distribution<int> distribution(0, 7);
    //  std::uniform_int_distribution<int> colorDistro(0, 200);
    //  int dice_roll = distribution(generator);

}

void RandomColorPeakFadeEffect::RenderEffect(uint64_t drawPass, uint32_t elapsedTimeMs, LightFxPixel2DArrayPtr layerData)
{
    LightFxCordornate layerSize = m_childLayer->GetSizeBounds();
    std::uniform_int_distribution<int> xDist(0, layerSize.X - 1);
    std::uniform_int_distribution<int> yDist(0, layerSize.Y - 1);

    // Pick a random cord.
    uint32_t xCord = xDist(m_randEngine);
    uint32_t yCord = yDist(m_randEngine);

    // Pick a random color
    std::uniform_real_distribution<double> colorDist(0, 1);
    layerData->at(xCord)[yCord].Color = GetRandomColor(colorDist(m_randEngine));
    layerData->at(xCord)[yCord].Color.A = 0.5;
}



LightFxColor RandomColorPeakFadeEffect::GetRandomColor(double value)
{
    double m_redRange[] = { 1, 1, 0, 0, 0, 1 };
    double m_blueRange[] = { 0, 1, 1, 1, 0, 0 };
    double m_greenRange[] = { 0, 0, 0, 1, 1, 1 };

    LightFxColor randomColor;

    // Wrap the value if we hit 1.
    if (value == 1)
    {
        value = 0;
    }

    // Find what bucket we are in
    int rangeBot = (int)std::floor(((value)* 6));
    int rangeTop = rangeBot + 1;
    if (rangeTop == 6)
    {
        rangeTop = 0;
    }

    // Find where we are in that bucket-
    int bucket = (((int)(value * 6 * 6)) % 6);
    double placeInRange = ((double)bucket) / 6.0;
    if (value == 1.0)
    {
        // Special case
        placeInRange = 1;
    }

    // Find the values per color
    randomColor.R = m_redRange[rangeBot] + (m_redRange[rangeTop] - m_redRange[rangeBot]) * placeInRange;
    randomColor.G = m_greenRange[rangeBot] + (m_greenRange[rangeTop] - m_greenRange[rangeBot]) * placeInRange;
    randomColor.B = m_blueRange[rangeBot] + (m_blueRange[rangeTop] - m_blueRange[rangeBot]) * placeInRange;
    randomColor.A = 1.0;
    return randomColor;
}