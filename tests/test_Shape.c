#include "unity.h"
#include "Ray.h"
#include "Shape.h"

void setUp() {

}

void tearDown() {

}

// void test_createSphere() {
//     Material mat = material_createMaterial(tuple_createColor(1, 0, 0), 0.1f, 0.9f, 0.9f, 200.0f);
//     Sphere newSphere1 = sphere_createSphere(tuple_createPoint(0, 1, 0), 1, 0, NULL, mat);

//    TEST_ASSERT_TRUE(tuple_tupleCompare(newSphere1.origin, tuple_createPoint(0, 1, 0))); 
//    TEST_ASSERT_EQUAL(1, newSphere1.radius);
//    TEST_ASSERT_EQUAL(0, newSphere1.instanceID);
// }

// void test_sphereDefaultTransform() {
//     Material mat = material_createMaterial(tuple_createColor(1, 0, 0), 0.1f, 0.9f, 0.9f, 200.0f);
//     Mat4 expected = MAT4_IDENTITY;
//     Sphere newSphere = sphere_createSphere(tuple_createPoint(0, 0, 0), 1, 0, NULL, mat);
//     TEST_ASSERT_TRUE(mat_mat4Compare(expected, newSphere.transform));
// }

// void test_sphereSetTransform(){
//     Material mat = material_createMaterial(tuple_createColor(1, 0, 0), 0.1f, 0.9f, 0.9f, 200.0f);
//     Mat4 expected;
//     mat_mat4CreateTranslation(expected, 2, 3, 4);
//     Sphere newSphere = sphere_createSphere(tuple_createPoint(0, 0, 0), 1, 0, NULL,mat);
//     sphere_setTransform(&newSphere, expected);
//     TEST_ASSERT_TRUE(mat_mat4Compare(expected, newSphere.transform));
// }

// void test_sphereCreateTransform() {
//     Material mat = material_createMaterial(tuple_createColor(1, 0, 0), 0.1f, 0.9f, 0.9f, 200.0f);
//     Mat4 expected;
//     mat_mat4CreateTranslation(expected, 2, 3, 4);
//     Sphere newSphere = sphere_createSphere(tuple_createPoint(0, 0, 0), 1, 0, expected, mat);
//     TEST_ASSERT_TRUE(mat_mat4Compare(expected, newSphere.transform));
// }

// void test_sphereNormalAt() {
//     Material mat = material_createMaterial(tuple_createColor(1, 0, 0), 0.1f, 0.9f, 0.9f, 200.0f);
//     Sphere s = sphere_createSphere(tuple_createPoint(0, 0, 0), 1, 0, NULL, mat);
//     Tuple nx = sphere_normalAt(s, tuple_createPoint(1, 0, 0));
//     Tuple ny = sphere_normalAt(s, tuple_createPoint(0, 1, 0));
//     Tuple nz = sphere_normalAt(s, tuple_createPoint(0, 0, 1));
//     Tuple nn = sphere_normalAt(s, tuple_createPoint(sqrtf(3)/3.0,  sqrtf(3)/3.0,  sqrtf(3)/3.0));

//     TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(1, 0, 0), nx));
//     TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0, 1, 0), ny));
//     TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0, 0, 1), nz));
//     TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(sqrtf(3)/3.0,  sqrtf(3)/3.0,  sqrtf(3)/3.0), nn));
//     TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(sqrtf(3)/3.0,  sqrtf(3)/3.0,  sqrtf(3)/3.0), tuple_vectorNormalize(nn)));
// }
// void test_sphereNormalAtTransformed() {
//     Material mat = material_createMaterial(tuple_createColor(1, 0, 0), 0.1f, 0.9f, 0.9f, 200.0f);
//     Sphere s = sphere_createSphere(tuple_createPoint(0,0,0), 1, 0, NULL, mat);
//     Mat4 translation;
//     mat_mat4CreateTranslation(translation, 0, 1, 0);
//     sphere_setTransform(&s, translation);

//     Tuple n = sphere_normalAt(s, tuple_createPoint(0, 1.70711f, -0.70711f));

//     TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0, 0.70711f, -0.70711f), n));

//     Mat4 scale;
//     Mat4 rotation;
//     Mat4 composite;
//     mat_mat4CreateScaling(scale, 1, 0.5f, 1);
//     mat_mat4CreateRotation_z(rotation, M_PI/5.0f);
//     mat_mat4MultiplyMat4(scale, rotation, composite);

//     sphere_setTransform(&s, composite);

//     Tuple n2 = sphere_normalAt(s, tuple_createPoint(0, sqrtf(2.0f)/2.0f, -sqrtf(2.0f)/2.0f));

//     TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0, 0.97014f, -0.24254), n2));
// }

// void test_sphereMaterial() {
//     Material mat = material_createMaterial(tuple_createColor(1, 0, 0), 1.0f, 10.0f, 5.0f, 100.0f);
//     Sphere sp = sphere_createSphere(tuple_createPoint(0, 0, 0), 1, 0, NULL, mat);

//     TEST_ASSERT_EQUAL_FLOAT(1.0f, sp.material.ambient);
//     TEST_ASSERT_EQUAL_FLOAT(10.0f, sp.material.diffuse);
//     TEST_ASSERT_EQUAL_FLOAT(5.0f, sp.material.specular);
//     TEST_ASSERT_EQUAL_FLOAT(100.0f, sp.material.shininess);
// }

void test_DefaultShapeTransform() {
    Mat4 identity = MAT4_IDENTITY;
    Shape s = shape_createDefaultShape(0, Sphere);
    TEST_ASSERT_TRUE(mat_mat4Compare(s.transform, identity));
}

void test_DefaultShapeAssignTransform() {
    Mat4 translation; 
    mat_mat4CreateTranslation(translation,2, 3, 4);

    Shape s = shape_createDefaultShape(0, Sphere);
    mat_mat4Copy(translation, s.transform);
    TEST_ASSERT_TRUE(mat_mat4Compare(s.transform, translation));
}

void test_DefaultShapeMaterial() {
    Material testmat = material_createMaterial(tuple_createColor(1, 1, 1), 0.1f, 0.9f, 0.9f, 200.0f);

    Shape s = shape_createDefaultShape(0, Sphere);

    TEST_ASSERT_TRUE(tuple_tupleCompare(s.material.surfaceColor, testmat.surfaceColor));
    TEST_ASSERT_EQUAL_FLOAT(s.material.ambient, 0.1f);
    TEST_ASSERT_EQUAL_FLOAT(s.material.diffuse, 0.9f);
    TEST_ASSERT_EQUAL_FLOAT(s.material.specular, 0.9f);
    TEST_ASSERT_EQUAL_FLOAT(s.material.shininess, 200.0f);
}

void test_DefaultShapeAssignMaterial() {

    Material testmat = material_createMaterial(tuple_createColor(1, 1, 1), 1, 1, 1, 1);

    Shape s = shape_createDefaultShape(0, Sphere);
    s = shape_assignMaterial(s, testmat);
    TEST_ASSERT_EQUAL_FLOAT(s.material.ambient, 1);
    TEST_ASSERT_EQUAL_FLOAT(s.material.diffuse, 1);
    TEST_ASSERT_EQUAL_FLOAT(s.material.specular, 1);
    TEST_ASSERT_EQUAL_FLOAT(s.material.shininess, 1);
}

// These should technically go in ray or intersection but whateva
void test_intersectingScaledShapeRay() {
    Ray r = ray_createRay(tuple_createPoint(0, 0, -5), tuple_createVector(0, 0, 1));
    Shape testShape = shape_createDefaultShape(0, Sphere);

    Mat4 Scaling;
    mat_mat4CreateScaling(Scaling, 2, 2, 2);
    mat_mat4Copy(Scaling, testShape.transform);
    
    int length;
    Intersection *xs; 
    Ray transformedRay = ray_rayShapeIntersect(r, testShape, &xs, &length);

    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createPoint(0, 0, -2.5f), transformedRay.origin));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0, 0, 0.5f), transformedRay.direction));
}

void test_intersectingTranslatedShapeRay() {
    Ray r = ray_createRay(tuple_createPoint(0, 0, -5), tuple_createVector(0, 0, 1));
    Shape testShape = shape_createDefaultShape(0, Sphere);

    Mat4 translated;
    mat_mat4CreateTranslation(translated, 5, 0, 0);
    mat_mat4Copy(translated, testShape.transform);

    int length;
    Intersection *xs; 
    Ray transformedRay = ray_rayShapeIntersect(r, testShape, &xs, &length);

    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createPoint(-5, 0, -5), transformedRay.origin));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0, 0, 1), transformedRay.direction));

}

void test_shapeNormalAtTranslated() {
    Shape testShape = shape_createDefaultShape(0, Sphere);

    Mat4 translated;
    mat_mat4CreateTranslation(translated, 0, 1, 0);
    mat_mat4Copy(translated, testShape.transform);
    
    Tuple n = shape_normalAt(testShape, tuple_createPoint(0, 1.70711f, -0.70711f));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0, 0.70711f, -0.70711f), n));

}

void test_shapeNormalAtTransformed() {

    Shape testShape = shape_createDefaultShape(0, Sphere);

    Mat4 scaled;
    mat_mat4CreateScaling(scaled, 1, 0.5f, 1);
    Mat4 rotated; 
    mat_mat4CreateRotation_z(rotated, M_PI/5.0f);

    Mat4 transform;
    mat_mat4MultiplyMat4(scaled, rotated, transform);

    mat_mat4Copy(transform, testShape.transform);
    
    Tuple n = shape_normalAt(testShape, tuple_createPoint(0, sqrtf(2)/2.0f, -sqrtf(2)/2.0f));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0, 0.97014f, -0.24255), n));
}

void test_planeNormalAt() {
    Shape p = shape_createDefaultShape(0, Plane);

    Tuple n1 = shape_normalAt(p, tuple_createPoint(0, 0, 0));
    Tuple n2 = shape_normalAt(p, tuple_createPoint(10, 0, -10));
    Tuple n3 = shape_normalAt(p, tuple_createPoint(-5, 0, 150));

    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0, 1, 0), n1));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0, 1, 0), n2));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0, 1, 0), n3));

}

void test_planeParallelRay() {
    Shape p = shape_createDefaultShape(0, Plane);

    Ray r = ray_createRay(tuple_createPoint(0, 10, 0), tuple_createVector(0, 0, 1));

    int length;
    Intersection *xs;
    ray_rayShapeIntersect(r, p, &xs, &length);

    TEST_ASSERT_TRUE(isnan(xs[0].t));
}

void test_planeCoplanarRay() {
    Shape p = shape_createDefaultShape(0, Plane);

    Ray r = ray_createRay(tuple_createPoint(0, 0, 0), tuple_createVector(0, 0, 1));

    int length;
    Intersection *xs;
    ray_rayShapeIntersect(r, p, &xs, &length);

    TEST_ASSERT_TRUE(isnan(xs[0].t));
}

void test_planeRayAbove() {
    Shape p = shape_createDefaultShape(10, Plane);

    Ray r = ray_createRay(tuple_createPoint(0, 1, 0), tuple_createVector(0, -1, 0));

    int length;
    Intersection *xs;
    ray_rayShapeIntersect(r, p, &xs, &length);

    TEST_ASSERT_EQUAL_INT(1, length);
    TEST_ASSERT_EQUAL_INT(1, xs[0].t);
    TEST_ASSERT_TRUE(xs[0].object .instanceID == p.instanceID);
}

void test_planeRayBelow() {
    Shape p = shape_createDefaultShape(10, Plane);

    Ray r = ray_createRay(tuple_createPoint(0, -1, 0), tuple_createVector(0, 1, 0));

    int length;
    Intersection *xs;
    ray_rayShapeIntersect(r, p, &xs, &length);

    TEST_ASSERT_EQUAL_INT(1, length);
    TEST_ASSERT_EQUAL_INT(1, xs[0].t);
    TEST_ASSERT_TRUE(xs[0].object .instanceID == p.instanceID);
}

int main() {
    RUN_TEST(test_DefaultShapeMaterial);
    RUN_TEST(test_DefaultShapeAssignMaterial);
    RUN_TEST(test_DefaultShapeTransform);
    RUN_TEST(test_DefaultShapeAssignTransform);
    RUN_TEST(test_intersectingTranslatedShapeRay);
    RUN_TEST(test_intersectingScaledShapeRay);
    RUN_TEST(test_shapeNormalAtTranslated);
    RUN_TEST(test_shapeNormalAtTransformed);
    RUN_TEST(test_planeCoplanarRay);
    RUN_TEST(test_planeNormalAt);
    RUN_TEST(test_planeParallelRay);
    RUN_TEST(test_planeRayAbove);
    RUN_TEST(test_planeRayBelow);
    return UNITY_END();
}