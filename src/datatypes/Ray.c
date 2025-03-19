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

        case(Cube):
            ray_rayCubeIntersect(transformedRay, shape, dest, length);
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

void ray_rayCubeIntersect(Ray ray, Shape cube, Intersection **dest, int *length){
    float xtmin, xtmax;
    float ytmin, ytmax;
    float ztmin, ztmax;
    ray_checkAxis(ray.origin.x, ray.direction.x, &xtmin, &xtmax);
    ray_checkAxis(ray.origin.y, ray.direction.y, &ytmin, &ytmax);
    ray_checkAxis(ray.origin.z, ray.direction.z, &ztmin, &ztmax);

    float tmin = -1e30; // arbitrarily small number
    float tmax = 1e30; // arbitrarily large number

    if (xtmin > tmin) {
        tmin = xtmin;
    }
    if (ytmin > tmin) {
        tmin = ytmin;
    }
    if (ztmin > tmin) {
        tmin = ztmin;
    }

    if (xtmax < tmax) {
        tmax = xtmax;
    }
    if (ytmax < tmax) {
        tmax = ytmax;
    }
    if (ztmax < tmax) {
        tmax = ztmax;
    }


    *dest = malloc(sizeof(Intersection) * 2);
    *length = 2;

    if (tmin > tmax) {
        (*dest)[0].object = cube;
        (*dest)[0].t = NAN; 
        (*dest)[1].object = cube;
        (*dest)[1].t = NAN; 
    }
    else {
        (*dest)[0].object = cube;
        (*dest)[0].t = tmin; 
        (*dest)[1].object = cube;
        (*dest)[1].t = tmax; 
    }   
}

void ray_checkAxis(float origin, float direction, float *tmin, float *tmax){
    float tminNumerator = (-1 - origin);
    float tmaxNumerator = (1 - origin);

    float localtmin;
    float localtmax;

    if (fabsf(direction) >= 0.01) { // EPSILON, 0.01 instead of 0.0001 as is the theme for this program
        localtmin = tminNumerator / direction;
        localtmax = tmaxNumerator / direction;
    }
    else {
        localtmin = tminNumerator * INFINITY;
        localtmax = tmaxNumerator * INFINITY; 
    }

    if (localtmin > localtmax) {
        *tmin = localtmax;
        *tmax = localtmin;
    }
    else {
        *tmin = localtmin;
        *tmax = localtmax;
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
    comps.underPoint = tuple_tupleSub(comps.point, tuple_tupleMuls(comps.normalv, 0.01f)); // EPSILON

    return comps;
}

float ray_schlick(Computations comps){
    float cos = tuple_vectorDot(comps.eyev, comps.normalv);

    if (comps.n1 > comps.n2) {
        float n = comps.n1 / comps.n2;
        float sin2_t = powf(n, 2) * (1.0f - powf(cos, 2));

        if (sin2_t > 1.0f) {
            return 1.0f;
        }

        float cos_t = sqrtf(1.0f - sin2_t);
        cos = cos_t;
    }

    float r0 = powf( (comps.n1 - comps.n2) / (comps.n1 + comps.n2), 2 );

    return r0 + (1 - r0) * powf((1 - cos), 5);
}
