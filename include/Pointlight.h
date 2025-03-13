#pragma once
#include "Tuple.h"

typedef struct {
    Tuple position;
    Tuple intensity;
} Pointlight;

Pointlight pointlight_createPointlight(Tuple position, Tuple intensity);