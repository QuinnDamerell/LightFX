#pragma once

#include <stdint.h>
#include <mutex>
#include <vector>

#include "Common.h"
#include "Fadables/IFader.h"
#include "Fadables/IFadable.h"
#include "TimelineObject.h"

namespace LightFx
{
    namespace Fadables
    {
        DECLARE_SMARTPOINTER(Fader);
        class Fader :
            public IFader,
            public TimelineObject
        {
        public:

            virtual void OnTick(uint64_t tick, milliseconds elapsedTime) override
            {
                // Call the base
                TimelineObject::OnTick(tick, elapsedTime);

                // Now update the intensity.
            };

            void AddFadingDrawable(IFadableWeakPtr fadeable)
            {
                m_drawables.insert(m_drawables.begin(), fadeable);
            }

            void RemoveFadingDrawable(IFadableWeakPtr fadeable)
            {
                // todo


            }

        private:
            std::vector<IFadableWeakPtr> m_drawables;

        };
    }
}