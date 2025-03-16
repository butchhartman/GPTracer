#pragma once
#include "Shape.h"

typedef struct {
    Shape object;
    float t;
} Intersection;

Intersection intersection_intersectionCreateIntersection(Shape object, float t);
Intersection intersection_determineHit(Intersection *intersections, int length);
