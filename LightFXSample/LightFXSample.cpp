// LightFXSample.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include "stdafx.h"
#include "LightFXBase.h"

int main()
{
    LightFxBasePtr base = std::make_shared<LightFxBase>();
    base->StartAnimation(33);

    for (std::string line; std::getline(std::cin, line);) {
        std::cout << line << std::endl;
    }

    return 0;
}

