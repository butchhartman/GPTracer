#pragma once
#include "Tuple.h"
#include "Pointlight.h"

typedef struct {
    Tuple surfaceColor;
    float ambient;
    float diffuse;
    float specular;
    float shininess;
} Material;

Material material_createMaterial(Tuple surfaceColor, float ambient, float diffuse, float specular, float shininess);
Tuple material_calculateLighting(Material material, Pointlight light, Tuple point, Tuple eyev, Tuple normalv);