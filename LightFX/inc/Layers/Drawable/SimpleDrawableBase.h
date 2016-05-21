#pragma once

#include <stdint.h>

#include "Common.h"
#include "Layers/Drawable/IDrawable.h"
#include "Layers/Drawable/IColorable.h"
#include "Layers/Drawable/TimelineObject.h"


namespace LightFx
{
    namespace Layers
    {
        namespace Drawable
        {
            DECLARE_SMARTPOINTER(SimpleDrawableBase);
            class SimpleDrawableBase :
                public IDrawable,
                public TimelineObject
            {
            public:

                // Sets the color element for this drawable
                void SetColorable(IColorablePtr colorable)
                {
                    m_colorable = colorable;
                    SetChildTimeline(std::dynamic_pointer_cast<TimelineObject>(m_colorable));
                }

            protected:
                // We can only be created by base classes
                SimpleDrawableBase() :
                    m_colorable(nullptr)
                {}

                //
                // IDrawable
                // 

                // Called when the drawable should draw something.
                virtual void OnDraw(uint64_t tickCount, milliseconds elapsedTime, BitmapPtr buffer);

                //
                // Base functions
                //
                
                // Called by the base when the sub class should draw pixels
                virtual void DrawPixels(uint64_t tickCount, milliseconds elapsedTime, BitmapPtr buffer, LightColor& color) = 0;

            private:
                IColorablePtr m_colorable;
            };
        }
    }
}