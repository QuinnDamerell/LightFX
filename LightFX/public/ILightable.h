#pragma once

// An interface implemented by anything that is lightable.
class ILightable
{
    // Sets the current value.
    virtual void SetValue(double brightness, double red, double gree, double blue) = 0;
};
