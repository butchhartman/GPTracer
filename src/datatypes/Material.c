#include "Material.h"
#include "Patterns.h"
#include "Shape.h"
Material material_createMaterial(Tuple surfaceColor, float ambient, float diffuse, float specular, float shininess){
    Material newm;
    newm.surfaceColor = surfaceColor;
    newm.ambient = ambient;
    newm.diffuse = diffuse;
    newm.specular = specular;
    newm.shininess = shininess;
    newm.pattern = pattern_stripe(tuple_createColor(-1, -1, -1), tuple_createColor(-1, -1, -1));
    return newm;    
}

