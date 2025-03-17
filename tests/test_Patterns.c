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

void test_patternDefault() {
    Mat4 expected = MAT4_IDENTITY;
    Pattern p = pattern_createPattern(COLOR_BLACK, COLOR_WHITE, Stripe);
    TEST_ASSERT_TRUE(mat_mat4Compare(expected, p.transform));
}

void test_patternTransformSet() {
    Mat4 expected; 
    mat_mat4CreateTranslation(expected, 1, 2, 3);
    Pattern p = pattern_createPattern(COLOR_BLACK, COLOR_WHITE, Stripe);
    mat_mat4Copy(expected, p.transform);
    TEST_ASSERT_TRUE(mat_mat4Compare(expected, p.transform));
}

void test_testPatternObjTrans() {
    Mat4 objTrans;
    mat_mat4CreateScaling(objTrans, 2, 2, 2);
    Shape shape = shape_createDefaultShape(0, Sphere);
    mat_mat4Copy(objTrans, shape.transform);

    Pattern pattern = pattern_createPattern(COLOR_WHITE, COLOR_BLACK, testPattern);

    Tuple c = pattern_patternAtObject(pattern, shape, tuple_createPoint(2, 3, 4));

    TEST_ASSERT_TRUE(tuple_tupleCompare(c, tuple_createColor(1, 1.5f, 2)));
}

void test_testPatternPatTrans() {
    Mat4 objTrans;
    mat_mat4CreateScaling(objTrans, 2, 2, 2);
    Shape shape = shape_createDefaultShape(0, Sphere);

    Pattern pattern = pattern_createPattern(COLOR_WHITE, COLOR_BLACK, testPattern);
    mat_mat4Copy(objTrans, pattern.transform);

    Tuple c = pattern_patternAtObject(pattern, shape, tuple_createPoint(2, 3, 4));
    TEST_ASSERT_TRUE(tuple_tupleCompare(c, tuple_createColor(1, 1.5, 2)));
}

void test_testPatternBoth() {
    Mat4 objTrans;
    mat_mat4CreateScaling(objTrans, 2, 2, 2);
    Shape shape = shape_createDefaultShape(0, Sphere);
    mat_mat4Copy(objTrans, shape.transform);

    Mat4 patternTrans;
    mat_mat4CreateTranslation(patternTrans, 0.5f, 1, 1.5f);
    Pattern pattern = pattern_createPattern(COLOR_WHITE, COLOR_BLACK, testPattern);
    mat_mat4Copy(patternTrans, pattern.transform);

    Tuple c = pattern_patternAtObject(pattern, shape, tuple_createPoint(2.5f, 3, 3.5f));
    TEST_ASSERT_TRUE(tuple_tupleCompare(c, tuple_createColor(0.75f, 0.5f, 0.25f)));
}

void test_patternGradient() {
    Pattern p = pattern_createPattern(COLOR_WHITE, COLOR_BLACK, Gradient);
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_patternAt(p, tuple_createPoint(0,0,0)), COLOR_WHITE));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_patternAt(p, tuple_createPoint(0.25f,0,0)), tuple_createColor(0.75f, 0.75f, 0.75f)));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_patternAt(p, tuple_createPoint(0.50f,0,0)), tuple_createColor(0.5f, 0.5f, 0.5f)));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_patternAt(p, tuple_createPoint(0.75f,0,0)), tuple_createColor(0.25f, 0.25f, 0.25f)));
}

void test_patternRing() {
    Pattern p = pattern_createPattern(COLOR_WHITE, COLOR_BLACK, Ring);
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_patternAt(p, tuple_createPoint(0,0,0)), COLOR_WHITE));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_patternAt(p, tuple_createPoint(1,0,0)), COLOR_BLACK));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_patternAt(p, tuple_createPoint(0,0,1)), COLOR_BLACK));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_patternAt(p, tuple_createPoint(0.708f,0,0.708f)), COLOR_BLACK));
}

void test_patternCheckers_x() {
    Pattern p = pattern_createPattern(COLOR_WHITE, COLOR_BLACK, Checker);
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_patternAt(p, tuple_createPoint(0,0,0)), COLOR_WHITE));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_patternAt(p, tuple_createPoint(0.99f,0,0)), COLOR_WHITE));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_patternAt(p, tuple_createPoint(1.01f,0,0)), COLOR_BLACK));
}

void test_patternCheckers_y() {
    Pattern p = pattern_createPattern(COLOR_WHITE, COLOR_BLACK, Checker);
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_patternAt(p, tuple_createPoint(0,0,0)), COLOR_WHITE));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_patternAt(p, tuple_createPoint(0,0.99f,0)), COLOR_WHITE));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_patternAt(p, tuple_createPoint(0,1.01f,0)), COLOR_BLACK));
}

void test_patternCheckers_z() {
    Pattern p = pattern_createPattern(COLOR_WHITE, COLOR_BLACK, Checker);
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_patternAt(p, tuple_createPoint(0,0,0)), COLOR_WHITE));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_patternAt(p, tuple_createPoint(0,0,0.99f)), COLOR_WHITE));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_patternAt(p, tuple_createPoint(0,0,1.01f)), COLOR_BLACK));
}

int main() {
    RUN_TEST(test_patternStripe);
    RUN_TEST(test_patternAt_x);
    RUN_TEST(test_patternAt_y);
    RUN_TEST(test_patternAt_z);
    RUN_TEST(test_patternAtObject);
    RUN_TEST(test_patternAtObject_patternTransform);
    RUN_TEST(test_patternAtObject_patternTransformBoth);
    RUN_TEST(test_patternDefault);
    RUN_TEST(test_patternTransformSet);
    RUN_TEST(test_testPatternBoth);
    RUN_TEST(test_testPatternObjTrans);
    RUN_TEST(test_testPatternPatTrans);
    RUN_TEST(test_patternGradient);
    RUN_TEST(test_patternRing);
    RUN_TEST(test_patternCheckers_x);
    RUN_TEST(test_patternCheckers_y);
    RUN_TEST(test_patternCheckers_z);
    return UNITY_END();
}