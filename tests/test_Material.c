#include "Pointlight.h"
#include "Tuple.h"
#include "unity.h"
#include "Material.h"
#include "World.h"
#include "Patterns.h"
#include "Shape.h"
void setUp() {

}

void tearDown() {

}

void test_createMaterial() {
    Material m = material_createMaterial(tuple_createColor(1, 0, 0), 0.1f, 0.9f, 0.9f, 200.0f);
    TEST_ASSERT_EQUAL_FLOAT(0.1f, m.ambient);
    TEST_ASSERT_EQUAL_FLOAT(0.9f, m.diffuse);
    TEST_ASSERT_EQUAL_FLOAT(0.9f, m.specular);
    TEST_ASSERT_EQUAL_FLOAT(200.0f, m.shininess);
}

void test_materialLighting_angle0() {
    Material m = material_createMaterial(tuple_createColor(1, 1, 1), 0.1f, 0.9f, 0.9f, 200.0f);
    Tuple position = tuple_createPoint(0, 0, 0);
    
    Tuple eyev = tuple_createVector(0, 0, -1);
    Tuple normalv = tuple_createVector(0, 0, -1);
    Pointlight light = pointlight_createPointlight(tuple_createPoint(0 , 0, -10), tuple_createColor(1, 1, 1));
    Tuple result = material_calculateLighting(m, light, position, eyev, normalv, 0, shape_createDefaultShape(0, Sphere));

    TEST_ASSERT_TRUE(tuple_tupleCompare(result, tuple_createColor(1.9f, 1.9f, 1.9f)));
}

void test_materialLighting_angle45() {

    Material m = material_createMaterial(tuple_createColor(1, 1, 1), 0.1f, 0.9f, 0.9f, 200.0f);
    Tuple position = tuple_createPoint(0, 0, 0);
    
    Tuple eyev = tuple_createVector(0, sqrtf(2.0f)/2.0f, -sqrtf(2.0f)/2.0f);
    Tuple normalv = tuple_createVector(0, 0, -1);
    Pointlight light = pointlight_createPointlight(tuple_createPoint(0 , 0, -10), tuple_createColor(1, 1, 1));
    Tuple result = material_calculateLighting(m, light, position, eyev, normalv, 0, shape_createDefaultShape(0, Sphere));

    TEST_ASSERT_TRUE(tuple_tupleCompare(result, tuple_createColor(1.0f, 1.0f, 1.0f)));
}

void test_materialLighting_angle0l45() {

    Material m = material_createMaterial(tuple_createColor(1, 1, 1), .1f, 0.9f, 0.9f, 200.0f);
    Tuple position = tuple_createPoint(0, 0, 0);
    
    Tuple eyev = tuple_createVector(0, 0, -1);
    Tuple normalv = tuple_createVector(0, 0, -1);
    Pointlight light = pointlight_createPointlight(tuple_createPoint(0 , 10, -10), tuple_createColor(1, 1, 1));
    Tuple result = material_calculateLighting(m, light, position, eyev, normalv, 0, shape_createDefaultShape(0, Sphere));

    TEST_ASSERT_TRUE(tuple_tupleCompare(result, tuple_createColor(0.7364f, 0.7364f, 0.7364f)));
}

void test_materialLighting_angleneg45l45() {

    Material m = material_createMaterial(tuple_createColor(1, 1, 1), 0.1f, 0.9f, 0.9f, 200.0f);
    Tuple position = tuple_createPoint(0, 0, 0);
    
    Tuple eyev = tuple_createVector(0, -sqrtf(2.0f)/2.0f, -sqrt(2.0f)/2.0f);
    Tuple normalv = tuple_createVector(0, 0, -1);
    Pointlight light = pointlight_createPointlight(tuple_createPoint(0 , 10, -10), tuple_createColor(1, 1, 1));
    Tuple result = material_calculateLighting(m, light, position, eyev, normalv, 0,shape_createDefaultShape(0, Sphere));

    TEST_ASSERT_TRUE(tuple_tupleCompare(result, tuple_createColor(1.6364f, 1.6364f, 1.6364f)));
}

void test_materialLighting_lightoccluded() {

    Material m = material_createMaterial(tuple_createColor(1, 1, 1), 0.1f, 0.9f, 0.9f, 200.0f);
    Tuple position = tuple_createPoint(0, 0, 0);
    
    Tuple eyev = tuple_createVector(0, 0, -1);
    Tuple normalv = tuple_createVector(0, 0, -1);
    Pointlight light = pointlight_createPointlight(tuple_createPoint(0 , 0, 10), tuple_createColor(1, 1, 1));
    Tuple result = material_calculateLighting(m, light, position, eyev, normalv, 0,shape_createDefaultShape(0, Sphere));

    TEST_ASSERT_TRUE(tuple_tupleCompare(result, tuple_createColor(0.1f, 0.1f, 0.1f)));
}

void test_materialLighting_shadow() {
    Material m = material_createMaterial(tuple_createColor(1, 1, 1), 0.1f, 0.9f, 0.9f, 200.0f);
    Tuple position = tuple_createPoint(0, 0, 0);
    
    Tuple eyev = tuple_createVector(0, 0, -1);
    Tuple normalv = tuple_createVector(0, 0, -1);
    Pointlight light = pointlight_createPointlight(tuple_createPoint(0 , 0, -10), tuple_createColor(1, 1, 1));
    Tuple result = material_calculateLighting(m, light, position, eyev, normalv, 1,shape_createDefaultShape(0, Sphere));

    TEST_ASSERT_TRUE(tuple_tupleCompare(result, tuple_createColor(0.1f, 0.1f, 0.1f)));
}

void test_materialLighting_pattern() {
    Material mat;
    mat.pattern = pattern_stripe(COLOR_WHITE, COLOR_BLACK);
    mat.ambient = 1;
    mat.diffuse = 0;
    mat.specular = 0;
    mat.shininess = 0;
    Tuple eyev = tuple_createVector(0, 0, -1);
    Tuple normalv = tuple_createVector(0, 0, -1);
    
    Pointlight light = pointlight_createPointlight(tuple_createPoint(0, 0, -10), tuple_createColor(1, 1, 1));

    Tuple c1 = material_calculateLighting(mat, light, tuple_createPoint(0.9f, 0, 0), eyev, normalv, 0,shape_createDefaultShape(0, Sphere));
    Tuple c2 = material_calculateLighting(mat, light, tuple_createPoint(1.1f, 0, 0), eyev, normalv, 0,shape_createDefaultShape(0, Sphere));

    TEST_ASSERT_TRUE(tuple_tupleCompare(c1, tuple_createColor(1,1,1)));
    TEST_ASSERT_TRUE(tuple_tupleCompare(c2, tuple_createColor(0,0,0)));
}
int main() {
    RUN_TEST(test_createMaterial);
    RUN_TEST(test_materialLighting_angle0);
    RUN_TEST(test_materialLighting_angle45);
    RUN_TEST(test_materialLighting_angle0l45);
    RUN_TEST(test_materialLighting_angleneg45l45);
    RUN_TEST(test_materialLighting_lightoccluded);
    RUN_TEST(test_materialLighting_shadow);
    RUN_TEST(test_materialLighting_pattern);
    return UNITY_END();
}