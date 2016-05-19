// LightFXSample.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include "stdafx.h"
#include "Panel.h"
#include "ConstantRateDriver.h"
#include "Layers\SolidColorLayer.h"

using namespace LightFx;

int main()
{
    PanelPtr base = std::make_shared<Panel>(5,5);

    SolidColorLayerPtr layer = std::make_shared<SolidColorLayer>();
    layer->SetColor(Pixel(1, 0, 0, .2));
    base->AddLayer(std::dynamic_pointer_cast<ILayer>(layer), 100);
    ConstantRateDriverPtr driver = std::make_shared<ConstantRateDriver>();
    driver->AddDriveable(std::dynamic_pointer_cast<IDrivable>(base));
    driver->Start(32);


    for (std::string line; std::getline(std::cin, line);) {
        std::cout << line << std::endl;
    }

    return 0;
}

