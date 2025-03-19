#pragma once
#include "Intersection.h"
#include "Mat.h"
#include "Shape.h"
#include "Tuple.h"

typedef struct {
    Tuple origin;
    Tuple direction;
} Ray;

typedef struct {
    float t;
    unsigned int inside;
    Shape object;
    Tuple point;
    Tuple eyev;
    Tuple normalv;
    Tuple overPoint;
    Tuple underPoint;
    Tuple reflectv;
    float n1;
    float n2;
} Computations;



Ray ray_createRay(Tuple origin, Tuple direction);
Tuple ray_rayPosition(Ray ray, float t);

Ray ray_rayShapeIntersect(Ray ray, Shape shape, Intersection** dest, int *length);
void ray_raySphereIntersect(Ray ray, Shape sphere, Intersection** dest, int *length);
void ray_rayPlaneIntersect(Ray ray, Shape plane, Intersection **dest, int *length);
void ray_rayCubeIntersect(Ray ray, Shape cube, Intersection **dest, int *length);

void ray_checkAxis(float origin, float direction, float *tmin, float *tmax);

Ray ray_transformRay(Ray ray, Mat4 transform);

Computations intersection_prepareComputations(Intersection intersection, Ray ray, Intersection *xs, int length);

float ray_schlick(Computations comps);