#pragma once

#include <stdint.h>
#include <vector>
#include <mutex>

#include "Common.h"
#include "ILayer.h"
#include "IDrawable.h"
#include "Bitmap.h"

namespace LightFx
{
    namespace Layers
    {
        namespace Drawable
        {
            DECLARE_SMARTPOINTER(DrawableLayer);
            class DrawableLayer :
                public ILayer
            {
            public:
                DrawableLayer() :
                    m_width(0),
                    m_height(0)
                { }

                //
                // ILayer
                //
                void UpdatePanelSize(uint64_t height, uint64_t width)
                {
                    m_width = width;
                    m_height = height;
                    m_bitmap = std::make_shared<Bitmap>(m_height, m_width);
                }

                BitmapPtr OnDraw(uint64_t tickCount, milliseconds elapsedTime, Bitmap& backBuffer);      

                //
                // General Access
                // 

                inline uint64_t GetWidth()
                {
                    return m_width;
                }

                inline uint64_t GetHeight()
                {
                    return m_height;
                }

                //
                // Drawable Access
                //
                void AddDrawable(IDrawablePtr drawable, uint64_t zIndex);

                bool RemoveDrawable(IDrawablePtr drawable);

            private:
                
                uint64_t m_width;
                uint64_t m_height;

                std::mutex m_drawableListMutex;
                std::vector<std::pair<uint64_t, IDrawablePtr>> m_drawableList;    

                BitmapPtr m_bitmap;
            };
        }
    }
}