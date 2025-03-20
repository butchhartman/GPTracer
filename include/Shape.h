#pragma once
#include "Mat.h"
#include "Tuple.h"
#include "Material.h"

enum Formfactor {Sphere, Plane, Cube, Cylinder};

typedef struct {
    Tuple origin;
    unsigned int instanceID;
    Mat4 transform;
    Material material;    
    enum Formfactor formfactor;
    float minimum;
    float maximum;
    float closed;
} Shape;

Shape shape_createDefaultShape(unsigned int instanceID, enum Formfactor formfactor);
Shape shape_glassySphere(unsigned int instanceID);
Shape shape_assignMaterial(Shape shape, Material mat);

Tuple shape_normalAt(Shape shape, Tuple point);
Tuple shape_sphereNormalAt(Shape sphere, Tuple point);
Tuple shape_cubeNormalAt(Shape cube, Tuple point);
Tuple shape_cylinderNormalAt(Shape cylinder, Tuple point);

Tuple pattern_patternAtObject(Pattern pattern, Shape object, Tuple worldPoint);


Tuple material_calculateLighting(Material material, Pointlight light, Tuple point, Tuple eyev, Tuple normalv, int inShadow, Shape object);

// Shape sphere_createSphere(Tuple origin, int radius, unsigned int instanceID, Mat4 transform, Material material, enum Formfactor formfactor);
// void sphere_setTransform(Shape *sphere, Mat4 transform);

// Tuple sphere_normalAt(Sphere sphere, Tuple point);