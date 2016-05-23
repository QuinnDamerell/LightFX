#pragma once

#include <stdint.h>
#include <mutex>
#include <vector>

#include "Common.h"
#include "Colorables/IColorable.h"
#include "Colorables/IColorer.h"
#include "TimelineObject.h"

namespace LightFx
{
    namespace Colorables
    {
        DECLARE_SMARTPOINTER(Colorer);
        class Colorer :
            public IColorer
        {
        public:

            // Fired when we should update
            virtual void OnTick(uint64_t tick, milliseconds elapsedTime) override;

            // Adds a drawable to the colorer
            virtual void AddColorable(IColorableWeakPtr colorable);

            // Removes a drawable to the colorer
            virtual void RemoveColorable(IColorableWeakPtr colorable);

        protected:

            // Called when the class should set the color
            virtual Pixel OnColorSelf(uint64_t tick, milliseconds elapsedTime)
            {
                // The default color does nothing here, classes that inherit form this should
                // override this and do work.
                return Pixel(0, 0, 0);
            }

        private:
            // Collection logic
            std::mutex m_colorablesLock;
            std::vector<IColorableWeakPtr> m_colorables;
        };
    }
}