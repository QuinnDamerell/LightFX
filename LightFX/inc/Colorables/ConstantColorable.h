#pragma once

#include <stdint.h>

#include "Common.h"
#include "Layers/Drawable/IColorable.h"
#include "Layers/Drawable/SimpleColorableBase.h"

namespace LightFx
{
    namespace Layers
    {
        namespace Drawable
        {
            DECLARE_SMARTPOINTER(ConstantColorable);
            class ConstantColorable :
                public SimpleColorableBase
            {

            public:
                ConstantColorable(LightColor color) :
                    m_color(color)
                { }

                void SetColor(LightColor color)
                {
                    m_color = color;
                }

            protected:

                // Called by the base when the sub class should get a color
                LightColor GetColor(uint64_t tickCount, milliseconds elapsedTime, double intensity)
                {
                    m_color.Intensity = intensity;
                    return m_color;
                }

            private:
                LightColor m_color;
            };
        }
    }
}