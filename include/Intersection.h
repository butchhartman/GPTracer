#pragma once
#include "Sphere.h"

typedef struct {
    Sphere object;
    float t;
} Intersection;

Intersection intersection_intersectionCreateIntersection(Sphere object, float t);
Intersection intersection_determineHit(Intersection *intersections, int length);