#pragma once

#include <stdint.h>
#include <mutex>

#include "Common.h"
#include "Drawables/IDrawable.h"
#include "Colorables/IColorable.h"
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
                m_cleanUpWhenComplete(cleanUpWhenComplete),
                m_forceCleanUp(false),
                m_xPos(0),
                m_yPos(0)
            { }

            // Sets and updates the size of the drawable
            virtual void SetSize(int64_t height, int64_t width);

            // Set the top left corner of the drawable. This is the position
            // where it will draw on the drawable under it.
            virtual void SetPosition(int64_t x, int64_t y);

            // Returns the width
            virtual int64_t GetWitdh();

            // Returns the height
            virtual int64_t GetHeight();

            // Returns the X Position of this drawable
            virtual int64_t GetXPosition();

            // Returns the Y Position of this drawable
            virtual int64_t GetYPosition();

            // Adds a drawable to the drawable
            virtual void AddDrawable(IDrawablePtr drawable, int64_t zIndex);

            // Called when the drawable should draw.
            virtual void OnDraw(uint64_t tickCount, milliseconds elapsedTime, BitmapPtr backBuffer);

            // If set, when all of the time line objects on this drawable are done
            // the drawable will be cleaned up.
            virtual void CleanupWhenComplete(bool cleanup);

            // Indicates if all of the time line objects are complete or not.
            virtual bool ShouldBeCleanedUp();

            //
            // IColorable

            // Sets a colorable object
            virtual void SetColorer(Colorables::IColorerPtr colorer);

            // Gets the colorer if there is one
            virtual Colorables::IColorerPtr GetColorer();

            // Sets the color to the object
            virtual void SetColor(Pixel color);

            // Gets the color of the object
            virtual Pixel GetColor();

        protected:

            typedef std::pair<IDrawablePtr, int64_t> DrawableZIndexPair;
            typedef std::pair<Colorables::IColorerPtr, int64_t> ColorerZIndexPair;

            // 
            // Drawable logic
            std::mutex m_drawableCollectionLock;
            std::vector<DrawableZIndexPair> m_drawableCollection;

            //
            // Colorable
            Pixel m_color;
            Colorables::IColorerPtr m_colorer;

            // 
            // Bitmap logic
            BitmapPtr m_bitmap;

            // Holds anytime that passed but we ignored.
            milliseconds m_ignoredDrawTime;

            // Position logic
            int64_t m_xPos;
            int64_t m_yPos;

            //
            // Clean up logic
            bool m_cleanUpWhenComplete;
            bool m_forceCleanUp;

            // Called when the drawable should draw it's self.
            virtual void OnDrawSelf(uint64_t tickCount, milliseconds elapsedTime)
            {
                // We don't have anything to draw, class that inherit from drawable should
                // overrite this and draw.
            }
        };
    }
}