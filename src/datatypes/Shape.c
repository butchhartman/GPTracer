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
