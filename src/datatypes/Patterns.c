#include "Patterns.h"
#include "Shape.h"

Pattern pattern_stripe(Tuple colorA, Tuple colorB){
    Mat4 iden = MAT4_IDENTITY;

    Pattern newPattern;
    newPattern.a = colorA;
    newPattern.b = colorB;
    mat_mat4Copy(iden, newPattern.transform);
    return newPattern;
}

Tuple pattern_stripeAt(Pattern pattern, Tuple point){
    if ((int)floorf(point.x) % 2 == 0) {
        return pattern.a;
    } 
    else {
        return pattern.b;
    }
}


