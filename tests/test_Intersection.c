#include "unity.h"
#include "Intersection.h"

void setUp() {

}

void tearDown() {

}


void test_intersectioinCreate() {
    Material mat = material_createMaterial(tuple_createColor(1, 0, 0),0.1f, 0.9f, 0.9f, 200.0f);
    Sphere s = sphere_createSphere(tuple_createPoint(0, 0, 0), 1, 0, NULL, mat);
    Intersection i = intersection_intersectionCreateIntersection(s, 3.5f);

    TEST_ASSERT_EQUAL_FLOAT(3.5f, i.t);
    TEST_ASSERT_EQUAL_INT(0, i.object.instanceID);
}

void test_aggregatingIntersections() {

    Material mat = material_createMaterial(tuple_createColor(1, 0, 0), 0.1f, 0.9f, 0.9f, 200.0f);
    Sphere s = sphere_createSphere(tuple_createPoint(0, 0, 0), 1, 0, NULL, mat);
    Intersection i = intersection_intersectionCreateIntersection(s, 3.5f);
    Intersection i2 = intersection_intersectionCreateIntersection(s, 2.0f);

    Intersection agg[2];
    agg[0] = i;
    agg[1] = i2;

    TEST_ASSERT_EQUAL_INT(2, sizeof(agg)/sizeof(agg[0]));
    TEST_ASSERT_EQUAL_FLOAT(3.5f, agg[0].t);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, agg[1].t);    
}

void test_intersectionDetermineHit() {
    Material mat = material_createMaterial(tuple_createColor(1, 0, 0), 0.1f, 0.9f, 0.9f, 200.0f);
    Sphere s = sphere_createSphere(tuple_createPoint(0,0,0), 1, 0, NULL, mat);
    Intersection i1 = intersection_intersectionCreateIntersection(s, 1);
    Intersection i2 = intersection_intersectionCreateIntersection(s, 2);
    
    Intersection is[2];
    is[0] = i1;
    is[1] = i2;

    Intersection i = intersection_determineHit(is, 2);

    TEST_ASSERT_EQUAL_FLOAT(1.0f, i.t);
}

void test_intersectionDetermineHit_someNegative(){

    Material mat = material_createMaterial(tuple_createColor(1, 0, 0), 0.1f, 0.9f, 0.9f, 200.0f);
    Sphere s = sphere_createSphere(tuple_createPoint(0,0,0), 1, 0, NULL, mat);
    Intersection i1 = intersection_intersectionCreateIntersection(s, -1);
    Intersection i2 = intersection_intersectionCreateIntersection(s, 1);
    
    Intersection is[2];
    is[0] = i1;
    is[1] = i2;

    Intersection i = intersection_determineHit(is, 2);

    TEST_ASSERT_EQUAL_FLOAT(1.0f, i.t);
}

void test_intersectionDetermineHit_allNegative() {

    Material mat = material_createMaterial(tuple_createColor(1, 0, 0), 0.1f, 0.9f, 0.9f, 200.0f);
    Sphere s = sphere_createSphere(tuple_createPoint(0,0,0), 1, 0, NULL, mat);
    Intersection i1 = intersection_intersectionCreateIntersection(s, -1);
    Intersection i2 = intersection_intersectionCreateIntersection(s, -2);
    
    Intersection is[2];
    is[0] = i1;
    is[1] = i2;

    Intersection i = intersection_determineHit(is,2);

    TEST_ASSERT_EQUAL_FLOAT(NAN, i.t);
}

void test_intersectionDetermineHit_manyIntersections() {

    Material mat = material_createMaterial(tuple_createColor(1, 0, 0), 0.1f, 0.9f, 0.9f, 200.0f);
    Sphere s = sphere_createSphere(tuple_createPoint(0,0,0), 1, 0, NULL, mat);
    Intersection i1 = intersection_intersectionCreateIntersection(s, 5);
    Intersection i2 = intersection_intersectionCreateIntersection(s, 7);
    Intersection i3 = intersection_intersectionCreateIntersection(s, -3);
    Intersection i4 = intersection_intersectionCreateIntersection(s, 2);
    
    Intersection is[4];
    is[0] = i1;
    is[1] = i2;
    is[2] = i3;
    is[3] = i4;

    Intersection i = intersection_determineHit(is, 4);

    TEST_ASSERT_EQUAL_FLOAT(2.0f, i.t);
}

int main() {
    RUN_TEST(test_intersectioinCreate);
    RUN_TEST(test_aggregatingIntersections);
    RUN_TEST(test_intersectionDetermineHit);
    RUN_TEST(test_intersectionDetermineHit_someNegative);
    RUN_TEST(test_intersectionDetermineHit_allNegative);
    RUN_TEST(test_intersectionDetermineHit_manyIntersections);
    return UNITY_END();
}