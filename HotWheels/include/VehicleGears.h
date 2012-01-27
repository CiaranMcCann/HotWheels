#pragma once
#include "stdafx.h"
#include "VehicleGearsDescription.h"
#include "VehicleGearsListener.h"
#include <vector>
#include "SoundManager.h"

class VehicleGears
{
public:
    VehicleGears(VehicleGearsDescription gearsDesc, Vehicle* veh)
    {
        vehicle = veh;
        gears = gearsDesc;
        currentGear = 0;
        locked = false;
    }

    void gearUp(std::vector<VehicleGearsListener*> listeners)
    {
        if (locked) return;

        if (currentGear < getMaxGear())
        {
            currentGear++;
			playGearUpSound();
            
            for (gearsListenerIterator it = listeners.begin(); it != listeners.end(); ++it)
                (*it)->gearChange(vehicle, currentGear - 1, currentGear);
        }
    }

    void gearDown(std::vector<VehicleGearsListener*> listeners)
    {
        if (locked) return;

        if (currentGear > -1)
        {
            currentGear--;
			playGearDownSound();

            for (gearsListenerIterator it = listeners.begin(); it != listeners.end(); ++it)
                (*it)->gearChange(vehicle, currentGear + 1, currentGear);
        }
    }

    void setGear(int gear) { currentGear = gear; }

    float getRatio(int gear)
    {
        if (gear == 0)
            return 0;
        else if (gear == -1)
            return gears.reverseGear;
        
        if (gear >= gears.forwardGears.size())
            return 1;

        return gears.forwardGears[gear - 1];
    }

    float VehicleGears::getCurrentRatio() { return getRatio(currentGear); }

    int getMaxGear() { return gears.forwardGears.size(); }
    int getCurrentGear() { return currentGear; }

protected:
    Vehicle* vehicle;
    VehicleGearsDescription gears;
    int currentGear;
    bool locked;


	void playGearUpSound(){

		if(currentGear == 0)
			SoundManager::getInstance()->play("gear1");
		else if( currentGear == 1)
			SoundManager::getInstance()->play("gear2");
		else if( currentGear == 2)
			SoundManager::getInstance()->play("gear3");
		else if( currentGear == 3)
			SoundManager::getInstance()->play("gear4");
		

	}


	void playGearDownSound(){

		if(currentGear == 3)
			SoundManager::getInstance()->play("gear4down");
		else if( currentGear == 2)
			SoundManager::getInstance()->play("gear3down");
		else if( currentGear == 1)
			SoundManager::getInstance()->play("gear2down");
		else if( currentGear == 0)
			SoundManager::getInstance()->play("gear1down");

	}

};