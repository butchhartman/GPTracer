#include <math.h>
#include "unity.h"
#include "Tuple.h"

void setUp() {

}

void tearDown() {

}

void test_tupleIsPoint() {
	int tupleIsPoint = 0;
	Tuple testTuple = { 4.3, -4.2, 3.1, 1.0 };
	TEST_ASSERT_EQUAL_FLOAT(4.3, testTuple.x);
	TEST_ASSERT_EQUAL_FLOAT(-4.2, testTuple.y);
	TEST_ASSERT_EQUAL_FLOAT(3.1, testTuple.z);
	TEST_ASSERT_EQUAL_FLOAT(1.0, testTuple.w);

	if (testTuple.w == 1.0) {
		tupleIsPoint = 1;
	}

	TEST_ASSERT_EQUAL_INT(1, tupleIsPoint);



}

void test_tupleIsVector() {
	int tupleIsVector = 0;
	Tuple testTuple = { 4.3, -4.2, 3.1, 0.0 };
	TEST_ASSERT_EQUAL_FLOAT(4.3, testTuple.x);
	TEST_ASSERT_EQUAL_FLOAT(-4.2, testTuple.y);
	TEST_ASSERT_EQUAL_FLOAT(3.1, testTuple.z);
	TEST_ASSERT_EQUAL_FLOAT(0.0, testTuple.w);

	if (testTuple.w == 0.0) {
		tupleIsVector = 1;
	}

	TEST_ASSERT_EQUAL_INT(1, tupleIsVector);
}

void test_tuple_createPoint() {
	Tuple point = tuple_createPoint(4, -4, 3);
	TEST_ASSERT_EQUAL_FLOAT(4, point.x);
	TEST_ASSERT_EQUAL_FLOAT(-4, point.y);
	TEST_ASSERT_EQUAL_FLOAT(3, point.z);
	TEST_ASSERT_EQUAL_FLOAT(1, point.w);;
}

void test_tuple_createVector() {
	Tuple vector = tuple_createVector(4, -4, 3);
	TEST_ASSERT_EQUAL_FLOAT(4, vector.x);
	TEST_ASSERT_EQUAL_FLOAT(-4, vector.y);
	TEST_ASSERT_EQUAL_FLOAT(3, vector.z);
	TEST_ASSERT_EQUAL_FLOAT(0, vector.w);;
}

void test_tuple_tupleCompare() {
	Tuple t1 = { 1.1, 0.3, -234, 1.0 };
	Tuple t2 = { 1.1, 0.3, -234, 0.0 };
	Tuple t3 = { 1.1, 0.3, -234, 1.0 };

	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(t1, t3));
	TEST_ASSERT_EQUAL_INT(0, tuple_tupleCompare(t1, t2));
}

void test_tuple_tupleAdd() {
	Tuple t1 = { 3, -2, 5, 1 };
	Tuple t2 = {-2, 3, 1, 0};
	Tuple sum = tuple_tupleAdd(t1, t2);
	Tuple testSum = { 1, 1, 6, 1 };
	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(sum, testSum));
}

void test_tuple_tupleSub_points() {
	Tuple t1 = tuple_createPoint(3, 2, 1);
	Tuple t2 = tuple_createPoint(5, 6, 7);
	Tuple diff = tuple_tupleSub(t1, t2);
	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(diff, tuple_createVector(-2, -4, -6)) );
}

void test_tuple_tupleSub_point_vector() {
	Tuple t1 = tuple_createPoint(3, 2, 1);
	Tuple t2 = tuple_createVector(5, 6, 7);
	Tuple diff = tuple_tupleSub(t1, t2);
	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(diff, tuple_createPoint(-2, -4, -6)) );
}

void test_tuple_tupleSub_vectors() {
	Tuple t1 = tuple_createVector(3, 2, 1);
	Tuple t2 = tuple_createVector(5, 6, 7);
	Tuple diff = tuple_tupleSub(t1, t2);
	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(diff, tuple_createVector(-2, -4, -6)));
}

void test_tuple_tupleSub_zero_vector() {
	Tuple t1 = tuple_createVector(0, 0, 0);
	Tuple t2 = tuple_createVector(5, 6, -7);
	Tuple diff = tuple_tupleSub(t1, t2);
	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(diff, tuple_createVector(-5, -6, 7)));
}

void test_tuple_tupleNegate() {
	Tuple t1 = { -1, -2, 3, -4 };
	Tuple t2 = { 1, 2, -3, 4 };
	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(t2, tuple_tupleNegate(t1) ) );
}

void test_tuple_tupleMuls() {
	Tuple t1 = {1, -2, -3, -4};
	float s1 = 2;
	float s2 = 0.5;
	Tuple p1 = {2, -4, -6, -8};
	Tuple p2 = {0.5, -1, -1.5, -2};

	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(p1, tuple_tupleMuls(t1, s1)));
	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(p2, tuple_tupleMuls(t1, s2)));
}

void test_tuple_tupleDivs() {
	Tuple t = { 1, -2, -3, -4 };
	float s = 2;
	Tuple q = { 0.5, -1, -1.5, -2 };

	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(q, tuple_tupleDivs(t, s)));
}

void test_tuple_vectorGetMagnitude() {
	Tuple v1 = tuple_createVector(1, 0, 0);
	Tuple v2 = tuple_createVector(0, 1, 0);
	Tuple v3 = tuple_createVector(0, 0, 1);
	Tuple v4 = tuple_createVector(1, 2, 3);
	Tuple v5 = tuple_createVector(-1, -2, -3);

	TEST_ASSERT_EQUAL_FLOAT(1.0, tuple_vectorGetMagnitude(v1));
	TEST_ASSERT_EQUAL_FLOAT(1.0, tuple_vectorGetMagnitude(v2));
	TEST_ASSERT_EQUAL_FLOAT(1.0, tuple_vectorGetMagnitude(v3));
	TEST_ASSERT_EQUAL_FLOAT(sqrtf(14), tuple_vectorGetMagnitude(v4));
	TEST_ASSERT_EQUAL_FLOAT(sqrtf(14), tuple_vectorGetMagnitude(v5));


}

void test_tuple_vectorNormalize() {
	Tuple v1 = tuple_createVector(4, 0, 0);
	Tuple v2 = tuple_createVector(1, 2, 3);
	
	Tuple n1 = { 1, 0, 0 };
	Tuple n2 = { 1/sqrtf(14), 2/sqrtf(14), 3/sqrtf(14)};
	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(n1, tuple_vectorNormalize(v1)));
	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(n2, tuple_vectorNormalize(v2)));

	// Check if normalized vector magnitudes are 1
	TEST_ASSERT_EQUAL_FLOAT(1.0f, tuple_vectorGetMagnitude(tuple_vectorNormalize(v1)) );
	TEST_ASSERT_EQUAL_FLOAT(1.0f, tuple_vectorGetMagnitude(tuple_vectorNormalize(v2)) );

}

void test_tuple_vectorDot() {
	Tuple v1 = tuple_createVector(1, 2, 3);
	Tuple v2 = tuple_createVector(2, 3, 4);
	float dot = tuple_vectorDot(v1, v2);

	TEST_ASSERT_EQUAL_FLOAT(20.0f, dot);
}

void test_tuple_vectorCross() {
	Tuple v1 = tuple_createVector(1,2,3);
	Tuple v2 = tuple_createVector(2,3,4);
	Tuple c1 = tuple_createVector(-1, 2, -1);
	Tuple c2 = tuple_createVector(1, -2, 1);

	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(c1, tuple_vectorCross(v1, v2)));
	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(c2, tuple_vectorCross(v2, v1)));
}

void test_tuple_createColor() {
	Tuple color = tuple_createColor(-0.5, 0.4, 1.7);
	TEST_ASSERT_EQUAL_FLOAT(-0.5, color.x);
	TEST_ASSERT_EQUAL_FLOAT(0.4, color.y);
	TEST_ASSERT_EQUAL_FLOAT(1.7, color.z);
	TEST_ASSERT_EQUAL_FLOAT(1.0, color.w);
}

void test_tuple_tupleAdd_colors() {
	Tuple color = tuple_createColor(0.9, 0.6, .75);
	Tuple color2 = tuple_createColor(.7, 0.1, 0.25);
	Tuple ans = { 1.6, 0.7, 1.0, 2.0 };
	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(ans, tuple_tupleAdd(color, color2)));

}

void test_tuple_tupleSub_colors() {
	Tuple color = tuple_createColor(0.9, 0.6, .75);
	Tuple color2 = tuple_createColor(.7, 0.1, 0.25);
	Tuple ans = {0.2, 0.5, 0.5, 0};
	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(ans, tuple_tupleSub(color, color2)));
}

void test_tuple_tupleMuls_colors() {
	Tuple color = tuple_createColor(0.2, 0.3, .4);
	float scalar = 2;
	Tuple ans = { 0.4, 0.6, 0.8, 2 };
	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(ans, tuple_tupleMuls(color, scalar)));
}

void test_tuple_colorBlend() {
	Tuple c1 = tuple_createColor( 1, 0.2, 0.4 );
	Tuple c2 = tuple_createColor( 0.9, 1, 0.1 );
	Tuple testAns = tuple_createColor(0.9, 0.2, 0.04);
	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(testAns, tuple_colorBlend(c1, c2)));

}

int main() {
	UNITY_BEGIN();
	RUN_TEST(test_tupleIsPoint);
	RUN_TEST(test_tupleIsVector);
	RUN_TEST(test_tuple_createPoint);
	RUN_TEST(test_tuple_createVector);
	RUN_TEST(test_tuple_tupleCompare);
	RUN_TEST(test_tuple_tupleAdd);
	RUN_TEST(test_tuple_tupleSub_points);
	RUN_TEST(test_tuple_tupleSub_point_vector);
	RUN_TEST(test_tuple_tupleSub_vectors);
	RUN_TEST(test_tuple_tupleSub_zero_vector);
	RUN_TEST(test_tuple_tupleNegate);
	RUN_TEST(test_tuple_tupleMuls);
	RUN_TEST(test_tuple_tupleDivs);
	RUN_TEST(test_tuple_vectorGetMagnitude);
	RUN_TEST(test_tuple_vectorNormalize);
	RUN_TEST(test_tuple_vectorDot);
	RUN_TEST(test_tuple_vectorCross);

	RUN_TEST(test_tuple_createColor);
	RUN_TEST(test_tuple_tupleAdd_colors);
	RUN_TEST(test_tuple_tupleSub_colors);
	RUN_TEST(test_tuple_tupleMuls_colors);
	RUN_TEST(test_tuple_colorBlend);


	return UNITY_END();
}