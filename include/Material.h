#pragma once
#include "Tuple.h"
#include "Pointlight.h"
#include "Patterns.h"

typedef struct {
    Tuple surfaceColor;
    Pattern pattern;
    float ambient;
    float diffuse;
    float specular;
    float shininess;
} Material;

Material material_createMaterial(Tuple surfaceColor, float ambient, float diffuse, float specular, float shininess);