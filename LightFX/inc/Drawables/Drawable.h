#pragma once

#include <stdint.h>
#include <mutex>

#include "Common.h"
#include "Drawables/IDrawable.h"
#include "Bitmap.h"

namespace LightFx
{
    namespace Drawables
    {
        DECLARE_SMARTPOINTER(Drawable);
        class Drawable :
            public IDrawable          
        {

        public:
            Drawable() :
                m_ignoredDrawTime(0)
            { }

            // Sets and updates the size of the drawable
            virtual void SetSize(uint64_t height, uint64_t width);

            // Returns the width
            virtual uint64_t GetWitdh();

            // Returns the height
            virtual uint64_t GetHeight();

            // Adds a drawable to the drawable
            virtual void AddDrawable(IDrawablePtr drawable, int64_t zIndex);

            // Called when the drawable should draw.
            virtual void OnDraw(uint64_t tickCount, milliseconds elapsedTime, BitmapPtr backBuffer);

        protected:

            typedef std::pair<IDrawablePtr, int64_t> DrawableZIndexPair;

            // 
            // Drawable logic
            std::mutex m_drawableCollectionLock;
            std::vector<DrawableZIndexPair> m_drawableCollection;

            // 
            // Bitmap logic
            BitmapPtr m_bitmap;

            // Holds anytime that passed but we ignored.
            milliseconds m_ignoredDrawTime;

            // Called when the drawable should draw it's self.
            virtual void OnDrawSelf(uint64_t tickCount, milliseconds elapsedTime)
            {
                // We don't have anything to draw, class that inherit from drawable should
                // overrite this and draw.
            }
        };
    }
}