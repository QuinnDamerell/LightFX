#pragma once

#include <stdint.h>
#include <mutex>
#include <vector>

#include "Common.h"
#include "Fadables/IFader.h"
#include "Fadables/IFadable.h"
#include "TimelineObject.h"
#include "IIntensityObject.h"

namespace LightFx
{
    namespace Fadables
    {
        DECLARE_SMARTPOINTER(Fader);
        class Fader :
            public IFader
        {
        public:
            Fader() :
                Fader(0,0, milliseconds(0))
            {}

            Fader(double to, double from) :   
                Fader(to, from, milliseconds(0))
            { }
            
            Fader(double to, double from, milliseconds duration) :
                m_to(to),
                m_from(from)
            { 
                SetDuration(duration);
            }

            virtual ~Fader() {}

            // Fired when we should update
            virtual void OnTick(uint64_t tick, milliseconds elapsedTime) override;

            // Used to add a drawable to our list
            void AddFadingDrawable(IIntensityObjectWeakPtr fadeable) override;

            // Used to remove a drawable to out list
            void RemoveFadingDrawable(IIntensityObjectWeakPtr fadeable) override;

            //
            // Fader logic
            virtual void SetTo(double to) { m_to = to; }
            virtual double GetTo() { return m_to; }

            virtual void SetFrom(double from) { m_from = from; }
            virtual double GetFrom() { return m_from; }

        private:
            // Collection logic
            std::mutex m_drawablesLock;
            std::vector<IIntensityObjectWeakPtr> m_drawables;

            // Fader vars
            double m_to;
            double m_from;
        };
    }
}