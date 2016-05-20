#pragma once

#include <algorithm>
#include <stdint.h>

#include "Common.h"

namespace LightFx
{
    namespace Layers
    {
        namespace Drawable
        {
            DECLARE_SMARTPOINTER(TimelineObject);
            class TimelineObject
            {

            public:
                // This can be created stand alone or in a chain.
                TimelineObject() :
                    m_remaining(milliseconds(0)),
                    m_duration(milliseconds(0)),
                    m_shouldCleanupWhenFinished(false),  
                    m_lastUpdateTickCount(8888888)
                {}  

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

            protected:

                // Sets a child time line we should care about
                void SetChildTimeline(TimelineObjectWeakPtr childTimeline)
                {
                    m_childTimeline = childTimeline;
                }

                // Called by the base class to set the duration.
                void SetDuration(milliseconds duration)
                {
                    m_duration = duration;
                    m_remaining = m_duration;
                }

                // Called by the base class to report more time has elapsed.
                void AddTimeElapsed(milliseconds timeElapsed, uint64_t tickCount)
                {
                    // Check the tick count to make sure we aren't updating twice.
                    // This can happen if the same fade is held by two different objects
                    if (tickCount != m_lastUpdateTickCount)
                    {
                        m_lastUpdateTickCount = tickCount;
                        m_remaining -= timeElapsed;
                    }
                }

                // Callable by the base class to report it is done.
                void SetFinished(bool finished)
                {
                    m_remaining = milliseconds(0);
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

            private:
                // Time line logic
                milliseconds m_duration;
                milliseconds m_remaining;
                uint64_t m_lastUpdateTickCount;

                TimelineObjectWeakPtr m_childTimeline;
                bool m_shouldCleanupWhenFinished;
            };
        }
    }
}