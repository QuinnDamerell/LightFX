#pragma once

#include <stdint.h>
#include <mutex>

#include "Common.h"
#include "Drawables/Drawable.h"
#include "Pixel.h"
#include "Bitmap.h"

namespace LightFx
{
    namespace Drawables
    {
        DECLARE_SMARTPOINTER(SolidDrawable);
        class SolidDrawable :
            public Drawable
        {
        public:
            SolidDrawable() :
                Drawable(false)
            {}

            SolidDrawable(bool shouldCleanUp) :
                Drawable(shouldCleanUp)
            {}

            // Sets the position of the drawing
            void SetPosition(uint64_t x, uint64_t y, uint64_t height, uint64_t width);

        protected:

            // Called when the drawable should draw it's self.
            virtual void OnDrawSelf(uint64_t tickCount, milliseconds elapsedTime) override;

        private:
            uint64_t m_x;
            uint64_t m_y;
            uint64_t m_height;
            uint64_t m_width;
        };
    }
}