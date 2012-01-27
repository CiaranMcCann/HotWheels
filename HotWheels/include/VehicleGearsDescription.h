#pragma once
#include "stdafx.h"
#include <vector>

struct VehicleGearsDescription
{
    std::vector<float> forwardGears;
    float forwardGearCount;
    float reverseGear;

    VehicleGearsDescription()
    {
        forwardGearCount = 6;
        reverseGear = -2.8f;

        forwardGears.push_back(2.66f);
        forwardGears.push_back(1.78f);
        forwardGears.push_back(1.30f);
        forwardGears.push_back(1.0f);
        forwardGears.push_back(0.74f);
        forwardGears.push_back(0.50f);
    }
};