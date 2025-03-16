#include "unity.h"
#include "Patterns.h"

void setUp() {

}

void tearDown() {

}

void test_patternStripe() {
    Pattern pattern = pattern_stripe(COLOR_WHITE, COLOR_BLACK);

    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern.a, COLOR_WHITE));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern.b, COLOR_BLACK));
}

void test_stripeAt_y() {
    Pattern pattern = pattern_stripe(COLOR_WHITE, COLOR_BLACK);
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_stripeAt(pattern, tuple_createPoint(0, 0, 0)), COLOR_WHITE));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_stripeAt(pattern, tuple_createPoint(0, 1, 0)), COLOR_WHITE));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_stripeAt(pattern, tuple_createPoint(0, 2, 0)), COLOR_WHITE));
}

void test_stripeAt_z() {
    Pattern pattern = pattern_stripe(COLOR_WHITE, COLOR_BLACK);
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_stripeAt(pattern, tuple_createPoint(0, 0, 0)), COLOR_WHITE));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_stripeAt(pattern, tuple_createPoint(0, 0, 1)), COLOR_WHITE));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_stripeAt(pattern, tuple_createPoint(0, 0, 1)), COLOR_WHITE));
}

void test_stripeAt_x() {
    Pattern pattern = pattern_stripe(COLOR_WHITE, COLOR_BLACK);
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_stripeAt(pattern, tuple_createPoint(0, 0, 0)), COLOR_WHITE));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_stripeAt(pattern, tuple_createPoint(0.9f, 0, 0)), COLOR_WHITE));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_stripeAt(pattern, tuple_createPoint(1, 0, 0)), COLOR_BLACK));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_stripeAt(pattern, tuple_createPoint(-0.1f, 0, 0)), COLOR_BLACK));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_stripeAt(pattern, tuple_createPoint(-1, 0, 0)), COLOR_BLACK));
    TEST_ASSERT_TRUE(tuple_tupleCompare(pattern_stripeAt(pattern, tuple_createPoint(-1.1f, 0, 0)), COLOR_WHITE));
}




int main() {
    RUN_TEST(test_patternStripe);
    RUN_TEST(test_stripeAt_x);
    RUN_TEST(test_stripeAt_y);
    RUN_TEST(test_stripeAt_z);
    return UNITY_END();
}