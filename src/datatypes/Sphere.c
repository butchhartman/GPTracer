#include "Sphere.h"



Sphere sphere_createSphere(Tuple origin, int radius, unsigned int instanceID, Mat4 transform, Material material){
    Sphere newSphere = {0};
    newSphere.origin = origin;
    newSphere.radius = radius;
    newSphere.instanceID = instanceID;
    if (transform != NULL) {
        mat_mat4Copy(transform, newSphere.transform);
    } else {
        Mat4 Iden = MAT4_IDENTITY;
        mat_mat4Copy(Iden, newSphere.transform);
    }

    newSphere.material = material;

    return newSphere;
}

void sphere_setTransform(Sphere *sphere, Mat4 transform){
    mat_mat4Copy(transform, sphere->transform);
}
// the passed point is in world coordinates
Tuple sphere_normalAt(Sphere sphere, Tuple point){

    Mat4 inverseTransform;
    mat_mat4Copy(sphere.transform, inverseTransform);
    mat_mat4Inverse(inverseTransform, inverseTransform);

    Tuple objectPoint = mat_mat4MultuplyTuple(inverseTransform, point);
    Tuple objectNormal = tuple_tupleSub(objectPoint, sphere.origin);
    mat_mat4Transpose(inverseTransform, inverseTransform); // beyond this point, the inverse transform is transposed
    Tuple worldNormal = mat_mat4MultuplyTuple(inverseTransform, objectNormal);
    worldNormal.w = 0.0f;
    return tuple_vectorNormalize(worldNormal);
}
