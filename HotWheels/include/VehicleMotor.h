#pragma once
#include "stdafx.h"
#include "VehicleMotorDescription.h"
#include "VehicleGears.h"

class VehicleMotor
{
public:
    VehicleMotor(VehicleMotorDescription motorDesc)
    {
        mDesc = motorDesc;
        rpm = 0;

        float v;
        maxTorque = 0; maxTorquePos = 0;
        for (unsigned int i = 0; i < motorDesc.torqueCurve.getSize(); i++)
        {
            v = motorDesc.torqueCurve.getValueAtIndex(i);
            if (v > maxTorque)
            {
                maxTorque = v;
                maxTorquePos = i;
            }
        }
    }

    void setRpm(float m_rpm) { rpm = m_rpm; }
	float getRpm() { return rpm; }

	float getMinRpm() { return mDesc.minRpm; }
	float getMaxRpm() { return mDesc.maxRpm; }
    float getMinRpmToGearDown() { return mDesc.minRpmToGearDown; }
    float getMaxRpmToGearUp() { return mDesc.maxRpmToGearUp; }
	int changeGears(VehicleGears* gears)
    {
        int gear = gears->getCurrentGear();

        if (gear == -1) return 0;

        if (rpm > mDesc.maxRpmToGearUp && gear < gears->getMaxGear())
            return 1;
        else if (rpm < mDesc.minRpmToGearDown && gear > 1)
            return -1;

        return 0;
    }

	float getTorque() { return mDesc.torqueCurve.getValue(rpm); }

protected:
    float rpm, maxTorque;
    int maxTorquePos;

    VehicleMotorDescription mDesc;
};