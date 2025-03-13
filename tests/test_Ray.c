#include "Intersection.h"
#include "unity.h"
#include "Ray.h"

void setUp() {

}

void tearDown(){

}


void test_rayCreate() {
    Tuple origin = tuple_createPoint(1, 2, 3);
    Tuple direction = tuple_createVector(4, 5, 6);

    Ray ray = ray_createRay(origin, direction);
    
    TEST_ASSERT_TRUE(tuple_tupleCompare(origin, ray.origin));
    TEST_ASSERT_TRUE(tuple_tupleCompare(direction, ray.direction));
}

void test_rayPosition() {
    Ray ray = ray_createRay(tuple_createPoint(2,3,4), tuple_createVector(1,0,0));

    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createPoint(2, 3, 4), ray_rayPosition(ray, 0.0f)));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createPoint(3, 3, 4), ray_rayPosition(ray, 1.0f)));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createPoint(1, 3, 4), ray_rayPosition(ray, -1.0f)));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createPoint(4.5, 3, 4), ray_rayPosition(ray, 2.5f)));
}

void test_raySphereIntersection() {
    Material mat = material_createMaterial(tuple_createColor(1, 0, 0), 0.1f, 0.9f, 0.9f, 200.0f);
    Ray ray = ray_createRay(tuple_createPoint(0, 0, -5), tuple_createVector(0, 0, 1));
    Sphere sphere = sphere_createSphere(tuple_createPoint(0, 0, 0), 1.0f, 0, NULL, mat);

    Intersection intersections[2];
    ray_raySphereIntersect(ray, sphere, intersections);

    TEST_ASSERT_EQUAL_INT(2, sizeof(intersections)/sizeof(intersections[0]));
    TEST_ASSERT_EQUAL_FLOAT(4.0f, intersections[0].t);
    TEST_ASSERT_EQUAL_FLOAT(6.0f, intersections[1].t);
    TEST_ASSERT_EQUAL_INT(0, intersections[0].object.instanceID);
    TEST_ASSERT_EQUAL_INT(0, intersections[1].object.instanceID);

}

void test_raySphereIntersection_tangent() {
    Material mat = material_createMaterial(tuple_createColor(1, 0, 0),0.1f, 0.9f, 0.9f, 200.0f);
    Ray ray = ray_createRay(tuple_createPoint(0, 1, -5), tuple_createVector(0, 0, 1));
    Sphere sphere = sphere_createSphere(tuple_createPoint(0,0,0), 1.0f, 0, NULL, mat);

    Intersection intersections[2];
    ray_raySphereIntersect(ray, sphere, intersections);

    TEST_ASSERT_EQUAL_INT(2, sizeof(intersections)/sizeof(intersections[0]));
    TEST_ASSERT_EQUAL_FLOAT(5.0f, intersections[0].t);
    TEST_ASSERT_EQUAL_FLOAT(5.0f, intersections[1].t);
    TEST_ASSERT_EQUAL_INT(0, intersections[0].object.instanceID);
    TEST_ASSERT_EQUAL_INT(0, intersections[1].object.instanceID);
}

void test_raySphereIntersection_Miss(){
    Material mat = material_createMaterial(tuple_createColor(1, 0, 0),0.1f, 0.9f, 0.9f, 200.0f);
    Ray ray = ray_createRay(tuple_createPoint(0, 2, -5), tuple_createVector(0, 0, 1));
    Sphere sphere = sphere_createSphere(tuple_createPoint(0,0,0), 1.0f, 0, NULL, mat);

    Intersection intersections[2];
    ray_raySphereIntersect(ray, sphere, intersections);

    TEST_ASSERT_EQUAL_INT(2, sizeof(intersections)/sizeof(intersections[0]));
    TEST_ASSERT_EQUAL_FLOAT(NAN, intersections[0].t);
    TEST_ASSERT_EQUAL_FLOAT(NAN, intersections[1].t);
    TEST_ASSERT_EQUAL_INT(0, intersections[0].object.instanceID);
    TEST_ASSERT_EQUAL_INT(0, intersections[1].object.instanceID);
}

void test_raySphereIntersect_insideSphere() {
    Material mat = material_createMaterial(tuple_createColor(1, 0, 0),0.1f, 0.9f, 0.9f, 200.0f);
    Ray ray = ray_createRay(tuple_createPoint(0, 0, 0), tuple_createVector(0, 0, 1));
    Sphere sphere = sphere_createSphere(tuple_createPoint(0,0,0), 1.0f, 0, NULL, mat);

    Intersection intersections[2];
    ray_raySphereIntersect(ray, sphere, intersections);

    TEST_ASSERT_EQUAL_INT(2, sizeof(intersections)/sizeof(intersections[0]));
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, intersections[0].t);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, intersections[1].t);
    TEST_ASSERT_EQUAL_INT(0, intersections[0].object.instanceID);
    TEST_ASSERT_EQUAL_INT(0, intersections[1].object.instanceID);
} 

void test_raySphereIntersect_behind() {
    Material mat = material_createMaterial(tuple_createColor(1, 0, 0),0.1f, 0.9f, 0.9f, 200.0f);
    Ray ray = ray_createRay(tuple_createPoint(0, 0, 5), tuple_createVector(0, 0, 1));
    Sphere sphere = sphere_createSphere(tuple_createPoint(0,0,0), 1.0f, 0, NULL, mat);

    Intersection intersections[2];
    ray_raySphereIntersect(ray, sphere, intersections);

    TEST_ASSERT_EQUAL_INT(2, sizeof(intersections)/sizeof(intersections[0]));
    TEST_ASSERT_EQUAL_FLOAT(-6.0f, intersections[0].t);
    TEST_ASSERT_EQUAL_FLOAT(-4.0f, intersections[1].t);
    TEST_ASSERT_EQUAL_INT(0, intersections[0].object.instanceID);
    TEST_ASSERT_EQUAL_INT(0, intersections[1].object.instanceID);
}

void test_rayTransform() {
    Ray ray = ray_createRay(tuple_createPoint(1, 2, 3), tuple_createVector(0, 1, 0));
    Mat4 translationMat;
    mat_mat4CreateTranslation(translationMat, 3, 4, 5);
    Ray transformedRay = ray_transformRay(ray, translationMat);

    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createPoint(4,6, 8), transformedRay.origin));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0,1, 0), transformedRay.direction));
}

void test_rayScale() {
    Ray ray = ray_createRay(tuple_createPoint(1, 2, 3), tuple_createVector(0, 1, 0));
    Mat4 translationMat;
    mat_mat4CreateScaling(translationMat, 2, 3, 4);
    Ray transformedRay = ray_transformRay(ray, translationMat);

    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createPoint(2,6, 12), transformedRay.origin));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0,3, 0), transformedRay.direction));
}

void test_rayScaledSphere() {
    Material mat = material_createMaterial(tuple_createColor(1, 0, 0),0.1f, 0.9f, 0.9f, 200.0f);
    Ray ray = ray_createRay(tuple_createPoint(0, 0, -5), tuple_createVector(0, 0, 1));
    Sphere s = sphere_createSphere(tuple_createPoint(0, 0, 0), 1, 0, NULL, mat);
    Mat4 scale;
    mat_mat4CreateScaling(scale, 2, 2, 2);
    sphere_setTransform(&s, scale);

    Intersection xs[2];
    ray_raySphereIntersect(ray, s, xs);

    TEST_ASSERT_EQUAL_INT(2, sizeof(xs) / sizeof(xs[0]));
    TEST_ASSERT_EQUAL_FLOAT(3.0f, xs[0].t);
    TEST_ASSERT_EQUAL_FLOAT(7.0f, xs[1].t);
}

void test_rayTranslatedSphere() {
    Material mat = material_createMaterial(tuple_createColor(1, 0, 0),0.1f, 0.9f, 0.9f, 200.0f);
    Ray ray = ray_createRay(tuple_createPoint(0, 0, -5), tuple_createVector(0, 0, 1));
    Sphere s = sphere_createSphere(tuple_createPoint(0, 0, 0), 1, 0, NULL, mat);
    Mat4 translation;
    mat_mat4CreateTranslation(translation, 5, 0, 0);
    sphere_setTransform(&s, translation);

    Intersection xs[2];
    ray_raySphereIntersect(ray, s, xs);

    TEST_ASSERT_EQUAL_INT(2, sizeof(xs) / sizeof(xs[0]));
    TEST_ASSERT_EQUAL_FLOAT(NAN , xs[0].t);
    TEST_ASSERT_EQUAL_FLOAT(NAN , xs[1].t);

}
int main() {
    RUN_TEST(test_rayCreate);
    RUN_TEST(test_rayPosition);
    RUN_TEST(test_raySphereIntersection);
    RUN_TEST(test_raySphereIntersect_behind);
    RUN_TEST(test_raySphereIntersect_insideSphere);
    RUN_TEST(test_raySphereIntersection_Miss);
    RUN_TEST(test_raySphereIntersection_tangent);
    RUN_TEST(test_rayTransform);
    RUN_TEST(test_rayScale);
    RUN_TEST(test_rayScaledSphere);
    RUN_TEST(test_rayTranslatedSphere);
    return UNITY_END();
}