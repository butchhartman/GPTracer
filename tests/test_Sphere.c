#include "unity.h"
#include "Sphere.h"

void setUp() {

}

void tearDown() {

}

void test_createSphere() {
    Sphere newSphere1 = sphere_createSphere(tuple_createPoint(0, 1, 0), 1, 0, NULL);

   TEST_ASSERT_TRUE(tuple_tupleCompare(newSphere1.origin, tuple_createPoint(0, 1, 0))); 
   TEST_ASSERT_EQUAL(1, newSphere1.radius);
   TEST_ASSERT_EQUAL(0, newSphere1.instanceID);
}

void test_sphereDefaultTransform() {
    Mat4 expected = MAT4_IDENTITY;
    Sphere newSphere = sphere_createSphere(tuple_createPoint(0, 0, 0), 1, 0, NULL);
    TEST_ASSERT_TRUE(mat_mat4Compare(expected, newSphere.transform));
}

void test_sphereSetTransform(){
    Mat4 expected;
    mat_mat4CreateTranslation(expected, 2, 3, 4);
    Sphere newSphere = sphere_createSphere(tuple_createPoint(0, 0, 0), 1, 0, NULL);
    sphere_setTransform(&newSphere, expected);
    TEST_ASSERT_TRUE(mat_mat4Compare(expected, newSphere.transform));
}

void test_sphereCreateTransform() {
    Mat4 expected;
    mat_mat4CreateTranslation(expected, 2, 3, 4);
    Sphere newSphere = sphere_createSphere(tuple_createPoint(0, 0, 0), 1, 0, expected);
    TEST_ASSERT_TRUE(mat_mat4Compare(expected, newSphere.transform));
}
int main() {
    RUN_TEST(test_createSphere);
    RUN_TEST(test_sphereDefaultTransform);
    RUN_TEST(test_sphereSetTransform);
    RUN_TEST(test_sphereCreateTransform);
    return UNITY_END();
}