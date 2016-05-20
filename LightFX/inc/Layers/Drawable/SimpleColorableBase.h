#pragma once

#include <stdint.h>

#include "Common.h"
#include "Layers/Drawable/IColorable.h"
#include "Layers/Drawable/IFadable.h"
#include "Layers/Drawable/TimelineObject.h"
#include "Bitmap.h"

namespace LightFx
{
    namespace Layers
    {
        namespace Drawable
        {
            DECLARE_SMARTPOINTER(SimpleColorableBase);
            class SimpleColorableBase :
                public IColorable,
                public TimelineObject
            {
            public:

                // Sets the fade element for this drawable
                void SetFadable(IFadablePtr faceable)
                {
                    m_fadable = faceable;
                    SetChildTimeline(std::dynamic_pointer_cast<TimelineObject>(m_fadable));                    
                }

            protected:
                // We can only be created by base classes
                SimpleColorableBase() :
                    m_fadable(nullptr)
                {}

                //
                // IColorable
                // 

                // Called when the colorable should return a color.
                virtual Pixel OnColor(uint64_t tickCount, milliseconds elapsedTime);

                //
                // Base functions
                //

                // Called by the base when the sub class should return a color
                virtual Pixel GetColor(uint64_t tickCount, milliseconds elapsedTime, double alpha) = 0;

            private:
                IFadablePtr m_fadable;
            };
        }
    }
}