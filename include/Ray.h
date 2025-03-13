#pragma once
#include "Intersection.h"
#include "Mat.h"
#include "Sphere.h"
#include "Tuple.h"

typedef struct {
    Tuple origin;
    Tuple direction;
} Ray;

Ray ray_createRay(Tuple origin, Tuple direction);
Tuple ray_rayPosition(Ray ray, float t);

void ray_raySphereIntersect(Ray ray, Sphere sphere, Intersection* dest);

Ray ray_transformRay(Ray ray, Mat4 transform);