#include "stdafx.h"
#include "Vehicle.h"





using namespace Ogre;
using namespace NxOgre;

int Vehicle::vehicleCount = 0; 

Vehicle::Vehicle(std::string name, VehicleDescription vehDesc, Critter::RenderSystem* critter, Ogre::SceneManager* mSceneMgr)
{
	//load sounds
	vehicleCount++;
	//SoundManager* p = SoundManager::getInstance();
	/*
	SoundManager::getInstance()->loadSound("C:\\Users\\Admin\\Dropbox\\HotWheels\\HotWheels\\bin\\Debug\\sounds\\generalCarSound.wav", "c", true);

	SoundManager::getInstance()->loadSound("C:\\Users\\Admin\\Dropbox\\HotWheels\\HotWheels\\bin\\Debug\\sounds\\1gear.wav", "gear1");
	SoundManager::getInstance()->loadSound("C:\\Users\\Admin\\Dropbox\\HotWheels\\HotWheels\\bin\\Debug\\sounds\\2gear.wav", "gear2");
	SoundManager::getInstance()->loadSound("C:\\Users\\Admin\\Dropbox\\HotWheels\\HotWheels\\bin\\Debug\\sounds\\3gear.wav", "gear3");
	SoundManager::getInstance()->loadSound("C:\\Users\\Admin\\Dropbox\\HotWheels\\HotWheels\\bin\\Debug\\sounds\\3gear.wav", "gear4");

	SoundManager::getInstance()->loadSound("C:\\Users\\Admin\\Dropbox\\HotWheels\\HotWheels\\bin\\Debug\\sounds\\1gearDown.wav", "gear1down");
	SoundManager::getInstance()->loadSound("C:\\Users\\Admin\\Dropbox\\HotWheels\\HotWheels\\bin\\Debug\\sounds\\2gearDown.wav", "gear2down");
	SoundManager::getInstance()->loadSound("C:\\Users\\Admin\\Dropbox\\HotWheels\\HotWheels\\bin\\Debug\\sounds\\3gearDown.wav", "gear3down");
	SoundManager::getInstance()->loadSound("C:\\Users\\Admin\\Dropbox\\HotWheels\\HotWheels\\bin\\Debug\\sounds\\4gearDown.wav", "gear4down");
	*/

	//SoundManager::getInstance()->loadSound("C:\\Users\\\lab422\\Dropbox\\HotWheels\\HotWheels\\bin\\Debug\\sounds\\generalCarSound.wav", "c", true);

	SoundManager::getInstance()->loadSound("C:\\Users\\lab422\\Dropbox\\HotWheels\\HotWheels\\bin\\Debug\\sounds\\1gear.wav", "gear1");
	SoundManager::getInstance()->loadSound("C:\\Users\\lab422\\Dropbox\\HotWheels\\HotWheels\\bin\\Debug\\sounds\\2gear.wav", "gear2");
	SoundManager::getInstance()->loadSound("C:\\Users\\lab422\\Dropbox\\HotWheels\\HotWheels\\bin\\Debug\\sounds\\3gear.wav", "gear3");
	SoundManager::getInstance()->loadSound("C:\\Users\\lab422\\Dropbox\\HotWheels\\HotWheels\\bin\\Debug\\sounds\\3gear.wav", "gear4");

	SoundManager::getInstance()->loadSound("C:\\Users\\lab422\\Dropbox\\HotWheels\\HotWheels\\bin\\Debug\\sounds\\1gearDown.wav", "gear1down");
	SoundManager::getInstance()->loadSound("C:\\Users\\lab422\\Dropbox\\HotWheels\\HotWheels\\bin\\Debug\\sounds\\2gearDown.wav", "gear2down");
	SoundManager::getInstance()->loadSound("C:\\Users\\lab422\\Dropbox\\HotWheels\\HotWheels\\bin\\Debug\\sounds\\3gearDown.wav", "gear3down");
	SoundManager::getInstance()->loadSound("C:\\Users\\lab422\\Dropbox\\HotWheels\\HotWheels\\bin\\Debug\\sounds\\4gearDown.wav", "gear4down");

	
	//SoundManager::getInstance()->loadSound("carrev.wav", "rev");

    vehicleName = name;

    Critter::BodyDescription bodyDesc;
    bodyDesc.mWakeUpCounter = 1E8;
    bodyDesc.mMass = vehDesc.mass;

    NxOgre::ShapeDescriptions shapedesc;

    vehDesc.chassis[0].mMaterial = VEHICLE_MATERIAL_ID;
    vehDesc.chassis[1].mMaterial = VEHICLE_MATERIAL_ID;

    shapedesc.push_back(&(vehDesc.chassis[0]));
    shapedesc.push_back(&(vehDesc.chassis[1]));

    steering = false;
    steer = 0;

	int i = 0;
    for ( i = 0; i < 4; i++)
    {
        vehDesc.wheelDesc[i].mMaterial = VEHICLE_MATERIAL_ID;
        shapedesc.push_back(&(vehDesc.wheelDesc[i]));
    }

    body = critter->createBody(shapedesc, NxOgre::Vec3(0, 10, 0), name.append(".mesh"), bodyDesc);
    if (vehDesc.disruptCOM)
        body->setCMassOffsetLocalPosition(vehDesc.centerOfMass);

//	body->getNode()->getEntityAt(0)->setCastShadows(true)

	printf("%d",body->getNbShapes());
    for (i = 0; i < 4; i++)
    {
		wheels[i] = new VehicleWheel(vehicleName, static_cast<Wheel*>(body->getShape(i)), vehDesc.wheelPositions[i],(i % 2 == 0) ? 0 : 180.0f, body->getNode()->getSceneNode());
        Wheel* wheel=wheels[i]->getWheel();
		wheel->setSteeringAngle(0);
    }

    gears = new VehicleGears(vehDesc.gearDesc, this);
    motor = new VehicleMotor(vehDesc.motorDesc);

    accelerationPedal = 0;
    vDesc = vehDesc;
	
	/*
	Ogre::Entity *missile = mSceneMgr->createEntity("missile", Ogre::SceneManager::PT_SPHERE);

	missile->setMaterialName("Examples/RustySteel");

	// Create a new sceneNode fro the cube, attach it to the rootSceneNode 
	//as a child of the scene manager
	Ogre::SceneNode* mSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("missileNode");

	//mSceneMgr->getRootSceneNode()->addChild(mSceneNode);
	mSceneNode->attachObject( missile );

	missile->setCastShadows(true);
	mSceneNode->scale(0.001, 0.001, 0.001);

	// Position the cube to sit exactly on the ground
	mSceneNode->setPosition(Vector3(-0.7,0.7,5.6));
	
	//body->getNode()->getSceneNode()->attachObject(directionalLight);
	//mSceneNode->attachObject(directionalLight);
	//directionalLight->setDirection(Ogre::Vector3( 0, -1,  0));
	//directionalLight->setPosition(Vector3(-0.7,0.7,5.6) );

	*/
	//Particle effects
	leftExhaust = mSceneMgr->createParticleSystem("leftExhaust"+ Utils::toString(vehicleCount), "smoke2/Smoke");
	rightExhaust = mSceneMgr->createParticleSystem("rightExhaust"+ Utils::toString(vehicleCount), "smoke2/Smoke");


	SceneNode* particleNodeLeft = mSceneMgr->createSceneNode("rightExhaust" + Utils::toString(vehicleCount));
	particleNodeLeft->attachObject(rightExhaust);
	particleNodeLeft->scale(0.05,0.05,0.05);
	particleNodeLeft->pitch(Ogre::Radian( Ogre::Degree(-90) ) );
	particleNodeLeft->setPosition(Ogre::Vector3(-0.6,0.4,-2.45));

	SceneNode* particleNodeRight = mSceneMgr->createSceneNode("leftExhaust" + Utils::toString(vehicleCount));
	particleNodeRight->attachObject(leftExhaust);
	particleNodeRight->scale(0.05,0.05,0.05);
	particleNodeRight->pitch(Ogre::Radian( Ogre::Degree(-90) ) );
	particleNodeRight->setPosition(Ogre::Vector3(0.6,0.4,-2.45));
	
	body->getNode()->getSceneNode()->addChild(particleNodeRight);
	body->getNode()->getSceneNode()->addChild(particleNodeLeft);
	
	Ogre::Entity* c = body->getNode()->getEntityAt(0);
}

Vehicle* Vehicle::createVehicle(NxOgre::String vehicleName, Critter::RenderSystem* critter,  Ogre::SceneManager* mSceneMgr)
{
    if (vehicleName == "")
        throw new std::exception("Vehicle does not exist!");

    std::string filename = "../../media/cars/";
    filename.append(vehicleName);
    filename.append(".car");

    VehicleDescription desc = Vehicle::readFromFile(filename);

   if (critter->getScene()->getMaterial(VEHICLE_MATERIAL_ID) == NULL)
        critter->getScene()->createMaterial()->setAll(0, 0.4f, 0.4f);

    return new Vehicle(vehicleName, desc, critter, mSceneMgr);
}

Vehicle::~Vehicle()
{
    for (int i = 0; i < 4; i++)
        delete wheels[i];

    critter->destroyBody(body);
	
}

void Vehicle::attachCamera(Ogre::Camera* pCamera){


	//Quaterain*UNIT vector = direction vector of lenght one. The direaction the model is going
	
	//Ogre::Vector3 direction = this->getBody()->getNode()->getSceneNode()->getOrientation()*Ogre::Vector3::UNIT_Y; 
	//Ogre::Vector3 camPos = mCar->getNode()->getPosition()-Ogre::Vector3(0,20,0);


	//pCamera->setPosition(Ogre::Vector3(0,4.4,-11));
	//pCamera->lookAt(mCar->getNode()->getPosition());

	this->getBody()->getNode()->getSceneNode()->attachObject(pCamera);


	pCamera->setPosition(0.17335796, 2.5439003, -7.2988391 );
	//pCamera->lookAt(mOrientation = {w=-0.013429106 x=0.00059386448 y=-0.99893796 ...})
	
	pCamera->setOrientation(Ogre::Quaternion(-0.018331267, 0.0014923215, -0.99654049, -0.081119210));
	
}



void Vehicle::postPhysics(float diff)
{
    if (!steering)
    {
        if (steer > 0)
            steer -= vDesc.maxSteer * VEHICLE_STEERING_COEF;
        else if (steer < 0)
            steer += vDesc.maxSteer * VEHICLE_STEERING_COEF;
        
        if (Ogre::Math::Abs(steer) < vDesc.maxSteer * VEHICLE_STEERING_COEF)
            steer = 0;

        wheels[ID_FLWheel - 3]->getWheel()->setSteeringAngle(NxOgre::Radian(steer * Ogre::Math::PI / 180 * vDesc.maxSteer));
        wheels[ID_FRWheel - 3]->getWheel()->setSteeringAngle(NxOgre::Radian(steer * Ogre::Math::PI / 180 * vDesc.maxSteer));
    }
    steering = false;

    for (int i = 0; i < 4; i++)
    {
        wheels[i]->update(diff);
        wheels[i]->getWheel()->setMotorTorque(0);
        wheels[i]->getWheel()->setBrakeTorque(0);
    }
    
    accelerationPedal = 0;
}



void Vehicle::update(float diff)
{

	if(Track::trackingEnabled && gears->getCurrentGear() > 1)
		Track::trackVechicleMovement(this->body->getGlobalPosition(), "aTrack.txt", 60);


	//if(this->getBody()->getGlobalPosition().y < 295)
	//this->getBody()->addForce(NxOgre::Vec3(0,500,0));

    float motorTorque = computeAxisTorque();

    if (accelerationPedal > 0)
    {
        if (gears->getCurrentGear() <= 1)
            gears->setGear(1);

        if (vDesc.backWheelTorque)
        {
            wheels[ID_BLWheel - 3]->getWheel()->setMotorTorque(motorTorque);
            wheels[ID_BRWheel - 3]->getWheel()->setMotorTorque(motorTorque);
        }
        if (vDesc.frontWheelTorque)
        {
            wheels[ID_FLWheel - 3]->getWheel()->setMotorTorque(motorTorque);
            wheels[ID_FRWheel - 3]->getWheel()->setMotorTorque(motorTorque);
        }
    }
    else if (accelerationPedal < 0)
    {
        if (gears->getCurrentGear() >= 0)
        {
            wheels[ID_BLWheel - 3]->getWheel()->setBrakeTorque(motorTorque);
            wheels[ID_BRWheel - 3]->getWheel()->setBrakeTorque(motorTorque);
            wheels[ID_FLWheel - 3]->getWheel()->setBrakeTorque(motorTorque);
            wheels[ID_FRWheel - 3]->getWheel()->setBrakeTorque(motorTorque);
        }
        else
        {
            wheels[ID_BLWheel - 3]->getWheel()->setMotorTorque(motorTorque);
            wheels[ID_BRWheel - 3]->getWheel()->setMotorTorque(motorTorque);
            wheels[ID_FLWheel - 3]->getWheel()->setMotorTorque(motorTorque);
            wheels[ID_FRWheel - 3]->getWheel()->setMotorTorque(motorTorque);
        }
    }

	
}

float Vehicle::computeRpmFromWheels()
{
    float wheelRpms = 0;
    int numWheels = 0;

    if (vDesc.backWheelTorque)
    {
        wheelRpms += wheels[ID_BLWheel - 3]->getRpm();
        wheelRpms += wheels[ID_BRWheel - 3]->getRpm();
        numWheels += 2;
    }

    if (vDesc.frontWheelTorque)
    {
        wheelRpms += wheels[ID_FLWheel - 3]->getRpm();
        wheelRpms += wheels[ID_FRWheel - 3]->getRpm();

        numWheels += 2;
    }

    // hack
    return wheelRpms * 3;
}

float Vehicle::computeMotorRpm(float rpm)
{
    float motorRpm = rpm * gears->getCurrentRatio();
    
    if (gears->getCurrentGear() == gears->getMaxGear() && motorRpm >= motor->getMaxRpm())
        return motor->getMaxRpm();

    if (gears->getCurrentGear() == -1 && motorRpm >= motor->getMinRpmToGearDown() / 4)
        return motor->getMinRpmToGearDown() / 4;

    int change = motor->changeGears(gears);

    if (change == 1)
    {
        gears->gearUp(gearListeners);
        return motor->getMinRpmToGearDown() + 100;
    }
    else if (change == -1)
    {
        gears->gearDown(gearListeners);
        return motor->getMaxRpmToGearUp() - 100;
    }

    return NxOgre::Math::max<float>(motorRpm, motor->getMinRpm());
}

float Vehicle::computeAxisTorque()
{
    float rpm = computeRpmFromWheels();
    float motorRpm = computeMotorRpm(rpm);
    motor->setRpm(motorRpm);
    float torque = motor->getTorque();

    return torque * gears->getCurrentRatio();
}

void Vehicle::accelerate()
{
    accelerationPedal = 1.0f;
	//SoundManager::getInstance()->play("c");
}

void Vehicle::deaccelerate()
{
    accelerationPedal = -1.0f;

    if (motor->getRpm() == motor->getMinRpm() && (gears->getCurrentGear() == 1 || gears->getCurrentGear() == 0))
    {
        gears->gearDown(gearListeners);
        gears->setGear(-1);
    }
}

void Vehicle::steerLeft()
{
    steering = true;
    steer += vDesc.maxSteer * VEHICLE_STEERING_COEF;
    if (steer > 1)
        steer = 1;

    wheels[ID_FLWheel - 3]->getWheel()->setSteeringAngle(NxOgre::Radian(steer * Ogre::Math::PI / 180 * vDesc.maxSteer));
    wheels[ID_FRWheel - 3]->getWheel()->setSteeringAngle(NxOgre::Radian(steer * Ogre::Math::PI / 180 * vDesc.maxSteer));
}

void Vehicle::steerRight()
{
    steering = true;
    steer -= vDesc.maxSteer * VEHICLE_STEERING_COEF;
    if (steer < -1)
        steer = -1;

    wheels[ID_FLWheel - 3]->getWheel()->setSteeringAngle(NxOgre::Radian(steer * Ogre::Math::PI / 180 * vDesc.maxSteer));
    wheels[ID_FRWheel - 3]->getWheel()->setSteeringAngle(NxOgre::Radian(steer * Ogre::Math::PI / 180 * vDesc.maxSteer));
}

VehicleDescription Vehicle::readFromFile(std::string filename)
{
    std::string cprop;
    float c1, c2, c3, c4, c5;
    int i;

    VehicleDescription desc;

    for (i = 0; i < 4; i++)
        desc.wheelDesc[i].mId = i + 3;

    std::ifstream ifs(filename.c_str());

    while (ifs.good())
    {
        ifs >> cprop;

        if (cprop == "FL_WHEEL")
        {
            ifs >> c1 >> c2 >> c3;
            desc.wheelDesc[ID_FLWheel - 3].mLocalPose = Vec3(c1, c2, c3);
            desc.wheelPositions[ID_FLWheel - 3] = Ogre::Vector3(c1, c2, c3);
        }
        else if (cprop == "FR_WHEEL")
        {
            ifs >> c1 >> c2 >> c3;
            desc.wheelDesc[ID_FRWheel - 3].mLocalPose = Vec3(c1, c2, c3);
            desc.wheelPositions[ID_FRWheel - 3] = Ogre::Vector3(c1, c2, c3);
        }
        else if (cprop == "BL_WHEEL")
        {
            ifs >> c1 >> c2 >> c3;
            desc.wheelDesc[ID_BLWheel - 3].mLocalPose = Vec3(c1, c2, c3);
            desc.wheelPositions[ID_BLWheel - 3] = Ogre::Vector3(c1, c2, c3);
        }
        else if (cprop == "BR_WHEEL")
        {
            ifs >> c1 >> c2 >> c3;
            desc.wheelDesc[ID_BRWheel - 3].mLocalPose = Vec3(c1, c2, c3);
            desc.wheelPositions[ID_BRWheel - 3] = Ogre::Vector3(c1, c2, c3);
        }
        else if (cprop == "WHEEL_RADIUS")
        {
            ifs >> c1;

            for (i = 0; i < 4; i++)
                desc.wheelDesc[i].mRadius = c1;
        }
        else if (cprop == "WHEEL_WIDTH")
        {
            ifs >> c1;

            for (i = 0; i < 4; i++)
                desc.wheelDesc[i].mSkinWidth = c1;
        }
        else if (cprop == "MASS")
        {
            ifs >> c1;
            desc.mass = c1;
        }
        else if (cprop == "COFMASS")
        {
            ifs >> c1 >> c2 >> c3;
            desc.centerOfMass = NxOgre::Vec3(c1, c2, c3);
            desc.disruptCOM = true;
        }
        else if (cprop == "F_TORQUE")
        {
            ifs >> c1;
            desc.frontWheelTorque = c1;
        }
        else if (cprop == "B_TORQUE")
        {
            ifs >> c1;
            desc.backWheelTorque = c1;
        }
        else if (cprop == "TORQUE_CURVE")
        {
            ifs >> c1 >> c2;
            desc.motorDesc.torqueCurve.insert(c1, c2);
        }
        else if (cprop == "MAX_STEER")
        {
            ifs >> c1;
            desc.maxSteer = c1;
        }
        else if (cprop == "MAX_VELOCITY")
        {
            ifs >> c1;
            desc.maxVelocity = c1;
        }
        else if (cprop == "CHA1")
        {
            ifs >> c1 >> c2 >> c3;
            desc.chassis[0].mSize.set(c1, c2, c3);
            ifs >> c1 >> c2 >> c3;
            desc.chassis[0].mLocalPose = NxOgre::Vec3(c1, c2, c3);
        }
        else if (cprop == "CHA2")
        {
            ifs >> c1 >> c2 >> c3;
            desc.chassis[1].mSize.set(c1, c2, c3);
            ifs >> c1 >> c2 >> c3;
            desc.chassis[1].mLocalPose = NxOgre::Vec3(c1, c2, c3);
        }
        else if (cprop == "LATTF")
        {
            ifs >> c1 >> c2 >> c3 >> c4 >> c5;

            for (i = 0; i < 4; i++)
            {
                desc.wheelDesc[i].mLateralTireFunction.mAsymptoteSlip = c1;
                desc.wheelDesc[i].mLateralTireFunction.mAsymptoteValue = c2;
                desc.wheelDesc[i].mLateralTireFunction.mExtremumSlip = c3;
                desc.wheelDesc[i].mLateralTireFunction.mExtremumValue = c4;
                desc.wheelDesc[i].mLateralTireFunction.mStiffnessFactor = c5;
            }
        }
        else if (cprop == "LOGTF")
        {
            ifs >> c1 >> c2 >> c3 >> c4 >> c5;

            for (i = 0; i < 4; i++)
            {
                desc.wheelDesc[i].mLongitudalTireFunction.mAsymptoteSlip = c1;
                desc.wheelDesc[i].mLongitudalTireFunction.mAsymptoteValue = c2;
                desc.wheelDesc[i].mLongitudalTireFunction.mExtremumSlip = c3;
                desc.wheelDesc[i].mLongitudalTireFunction.mExtremumValue = c4;
                desc.wheelDesc[i].mLongitudalTireFunction.mStiffnessFactor = c5;
            }
        }
        else if (cprop == "LATTF_F")
        {
            ifs >> c1 >> c2 >> c3 >> c4 >> c5;

            for (i = 0; i < 2; i++)
            {
                desc.wheelDesc[i].mLateralTireFunction.mAsymptoteSlip = c1;
                desc.wheelDesc[i].mLateralTireFunction.mAsymptoteValue = c2;
                desc.wheelDesc[i].mLateralTireFunction.mExtremumSlip = c3;
                desc.wheelDesc[i].mLateralTireFunction.mExtremumValue = c4;
                desc.wheelDesc[i].mLateralTireFunction.mStiffnessFactor = c5;
            }
        }
        else if (cprop == "LATTF_B")
        {
            ifs >> c1 >> c2 >> c3 >> c4 >> c5;

            for (i = 2; i < 4; i++)
            {
                desc.wheelDesc[i].mLateralTireFunction.mAsymptoteSlip = c1;
                desc.wheelDesc[i].mLateralTireFunction.mAsymptoteValue = c2;
                desc.wheelDesc[i].mLateralTireFunction.mExtremumSlip = c3;
                desc.wheelDesc[i].mLateralTireFunction.mExtremumValue = c4;
                desc.wheelDesc[i].mLateralTireFunction.mStiffnessFactor = c5;
            }
        }
        else if (cprop == "LOGTF_F")
        {
            ifs >> c1 >> c2 >> c3 >> c4 >> c5;

            for (i = 0; i < 2; i++)
            {
                desc.wheelDesc[i].mLongitudalTireFunction.mAsymptoteSlip = c1;
                desc.wheelDesc[i].mLongitudalTireFunction.mAsymptoteValue = c2;
                desc.wheelDesc[i].mLongitudalTireFunction.mExtremumSlip = c3;
                desc.wheelDesc[i].mLongitudalTireFunction.mExtremumValue = c4;
                desc.wheelDesc[i].mLongitudalTireFunction.mStiffnessFactor = c5;
            }
        }
        else if (cprop == "LOGTF_B")
        {
            ifs >> c1 >> c2 >> c3 >> c4 >> c5;

            for (i = 2; i < 4; i++)
            {
                desc.wheelDesc[i].mLongitudalTireFunction.mAsymptoteSlip = c1;
                desc.wheelDesc[i].mLongitudalTireFunction.mAsymptoteValue = c2;
                desc.wheelDesc[i].mLongitudalTireFunction.mExtremumSlip = c3;
                desc.wheelDesc[i].mLongitudalTireFunction.mExtremumValue = c4;
                desc.wheelDesc[i].mLongitudalTireFunction.mStiffnessFactor = c5;
            }
        }
        else if (cprop == "NOFGEARS")
        {
            ifs >> c1;
            desc.gearDesc.forwardGearCount = c1;
            desc.gearDesc.forwardGears.clear();

            for (i = 0; i < c1; i++)
                desc.gearDesc.forwardGears.push_back(0);
        }
        else if (cprop == "GEARS")
        {
            ifs >> c1;
            desc.gearDesc.forwardGearCount = c1;
            desc.gearDesc.forwardGears.clear();

            for (i = 0; i < desc.gearDesc.forwardGearCount; i++)
            {
                ifs >> c2;
                desc.gearDesc.forwardGears.push_back(c2);
            }

            ifs >> c3;
            desc.gearDesc.reverseGear = c3;
        }
        else if (cprop == "RPM")
        {
            ifs >> c1 >> c2 >> c3 >> c4;
            desc.motorDesc.minRpmToGearDown = c1;
            desc.motorDesc.maxRpmToGearUp = c2;
            desc.motorDesc.minRpm = c3;
            desc.motorDesc.maxRpm = c4;
        }
        else if (cprop == "IWM")
        {
            ifs >> c1;
            for (i = 0; i < 4; i++)
                desc.wheelDesc[i].mInverseWheelMass = c1;
        }
        else if (cprop == "SUSPENSION")
        {
            ifs >> c1 >> c2 >> c3 >> c4;
            for (i = 0; i < 4; i++)
            {
                desc.wheelDesc[i].mSuspension.mDamper = c1;
                desc.wheelDesc[i].mSuspension.mSpring = c2;
                desc.wheelDesc[i].mSuspension.mTargetValue = c3;
                desc.wheelDesc[i].mSuspensionTravel = c4;
            }
        }
    }

    ifs.close();

    return desc;
}