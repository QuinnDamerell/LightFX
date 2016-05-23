#pragma once

#include <stdint.h>

#include "Common.h"
#include "TimelineObject.h"

namespace LightFx
{    
    // We have to forward declare IIntensityObject here or we will had a
    // header cycle.
    class IIntensityObject;

    namespace Fadables
    {
        DECLARE_SMARTPOINTER(IFader);
        class IFader
            : public TimelineObject
        {

        public:
            //
            // Management

            virtual void AddFadingDrawable(std::weak_ptr<IIntensityObject> fadeable) = 0;

            virtual void RemoveFadingDrawable(std::weak_ptr<IIntensityObject> fadeable) = 0;

            //
            // Vars
            virtual void SetTo(double to) = 0;
            virtual double GetTo() = 0;

            virtual void SetFrom(double from) = 0;
            virtual double GetFrom() = 0;
        };
    }    
}