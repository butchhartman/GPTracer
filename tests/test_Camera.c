#include "unity.h"
#include "Camera.h"
#include "CommonOperations.h"
#include "Ray.h"
#include "World.h"
#include "Canvas.h" 
void setUp() {

}

void tearDown() {

}

void test_createCamera() {
    int hsize = 160;
    int vsize = 120;
    float FOV = rad(90);
    Camera c = camera_createCamera(hsize, vsize, FOV, NULL);
    
    Mat4 expectedDefaultTransform = MAT4_IDENTITY;

    TEST_ASSERT_EQUAL_INT(160, c.hsize);
    TEST_ASSERT_EQUAL_INT(120, c.vsize);
    TEST_ASSERT_EQUAL_FLOAT(rad(90), c.fov);
    TEST_ASSERT_TRUE(mat_mat4Compare(expectedDefaultTransform, c.transform));

}

void test_createCamera_pixelsize_h() {
    Camera c = camera_createCamera(200, 125, rad(90), NULL);
    TEST_ASSERT_EQUAL_FLOAT(0.01f, c.pixelSize);
}

void test_createCamera_pixelsize_v() {
    Camera c = camera_createCamera(125, 200, rad(90), NULL);
    TEST_ASSERT_EQUAL_FLOAT(0.01f, c.pixelSize);
}

void test_rayForPixel_1() {
    Camera camera = camera_createCamera(201, 101, rad(90), NULL);
    Ray r = camera_rayForPixel(camera, 100, 50);

    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createPoint(0, 0, 0), r.origin));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0, 0, -1), r.direction));
}


void test_rayForPixel_2() {
    Camera camera = camera_createCamera(201, 101, rad(90), NULL);
    Ray r = camera_rayForPixel(camera, 0, 0);

    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createPoint(0, 0, 0), r.origin));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0.66519f, 0.33259f, -0.66851f), r.direction));
}

void test_rayForPixel_3() {
    Mat4 rotation;
    mat_mat4CreateRotation_y(rotation, M_PI/4.0f);
    Mat4 translation;
    mat_mat4CreateTranslation(translation, 0, -2, 5);
   Mat4 transform;
   mat_mat4MultiplyMat4(rotation, translation, transform);

    Camera camera = camera_createCamera(201, 101, rad(90), transform);
    Ray r = camera_rayForPixel(camera, 100, 50);

    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createPoint(0, 2, -5), r.origin));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(sqrtf(2.0f)/2.0f, 0, -sqrtf(2.0f)/2.0f), r.direction));
}

void test_render() {
    World w = world_createDefault();
    Camera c = camera_createCamera(11, 11, M_PI/2.0f, NULL);
    Tuple from = tuple_createPoint(0, 0, -5);
    Tuple to = tuple_createPoint(0, 0, 0);
    Tuple up = tuple_createPoint(0, 1, 0);
    
    mat_mat4CreateView(c.transform, from, to, up);

    Canvas image = camera_render(c, w);
    TEST_ASSERT_TRUE(tuple_tupleCompare(canvas_pixelAt(image, 5, 5), tuple_createColor(0.38066f, 0.47583f, 0.2855f)));

}

int main() {
    RUN_TEST(test_createCamera);
    RUN_TEST(test_createCamera_pixelsize_h);
    RUN_TEST(test_createCamera_pixelsize_v);
    RUN_TEST(test_render);
    RUN_TEST(test_rayForPixel_1);
    RUN_TEST(test_rayForPixel_2);
    RUN_TEST(test_rayForPixel_3);
    return UNITY_END();
}