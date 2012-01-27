#pragma once
#include "stdafx.h"
#include "NxOgre.h"
#include <map>

class LinearInterpolationValues
{
public:
    LinearInterpolationValues() : min(0), max(0), map() { }
    void clear() { map.clear(); }
    void insert(float index, float value)
    {
        if (map.empty())
            min = max = index;
        else
        {
            min = NxOgre::Math::min<float>(min, index);
            max = NxOgre::Math::min<float>(max, index);
        }

        map[index] = value;
    }

    float getValue(float number) const
    {
        constMapIterator lower = map.begin();
        if (number < min)
            return lower->second;

        constMapIterator upper = map.end();
        upper--;

        if (number > max)
            return upper->second;

        upper = map.lower_bound(number);
        if (upper == lower)
            return upper->second;

        lower = upper;
        lower--;

        float w1 = number - lower->first;
        float w2 = upper->first - number;
        return ((w2 * lower->second) + (w1 * upper->second)) / (w1 + w2);
    }

    float getValueAtIndex(unsigned int index)
    {
        constMapIterator it = map.begin();

        for (unsigned int i = 0; i < index; i++)
            ++it;
        
        return it->second;
    }

    unsigned int getSize() { return map.size(); }

protected:
    float min, max;
    std::map<float, float> map;

    typedef std::map<float, float>::iterator mapIterator;
    typedef std::map<float, float>::const_iterator constMapIterator;
};