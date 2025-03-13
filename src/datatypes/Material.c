#include "Material.h"

Material material_createMaterial(Tuple surfaceColor, float ambient, float diffuse, float specular, float shininess){
    Material newm;
    newm.surfaceColor = surfaceColor;
    newm.ambient = ambient;
    newm.diffuse = diffuse;
    newm.specular = specular;
    newm.shininess = shininess;
    return newm;    
}

Tuple material_calculateLighting(Material material, Pointlight light, Tuple point, Tuple eyev, Tuple normalv){
    Tuple effectiveColor = tuple_colorBlend(material.surfaceColor, light.intensity);

    Tuple lightv = tuple_vectorNormalize(tuple_tupleSub(light.position, point));

    Tuple ambient = tuple_tupleMuls(effectiveColor, material.ambient);
    Tuple diffuse = {0};
    Tuple specular = {0};
    float lightDotNormal = tuple_vectorDot(lightv, normalv);
    if (lightDotNormal < 0) {
        diffuse = tuple_createColor(0.0f, 0.0f, 0.0f);
        specular = tuple_createColor(0.0f, 0.0f, 0.0f);
    } 
    else {
        diffuse = tuple_tupleMuls(tuple_tupleMuls(effectiveColor, material.diffuse), lightDotNormal);

        Tuple reflectv = tuple_reflect(tuple_tupleNegate(lightv), normalv);
        float reflectDotEye = tuple_vectorDot(reflectv, eyev);

        if (reflectDotEye <= 0) {
            specular = tuple_createColor(0.0f, 0.0f, 0.0f);
        }
        else {
            float factor = powf(reflectDotEye, material.shininess);
            specular = tuple_tupleMuls(tuple_tupleMuls(light.intensity, material.specular), factor);
        }

    }
    // hack to reset the w value so that comparisons function correctly
    Tuple result = tuple_tupleAdd(tuple_tupleAdd(ambient, diffuse), specular);
    result.w = 1.0f;
    return result;
}
