#include "World.h"
#include "CommonOperations.h"
World world_createDefault(){
    World newWorld;
    newWorld.light = pointlight_createPointlight(tuple_createPoint(-10, 10, -10), tuple_createColor(1, 1, 1));
    newWorld.objectCount= 2;
    
    newWorld.objects = malloc(newWorld.objectCount * sizeof(Shape));

    Material sphereMat = material_createMaterial(tuple_createColor(0.8f, 1.0f, 0.6f), 0.1f, 0.7f, 0.2f, 200.0f);
    Material sphereMat2 = material_createMaterial(tuple_createColor(1, 1, 1), 0.1f, 0.9f, 0.9f, 200.0f);
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
    xs = malloc(sizeof(Intersection) * world.objectCount * 2);
    Intersection txs[2];
    for (unsigned int i = 0; i < world.objectCount; i++) {
        ray_rayShapeIntersect(ray, world.objects[i], txs);
        xs[i * 2].t = txs[0].t;
        xs[i * 2 + 1].t = txs[1].t;
        xs[i * 2].object = txs[0].object;
        xs[i * 2 + 1].object = txs[1].object;
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

Tuple world_shadeHit(World world, Computations comps){
    int inShadow = world_pointInShadow(world, comps.overPoint);
    return material_calculateLighting(comps.object.material, world.light, comps.point, comps.eyev, comps.normalv, inShadow); // Cannot believe the tests will pass even if the normal vector is swapped for the eye vector
}

Tuple world_worldColorAt(World world, Ray ray){
    int length;
    Intersection *xs = world_intersectWorld(world, ray, &length);
    Intersection hit = intersection_determineHit(xs, length);
    if (isnan(hit.t)) {
        return tuple_createColor(0, 0, 0);
    }
    Computations comps = intersection_prepareComputations(hit, ray);
    return world_shadeHit(world, comps);
}

int world_pointInShadow(World world, Tuple point){
    Tuple vectorToLs = tuple_tupleSub(world.light.position, point);
    float distance = tuple_vectorGetMagnitude(vectorToLs);
    Tuple direction = tuple_vectorNormalize(vectorToLs);


    Ray ray = ray_createRay(point, direction);
    int noXs;
    Intersection *xs = world_intersectWorld(world, ray, &noXs);

    Intersection hit = intersection_determineHit(xs, noXs);
    if (!isnan(hit.t) && hit.t < distance) {
        return 1;
    }
    else {
        return 0;
    }
}
