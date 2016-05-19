#pragma once

#include <stdint.h>

#include "Common.h"

namespace LightFx
{
    DECLARE_SMARTPOINTER(IDrivable);
    class IDrivable
    {
    public:
        virtual void OnTick(uint64_t tick, uint64_t elapsedTimeMs) = 0;
    };
}
#pragma once
