#pragma once
#include "Tuple.h"
#include "Canvas.h"
#include "PPM.h"

typedef struct {
	Tuple position;
	Tuple velocity;
} Projectile;

typedef struct {
	Tuple gravity;
	Tuple wind;
} Environment;
