#pragma once
#include "Intersection.h"
#include "Mat.h"
#include "Sphere.h"
#include "Tuple.h"

typedef struct {
    Tuple origin;
    Tuple direction;
} Ray;

typedef struct {
    float t;
    unsigned int inside;
    Sphere object;
    Tuple point;
    Tuple eyev;
    Tuple normalv;
} Computations;



Ray ray_createRay(Tuple origin, Tuple direction);
Tuple ray_rayPosition(Ray ray, float t);

void ray_raySphereIntersect(Ray ray, Sphere sphere, Intersection* dest);

Ray ray_transformRay(Ray ray, Mat4 transform);

Computations intersection_prepareComputations(Intersection intersection, Ray ray);