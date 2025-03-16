#pragma once
#include "Tuple.h"
#include "Mat.h"

#define COLOR_BLACK tuple_createColor(0, 0, 0)
#define COLOR_WHITE tuple_createColor(1, 1, 1)

typedef struct {
    Tuple a;
    Tuple b;
    Mat4 transform;
} Pattern;

Pattern pattern_stripe(Tuple colorA, Tuple colorB);
Tuple pattern_stripeAt(Pattern pattern, Tuple point);