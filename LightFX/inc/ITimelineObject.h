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


    };

    
    class ITimelineObjectCallback
    {
    public:
        virtual void OnTimelineFinished(ITimelineObjectPtr timeline) = 0;
    };
}