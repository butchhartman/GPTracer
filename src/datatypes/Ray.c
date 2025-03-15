#include "Ray.h"

Ray ray_createRay(Tuple origin, Tuple direction){
    Ray newRay;
    newRay.origin = origin;
    newRay.direction = direction;
    return newRay;
}

Tuple ray_rayPosition(Ray ray, float t){
    return tuple_tupleAdd(ray.origin, tuple_tupleMuls(ray.direction, t));
}

void ray_raySphereIntersect(Ray ray, Sphere sphere, Intersection *dest){
    Mat4 invSphereTransform;
    mat_mat4Inverse(sphere.transform, invSphereTransform);

    Ray transformedRay = ray_transformRay(ray, invSphereTransform);
    Tuple vectorSphereToRay = tuple_tupleSub(transformedRay.origin, sphere.origin);
    
    float a = tuple_vectorDot(transformedRay.direction, transformedRay.direction);
    float b = 2.0f * tuple_vectorDot(transformedRay.direction, vectorSphereToRay);
    float c = tuple_vectorDot(vectorSphereToRay, vectorSphereToRay) - sphere.radius; // This value is a constant - 1, but im assuming its the sphere radius

    float discriminant = powf(b, 2) - 4 * a * c;
   

    if (discriminant < 0) {
    
        dest[0].object = sphere;
        dest[0].t = NAN;
        dest[1].object = sphere;
        dest[1].t = NAN; 
    } 
    else {
        dest[0].object = sphere;
        dest[0].t =  (-b - sqrtf(discriminant)) / (2.0f * a);
        dest[1].object = sphere;
        dest[1].t = (-b + sqrtf(discriminant)) / (2.0f * a);
    }
}

Ray ray_transformRay(Ray ray, Mat4 transform){
    Ray transformedRay;
    transformedRay.origin = mat_mat4MultuplyTuple(transform, ray.origin);
    transformedRay.direction = mat_mat4MultuplyTuple(transform, ray.direction);

    return transformedRay;
}

Computations intersection_prepareComputations(Intersection intersection, Ray ray){
    Computations comps;

    comps.t = intersection.t;
    comps.object = intersection.object;

    comps.point = ray_rayPosition(ray, comps.t);
    comps.eyev = tuple_tupleNegate(ray.direction);
    comps.normalv = sphere_normalAt(comps.object, comps.point);

    if (tuple_vectorDot(comps.normalv, comps.eyev) < 0) {
        comps.inside = 1;
        comps.normalv = tuple_tupleNegate(comps.normalv);
    }
    else {
        comps.inside = 0;
    }

    comps.overPoint = tuple_tupleAdd(comps.point, tuple_tupleMuls(comps.normalv, 0.01f)); // EPSILON : The epsilon value here is higher than standard (0.0001) because otherwise it casues acne

    return comps;
}