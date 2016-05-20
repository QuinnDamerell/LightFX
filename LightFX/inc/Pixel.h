#pragma once

#include <stdint.h>
#include <vector>
#include <random>
#include <algorithm>

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

    // Generates a random color based on a random value from 1 - 0
    // and color ranges. If the color is generated based on 3 random values from 1 - 0
    // for each RBG there is a higher chance of hitting 50% for each value, thus the 
    // resulting colors are more likely to be in the middle of the color range.
    static Pixel GenerateRandomColor(bool randomAlpha = false)
    {
        const uint8_t RANGE_SIZE = 6;
        const double redRange[] = { 1, 1, 0, 0, 0, 1 };
        const double blueRange[] = { 0, 1, 1, 1, 0, 0 };
        const double greenRange[] = { 0, 0, 0, 1, 1, 1 };

        // Create a random value
        std::random_device rand;
        std::uniform_real_distribution<double> dist(0, 1);
        double randomValue = dist(rand);

        // Wrap if it is exactly 1
        if (randomValue == 1)
        {
            randomValue = 0;
        }

        // Find what bucket we are in for the value. (Which slice of the 1/6th are we)
        uint8_t rangeBot = (uint8_t)std::floor(((randomValue) * RANGE_SIZE));
        uint8_t rangeTop = rangeBot + 1;
        if (rangeTop == RANGE_SIZE)
        {
            rangeTop = 0;
        }

        // Within the that slice of 1/6th, how far are we through it?
        // First normalize the value so it is between 0 and 1/6th of (1 - 0)
        double normalizedValue = randomValue - ((1.0 / static_cast<double>(RANGE_SIZE)) * rangeBot);

        // Now calc the % of the normalized value and the size of the 1/6th.
        double locationInRange = normalizedValue / (1.0 / static_cast<double>(RANGE_SIZE));

        // Now set the value
        Pixel randomColor;
        randomColor.A = 1;
        randomColor.R = redRange[rangeBot] + (redRange[rangeTop] - redRange[rangeBot]) * locationInRange;
        randomColor.G = greenRange[rangeBot] + (greenRange[rangeTop] - greenRange[rangeBot]) * locationInRange;
        randomColor.B = blueRange[rangeBot] + (blueRange[rangeTop] - blueRange[rangeBot]) * locationInRange;

        // Set a random alpha if needed
        if (randomAlpha)
        {
            // Technically this should be part of the range, but this is good enough for now.
            randomColor.A = dist(rand);
        }

        return randomColor;
    }
}