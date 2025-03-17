#pragma once
#include "Tuple.h"
#include "Mat.h"

#define COLOR_BLACK tuple_createColor(0, 0, 0)
#define COLOR_WHITE tuple_createColor(1, 1, 1)

enum patternType{Stripe};

typedef struct {
    Tuple a;
    Tuple b;
    Mat4 transform;
    enum patternType patterntype;
} Pattern;

Pattern pattern_createPattern(Tuple colorA, Tuple colorB, enum patternType pattern);
Tuple pattern_patternAt(Pattern pattern, Tuple point);