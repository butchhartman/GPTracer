#include "unity.h"
#include "Sphere.h"

void setUp() {

}

void tearDown() {

}

void test_createSphere() {
    Material mat = material_createMaterial(tuple_createColor(1, 0, 0), 0.1f, 0.9f, 0.9f, 200.0f);
    Sphere newSphere1 = sphere_createSphere(tuple_createPoint(0, 1, 0), 1, 0, NULL, mat);

   TEST_ASSERT_TRUE(tuple_tupleCompare(newSphere1.origin, tuple_createPoint(0, 1, 0))); 
   TEST_ASSERT_EQUAL(1, newSphere1.radius);
   TEST_ASSERT_EQUAL(0, newSphere1.instanceID);
}

void test_sphereDefaultTransform() {
    Material mat = material_createMaterial(tuple_createColor(1, 0, 0), 0.1f, 0.9f, 0.9f, 200.0f);
    Mat4 expected = MAT4_IDENTITY;
    Sphere newSphere = sphere_createSphere(tuple_createPoint(0, 0, 0), 1, 0, NULL, mat);
    TEST_ASSERT_TRUE(mat_mat4Compare(expected, newSphere.transform));
}

void test_sphereSetTransform(){
    Material mat = material_createMaterial(tuple_createColor(1, 0, 0), 0.1f, 0.9f, 0.9f, 200.0f);
    Mat4 expected;
    mat_mat4CreateTranslation(expected, 2, 3, 4);
    Sphere newSphere = sphere_createSphere(tuple_createPoint(0, 0, 0), 1, 0, NULL,mat);
    sphere_setTransform(&newSphere, expected);
    TEST_ASSERT_TRUE(mat_mat4Compare(expected, newSphere.transform));
}

void test_sphereCreateTransform() {
    Material mat = material_createMaterial(tuple_createColor(1, 0, 0), 0.1f, 0.9f, 0.9f, 200.0f);
    Mat4 expected;
    mat_mat4CreateTranslation(expected, 2, 3, 4);
    Sphere newSphere = sphere_createSphere(tuple_createPoint(0, 0, 0), 1, 0, expected, mat);
    TEST_ASSERT_TRUE(mat_mat4Compare(expected, newSphere.transform));
}

void test_sphereNormalAt() {
    Material mat = material_createMaterial(tuple_createColor(1, 0, 0), 0.1f, 0.9f, 0.9f, 200.0f);
    Sphere s = sphere_createSphere(tuple_createPoint(0, 0, 0), 1, 0, NULL, mat);
    Tuple nx = sphere_normalAt(s, tuple_createPoint(1, 0, 0));
    Tuple ny = sphere_normalAt(s, tuple_createPoint(0, 1, 0));
    Tuple nz = sphere_normalAt(s, tuple_createPoint(0, 0, 1));
    Tuple nn = sphere_normalAt(s, tuple_createPoint(sqrtf(3)/3.0,  sqrtf(3)/3.0,  sqrtf(3)/3.0));

    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(1, 0, 0), nx));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0, 1, 0), ny));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0, 0, 1), nz));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(sqrtf(3)/3.0,  sqrtf(3)/3.0,  sqrtf(3)/3.0), nn));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(sqrtf(3)/3.0,  sqrtf(3)/3.0,  sqrtf(3)/3.0), tuple_vectorNormalize(nn)));
}
void test_sphereNormalAtTransformed() {
    Material mat = material_createMaterial(tuple_createColor(1, 0, 0), 0.1f, 0.9f, 0.9f, 200.0f);
    Sphere s = sphere_createSphere(tuple_createPoint(0,0,0), 1, 0, NULL, mat);
    Mat4 translation;
    mat_mat4CreateTranslation(translation, 0, 1, 0);
    sphere_setTransform(&s, translation);

    Tuple n = sphere_normalAt(s, tuple_createPoint(0, 1.70711f, -0.70711f));

    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0, 0.70711f, -0.70711f), n));

    Mat4 scale;
    Mat4 rotation;
    Mat4 composite;
    mat_mat4CreateScaling(scale, 1, 0.5f, 1);
    mat_mat4CreateRotation_z(rotation, M_PI/5.0f);
    mat_mat4MultiplyMat4(scale, rotation, composite);

    sphere_setTransform(&s, composite);

    Tuple n2 = sphere_normalAt(s, tuple_createPoint(0, sqrtf(2.0f)/2.0f, -sqrtf(2.0f)/2.0f));

    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0, 0.97014f, -0.24254), n2));
}

void test_sphereMaterial() {
    Material mat = material_createMaterial(tuple_createColor(1, 0, 0), 1.0f, 10.0f, 5.0f, 100.0f);
    Sphere sp = sphere_createSphere(tuple_createPoint(0, 0, 0), 1, 0, NULL, mat);

    TEST_ASSERT_EQUAL_FLOAT(1.0f, sp.material.ambient);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, sp.material.diffuse);
    TEST_ASSERT_EQUAL_FLOAT(5.0f, sp.material.specular);
    TEST_ASSERT_EQUAL_FLOAT(100.0f, sp.material.shininess);
}
int main() {
    RUN_TEST(test_createSphere);
    RUN_TEST(test_sphereDefaultTransform);
    RUN_TEST(test_sphereSetTransform);
    RUN_TEST(test_sphereCreateTransform);
    RUN_TEST(test_sphereNormalAt);
    RUN_TEST(test_sphereNormalAtTransformed);
    RUN_TEST(test_sphereMaterial);
    return UNITY_END();
}