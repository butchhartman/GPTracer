#include "unity.h"
#include "World.h"

void setUp() {

}

void tearDown() {

}

void test_worldInit() {
    World world = world_createDefault();

    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createColor(0.8f, 1.0f, 0.6f), world.spheres[0].material.surfaceColor));
    TEST_ASSERT_EQUAL_FLOAT(0.7f, world.spheres[0].material.diffuse);
    TEST_ASSERT_EQUAL_FLOAT(0.2f, world.spheres[0].material.specular);

    Mat4 expectedScaling;
    mat_mat4CreateScaling(expectedScaling, 0.5f, 0.5f, 0.5f);
    TEST_ASSERT_TRUE(mat_mat4Compare(world.spheres[1].transform, expectedScaling));

    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createPoint(-10, 10, -10), world.light.position));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createColor(1, 1, 1), world.light.intensity));

}

void test_worldIntersect() {
    World world = world_createDefault();
    Ray r = ray_createRay(tuple_createPoint(0, 0, -5), tuple_createVector(0, 0, 1));

    int length;
    Intersection *xs = world_intersectWorld(world, r, &length);

    TEST_ASSERT_EQUAL_INT(4, length);
    TEST_ASSERT_EQUAL_FLOAT(4.0f, xs[0].t);
    TEST_ASSERT_EQUAL_FLOAT(4.5f, xs[1].t);
    TEST_ASSERT_EQUAL_FLOAT(5.5f, xs[2].t);
    TEST_ASSERT_EQUAL_FLOAT(6.0f, xs[3].t);

}

void test_shadeHit() {
    World w = world_createDefault();
    Ray r = ray_createRay(tuple_createPoint(0, 0, -5), tuple_createVector(0, 0, 1));
    Sphere shape = w.spheres[0];
    Intersection i = intersection_intersectionCreateIntersection(shape, 4);

    Computations comps = intersection_prepareComputations(i, r);

    Tuple c = world_shadeHit(w, comps);
    
    TEST_ASSERT_TRUE(tuple_tupleCompare(c, tuple_createColor(0.38066f, 0.47583f, 0.2855f)));
}

void test_shadeHit_inside() {
    World w = world_createDefault();
    w.light = pointlight_createPointlight(tuple_createPoint(0, 0.25f, 0), tuple_createColor(1, 1, 1));
    Ray r = ray_createRay(tuple_createPoint(0, 0, 0), tuple_createVector(0, 0, 1));
    Sphere shape = w.spheres[1];
    Intersection i = intersection_intersectionCreateIntersection(shape, 0.5f);
    Computations comps = intersection_prepareComputations(i, r);

    Tuple c = world_shadeHit(w, comps);
    
    TEST_ASSERT_TRUE(tuple_tupleCompare(c, tuple_createColor(0.90498f, 0.90498f, 0.90498f)));
}

void test_colorAt() {
    World w = world_createDefault();
    Ray r = ray_createRay(tuple_createPoint(0, 0, -5), tuple_createVector(0, 1, 0));
    Tuple c = world_worldColorAt(w, r);

    TEST_ASSERT_TRUE(tuple_tupleCompare(c, tuple_createColor(0, 0, 0)));

}

void test_colorAt_hit() {
    World w = world_createDefault();
    Ray r = ray_createRay(tuple_createPoint(0, 0, -5), tuple_createVector(0, 0, 1));
    Tuple c = world_worldColorAt(w, r);

    TEST_ASSERT_TRUE(tuple_tupleCompare(c, tuple_createColor(0.38066f, 0.47583f, 0.2855f)));

}
void test_colorAt_inside() {
    World w = world_createDefault();
    Ray r = ray_createRay(tuple_createPoint(0, 0, 0.75), tuple_createVector(0, 0, -1));
    
    w.spheres[0].material.ambient = 1;
    w.spheres[1].material.ambient = 1;

    Tuple c = world_worldColorAt(w, r);
    Tuple realColor = tuple_createColor(w.spheres[0].material.surfaceColor.x,  w.spheres[0].material.surfaceColor.y,  w.spheres[0].material.surfaceColor.z);

    TEST_ASSERT_TRUE(tuple_tupleCompare(c, realColor));
}

int main() {
    RUN_TEST(test_worldInit);
    RUN_TEST(test_worldIntersect);
    RUN_TEST(test_shadeHit);
    RUN_TEST(test_shadeHit_inside);
    RUN_TEST(test_colorAt);
    RUN_TEST(test_colorAt_hit);
    RUN_TEST(test_colorAt_inside);
    return UNITY_END();
}