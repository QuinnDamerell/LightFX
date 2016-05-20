#pragma once

#include <stdint.h>

#include "Common.h"

#include "Panel.h"
#include "ConstantRateDriver.h"
#include "Layers\SolidColorLayer.h"
#include "OutputBitmap.h"

#include "Layers/Drawable/DrawableLayer.h"

namespace LightFx
{
    DECLARE_SMARTPOINTER(LightFxSampleRunner);
    class LightFxSampleRunner :
        public std::enable_shared_from_this<LightFxSampleRunner>,
        public IPanelRenderedCallback
    {
    public:

        // Called when we should setup.
        void Setup();       

        // Called when a render is complete
        void OnPanelRendered() override;

        double alpha = 0;
        PanelPtr m_panel;
        ConstantRateDriverPtr m_driver;
        Layers::SolidColorLayerPtr overlay;
        Layers::Drawable::DrawableLayerPtr  m_drawableLayer;
    };
}
