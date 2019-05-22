#pragma once

#include <stdint.h>

#include "Common.h"
#include "Bitmap.h"
#include "IntensityObject.h"
#include "Colorables/IColorable.h"

namespace LightFx
{
    namespace Drawables
    {
        DECLARE_SMARTPOINTER(IDrawable);
        class IDrawable :
            public IntensityObject,
            public Colorables::IColorable
        {
        public:
            // Sets and updates the size of the drawable
            virtual void SetSize(int64_t height, int64_t width) = 0;

            // Set the top left corner of the drawable. This is the position
            // where it will draw on the drawable under it.
            virtual void SetPosition(int64_t x, int64_t y) = 0;

            // Returns the width
            virtual int64_t GetWitdh() = 0;

            // Returns the height
            virtual int64_t GetHeight() = 0;

            // Returns the X Position of this drawable
            virtual int64_t GetXPosition() = 0;

            // Returns the Y Position of this drawable
            virtual int64_t GetYPosition() = 0;

			// Sets a flag indicating if this drawable should be cleaned up and
			// deleted.
			virtual void SetCleanupFlag(bool cleanup) = 0;

            // Adds a drawable to the drawable
            virtual void AddDrawable(IDrawablePtr drawable, int64_t zIndex) = 0;

            // Called when the drawable should draw.
            virtual void OnDraw(uint64_t tickCount, milliseconds elapsedTime, BitmapPtr backBuffer) = 0;

            // If set, when all of the time line objects on this drawable are done
            // the drawable will be cleaned up.
            virtual void CleanupWhenComplete(bool cleanup) = 0;

            // Indicates if all of the time line objects are complete or not.
            virtual bool ShouldBeCleanedUp() = 0;
        };
    }    
}