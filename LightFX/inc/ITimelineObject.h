#pragma once

#include <stdint.h>

#include "Common.h"
#include "IDrivable.h"


namespace LightFx
{    
    DECLARE_SMARTPOINTER(ITimelineObjectCallback);
    DECLARE_SMARTPOINTER(ITimelineObject);
    class ITimelineObject :
        public IDrivable
    {
    public:
        // Sets a callback that is fired when the timeline is done.
        virtual void SetFinishedCallback(ITimelineObjectCallbackWeakPtr callback) = 0;

        // Called by the base class to set the duration.
        virtual void SetDuration(milliseconds duration) = 0;
    };

    // Used send notifications when time lines are complete    
    class ITimelineObjectCallback
    {
    public:
        virtual void OnTimelineFinished(ITimelineObjectPtr timeline) = 0;
    };
}