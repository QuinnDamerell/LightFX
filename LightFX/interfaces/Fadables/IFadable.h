#pragma once

#include <stdint.h>

#include "Common.h"

#include "Fadables/IFader.h"

namespace LightFx
{
    namespace Fadables
    {
        DECLARE_SMARTPOINTER(IFadable);
        class IFadable
        {

        public:
            // Sets a fader object
            virtual void SetFader(IFaderPtr fader) = 0;

            // Gets the fader if there is one
            virtual Fadables::IFaderPtr GetFader() = 0;
        };
    }    
}