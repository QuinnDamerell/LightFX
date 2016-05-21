#pragma once

#include <stdint.h>

#include "Common.h"
#include "Layers/Drawable/IColorable.h"
#include "Layers/Drawable/IIntensitable.h"
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
                void SetFadable(IIntensitablePtr intensitable)
                {
                    m_intensitable = intensitable;
                    SetChildTimeline(std::dynamic_pointer_cast<TimelineObject>(m_intensitable));
                }

            protected:
                // We can only be created by base classes
                SimpleColorableBase() :
                    m_intensitable(nullptr)
                {}

                //
                // IColorable
                // 

                // Called when the colorable should return a color.
                virtual LightColor OnColor(uint64_t tickCount, milliseconds elapsedTime);

                //
                // Base functions
                //

                // Called by the base when the sub class should return a color
                virtual LightColor GetColor(uint64_t tickCount, milliseconds elapsedTime, double intensity) = 0;

            private:
                IIntensitablePtr m_intensitable;
            };
        }
    }
}