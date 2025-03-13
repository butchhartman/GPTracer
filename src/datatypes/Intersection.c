#include "Intersection.h"

Intersection intersection_intersectionCreateIntersection(Sphere object, float t){
    Intersection i;
    i.object = object;
    i.t = t;
    return i;
}

Intersection intersection_determineHit(Intersection *intersections, int length){
    Intersection hit = {0};
    hit.t = 1e30; // arbitrarily high number
    for (int i = 0; i < length; i++) {

        if (intersections[i].t > 0 && intersections[i].t < hit.t) {
            hit = intersections[i];
        }
    }

    if (floatCompare(hit.t, 1e30) == 1) { // If the closest hit value was not changed, return the closest hit as NAN
        hit.t = NAN;
    }

    return hit;
}
