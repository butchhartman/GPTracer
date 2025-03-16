#pragma once
#include "Tuple.h"
#include "Shape.h"
#include "Ray.h"
#include "Intersection.h"
#include "Canvas.h"
#include "Mat.h"
#include "PPM.h"
#include "World.h"
#include "Camera.h"
#include <time.h>

typedef struct {
	Tuple position;
	Tuple velocity;
} Projectile;

typedef struct {
	Tuple gravity;
	Tuple wind;
} Environment;
