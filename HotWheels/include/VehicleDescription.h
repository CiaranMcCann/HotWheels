#pragma once
#include "stdafx.h"
#include "VehicleGearsDescription.h"
#include "VehicleMotorDescription.h"

using namespace Ogre;
using namespace NxOgre;

struct VehicleDescription
{
    WheelDescription wheelDesc[4];
    Ogre::Vector3 wheelPositions[4];
    BoxDescription chassis[2];
    VehicleGearsDescription gearDesc;
    VehicleMotorDescription motorDesc;
    float maxVelocity, maxSteer, mass;
    float frontWheelTorque, backWheelTorque;
    NxOgre::Vec3 centerOfMass;
    bool disruptCOM;

    VehicleDescription()
    {
        frontWheelTorque = 0;
        backWheelTorque = 0;
        maxSteer = 0;
        mass = 1;
        disruptCOM = false;
    }
};