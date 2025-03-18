#include "unity.h"
#include "World.h"

void setUp() {

}

void tearDown() {

}

void test_worldInit() {
    World world = world_createDefault();

    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createColor(0.8f, 1.0f, 0.6f), world.objects[0].material.surfaceColor));
    TEST_ASSERT_EQUAL_FLOAT(0.7f, world.objects[0].material.diffuse);
    TEST_ASSERT_EQUAL_FLOAT(0.2f, world.objects[0].material.specular);

    Mat4 expectedScaling;
    mat_mat4CreateScaling(expectedScaling, 0.5f, 0.5f, 0.5f);
    TEST_ASSERT_TRUE(mat_mat4Compare(world.objects[1].transform, expectedScaling));

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
    Shape shape = w.objects[0];
    Intersection i = intersection_intersectionCreateIntersection(shape, 4);

    Computations comps = intersection_prepareComputations(i, r, NULL, -1);

    Tuple c = world_shadeHit(w, comps, 1);
    
    TEST_ASSERT_TRUE(tuple_tupleCompare(c, tuple_createColor(0.38066f, 0.47583f, 0.2855f)));
}

void test_shadeHit_inside() {
    World w = world_createDefault();
    w.light = pointlight_createPointlight(tuple_createPoint(0, 0.25f, 0), tuple_createColor(1, 1, 1));
    Ray r = ray_createRay(tuple_createPoint(0, 0, 0), tuple_createVector(0, 0, 1));
    Shape shape = w.objects[1];
    Intersection i = intersection_intersectionCreateIntersection(shape, 0.5f);
    Computations comps = intersection_prepareComputations(i, r, NULL, -1);

    Tuple c = world_shadeHit(w, comps, 1);
    
    TEST_ASSERT_TRUE(tuple_tupleCompare(c, tuple_createColor(0.90498f, 0.90498f, 0.90498f)));
}

void test_colorAt() {
    World w = world_createDefault();
    Ray r = ray_createRay(tuple_createPoint(0, 0, -5), tuple_createVector(0, 1, 0));
    Tuple c = world_worldColorAt(w, r, 1);

    TEST_ASSERT_TRUE(tuple_tupleCompare(c, tuple_createColor(0, 0, 0)));

}

void test_colorAt_hit() {
    World w = world_createDefault();
    Ray r = ray_createRay(tuple_createPoint(0, 0, -5), tuple_createVector(0, 0, 1));
    Tuple c = world_worldColorAt(w, r, 1);

    TEST_ASSERT_TRUE(tuple_tupleCompare(c, tuple_createColor(0.38066f, 0.47583f, 0.2855f)));

}
void test_colorAt_inside() {
    World w = world_createDefault();
    Ray r = ray_createRay(tuple_createPoint(0, 0, 0.75), tuple_createVector(0, 0, -1));
    
    w.objects[0].material.ambient = 1;
    w.objects[1].material.ambient = 1;

    Tuple c = world_worldColorAt(w, r, 1);
    Tuple realColor = tuple_createColor(w.objects[1].material.surfaceColor.x,  w.objects[1].material.surfaceColor.y,  w.objects[1].material.surfaceColor.z);

    TEST_ASSERT_TRUE(tuple_tupleCompare(c, realColor));
}

void test_inShadow() {
    World w = world_createDefault();
    Tuple point = tuple_createPoint(0, 10, 0);
    TEST_ASSERT_FALSE(world_pointInShadow(w, point));
}


void test_inShadow_2() {
    World w = world_createDefault();
    Tuple point = tuple_createPoint(10, -10, 10);
    TEST_ASSERT_TRUE(world_pointInShadow(w, point));
}

void test_inShadow_3() {
    World w = world_createDefault();
    Tuple point = tuple_createPoint(-20, 20, -20);
    TEST_ASSERT_FALSE(world_pointInShadow(w, point));
}

void test_inShadow_4() {
    World w = world_createDefault();
    Tuple point = tuple_createPoint(-2, 2, -2);
    TEST_ASSERT_FALSE(world_pointInShadow(w, point));
}

void test_inShadow_5() {
    World w = world_createDefault();
    w.light = pointlight_createPointlight(tuple_createPoint(0, 0, -10), tuple_createColor(1, 1, 1));
    Mat4 translation;
    mat_mat4CreateTranslation(translation, 0, 0, 10);
    Material mat = w.objects[0].material;
    mat.surfaceColor = tuple_createColor(1, 1, 1);
    mat.ambient = 0.1f;
    Shape news = shape_createDefaultShape(0, Sphere);
    news.material = mat;
    mat_mat4Copy(translation, news.transform);
    
    w.objects[1] = news;

    Ray ray = ray_createRay(tuple_createPoint(0, 0, 5), tuple_createVector(0, 0, 1));
    Intersection i = intersection_intersectionCreateIntersection(w.objects[1], 4.0f);
    Computations comps = intersection_prepareComputations(i, ray, NULL, -1);
    Tuple c = world_shadeHit(w, comps, 1);

    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createColor(0.1f, 0.1f, 0.1f), c));
}

void test_inShadow_offset() {
    Ray ray = ray_createRay(tuple_createPoint(0, 0, -5), tuple_createVector(0, 0, 1));
    Mat4 strans;
    mat_mat4CreateTranslation(strans,0, 0, 1);
    Material mat = material_createMaterial(tuple_createColor(1,1,1), 1, 1, 1, 1, 0.0f);
    Shape sphere = shape_createDefaultShape(0, Sphere);
    sphere.material = mat;
    mat_mat4Copy(strans, sphere.transform); 
    
    Intersection i = intersection_intersectionCreateIntersection(sphere, 5);
    Computations comps = intersection_prepareComputations(i, ray, NULL, -1);
    TEST_ASSERT_TRUE(comps.overPoint.z < -0.0001f/2.0f);
    TEST_ASSERT_TRUE(comps.point.z > comps.overPoint.z);
}

int main() {
    RUN_TEST(test_worldInit);
    RUN_TEST(test_worldIntersect);
    RUN_TEST(test_shadeHit);
    RUN_TEST(test_shadeHit_inside);
    RUN_TEST(test_colorAt);
    RUN_TEST(test_colorAt_hit);
    RUN_TEST(test_colorAt_inside);
    RUN_TEST(test_inShadow);
    RUN_TEST(test_inShadow_2);
    RUN_TEST(test_inShadow_3);
    RUN_TEST(test_inShadow_4);
    RUN_TEST(test_inShadow_5);
    RUN_TEST(test_inShadow_offset);
    return UNITY_END();

}

// FIXME :: UNCOMMENT!