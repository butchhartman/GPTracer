#include "Material.h"
#include "Patterns.h"
#include "Shape.h"
Material material_createMaterial(Tuple surfaceColor, float ambient, float diffuse, float specular, float shininess, float reflective){
    Material newm;
    newm.surfaceColor = surfaceColor;
    newm.ambient = ambient;
    newm.diffuse = diffuse;
    newm.specular = specular;
    newm.shininess = shininess;
    newm.pattern = pattern_createPattern(tuple_createColor(-1, -1, -1), tuple_createColor(-1, -1, -1), Stripe);
    newm.reflective = reflective;
    return newm;    
}

