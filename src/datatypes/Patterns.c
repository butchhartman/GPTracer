#include "Patterns.h"
#include "Shape.h"

Pattern pattern_createPattern(Tuple colorA, Tuple colorB, enum patternType pattern){
    Mat4 iden = MAT4_IDENTITY;

    Pattern newPattern;
    newPattern.a = colorA;
    newPattern.b = colorB;
    mat_mat4Copy(iden, newPattern.transform);
    newPattern.patterntype = pattern;
    return newPattern;
}

// This is the only function that differentiate different patterns from each other.
Tuple pattern_patternAt(Pattern pattern, Tuple point){

    switch (pattern.patterntype) {
        
        case (testPattern):

            return tuple_createColor(point.x, point.y, point.z);

            break;
        
        case (Stripe):
            if ((int)floorf(point.x) % 2 == 0) {
                return pattern.a;
            } 
            else {
                return pattern.b;
            }

            break;
        
        case (Gradient):
            Tuple distance = tuple_tupleSub(pattern.b, pattern.a);
            float fraction = point.x - floorf(point.x);
            return tuple_tupleAdd(pattern.a, tuple_tupleMuls(distance, fraction));
            break;
        
        case (Ring):
            if ( (int)floorf( sqrtf(powf(point.x, 2) + powf(point.z, 2)) ) % 2 == 0) {
                return pattern.a;
            } 
            else {
                return pattern.b;    
            }
            break;

        case (Checker):
            if ( (int)(fabsf(point.x) + fabsf(point.y) + fabsf(point.z)) % 2 == 0) {
                return pattern.a;
            }
            else {
                return pattern.b;
            }
            break;

        default:
            return tuple_createColor(1, 1, 0);
            break;
    }

}


