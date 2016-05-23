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
        // Drawable is the base class of anything that is rendered.
        // Is serves two main purposes:
        //    1) Since a drawable can have drawable children, they can be used as layers to group items.
        //    2) It is also what all things that actually draw use, it is also used to create things that draw color.
        //
        // Intensity
        //    Drawable inherits from IntensityObject thus it has intensity and can be faded.
        // Clean Up
        //    If CleanupWhenComplete is set, the drawable will be automatically removed from the render tree when all FX are done on it.
        //    This allows a "fire and forget" where the customer can create panels that will fade out and then are removed.
        //    Conditions:
        //        CleanupWhenComplete must be set to true
        //        The drawable must have at least one fader or colorable
        //        Both the fader and colorable must report complete.

        DECLARE_SMARTPOINTER(Drawable);
        class Drawable :
            public IDrawable          
        {

        public:
            Drawable() :
                Drawable(0)
            { }

            Drawable(bool cleanUpWhenComplete) :
                m_ignoredDrawTime(0),
                m_cleanUpWhenComplete(cleanUpWhenComplete)
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

            // If set, when all of the time line objects on this drawable are done
            // the drawable will be cleaned up.
            virtual void CleanupWhenComplete(bool cleanup);

            // Indicates if all of the time line objects are complete or not.
            virtual bool ShouldBeCleanedUp();

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

            //
            // Clean up logic
            bool m_cleanUpWhenComplete;

            // Called when the drawable should draw it's self.
            virtual void OnDrawSelf(uint64_t tickCount, milliseconds elapsedTime)
            {
                // We don't have anything to draw, class that inherit from drawable should
                // overrite this and draw.
            }
        };
    }
}