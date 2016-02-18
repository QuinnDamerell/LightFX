#pragma once

#include "Common.h"
#include "ILightable.h"

class EffectBase :
    public ILightable
{
public:
    EffectBase() {}
    ~EffectBase() {}

protected:
    void CalculateEffect();

private:
    void SetValue(double brightness, double red, double gree, double blue);
};