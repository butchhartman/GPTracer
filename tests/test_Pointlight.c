#include "unity.h"
#include "Pointlight.h"

void setUp() {

}

void tearDown() {

}

void test_pointlightCreate() {
    Pointlight plight = pointlight_createPointlight(tuple_createPoint(0, 0, 0), tuple_createColor(1, 1, 1));

    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createPoint(0,0,0), plight.position));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createColor(1,1,1), plight.intensity));
}


int main() {
    RUN_TEST(test_pointlightCreate);
    return UNITY_END();
}