#include <math.h>
#include "Tuple.h"

const float EPSILON = 0.0001f;

Tuple tuple_createPoint(float x, float y, float z)
{
	Tuple point = { 0 };
	point.x = x;
	point.y = y;
	point.z = z;
	point.w = 1;
	return point;
}

Tuple tuple_createVector(float x, float y, float z)
{
	Tuple vector = { 0 };
	vector.x = x;
	vector.y = y;
	vector.z = z;
	vector.w = 0;
	return vector;
}

static int tuple_floatCompare(float a, float b)
{
	if (fabsf(a - b) < EPSILON) {
		return 1;
	}
	else {
		return 0;
	}
}

int tuple_tupleCompare(Tuple t1, Tuple t2)
{

	if (tuple_floatCompare(t1.x, t2.x) &&
		tuple_floatCompare(t1.y , t2.y) &&
		tuple_floatCompare(t1.z, t2.z) &&
		tuple_floatCompare(t1.w, t2.w)) {
		return 1;
	}
	else {
		return 0;
	}
	if (t1.x == t2.x &&
		t1.y == t2.y &&
		t1.z == t2.z &&
		t1.w == t2.w) {
		return 1;
	}
	else {
		return 0;
	}
}

Tuple tuple_tupleAdd(Tuple t1, Tuple t2)
{
	Tuple sum = { 0 };
	sum.x = t1.x + t2.x;
	sum.y = t1.y + t2.y;
	sum.z = t1.z + t2.z;
	sum.w = t1.w + t2.w;

	return sum;
}

Tuple tuple_tupleSub(Tuple t1, Tuple t2)
{
	Tuple difference = { 0 };
	difference.x = t1.x - t2.x;
	difference.y = t1.y - t2.y;
	difference.z = t1.z - t2.z;
	difference.w = t1.w - t2.w;

	return difference;
}

Tuple tuple_tupleNegate(Tuple t)
{
	Tuple neg = { -t.x, -t.y, -t.z, - t.w };
	return neg;
}

Tuple tuple_tupleMuls(Tuple t, float s)
{
	Tuple muls = { t.x * s, t.y * s, t.z * s, t.w * s };
	return muls;
}

Tuple tuple_tupleDivs(Tuple t, float s)
{
	Tuple divs = {t.x / s, t.y / s, t.z / s, t.w / s};
	return divs;
}

float tuple_vectorGetMagnitude(Tuple v)
{
	float m = sqrtf( powf(v.x, 2) + powf(v.y, 2) + powf(v.z, 2) + powf(v.w, 2));
	return m;
}

Tuple tuple_vectorNormalize(Tuple v)
{
	float mag = tuple_vectorGetMagnitude(v);
	Tuple vNorm = { v.x / mag, v.y / mag, v.z / mag, v.w / mag };
	return vNorm;
}

float tuple_vectorDot(Tuple v1, Tuple v2)
{
	float scalar = (v1.x * v2.x +
					v1.y * v2.y +
					v1.z * v2.z +
					v1.w * v2.w);
	return scalar;
}

Tuple tuple_vectorCross(Tuple v1, Tuple v2)
{
	Tuple cross = tuple_createVector( v1.y * v2.z - v1.z * v2.y,
									  v1.z * v2.x - v1.x * v2.z,
									  v1.x * v2.y - v1.y * v2.x);
	return cross;
}

void tuple_tuplePrint(Tuple t)
{
	printf("( %f, %f, %f, %f)\n", t.x, t.y, t.z, t.w);
}
