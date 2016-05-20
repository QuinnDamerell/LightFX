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
                ConstantColorable(Pixel color) :
                    m_color(color)
                { }

                void SetColor(Pixel color)
                {
                    m_color = color;
                }

            protected:

                // Called by the base when the sub class should get a color
                Pixel GetColor(uint64_t tickCount, milliseconds elapsedTime, double alpha)
                {
                    m_color.A = alpha;
                    return m_color;
                }

            private:
                Pixel m_color;
            };
        }
    }
}