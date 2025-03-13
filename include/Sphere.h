#pragma once
#include "Mat.h"
#include "Tuple.h"

typedef struct {
    Tuple origin;
    int radius;    
    unsigned int instanceID;
    Mat4 transform;
} Sphere;

Sphere sphere_createSphere(Tuple origin, int radius, unsigned int instanceID, Mat4 transform);
void sphere_setTransform(Sphere *sphere, Mat4 transform);