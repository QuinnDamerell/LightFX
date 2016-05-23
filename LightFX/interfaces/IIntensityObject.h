#pragma once

#include <stdint.h>

#include "Common.h"

#include "Fadables/IFadable.h"

namespace LightFx
{
    DECLARE_SMARTPOINTER(IIntensityObject);
    class IIntensityObject :
        public Fadables::IFadable
    {
    public:

        // Gets the intensity for the object
        virtual double GetIntensity() = 0 ;

        // Sets the intensity for the object
        virtual void SetIntensity(double intensity) = 0;
    };    
}