#pragma once

#include <algorithm>
#include <stdint.h>

#include "Common.h"
#include "ITimelineObject.h"
#include "SharedFromThisHelper.h"

namespace LightFx
{
    DECLARE_SMARTPOINTER(TimelineObject);            
    class TimelineObject :
        public ITimelineObject,
        public SharedFromThis
    {

    public:
        TimelineObject() :
            m_remaining(milliseconds(0)),
            m_duration(milliseconds(0)),
            m_lastUpdateTickCount(8888888)
        {}  

        virtual ~TimelineObject() {};

        // Fired when time has passed
        virtual void OnTick(uint64_t tick, milliseconds elapsedTime);

        // Sets a callback that is fired when the timeline is done.
        void SetFinishedCallback(ITimelineObjectCallbackWeakPtr callback)
        {
            m_finishedCallback = callback;
        }

        // Indicates if the time line is done or not
        virtual bool IsComplete() 
        {
            return m_remaining.count() <= 0;
        };

        // Called by the base class to set the duration.
        void SetDuration(milliseconds duration);

    protected:

        // Callable by the base class to report it is done.
        void SetFinished(bool finished);

        // Returns the progress.
        double GetProgress();

        // Returns an interpolated value between from and to based on progress.
        double InterpolateValue(double from, double to);

        // Fires the callback if it is there.
        void FireFinishedCallback();

    private:
        // Time line logic
        milliseconds m_duration;
        milliseconds m_remaining;
        uint64_t m_lastUpdateTickCount;

        // Other logic
        ITimelineObjectCallbackWeakPtr m_finishedCallback;
    };
}   
