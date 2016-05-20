// LightFXSample.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include "stdafx.h"
#include "LightFxSampleRunner.h"

using namespace LightFx;

int main()
{
    LightFxSampleRunnerPtr runner = std::make_shared<LightFxSampleRunner>();
    runner->Setup();


    for (std::string line; std::getline(std::cin, line);) {
        std::cout << line << std::endl;
    }

    return 0;
}

