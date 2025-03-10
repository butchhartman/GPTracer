#pragma once
#include "Tuple.h"

typedef struct {
	Tuple position;
	Tuple velocity;
} Projectile;

typedef struct {
	Tuple gravity;
	Tuple wind;
} Environment;
