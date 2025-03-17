#include "unity.h"
#include "Patterns.h"
#include "Shape.h"

void setUp() {

}

void tearDown() {

}

void test_patternStripe() {
    Pattern pattern = pattern_createPattern(COLOR_WHITE, COLOR_BLACK, Stripe);

    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern.a, COLOR_WHITE));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern.b, COLOR_BLACK));
}

void test_patternAt_y() {
    Pattern pattern = pattern_createPattern(COLOR_WHITE, COLOR_BLACK, Stripe);
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_patternAt(pattern, tuple_createPoint(0, 0, 0)), COLOR_WHITE));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_patternAt(pattern, tuple_createPoint(0, 1, 0)), COLOR_WHITE));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_patternAt(pattern, tuple_createPoint(0, 2, 0)), COLOR_WHITE));
}

void test_patternAt_z() {
    Pattern pattern = pattern_createPattern(COLOR_WHITE, COLOR_BLACK, Stripe);
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_patternAt(pattern, tuple_createPoint(0, 0, 0)), COLOR_WHITE));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_patternAt(pattern, tuple_createPoint(0, 0, 1)), COLOR_WHITE));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_patternAt(pattern, tuple_createPoint(0, 0, 1)), COLOR_WHITE));
}

void test_patternAt_x() {
    Pattern pattern = pattern_createPattern(COLOR_WHITE, COLOR_BLACK, Stripe);
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_patternAt(pattern, tuple_createPoint(0, 0, 0)), COLOR_WHITE));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_patternAt(pattern, tuple_createPoint(0.9f, 0, 0)), COLOR_WHITE));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_patternAt(pattern, tuple_createPoint(1, 0, 0)), COLOR_BLACK));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_patternAt(pattern, tuple_createPoint(-0.1f, 0, 0)), COLOR_BLACK));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_patternAt(pattern, tuple_createPoint(-1, 0, 0)), COLOR_BLACK));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_patternAt(pattern, tuple_createPoint(-1.1f, 0, 0)), COLOR_WHITE));
}

void test_patternAtObject() {
    Mat4 transform;
    mat_mat4CreateScaling(transform, 2, 2, 2);
    
    Pattern pattern = pattern_createPattern(COLOR_WHITE, COLOR_BLACK, Stripe);

    Shape sphere = shape_createDefaultShape(0, Sphere);
    mat_mat4Copy(transform, sphere.transform);
    sphere.material.pattern = pattern;

    Tuple c = pattern_patternAtObject(pattern, sphere, tuple_createPoint(1.5f, 0, 0));

    TEST_ASSERT_TRUE(tuple_tupleCompare(c, COLOR_WHITE));
}


void test_patternAtObject_patternTransform() {
    Mat4 transform;
    mat_mat4CreateScaling(transform, 2, 2, 2);
    
    Pattern pattern = pattern_createPattern(COLOR_WHITE, COLOR_BLACK, Stripe);
    mat_mat4Copy(transform, pattern.transform);

    Shape sphere = shape_createDefaultShape(0, Sphere);
    sphere.material.pattern = pattern;

    Tuple c = pattern_patternAtObject(pattern, sphere, tuple_createPoint(1.5f, 0, 0));
    TEST_ASSERT_TRUE(tuple_tupleCompare(COLOR_WHITE, c));
}


void test_patternAtObject_patternTransformBoth() {
    Mat4 transform;
    mat_mat4CreateScaling(transform, 2, 2, 2);
    
    Pattern pattern = pattern_createPattern(COLOR_WHITE, COLOR_BLACK, Stripe);
    mat_mat4Copy(transform, pattern.transform);

    Shape sphere = shape_createDefaultShape(0, Sphere);
    mat_mat4Copy(transform, sphere.transform);
    sphere.material.pattern = pattern;

    Tuple c = pattern_patternAtObject(pattern, sphere, tuple_createPoint(2.5f, 0, 0));
    TEST_ASSERT_TRUE(tuple_tupleCompare(COLOR_WHITE, c));
}

int main() {
    RUN_TEST(test_patternStripe);
    RUN_TEST(test_patternAt_x);
    RUN_TEST(test_patternAt_y);
    RUN_TEST(test_patternAt_z);
    RUN_TEST(test_patternAtObject);
    RUN_TEST(test_patternAtObject_patternTransform);
    RUN_TEST(test_patternAtObject_patternTransformBoth);
    return UNITY_END();
}