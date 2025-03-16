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

void test_rayShapeIntersection() {
    Material mat = material_createMaterial(tuple_createColor(1, 0, 0), 0.1f, 0.9f, 0.9f, 200.0f);
    Ray ray = ray_createRay(tuple_createPoint(0, 0, -5), tuple_createVector(0, 0, 1));
    Shape sphere = shape_createDefaultShape(0, Sphere); 
    sphere.material = mat;

    Intersection intersections[2];
    ray_rayShapeIntersect(ray, sphere, intersections);

    TEST_ASSERT_EQUAL_INT(2, sizeof(intersections)/sizeof(intersections[0]));
    TEST_ASSERT_EQUAL_FLOAT(4.0f, intersections[0].t);
    TEST_ASSERT_EQUAL_FLOAT(6.0f, intersections[1].t);
    TEST_ASSERT_EQUAL_INT(0, intersections[0].object.instanceID);
    TEST_ASSERT_EQUAL_INT(0, intersections[1].object.instanceID);

}

void test_rayShapeIntersection_tangent() {
    Material mat = material_createMaterial(tuple_createColor(1, 0, 0),0.1f, 0.9f, 0.9f, 200.0f);
    Ray ray = ray_createRay(tuple_createPoint(0, 1, -5), tuple_createVector(0, 0, 1));
    Shape sphere = shape_createDefaultShape(0, Sphere); 
    sphere.material = mat;

    Intersection intersections[2];
    ray_rayShapeIntersect(ray, sphere, intersections);

    TEST_ASSERT_EQUAL_INT(2, sizeof(intersections)/sizeof(intersections[0]));
    TEST_ASSERT_EQUAL_FLOAT(5.0f, intersections[0].t);
    TEST_ASSERT_EQUAL_FLOAT(5.0f, intersections[1].t);
    TEST_ASSERT_EQUAL_INT(0, intersections[0].object.instanceID);
    TEST_ASSERT_EQUAL_INT(0, intersections[1].object.instanceID);
}

void test_rayShapeIntersection_Miss(){
    Material mat = material_createMaterial(tuple_createColor(1, 0, 0),0.1f, 0.9f, 0.9f, 200.0f);
    Ray ray = ray_createRay(tuple_createPoint(0, 2, -5), tuple_createVector(0, 0, 1));
    Shape sphere = shape_createDefaultShape(0, Sphere); 
    sphere.material = mat;

    Intersection intersections[2];
    ray_rayShapeIntersect(ray, sphere, intersections);

    TEST_ASSERT_EQUAL_INT(2, sizeof(intersections)/sizeof(intersections[0]));
    TEST_ASSERT_EQUAL_FLOAT(NAN, intersections[0].t);
    TEST_ASSERT_EQUAL_FLOAT(NAN, intersections[1].t);
    TEST_ASSERT_EQUAL_INT(0, intersections[0].object.instanceID);
    TEST_ASSERT_EQUAL_INT(0, intersections[1].object.instanceID);
}

void test_rayShapeIntersect_insideSphere() {
    Material mat = material_createMaterial(tuple_createColor(1, 0, 0),0.1f, 0.9f, 0.9f, 200.0f);
    Ray ray = ray_createRay(tuple_createPoint(0, 0, 0), tuple_createVector(0, 0, 1));
    Shape sphere = shape_createDefaultShape(0, Sphere); 
    sphere.material = mat;

    Intersection intersections[2];
    ray_rayShapeIntersect(ray, sphere, intersections);

    TEST_ASSERT_EQUAL_INT(2, sizeof(intersections)/sizeof(intersections[0]));
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, intersections[0].t);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, intersections[1].t);
    TEST_ASSERT_EQUAL_INT(0, intersections[0].object.instanceID);
    TEST_ASSERT_EQUAL_INT(0, intersections[1].object.instanceID);
} 

void test_rayShapeIntersect_behind() {
    Material mat = material_createMaterial(tuple_createColor(1, 0, 0),0.1f, 0.9f, 0.9f, 200.0f);
    Ray ray = ray_createRay(tuple_createPoint(0, 0, 5), tuple_createVector(0, 0, 1));
    Shape sphere = shape_createDefaultShape(0, Sphere); 
    sphere.material = mat;

    Intersection intersections[2];
    ray_rayShapeIntersect(ray, sphere, intersections);

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

void test_rayScaledShape() {
    Material mat = material_createMaterial(tuple_createColor(1, 0, 0),0.1f, 0.9f, 0.9f, 200.0f);
    Ray ray = ray_createRay(tuple_createPoint(0, 0, -5), tuple_createVector(0, 0, 1));
    Shape s = shape_createDefaultShape(0, Sphere); 
    Mat4 scale;
    mat_mat4CreateScaling(scale, 2, 2, 2);
    s.material = mat;
    mat_mat4Copy(scale, s.transform);

    Intersection xs[2];
    ray_rayShapeIntersect(ray, s, xs);

    TEST_ASSERT_EQUAL_INT(2, sizeof(xs) / sizeof(xs[0]));
    TEST_ASSERT_EQUAL_FLOAT(3.0f, xs[0].t);
    TEST_ASSERT_EQUAL_FLOAT(7.0f, xs[1].t);
}

void test_rayTranslatedShape() {
    Material mat = material_createMaterial(tuple_createColor(1, 0, 0),0.1f, 0.9f, 0.9f, 200.0f);
    Ray ray = ray_createRay(tuple_createPoint(0, 0, -5), tuple_createVector(0, 0, 1));
    Shape s = shape_createDefaultShape(0, Sphere); 
    Mat4 translation;
    mat_mat4CreateTranslation(translation, 5, 0, 0);
    s.material = mat;
    mat_mat4Copy(translation, s.transform);

    Intersection xs[2];
    ray_rayShapeIntersect(ray, s, xs);

    TEST_ASSERT_EQUAL_INT(2, sizeof(xs) / sizeof(xs[0]));
    TEST_ASSERT_EQUAL_FLOAT(NAN , xs[0].t);
    TEST_ASSERT_EQUAL_FLOAT(NAN , xs[1].t);

}

int main() {
    RUN_TEST(test_rayCreate);
    RUN_TEST(test_rayPosition);
    RUN_TEST(test_rayShapeIntersection);
    RUN_TEST(test_rayShapeIntersect_behind);
    RUN_TEST(test_rayShapeIntersect_insideSphere);
    RUN_TEST(test_rayShapeIntersection_Miss);
    RUN_TEST(test_rayShapeIntersection_tangent);
    RUN_TEST(test_rayTransform);
    RUN_TEST(test_rayScale);
    RUN_TEST(test_rayScaledShape);
    RUN_TEST(test_rayTranslatedShape);
    return UNITY_END();
}

//FIXME :: UNCOMMENT!!