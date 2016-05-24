#pragma once

#include <stdint.h>

#include "Common.h"
#include "Drawables/Drawable.h"
#include "ITimelineObject.h"
#include "SharedFromThisHelper.h"
#include "Pixel.h"
#include "Bitmap.h"

namespace LightFx
{
    namespace Drawables
    {
        // The direction of the swipe
        enum class SwipeDirection
        {
            Up,
            Down,
            Left,
            Right
        };

        DECLARE_SMARTPOINTER(SwipeDrawable);
        class SwipeDrawable :
            public Drawable,
            public ITimelineObjectCallback,
            public SharedFromThis
        {
        public:
            SwipeDrawable() :
                SwipeDrawable(true)
            {}

            SwipeDrawable(bool shouldCleanUp) :
                Drawable(shouldCleanUp),
                m_direction(SwipeDirection::Up),
                m_currentPosition(0)
            {}

            void SetDirection(SwipeDirection direction)
            {
                m_direction = direction;
            }

            // Fired when the last pass finshes
            void OnTimelineFinished(ITimelineObjectPtr timeline);

        protected:

            // Called when the drawable should draw it's self.
            virtual void OnDrawSelf(uint64_t tickCount, milliseconds elapsedTime) override;

        private:
            SwipeDirection m_direction;
            int64_t m_currentPosition;
        };  
    }
}