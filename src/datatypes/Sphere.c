#include "Sphere.h"



Sphere sphere_createSphere(Tuple origin, int radius, unsigned int instanceID, Mat4 transform){
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
    return newSphere;
}

void sphere_setTransform(Sphere *sphere, Mat4 transform){
    mat_mat4Copy(transform, sphere->transform);
}
