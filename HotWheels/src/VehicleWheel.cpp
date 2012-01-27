#include "stdafx.h"
#include "NxOgre.h"
#include "VehicleWheel.h"

using namespace Ogre;
using namespace NxOgre;

VehicleWheel::VehicleWheel(std::string vehicleName, Wheel* wheel, Ogre::Vector3 position, float baseOrientation, SceneNode* parent)
{
    this->parent = parent;
    this->wheel = wheel;
    this->baseOrientation = baseOrientation;

    wheelEntity = parent->getCreator()->createEntity(vehicleName.append("_wheel.mesh"));

    thisNode = parent->createChildSceneNode(position);
    thisNode->attachObject(wheelEntity);

    spin = 0;
    rpmLast = 0;
}

VehicleWheel::~VehicleWheel()
{
    SceneManager* sm = thisNode->getCreator();
    sm->destroyEntity(wheelEntity);
    sm->destroySceneNode(thisNode);
}

float VehicleWheel::getRpm()
{
    return wheel->getAxleSpeed() / (2*Ogre::Math::PI) * 60.0f;
}

void VehicleWheel::update(float diff)
{
    Matrix3 x;
    Matrix3 z;
    
    spin += wheel->getAxleSpeed() * diff;
    if (spin > Ogre::Math::PI * 2)
        spin -= Ogre::Math::PI * 2;
    else if (spin < -Ogre::Math::PI * 2)
        spin += Ogre::Math::PI * 2;

    if (baseOrientation == 0)
        x.FromEulerAnglesXYZ(Ogre::Radian(spin), Ogre::Radian(), Ogre::Radian());
    else
        x.FromEulerAnglesXYZ(Ogre::Radian(-spin), Ogre::Radian(), Ogre::Radian());

    z.FromEulerAnglesXYZ(Ogre::Radian(), Ogre::Radian(baseOrientation * Ogre::Math::PI/180 - wheel->getSteeringAngle()), Ogre::Radian());

    // z * x ?! weird but works.
    x = z * x;
    
    Quaternion y;
    y.FromRotationMatrix(x);

    thisNode->setOrientation(y);
}