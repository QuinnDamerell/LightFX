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
            DECLARE_SMARTPOINTER(ConstantFadable);
            class ConstantFadable :
                public SimpleFadableBase
            {

            public:
                ConstantFadable(double alpha) :
                    m_alpha(alpha)
                { }

                void SetAlpha(double alpha)
                {
                    m_alpha = alpha;
                }

            protected:

                // Called by the base when the sub class should get a alpha
                double OnFade(uint64_t tickCount, milliseconds elapsedTime)
                {
                    return m_alpha;
                }

            private:
                double m_alpha;
            };
        }
    }
}