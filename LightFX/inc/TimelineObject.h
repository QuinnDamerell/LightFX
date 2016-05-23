#pragma once

#include <algorithm>
#include <stdint.h>

#include "Common.h"
#include "ITimelineObject.h"

namespace LightFx
{
    DECLARE_SMARTPOINTER(TimelineObject);            
    class TimelineObject :
        public ITimelineObject,
        public std::enable_shared_from_this<TimelineObject>
    {

    public:
        // This can be created stand alone or in a chain.
        TimelineObject() :
            m_remaining(milliseconds(0)),
            m_duration(milliseconds(0)),
            m_lastUpdateTickCount(8888888)
        {}  

        virtual ~TimelineObject() {};

        virtual void OnTick(uint64_t tick, milliseconds elapsedTime)
        {
            // If we have no remaining time we are done.
            if (m_remaining.count() <= 0)
            {
                return;
            }

            // Check the tick count to make sure we aren't updating twice.
            // This can happen if the same fade is held by two different objects
            if (tick != m_lastUpdateTickCount)
            {
                m_lastUpdateTickCount = tick;
                m_remaining -= elapsedTime;
            }

            // Check if we are finished
            if (m_remaining.count() <= 0)
            {
                SetFinished(true);
            }
        }

        // Sets a callback that is fired when the timeline is done.
        void SetFinishedCallback(ITimelineObjectCallbackWeakPtr callback)
        {
            m_finishedCallback = callback;
        }

        // Returns if we and our child are finished.
        bool IsFinished()
        {
            if (m_remaining.count() <= 0)
            {
                if (auto chlid = m_childTimeline.lock())
                {
                    return chlid->IsFinished();
                }
                return true;
            }
            return false;
        };

        // Returns if we should be cleaned up or not.
        bool ShouldCleanup()
        {
            if (IsFinished())
            {
                if (auto chlid = m_childTimeline.lock())
                {
                    return chlid->ShouldCleanup();
                }
                return m_shouldCleanupWhenFinished;
            }
            return false;
        }

        // Indicates if we should clean up when done or not.
        void ShouldCleanupWhenFinshed(bool shouldDoIt)
        {
            m_shouldCleanupWhenFinished = shouldDoIt;
        }

        // Called by the base class to set the duration.
        void SetDuration(milliseconds duration)
        {
            m_duration = duration;
            m_remaining = m_duration;
        }

    protected:

        // Sets a child time line we should care about
        void SetChildTimeline(TimelineObjectWeakPtr childTimeline)
        {
            m_childTimeline = childTimeline;
        }

        // Callable by the base class to report it is done.
        void SetFinished(bool finished)
        {
            m_remaining = milliseconds(0);

            // Fire the callback.
            FireFinishedCallback();
        }

        // Returns the progress.
        double GetProgress()
        {
            double progress = (static_cast<double>(m_remaining.count()) / static_cast<double>(m_duration.count()));
            return progress > 1 ? 1 : (progress < 0 ? 0 : progress);
        }

        // Returns an interpolated value between from and to based on progress.
        double InterpolateValue(double from, double to)
        {
            return to - (to - from) * GetProgress();
        }

        // Fires the callback if it is there.
        void FireFinishedCallback()
        {
            if (auto callback = m_finishedCallback.lock())
            {
                callback->OnTimelineFinished(shared_from_this());
            }
        }

    private:
        // Time line logic
        milliseconds m_duration;
        milliseconds m_remaining;
        uint64_t m_lastUpdateTickCount;

        // Other logic
        ITimelineObjectCallbackWeakPtr m_finishedCallback;
        TimelineObjectWeakPtr m_childTimeline;
        bool m_shouldCleanupWhenFinished;
    };
}
     
    
}