#pragma once

#include <stdint.h>

#include "Common.h"
#include "TimelineObject.h"

namespace LightFx
{    
    namespace Colorables
    {
        // We have to forward declare colorable here so we don't get
        // a header cycle.
        class IColorable;

        DECLARE_SMARTPOINTER(IColorer);
        class IColorer
            : public TimelineObject
        {

        public:
            //
            // Management

            virtual void AddColorable(std::weak_ptr<IColorable> colorable) = 0;

            virtual void RemoveColorable(std::weak_ptr<IColorable> colorable) = 0;
        };
    }    
}