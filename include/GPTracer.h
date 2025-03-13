#pragma once
#include "Tuple.h"
#include "Sphere.h"
#include "Ray.h"
#include "Intersection.h"
#include "Canvas.h"
#include "Mat.h"
#include "PPM.h"

typedef struct {
	Tuple position;
	Tuple velocity;
} Projectile;

typedef struct {
	Tuple gravity;
	Tuple wind;
} Environment;
