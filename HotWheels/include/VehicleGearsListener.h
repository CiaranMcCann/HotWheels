#pragma once
#include "stdafx.h"
#include "VehicleGears.h"
#include "Vehicle.h"
#include <vector>

class Vehicle;

class VehicleGearsListener
{
public:
    virtual void gearChange(Vehicle* vehicle, int previousGear, int newGear)=0;
};

typedef std::vector<VehicleGearsListener*>::iterator gearsListenerIterator;