#include <cstdio>
#include <iostream>
#include <random>

#include "LightFxSampleRunner.h"
#include "Layers/Drawable/Draw/DrawablePixel.h"
#include "Layers/Drawable/Color/ConstantColorable.h"
#include "Layers/Drawable/Fade/SimpleFade.h"


using namespace LightFx;
using namespace LightFx::Layers;
using namespace LightFx::Layers::Drawable;

void LightFxSampleRunner::Setup()
{
    // Make our panel
    m_panel = std::make_shared<Panel>(8, 8);
    m_panel->SetPanelRenderedCallback(std::dynamic_pointer_cast<IPanelRenderedCallback>(shared_from_this()));

    // Make the driver for the panel
    m_driver = std::make_shared<ConstantRateDriver>();
    m_driver->AddDriveable(std::dynamic_pointer_cast<IDrivable>(m_panel));

    // Create some layers
    SolidColorLayerPtr background = std::make_shared<SolidColorLayer>();
    background->SetColor(Pixel(.2, 0, 0, 1));

    // Create a drawable layer, we will use this later
    m_drawableLayer = std::make_shared<DrawableLayer>();

    // Add the layers         
    m_panel->AddLayer(std::dynamic_pointer_cast<ILayer>(background), 100);
    m_panel->AddLayer(std::dynamic_pointer_cast<ILayer>(m_drawableLayer), 105);

    // Start the driver
    m_driver->Start(milliseconds(500));
}

int64_t renderCount = 0;
std::random_device rd;
std::uniform_int_distribution<int> dist(0, 7);
std::uniform_int_distribution<int> largerDist(10, 20);
std::normal_distribution<double> doubleDist(0, 1);

// Called when a render is complete
void LightFxSampleRunner::OnPanelRendered()
{
    // Every 20 renders lets add a new pixel
    renderCount--;
    if (renderCount < 0)
    {
        renderCount = largerDist(rd);

        // Create a drawable pixel and place is randomly
        DrawablePixelPtr pixel = std::make_shared<DrawablePixel>(dist(rd), dist(rd));

        // Give it a constant color but random color
        ConstantColorablePtr color = std::make_shared<ConstantColorable>(Pixel(.6, doubleDist(rd), doubleDist(rd), doubleDist(rd)));

        // And make a nice fade effect
        SimpleFadePtr fade = std::make_shared<SimpleFade>(1, 0.0, milliseconds(10000));

        // Set the color to the pixel
        pixel->SetColorable(color);

        // Add the fade to the color
        color->SetFadable(fade);

        // And add the pixel to the drawing panel
        m_drawableLayer->AddDrawable(pixel, 99);
    }

    std::cout << "\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n";

    OutputBitmapPtr outputBitmap = m_panel->GetOutputBitmap();
    uint8_t* array = outputBitmap->GetPixelArray();
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8 * 3; x++)
        {
            if (x % 3 == 0)
                std::cout << "[";
            uint64_t itnvalue = (uint8_t)(array[(8 * y * 3) + x]);
            std::cout << itnvalue << ",";
            if (x % 3 == 2)
                std::cout << "]";
        }
        std::cout << "\r\n";
    }
};