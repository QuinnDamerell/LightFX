#pragma once

#include <stdint.h>
#include <vector>

#include "Common.h"

namespace LightFx
{    
    class Pixel
    {        
        public:
            Pixel() :
                A(0),
                R(0),
                G(0),
                B(0)
            {};

            Pixel(double a, double r, double g, double b) :
                A(a),
                R(r),
                G(g),
                B(b)
            { }

            double A;
            double R;
            double G;
            double B;
    };

    typedef std::vector<std::vector<Pixel>> Pixel2DArray;
    typedef std::shared_ptr<std::vector<std::vector<Pixel>>> Pixel2DArrayPtr;
}