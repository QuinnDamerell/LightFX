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
        DECLARE_SMARTPOINTER(RainbowColorer);
        class RainbowColorer :
            public Colorer
        {
        public:

            RainbowColorer() :
                RainbowColorer(milliseconds(20000))
            { }

            RainbowColorer(milliseconds cycleTime) :
                m_fullCycleTime(cycleTime),
                m_cycleTimeRemaining(milliseconds(0))
            { }      

        protected:
            // Called when the class should set the color
            virtual Pixel OnColorSelf(uint64_t tick, milliseconds elapsedTime);

        private:
            milliseconds m_cycleTimeRemaining;
            milliseconds m_fullCycleTime;
        };
    }
}