#pragma once

#include <stdint.h>

#include "Common.h"
#include "Layers/Drawable/IFadable.h"
#include "Layers/Drawable/SimpleFadableBase.h"

namespace LightFx
{
    namespace Layers
    {
        namespace Drawable
        {
            DECLARE_SMARTPOINTER(SimpleFade);
            class SimpleFade :
                public SimpleFadableBase
            {

            public:
                SimpleFade(double startValue, double endValue, milliseconds duration) :
                    m_startValue(startValue),
                    m_endValue(endValue)
                {
                    // Set our duration
                    SetDuration(duration);
                }

                virtual ~SimpleFade() {};

                void SetToAndFrom(double to, double from)
                {
                    m_startValue = from;
                    m_endValue = to;
                }

            protected:

                // Called by the base when the sub class should get a alpha
                double OnFade(uint64_t tickCount, milliseconds elapsedTime)
                {
                    // Report the time elapsed
                    AddTimeElapsed(elapsedTime, tickCount);

                    // Interpolate the fade
                    return InterpolateValue(m_startValue, m_endValue);
                }

            private:
                double m_startValue;
                double m_endValue;
            };
        }
    }
}