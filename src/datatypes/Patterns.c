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
        
        case (Stripe):
            if ((int)floorf(point.x) % 2 == 0) {
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


