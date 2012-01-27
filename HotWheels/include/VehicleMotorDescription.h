#pragma once
#include "stdafx.h"
#include "LinearInterpolationValues.h"

struct VehicleMotorDescription
{
    LinearInterpolationValues torqueCurve;
    float minRpmToGearDown;
	float maxRpmToGearUp;
	float maxRpm;
	float minRpm;

    VehicleMotorDescription()
    {
        torqueCurve.clear();
        minRpmToGearDown = 1500.0f;
        maxRpmToGearUp   = 4000.0f;
        minRpm           = 1000.0f;
        maxRpm           = 5000.0f;
    }
};