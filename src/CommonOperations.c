#include "CommonOperations.h"

const float EPSILON = 0.0001f;


int floatCompare(float a, float b)
{
	if (fabsf(a - b) < EPSILON) {
		return 1;
	}
	else {
		return 0;
	}
}