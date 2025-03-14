#include "CommonOperations.h"
#include "Intersection.h"
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

	return 1000; // This is to silence the compiler warning. Should never reach this.
}

float rad(float angle){
	return (angle / 180.0f) * (float)M_PI;
}


// Bubble sort implementation from geeks for geeks
void bubbleSort(Intersection arr[], int n) {
   for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].t > arr[j + 1].t && !(arr[j].t - arr[j + 1].t < EPSILON)) {
                float temp = arr[j].t;
                arr[j].t = arr[j + 1].t;
                arr[j + 1].t = temp;
            } 
        }
    }
}