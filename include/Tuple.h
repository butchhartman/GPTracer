#pragma once
#include <stdio.h>

typedef struct {
	float x;
	float y;
	float z;
	float w;
} Tuple;


/*
* Creates a point from the passed parameters. (Point is a tuple with w = 1)
* 
* \param x - The x member of the tuple
* \param y - The y member of the tuple
* \param z - The z member of the tuple
* 
* \return A tuple with the respective x, y, and z members and a w value of 1
*/
Tuple tuple_createPoint(float x, float y, float z);

/*
* Creates a vector from the passed parameters. (Vector is a tuple with w = 0)
*
* \param x - The x member of the tuple
* \param y - The y member of the tuple
* \param z - The z member of the tuple
*
* \return A tuple with the respective x, y, and z members and a w value of 0
*/
Tuple tuple_createVector(float x, float y, float z);

/*
* Compares the equality of two floats
* 
* \param a - The first float to be compared
* 
* \param b - The second float to be compared
* 
* \return 1 if the floats are equal, otherwise 0
*/
static int tuple_floatCompare(float a, float b);

/*
* Compares and checks if the passed tuples are equal
* 
* \param t1 - The first tuple to compare
* \param t2 - The second tuple to compare
* 
* \return 1 if the tuples are exactly equal, otherwise 0
*/
int tuple_tupleCompare(Tuple t1, Tuple t2);

Tuple tuple_tupleAdd(Tuple t1, Tuple t2);

Tuple tuple_tupleSub(Tuple t1, Tuple t2);

Tuple tuple_tupleNegate(Tuple t);

Tuple tuple_tupleMuls(Tuple t, float s);

Tuple tuple_tupleDivs(Tuple t, float s);

float tuple_vectorGetMagnitude(Tuple v);

Tuple tuple_vectorNormalize(Tuple v);

float tuple_vectorDot(Tuple v1, Tuple v2);

Tuple tuple_vectorCross(Tuple v1, Tuple v2);

void tuple_tuplePrint(Tuple t);