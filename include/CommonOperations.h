#pragma once
#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>

/*
* Helper function
* Compares two float numbers for equality.
*
* \param a - Number 1 for comparison
* \param b - Number 2 for comparison
*
* \return 1 if floats are equal, otherwise 0
*/
int floatCompare(float a, float b);

int isOdd(int a);
// degrees to radians
float rad(float angle);