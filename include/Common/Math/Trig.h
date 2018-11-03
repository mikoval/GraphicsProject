#ifndef TRIG_H
#define TRIG_H

#include <iostream>
#include <assert.h>
#include <Math/Constants.h>

using namespace std;

static inline float radians(const float &degrees){
    return (degrees / 180.0) * PI;
}

static inline float degrees(const float &radians){
    return (radians / PI) * 180;
}

#endif