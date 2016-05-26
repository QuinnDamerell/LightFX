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
        DECLARE_SMARTPOINTER(ExpandingDrawable);
        class ExpandingDrawable :
            public Drawable,
            public ITimelineObjectCallback,
            public SharedFromThis
        {
        public:
            ExpandingDrawable();

            ExpandingDrawable(bool shouldCleanUp);

            void SetStartingPoint(int64_t x, int64_t y)
            {
                m_startingX = x;
                m_startingY = y;
            }

            void SetTimeBetweenRows(std::chrono::milliseconds timeBetweenDraws)
            {
                m_timeBetweenDraws = timeBetweenDraws;
            }

            // Fired when the last pass finishes
            void OnTimelineFinished(ITimelineObjectPtr timeline);

        protected:

            // Called when the drawable should draw it's self.
            virtual void OnDrawSelf(uint64_t tickCount, milliseconds elapsedTime) override;

        private:
            int64_t m_currentPosition;
            int64_t m_startingX;
            int64_t m_startingY;

            // Holds the last side we drew, used for clean up.
            IDrawablePtr m_lastDrawnSide;

            // Keeps track of how long before the next draw.
            std::chrono::milliseconds m_timeBetweenDraws;
            std::chrono::milliseconds m_timeUntilNextDraw;

            // The direction of the current draw
            enum class SquareSide
            {
                Top = 0,
                Right = 1,
                Bottom = 2,
                Left = 3,
                End = 4
            };            
        };
    }
}