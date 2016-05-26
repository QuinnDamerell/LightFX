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
            void SetPosition(int64_t x, int64_t y, int64_t height, int64_t width);

        protected:

            // Called when the drawable should draw it's self.
            virtual void OnDrawSelf(uint64_t tickCount, milliseconds elapsedTime) override;

        private:
            int64_t m_x;
            int64_t m_y;
            int64_t m_height;
            int64_t m_width;
        };
    }
}