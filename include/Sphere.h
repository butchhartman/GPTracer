#pragma once
#include "Mat.h"
#include "Tuple.h"
#include "Material.h"

typedef struct {
    Tuple origin;
    int radius;    
    unsigned int instanceID;
    Mat4 transform;
    Material material;    
} Sphere;

Sphere sphere_createSphere(Tuple origin, int radius, unsigned int instanceID, Mat4 transform, Material material);
void sphere_setTransform(Sphere *sphere, Mat4 transform);

Tuple sphere_normalAt(Sphere sphere, Tuple point);