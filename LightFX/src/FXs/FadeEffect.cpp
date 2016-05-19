
#include "FXs\FadeEffect.h"

void FadeEffect::RenderEffect(uint64_t drawPass, uint32_t elapsedTimeMs, LightFxPixel2DArrayPtr layerData)
{
    // Return if we shouldn't run.
    if (!m_isRunning)
    {
        return;
    }

    // Compute the fade value we should be at
    m_durationRemaining -= std::chrono::milliseconds(elapsedTimeMs);

    // If we are done set the duration to 0 to ensure we render it.
    if (m_durationRemaining.count() < 0)
    {
        m_durationRemaining = std::chrono::milliseconds(0);
    }

    // Compute the progress
    double progress = ((double)m_durationRemaining.count()) / ((double)m_duration.count());

    // Get the colors
    double alpha, red, green, blue;
    if (activePixelElements & ACTIVE_COLOR_ALPHA)
    {
        alpha = ((m_from.A - m_to.A) * progress) + m_to.A;
    }
    if (activePixelElements & ACTIVE_COLOR_RED)
    {
        red = ((m_from.R - m_to.R) * progress) + m_to.R;
    }
    if (activePixelElements & ACTIVE_COLOR_GREEN)
    {
        green = ((m_from.G - m_to.G) * progress) + m_to.G;
    }
    if (activePixelElements & ACTIVE_COLOR_BLUE)
    {
        blue = ((m_from.B - m_to.B) * progress) + m_to.B;
    }
    
    // Set the color to the grid.
    LightFxCordornate layerSize = m_childLayer->GetSizeBounds();
    for (int x = 0; x < layerSize.X; x++)
    {
        for (int y = 0; y < layerSize.Y; y++)
        {
            if (activePixelElements & ACTIVE_COLOR_ALPHA)
            {
                layerData->at(x)[y].Color.A = alpha;
            }    
            if (activePixelElements & ACTIVE_COLOR_RED)
            {
                layerData->at(x)[y].Color.R = red;
            }
            if (activePixelElements & ACTIVE_COLOR_GREEN)
            {
                layerData->at(x)[y].Color.G = green;
            }
            if (activePixelElements & ACTIVE_COLOR_BLUE)
            {
                layerData->at(x)[y].Color.B = blue;
            }
        }
    }

    // After we set the values if we are done indicate that we are.
    if (m_durationRemaining.count() <= 0)
    {
        if (m_shouldBounceLoop)
        {
            // Reverse direction for the bounce
            m_durationRemaining = m_duration;
            LightFxColor temp = m_to;
            m_to = m_from;
            m_from = temp;
        }
        else if (m_shouldResetLoop)
        {
            m_durationRemaining = m_duration;
        }
        else
        {
            OnAnimationComplete();
        }        
    }
}