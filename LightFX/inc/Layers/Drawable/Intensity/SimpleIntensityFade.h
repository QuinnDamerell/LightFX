#pragma once

#include <stdint.h>

#include "Common.h"
#include "Layers/Drawable/IIntensitable.h"
#include "Layers/Drawable/SimpleIntensitableBase.h"

namespace LightFx
{
    namespace Layers
    {
        namespace Drawable
        {
            DECLARE_SMARTPOINTER(SimpleIntensityFade);
            class SimpleIntensityFade :
                public SimpleIntensitableBase
            {

            public:
                SimpleIntensityFade(double startValue, double endValue, milliseconds duration) :
                    m_startValue(startValue),
                    m_endValue(endValue)
                {
                    // Set our duration
                    SetDuration(duration);
                }

                virtual ~SimpleIntensityFade() {};

                void SetToAndFrom(double to, double from)
                {
                    m_startValue = from;
                    m_endValue = to;
                }

            protected:

                // Called by the base when the sub class should get a intensity
                double OnIntensity(uint64_t tickCount, milliseconds elapsedTime)
                {
                    // Report the time elapsed
                    AddTimeElapsed(elapsedTime, tickCount);

                    // Interpolate the intensity
                    return InterpolateValue(m_startValue, m_endValue);
                }

            private:
                double m_startValue;
                double m_endValue;
            };
        }
    }
}