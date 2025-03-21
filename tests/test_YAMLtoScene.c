#include "unity.h"
#include "YAMLtoScene.h"

void setUp() {

}

void tearDown() {

}

void test_emptyWorld() {
    World w;
    w.objectCount = 0;
    yaml_parseScene(&w, "../../../yaml/emptyWorld.yaml");
    TEST_ASSERT_EQUAL_INT(0, w.objectCount);
}

void test_light() {
    World w;
    yaml_parseScene(&w, "../../../yaml/testLight.yaml");
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createPoint(50, 100, -50), w.light.position));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createPoint(1, 1, 1), w.light.intensity));
}

int main() {
    RUN_TEST(test_emptyWorld);
    RUN_TEST(test_light);
    return UNITY_END();
}