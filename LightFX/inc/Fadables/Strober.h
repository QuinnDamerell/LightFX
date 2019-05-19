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
        DECLARE_SMARTPOINTER(Strober);
        class Strober :
            public IFader
        {
        public:
            Strober() :
                Strober(milliseconds(0), milliseconds(0), 1, 0)
            {}

            Strober(milliseconds interval, milliseconds duration) :   
                Strober(interval, duration, 1, 0)
            { }
            
            Strober(milliseconds interval, milliseconds duration, double onValue, double offValue) :
                m_onValue(onValue),
                m_offValue(offValue),
                m_interval(interval),
                m_intervalCounter(interval.count())
            { 
                SetDuration(duration);
            }

            virtual ~Strober() {}

            // Fired when we should update
            virtual void OnTick(uint64_t tick, milliseconds elapsedTime) override;

            // Used to add a drawable to our list
            void AddFadingDrawable(IIntensityObjectWeakPtr fadeable) override;

            // Used to remove a drawable to out list
            void RemoveFadingDrawable(IIntensityObjectWeakPtr fadeable) override;

            //
            // Fader logic
            virtual void SetTo(double on) { m_onValue = on; }
            virtual double GetTo() { return m_onValue; }

            virtual void SetFrom(double off) { m_offValue = off; }
            virtual double GetFrom() { return m_offValue; }

            virtual void SetInterval(milliseconds inter) { m_interval = inter; }
            virtual milliseconds GetInterval() { return m_interval; }

        private:
            // Collection logic
            std::mutex m_drawablesLock;
            std::vector<IIntensityObjectWeakPtr> m_drawables;

            // Fader vars
            double m_onValue;
            double m_offValue;
            milliseconds m_interval;
            int64_t m_intervalCounter;
        };
    }
}