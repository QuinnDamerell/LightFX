#pragma once

#include <stdint.h>
#include <mutex>
#include <vector>

#include "Common.h"
#include "Colorables/Colorer.h"

namespace LightFx
{
    namespace Colorables
    {
        DECLARE_SMARTPOINTER(CrossfadeColorer);
        class CrossfadeColorer :
            public Colorer
        {
        public:
            CrossfadeColorer() :
                CrossfadeColorer(Pixel(1,1,1), Pixel(1,1,1), milliseconds(0))
            { }

            CrossfadeColorer(Pixel colorTo, Pixel ColorFrom, milliseconds fadeTime)
            { 
                SetDuration(fadeTime);
            }

            void SetToColor(Pixel to)
            {
                m_toColor = to;
            }

            void SetFromColor(Pixel from)
            {
                m_fromColor = from;
            }

        protected:
            // Called when the class should set the color
            virtual Pixel OnColorSelf(uint64_t tick, milliseconds elapsedTime);

            // Returns an interpolated color between from and to based on progress.
            Pixel InterpolateColor(Pixel from, Pixel to);

        private:
            Pixel m_fromColor;
            Pixel m_toColor;
        };
    }
}