#include "World.h"
#include "CommonOperations.h"
World world_createDefault(){
    World newWorld;
    newWorld.light = pointlight_createPointlight(tuple_createPoint(-10, 10, -10), tuple_createColor(1, 1, 1));
    newWorld.objectCount= 2;
    
    newWorld.objects = malloc(newWorld.objectCount * sizeof(Shape));

    Material sphereMat = material_createMaterial(tuple_createColor(0.8f, 1.0f, 0.6f), 0.1f, 0.7f, 0.2f, 200.0f, 0.0f);
    Material sphereMat2 = material_createMaterial(tuple_createColor(1, 1, 1), 0.1f, 0.9f, 0.9f, 200.0f, 0.0f);
    Mat4 s2Transform;
    mat_mat4CreateScaling(s2Transform, 0.5, 0.5, 0.5);

    Shape s1 = shape_createDefaultShape(0, Sphere);
    s1.material = sphereMat;
    Shape s2 = shape_createDefaultShape(1, Sphere);
   s2.material = sphereMat2;
   mat_mat4Copy(s2Transform, s2.transform); 

    newWorld.objects[0] = s1; 
    newWorld.objects[1] = s2;

    return newWorld;
}

Intersection *world_intersectWorld(World world, Ray ray, int *length){
    Intersection *xs;
    xs = malloc(sizeof(Intersection) * world.objectCount * 2); // If objects can ever have more than two intersections this will cause problems
    Intersection *txs;
    for (unsigned int i = 0; i < world.objectCount; i++) {
        ray_rayShapeIntersect(ray, world.objects[i], &txs, length);
        
        for (int j = 0; j < *length; j++) {
            xs[j * 2 + i].t = txs[j].t;         // The + i here acts as a bootleg stride to make sure objects do not write over each other's entries.
            xs[j * 2 + i].object = txs[j].object;
        }
        free(txs);
        // xs[i * 2].t = txs[0].t;
        // xs[i * 2 + 1].t = txs[1].t;
        // xs[i * 2].object = txs[0].object;
        // xs[i * 2 + 1].object = txs[1].object;
    }
    // TODO : move to function. 
    //THIS WHOLE FUCKING ERROR WAS CAUSED BY MY DUMBASS FORGETTING TO SORT THE OBJECT OF THE STRUCT WITH THE T VALUE!
    // ONLY SORTING THE T VALUES CAUSED OBJECTS TO BE DRAWN OVER EACH OTHER! I DONT EVEN FUCKING KNOW WHY!!!
    int n = 2*world.objectCount;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (xs[j].t < xs[min].t)
                min = j;
        }
       if (min != i) {
            float temp = xs[min].t;
            Shape tspmo = xs[min].object;
            xs[min].t = xs[i].t;
            xs[min].object = xs[i].object;
            xs[i].t = temp;
            xs[i].object = tspmo;
        }
    }
    //bubbleSort(xs, 2*world.objectCount);

    // for (unsigned int i = 0; i < 2*world.objectCount; i++) {
    //     printf("ARR %d : %f\n", i, xs[i].t);
    // }
    *length = 2 * world.objectCount;
    return xs;
}

Tuple world_shadeHit(World world, Computations comps, int remaining){
    int inShadow = world_pointInShadow(world, comps.overPoint);
    Tuple lightingColor = material_calculateLighting(comps.object.material, world.light, comps.point, comps.eyev, comps.normalv, inShadow, comps.object); // Cannot believe the tests will pass even if the normal vector is swapped for the eye vector
    Tuple reflectedColor = world_reflectedColor(world, comps, remaining);
    Tuple refractedColor = world_refractedColor(world, comps, remaining);
    Tuple combinedColor = tuple_tupleAdd(lightingColor, tuple_tupleAdd(refractedColor, reflectedColor));
    combinedColor.w = 1; // hack to avoid w inconsistencies when adding colors 
    return combinedColor; 
}

Tuple world_worldColorAt(World world, Ray ray, int remaining){
    int length;
    Intersection *xs = world_intersectWorld(world, ray, &length);
    Intersection hit = intersection_determineHit(xs, length);
    if (isnan(hit.t)) {
        return tuple_createColor(0, 0, 0);
    }
    Computations comps = intersection_prepareComputations(hit, ray, xs, length);
    free(xs);
    return world_shadeHit(world, comps, remaining);
}

int world_pointInShadow(World world, Tuple point){
    Tuple vectorToLs = tuple_tupleSub(world.light.position, point);
    float distance = tuple_vectorGetMagnitude(vectorToLs);
    Tuple direction = tuple_vectorNormalize(vectorToLs);


    Ray ray = ray_createRay(point, direction);
    int noXs;
    Intersection *xs = world_intersectWorld(world, ray, &noXs);

    Intersection hit = intersection_determineHit(xs, noXs);
    free(xs);
    if (!isnan(hit.t) && hit.t < distance) {
        return 1;
    }
    else {
        return 0;
    }
}

Tuple world_reflectedColor(World w, Computations comps, int remaining){
    if (comps.object.material.reflective == 0) {
        return COLOR_BLACK;
    }

    if (remaining <= 0) {
        return COLOR_BLACK;
    }

    Ray reflectRay = ray_createRay(comps.overPoint, comps.reflectv);
    Tuple color = world_worldColorAt(w, reflectRay, remaining - 1);
    Tuple reflectedColor = tuple_tupleMuls(color, comps.object.material.reflective);
    reflectedColor.w = 1; // hack to keep things consistent with colors
    return reflectedColor;
}

Tuple world_refractedColor(World w, Computations comps, int remaining){
    if (comps.object.material.transparency == 0 || remaining == 0) {
        return COLOR_BLACK;
    }

    float nRatio = comps.n1 / comps.n2;
    float cosi = tuple_vectorDot(comps.eyev, comps.normalv);
    float sin2t = powf(nRatio, 2) * (1 - powf(cosi, 2));

    if (sin2t > 1) {
        return COLOR_BLACK;
    }

    float cost = sqrtf(1.0f - sin2t);

    Tuple direction = tuple_tupleSub(tuple_tupleMuls(comps.normalv, nRatio * cosi - cost), tuple_tupleMuls(comps.eyev, nRatio));
    Ray refractedRay = ray_createRay(comps.underPoint, direction);

    Tuple color = world_worldColorAt(w, refractedRay, remaining - 1);

    return color;
}
