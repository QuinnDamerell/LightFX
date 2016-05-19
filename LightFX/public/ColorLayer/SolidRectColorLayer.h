#pragma once

#include <stdint.h>
#include <string>

#include "Common.h"
#include "ColorLayerBase.h"

DECLARE_SMARTPOINTER(SolidRectColorLayer);
class SolidRectColorLayer :
    public ColorLayerBase
{
public:
    SolidRectColorLayer(std::string layerName, LightFxCordornate size, LightFxCordornate offset, LightFxColor color) :
        ColorLayerBase(layerName, size, offset)
    {
        // Set the color to the grid.
        for (int x = 0; x < m_size.X; x++)
        {
            for (int y = 0; y < m_size.Y; y++)
            {
                m_layerData->at(x)[y].Color.A = color.A;
                m_layerData->at(x)[y].Color.R = color.R;
                m_layerData->at(x)[y].Color.G = color.G;
                m_layerData->at(x)[y].Color.B = color.B;
            }
        }
    }

    ~SolidRectColorLayer()
    {
        for (int i = 0; i < m_size.X; i++)
        {
            m_layerData->at(i).clear();
        }
        m_layerData->clear();
    }
};

