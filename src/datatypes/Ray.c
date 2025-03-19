#include "Ray.h"
#include "malloc.h"
#include "stdio.h"
#include "string.h"
Ray ray_createRay(Tuple origin, Tuple direction){
    Ray newRay;
    newRay.origin = origin;
    newRay.direction = direction;
    return newRay;
}

Tuple ray_rayPosition(Ray ray, float t){
    return tuple_tupleAdd(ray.origin, tuple_tupleMuls(ray.direction, t));
}

// Calls shape-specific intersect functions based on the shape's formfactor
Ray ray_rayShapeIntersect(Ray ray, Shape shape, Intersection **dest, int *length){
    Mat4 invSphereTransform;
    mat_mat4Inverse(shape.transform, invSphereTransform);

    Ray transformedRay = ray_transformRay(ray, invSphereTransform);

    switch (shape.formfactor){

        case (Sphere):
            ray_raySphereIntersect(transformedRay, shape, dest, length);
            break;

        case(Plane):
            ray_rayPlaneIntersect(transformedRay, shape, dest, length);
            break;

        default:
            break;

    }

    return transformedRay;
}

void ray_raySphereIntersect(Ray ray, Shape sphere, Intersection **dest, int *length) // TODO : REFACTOR TO MAKE THIS UTILIZE MALLOC AND RETURN A LENGTH
{
    *dest = malloc(sizeof(Intersection) * 2);
    *length = 2;

    if (*dest == NULL) {
        return;
    }

    Tuple vectorSphereToRay = tuple_tupleSub(ray.origin, sphere.origin);
    
    float a = tuple_vectorDot(ray.direction, ray.direction);
    float b = 2.0f * tuple_vectorDot(ray.direction, vectorSphereToRay);
    float c = tuple_vectorDot(vectorSphereToRay, vectorSphereToRay) - 1; // This value is a constant - 1, but im assuming its the sphere radius

    float discriminant = powf(b, 2) - 4 * a * c;
  

    if (discriminant < 0) {
    
        (*dest)[0].object = sphere;
        (*dest)[0].t = NAN;
        (*dest)[1].object = sphere;
        (*dest)[1].t = NAN; 
    } 
    else {
        (*dest)[0].object = sphere;
        (*dest)[0].t =  (-b - sqrtf(discriminant)) / (2.0f * a);
        (*dest)[1].object = sphere;
        (*dest)[1].t = (-b + sqrtf(discriminant)) / (2.0f * a);
    }
}

void ray_rayPlaneIntersect(Ray ray, Shape plane, Intersection **dest, int *length){
    *dest = malloc(sizeof(Intersection));
    *length = 1;
    (*dest)[0].object = plane;
    
    if (fabsf(ray.direction.y) < 0.0001) { // EPSILON
        (*dest)[0].t = NAN;
    } else {
        (*dest)[0].t = -ray.origin.y / ray.direction.y;
    }

}


Ray ray_transformRay(Ray ray, Mat4 transform){
    Ray transformedRay;
    transformedRay.origin = mat_mat4MultuplyTuple(transform, ray.origin);
    transformedRay.direction = mat_mat4MultuplyTuple(transform, ray.direction);

    return transformedRay;
}

Computations intersection_prepareComputations(Intersection intersection, Ray ray, Intersection *xs, int length){
    Computations comps;
    Intersection *containers;
    if (xs != NULL) {
        containers = malloc(length * sizeof(Intersection));

    int highestOccupiedIndex = -1;
    for (int i = 0; i < length; i++) {
        if (xs[i].t == intersection.t) { // this may cause problems if multiple intersections can have the same T value
            if (highestOccupiedIndex == -1) {
                comps.n1 = 1.0f;
            }
            else {
                comps.n1 = containers[highestOccupiedIndex].object.material.refractiveIndex;
            }
        }

        // detecting if xs[i] is already in containers
        int iInContainer = 0;
        int containerAt = 0;
        for (int j = 0; j <= highestOccupiedIndex; j++) {
            if (containers[j].object.instanceID == xs[i].object.instanceID) {
                iInContainer = 1;
                containerAt = j;
            }
        }

        if (iInContainer == 1) {
            // I need to detect when the thing i want to remove is not the thing at the current index
            // I need to detect when the thing i want to remove is the thing at the current index
            // I dont think its detecting that C is already in there
            

            if (highestOccupiedIndex - 1 >= 0 && containerAt != highestOccupiedIndex) {
                for (int l = containerAt; l <= highestOccupiedIndex; l++) // may be a source of errors, intent is to shift the array after the removed index to the left
                containers[l] = containers[l+1];
            }
            highestOccupiedIndex--;
            
        } 
        else {
            highestOccupiedIndex++;
            containers[highestOccupiedIndex] = xs[i]; // Should 'append' an intersection by increasing the highest occupied index and putting it there. 
        }

        if (xs[i].t == intersection.t) {
            if (highestOccupiedIndex == -1) {
                comps.n2 = 1.0f;
            }
            else {
                comps.n2 = containers[highestOccupiedIndex].object.material.refractiveIndex;
            }
            break;
        }

    }
    free(containers);
    }

    comps.t = intersection.t;
    comps.object = intersection.object;

    comps.point = ray_rayPosition(ray, comps.t);
    comps.eyev = tuple_tupleNegate(ray.direction);
    comps.normalv = shape_normalAt(intersection.object, comps.point); 

    if (tuple_vectorDot(comps.normalv, comps.eyev) < 0) {
        comps.inside = 1;
        comps.normalv = tuple_tupleNegate(comps.normalv);
    }
    else {
        comps.inside = 0;
    }
    comps.reflectv = tuple_reflect(ray.direction, comps.normalv);
    comps.overPoint = tuple_tupleAdd(comps.point, tuple_tupleMuls(comps.normalv, 0.01f)); // EPSILON : The epsilon value here is higher than standard (0.0001) because otherwise it casues acne

    return comps;
}