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
    Material m = material_createMaterial(tuple_createColor(1, 0, 0), 0.1f, 0.9f, 0.9f, 200.0f, 0.0f);
    TEST_ASSERT_EQUAL_FLOAT(0.1f, m.ambient);
    TEST_ASSERT_EQUAL_FLOAT(0.9f, m.diffuse);
    TEST_ASSERT_EQUAL_FLOAT(0.9f, m.specular);
    TEST_ASSERT_EQUAL_FLOAT(200.0f, m.shininess);
}

void test_materialLighting_angle0() {
    Material m = material_createMaterial(tuple_createColor(1, 1, 1), 0.1f, 0.9f, 0.9f, 200.0f, 0.0f);
    Tuple position = tuple_createPoint(0, 0, 0);
    
    Tuple eyev = tuple_createVector(0, 0, -1);
    Tuple normalv = tuple_createVector(0, 0, -1);
    Pointlight light = pointlight_createPointlight(tuple_createPoint(0 , 0, -10), tuple_createColor(1, 1, 1));
    Tuple result = material_calculateLighting(m, light, position, eyev, normalv, 0, shape_createDefaultShape(0, Sphere));

    TEST_ASSERT_TRUE(tuple_tupleCompare(result, tuple_createColor(1.9f, 1.9f, 1.9f)));
}

void test_materialLighting_angle45() {

    Material m = material_createMaterial(tuple_createColor(1, 1, 1), 0.1f, 0.9f, 0.9f, 200.0f, 0.0f);
    Tuple position = tuple_createPoint(0, 0, 0);
    
    Tuple eyev = tuple_createVector(0, sqrtf(2.0f)/2.0f, -sqrtf(2.0f)/2.0f);
    Tuple normalv = tuple_createVector(0, 0, -1);
    Pointlight light = pointlight_createPointlight(tuple_createPoint(0 , 0, -10), tuple_createColor(1, 1, 1));
    Tuple result = material_calculateLighting(m, light, position, eyev, normalv, 0, shape_createDefaultShape(0, Sphere));

    TEST_ASSERT_TRUE(tuple_tupleCompare(result, tuple_createColor(1.0f, 1.0f, 1.0f)));
}

void test_materialLighting_angle0l45() {

    Material m = material_createMaterial(tuple_createColor(1, 1, 1), .1f, 0.9f, 0.9f, 200.0f, 0.0f);
    Tuple position = tuple_createPoint(0, 0, 0);
    
    Tuple eyev = tuple_createVector(0, 0, -1);
    Tuple normalv = tuple_createVector(0, 0, -1);
    Pointlight light = pointlight_createPointlight(tuple_createPoint(0 , 10, -10), tuple_createColor(1, 1, 1));
    Tuple result = material_calculateLighting(m, light, position, eyev, normalv, 0, shape_createDefaultShape(0, Sphere));

    TEST_ASSERT_TRUE(tuple_tupleCompare(result, tuple_createColor(0.7364f, 0.7364f, 0.7364f)));
}

void test_materialLighting_angleneg45l45() {

    Material m = material_createMaterial(tuple_createColor(1, 1, 1), 0.1f, 0.9f, 0.9f, 200.0f, 0.0f);
    Tuple position = tuple_createPoint(0, 0, 0);
    
    Tuple eyev = tuple_createVector(0, -sqrtf(2.0f)/2.0f, -sqrt(2.0f)/2.0f);
    Tuple normalv = tuple_createVector(0, 0, -1);
    Pointlight light = pointlight_createPointlight(tuple_createPoint(0 , 10, -10), tuple_createColor(1, 1, 1));
    Tuple result = material_calculateLighting(m, light, position, eyev, normalv, 0,shape_createDefaultShape(0, Sphere));

    TEST_ASSERT_TRUE(tuple_tupleCompare(result, tuple_createColor(1.6364f, 1.6364f, 1.6364f)));
}

void test_materialLighting_lightoccluded() {

    Material m = material_createMaterial(tuple_createColor(1, 1, 1), 0.1f, 0.9f, 0.9f, 200.0f, 0.0f);
    Tuple position = tuple_createPoint(0, 0, 0);
    
    Tuple eyev = tuple_createVector(0, 0, -1);
    Tuple normalv = tuple_createVector(0, 0, -1);
    Pointlight light = pointlight_createPointlight(tuple_createPoint(0 , 0, 10), tuple_createColor(1, 1, 1));
    Tuple result = material_calculateLighting(m, light, position, eyev, normalv, 0,shape_createDefaultShape(0, Sphere));

    TEST_ASSERT_TRUE(tuple_tupleCompare(result, tuple_createColor(0.1f, 0.1f, 0.1f)));
}

void test_materialLighting_shadow() {
    Material m = material_createMaterial(tuple_createColor(1, 1, 1), 0.1f, 0.9f, 0.9f, 200.0f, 0.0f);
    Tuple position = tuple_createPoint(0, 0, 0);
    
    Tuple eyev = tuple_createVector(0, 0, -1);
    Tuple normalv = tuple_createVector(0, 0, -1);
    Pointlight light = pointlight_createPointlight(tuple_createPoint(0 , 0, -10), tuple_createColor(1, 1, 1));
    Tuple result = material_calculateLighting(m, light, position, eyev, normalv, 1,shape_createDefaultShape(0, Sphere));

    TEST_ASSERT_TRUE(tuple_tupleCompare(result, tuple_createColor(0.1f, 0.1f, 0.1f)));
}

void test_materialLighting_pattern() {
    Material mat;
    mat.pattern = pattern_createPattern(COLOR_WHITE, COLOR_BLACK, Stripe);
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

void test_defaultMaterialReflectiveAttrib() {
    Material mat = material_createMaterial(COLOR_BLACK, 0.1f, 0.9f, 0.9f, 200.0f, 0.0f);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, mat.reflective);
}

void test_preComputeReflectionVector() {
    Shape plane = shape_createDefaultShape(0, Plane);
    Ray r = ray_createRay(tuple_createPoint(0, 1, -1), tuple_createVector(0, -sqrtf(2.0f)/2.0f, sqrtf(2.0f)/2.0f));
    Intersection i = intersection_intersectionCreateIntersection(plane, sqrtf(2.0f));
    Computations comps = intersection_prepareComputations(i, r);
    TEST_ASSERT_TRUE(tuple_tupleCompare(comps.reflectv, tuple_createVector(0, sqrtf(2.0f)/2.0f, sqrtf(2.0f)/2.0f)));
}

void test_strikeNonreflective() {
    World w = world_createDefault();
    Ray r = ray_createRay(tuple_createPoint(0, 0, 0), tuple_createVector(0, 0, 1));
    w.objects[0].material.ambient = 1;
    Intersection i = intersection_intersectionCreateIntersection(w.objects[0], 1);
    Computations comps = intersection_prepareComputations(i, r);
    Tuple color = world_reflectedColor(w, comps, 1);
    TEST_ASSERT_TRUE(tuple_tupleCompare(color, COLOR_BLACK));
}

void test_strikeReflectiveSurface() {
    World w = world_createDefault();
    w.objectCount = 3;
    w.objects = realloc(w.objects, 3*sizeof(Shape));
    Shape plane = shape_createDefaultShape(2, Plane);
    plane.material.reflective = 0.5f;
    Mat4 transform;
    mat_mat4CreateTranslation(transform, 0, -1, 0);
    mat_mat4Copy(transform, plane.transform);
    w.objects[2] = plane;

    Ray r = ray_createRay(tuple_createPoint(0, 0, -3), tuple_createVector(0, -sqrtf(2.0f)/2.0f, sqrtf(2.0f)/2.0f));
    Intersection i = intersection_intersectionCreateIntersection(w.objects[2], sqrtf(2.0f));
    Computations comps = intersection_prepareComputations(i, r);
    Tuple color = world_reflectedColor(w, comps, 1);
    
    TEST_ASSERT_TRUE(tuple_tupleCompare(color, tuple_createColor(0.1920f, 0.2400f, 0.14404f)));

}

void test_shadeHitReflective(){
    World w = world_createDefault();
    w.objectCount = 3;
    w.objects = realloc(w.objects, 3*sizeof(Shape));
    Shape plane = shape_createDefaultShape(2, Plane);
    plane.material.reflective = 0.5f;
    Mat4 transform;
    mat_mat4CreateTranslation(transform, 0, -1, 0);
    mat_mat4Copy(transform, plane.transform);
    w.objects[2] = plane;

    Ray r = ray_createRay(tuple_createPoint(0, 0, -3), tuple_createVector(0, -sqrtf(2.0f)/2.0f, sqrtf(2.0f)/2.0f));
    Intersection i = intersection_intersectionCreateIntersection(w.objects[2], sqrtf(2.0f));
    Computations comps = intersection_prepareComputations(i, r);
    Tuple color = world_shadeHit(w, comps, 1);
    
    TEST_ASSERT_TRUE(tuple_tupleCompare(color, tuple_createColor(0.87848f, 0.92649f, 0.83048f)));
}

void test_avoidInfiniteRecursion() {
    World w = world_createDefault();
    Mat4 p1Trans;
    mat_mat4CreateTranslation(p1Trans, 0, -1, 0);
    Shape pl = shape_createDefaultShape(0, Plane);
    pl.material.reflective = 1;
    mat_mat4Copy(p1Trans, pl.transform);


    Mat4 p2Trans;
    mat_mat4CreateTranslation(p2Trans, 0, 1, 0);
    Shape p2 = shape_createDefaultShape(1, Plane);
    p2.material.reflective = 1;
    mat_mat4Copy(p2Trans, p2.transform);

    w.objects[0] = pl;
    w.objects[1] = p2;

    Ray r = ray_createRay(tuple_createPoint(0, 0, 0), tuple_createVector(0, 1, 0));
    world_worldColorAt(w, r, 4);
    TEST_ASSERT_TRUE(1);
}

void test_recursiveReflectionReturnsAtLimit() {
    World w = world_createDefault();
    Mat4 p1Trans;
    mat_mat4CreateTranslation(p1Trans, 0, -1, 0);
    Shape pl = shape_createDefaultShape(0, Plane);
    pl.material.reflective = 0.5f;
    pl.material.ambient = 0;
    mat_mat4Copy(p1Trans, pl.transform);


    Mat4 p2Trans;
    mat_mat4CreateTranslation(p2Trans, 0, 1, 0);
    Shape p2 = shape_createDefaultShape(1, Plane);
    p2.material.reflective = 0.5;
    p2.material.ambient = 0;
    mat_mat4Copy(p2Trans, p2.transform);

    w.objects[0] = pl;
    w.objects[1] = p2;

    Ray r = ray_createRay(tuple_createPoint(0, 0, 0), tuple_createVector(0, 1, 0));
    Tuple color = world_worldColorAt(w, r, 0);
    TEST_ASSERT_TRUE(tuple_tupleCompare(color, COLOR_BLACK));

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
    RUN_TEST(test_defaultMaterialReflectiveAttrib);
    RUN_TEST(test_preComputeReflectionVector);
    RUN_TEST(test_strikeNonreflective);
    RUN_TEST(test_strikeReflectiveSurface);
    RUN_TEST(test_shadeHitReflective);
    RUN_TEST(test_avoidInfiniteRecursion);
    RUN_TEST(test_recursiveReflectionReturnsAtLimit);
    return UNITY_END();
}