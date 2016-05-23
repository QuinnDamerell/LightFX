#pragma once

#include <stdint.h>

#include "Common.h"

#include "Colorables/IColorer.h"
#include "Pixel.h"

namespace LightFx
{
    namespace Colorables
    {
        DECLARE_SMARTPOINTER(IColorable);
        class IColorable
        {

        public:
            // Sets a colorable object
            virtual void SetColorer(IColorerPtr colorer) = 0;

            // Gets the colorer if there is one
            virtual IColorerPtr GetColorer() = 0;

            // Sets the color to the object
            virtual void SetColor(Pixel color) = 0;

            // Gets the color of the object
            virtual Pixel GetColor() = 0;
        };
    }    
}