#pragma once
#include <stdio.h>
#include "CommonOperations.h"

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

/*
* Creates a tuple represnting an RGB value
* 
* \param r - Red value (0-1)
* \param g - Green value (0-1)
* \param b - Blue value (0-1);
* 
* \return Tuple - A tuple representing a color value. It w value is technically 1 one but in its application the w value is clipped.
*/
Tuple tuple_createColor(float r, float g, float b);

/*
* Compares and checks if the passed tuples are equal
* 
* \param t1 - The first tuple to compare
* \param t2 - The second tuple to compare
* 
* \return 1 if the tuples are exactly equal, otherwise 0
*/
int tuple_tupleCompare(Tuple t1, Tuple t2);

/*
* Adds two tuples together.
* 
* \param t1 - Addend 1
* \param t2 - Addend 2
* 
* \return A tuple representing the sum of the addend tuple's corresponding values.
*/
Tuple tuple_tupleAdd(Tuple t1, Tuple t2);

/*
* Subtracts t2 from t1 (t1 - t2).
* 
* \param t1 - Minuend
* \param t2 - Subtrahend
* 
* \return A tuple representing the difference between the minuend and subtrahend tuple's corresponding values.
*/
Tuple tuple_tupleSub(Tuple t1, Tuple t2);

/*
* Negates a tuple (all components negated).
* 
* \param t1 - The tuple to be negated
* 
* \return A equal to the passed tuple with all components signs reversed.
*/
Tuple tuple_tupleNegate(Tuple t);

/*
* Multiplies a tuple by a scalar value
* 
* \param t - Tuple to be multiplied by the scalar
* \param s - Float representing the scalar value
* 
* \return A tuple with all its values multiplied by the scalar
*/
Tuple tuple_tupleMuls(Tuple t, float s);

/*
* Divides a tuple by a scalar value
* 
* \param t - Tuple to be the dividend
* \param s - Float to be the scalar divisor
* 
* \return A tuple with all its values divided by the scalar
*/
Tuple tuple_tupleDivs(Tuple t, float s);

/*
* Calculates the length of a vector.
* 
* \param v - The tuple vector
* 
* \return A float representing the length of the passed vector.
*/
float tuple_vectorGetMagnitude(Tuple v);

/*
* Normalizes a vector's length to 1
* 
* \param v - The tuple vector to normalize
* 
* \return A tuple with equal direction to the passed vector, but a magnitude of 1
*/
Tuple tuple_vectorNormalize(Tuple v);

/*
* Calculates the dot product between two vectors
* (Dot product is the product of the parts the the two vectors that go in the same direction. I think this implementation only works for unit vector but maybe not);
* 
* \param v1 - The first vector
* \param v2 - The second vector
* 
* \return a float representing the dot product of the two vectors
*/
float tuple_vectorDot(Tuple v1, Tuple v2);

/*
* Calculates the cross product between two vectors
* 
* \param v1 - The first vector
* \param v2 - The second vector
* 
* \return A tuple reprsenting the cross product of the two vectors (vector that is perpendicular to the intersection of then two vectors?)
*/
Tuple tuple_vectorCross(Tuple v1, Tuple v2);

/*
* Blends two color tuples together
* 
* \param c1 - The first color
* \param c2 - The second color
* 
* \return A tuple composed of the product of the passed tuple's corresponding components
*/
Tuple tuple_colorBlend(Tuple c1, Tuple c2);

/*
* Prints a tuple's value to the console.
* 
* \param t - The tuple to be printed
*/
void tuple_tuplePrint(Tuple t);

float* tuple_tupleGetMember(Tuple tuple, int memberIndex);

Tuple tuple_reflect(Tuple vector, Tuple normal);