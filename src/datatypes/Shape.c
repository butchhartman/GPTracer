#include "Shape.h"


Shape shape_createDefaultShape(unsigned int instanceID, enum Formfactor formfactor) {
    Material defaultMat = material_createMaterial(tuple_createColor(1, 1, 1), 0.1f, 0.9f, 0.9f, 200.0f);
    Mat4 defaultTransform = MAT4_IDENTITY;

    Shape defaultShape;
    defaultShape.origin = tuple_createPoint(0, 0, 0);
    defaultShape.material = defaultMat;    
    defaultShape.instanceID = instanceID;
    mat_mat4Copy(defaultTransform, defaultShape.transform);
    defaultShape.formfactor = formfactor;

    return defaultShape;
}

Shape shape_assignMaterial(Shape shape, Material mat) {
    Shape newShape = shape;
    newShape.material = mat;
    return newShape;
}

Tuple shape_normalAt(Shape shape, Tuple point){
    Mat4 invShapeTransform;
    mat_mat4Inverse(shape.transform, invShapeTransform);

    Tuple localPoint = mat_mat4MultuplyTuple(invShapeTransform, point);
    Tuple localNormal;

    switch (shape.formfactor) {

        case (Sphere):
            localNormal = shape_sphereNormalAt(shape, localPoint);
            break;
        
        case (Plane):
            localNormal = tuple_createVector(0, 1, 0); // Planes are flat, with a constant normal vector throughout.   
            break; 

        default:
            break;
    }

    Mat4 transposedInvShapeTransform;
    mat_mat4Transpose(invShapeTransform, transposedInvShapeTransform);
    Tuple worldNormal = mat_mat4MultuplyTuple(transposedInvShapeTransform, localNormal);
    worldNormal.w = 0; // hack to avoid more complicated computations
    return tuple_vectorNormalize(worldNormal);
}

Tuple shape_sphereNormalAt(Shape sphere, Tuple point){
   return tuple_createVector(point.x, point.y, point.z);// Supposed to be point - origin position, but origin is always 0, 0, 0, so simplified
}
// kind of disgusting that I put this here but ̅ \_(ツ)_/ ̅  
Tuple pattern_stripeAtObject(Pattern pattern, Shape object, Tuple worldPoint){
    Mat4 invObjTrans;
    Mat4 invPatTrans;
    mat_mat4Inverse(object.transform, invObjTrans);
    mat_mat4Inverse(pattern.transform, invPatTrans);

    Tuple obejectPoint = mat_mat4MultuplyTuple(invObjTrans, worldPoint);
    Tuple patternPoint = mat_mat4MultuplyTuple(invPatTrans, obejectPoint);

    return pattern_stripeAt(pattern, patternPoint);
}

// again, hate that this is here
Tuple material_calculateLighting(Material material, Pointlight light, Tuple point, Tuple eyev, Tuple normalv, int inShadow, Shape object){
    Tuple originalColor;
    
    if (material.pattern.a.x != -1 && material.pattern.b.x != -1) { // if a pattern is set, negative RGV values are invalid and used to represent not a color
        originalColor = pattern_stripeAtObject(material.pattern, object,  point);
    } 
    else  {
        originalColor = material.surfaceColor;
    }

    Tuple effectiveColor = tuple_colorBlend(originalColor, light.intensity);

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
    Tuple result;
    if (inShadow == 0) {
        result = tuple_tupleAdd(tuple_tupleAdd(ambient, diffuse), specular);
    }
    else {
        result = ambient;
    }
    // hack to reset the w value so that comparisons function correctly
    result.w = 1;
    return result;
}
// Sphere sphere_createSphere(Tuple origin, int radius, unsigned int instanceID, Mat4 transform, Material material){

//     Sphere newSphere = {0};
//     newSphere.origin = origin;
//     newSphere.radius = radius;
//     newSphere.instanceID = instanceID;
//     if (transform != NULL) {
//         mat_mat4Copy(transform, newSphere.transform);
//     } else {
//         Mat4 Iden = MAT4_IDENTITY;
//         mat_mat4Copy(Iden, newSphere.transform);
//     }

//     newSphere.material = material;

//     return newSphere;
// }

// void sphere_setTransform(Sphere *sphere, Mat4 transform){
//     mat_mat4Copy(transform, sphere->transform);
// }
// // the passed point is in world coordinates
// Tuple sphere_normalAt(Sphere sphere, Tuple point){

//     Mat4 inverseTransform;
//     mat_mat4Copy(sphere.transform, inverseTransform);
//     mat_mat4Inverse(inverseTransform, inverseTransform);

//     Tuple objectPoint = mat_mat4MultuplyTuple(inverseTransform, point);
//     Tuple objectNormal = tuple_tupleSub(objectPoint, sphere.origin);
//     mat_mat4Transpose(inverseTransform, inverseTransform); // beyond this point, the inverse transform is transposed
//     Tuple worldNormal = mat_mat4MultuplyTuple(inverseTransform, objectNormal);
//     worldNormal.w = 0.0f;
//     return tuple_vectorNormalize(worldNormal);
// }
