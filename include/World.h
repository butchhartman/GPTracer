#pragma once
#include <malloc.h>
#include "Tuple.h"
#include "Shape.h"
#include "Pointlight.h"
#include "Material.h"
#include "Ray.h"
#include "Intersection.h"


typedef struct {
    Pointlight light;
    Shape *objects;
    unsigned int objectCount;
} World;

World world_createDefault();

Intersection *world_intersectWorld(World world, Ray ray, int *length);
Tuple world_shadeHit(World world, Computations comps);

Tuple world_worldColorAt(World world, Ray ray);
int world_pointInShadow(World world, Tuple point);