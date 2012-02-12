#pragma once
#include "stdafx.h"
#include "NxOgre.h"

using namespace Ogre;
using namespace NxOgre;

class VehicleWheel
{
public:
    VehicleWheel(std::string vehicleName, Wheel* wheel, Ogre::Vector3 position, float baseOrientation, SceneNode* parent);
    ~VehicleWheel();

    void update(float diff);
    float getRpm();

    Wheel* getWheel() { return wheel; }
	SceneNode* getNode() { return thisNode; }

protected:
    float baseOrientation;
    float spin;
    Entity* wheelEntity;
    Wheel* wheel;
    SceneNode* parent;
    SceneNode* thisNode;

    float rpmLast;
};