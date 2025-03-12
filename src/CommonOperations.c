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

int isOdd(int a)
{
	if (a%2 == 0) {
		return 0;
	} 
	else if (a%2 == 1){
		return 1;
	}
}

float rad(float angle){
	return (angle / 180.0) * M_PI;
}
