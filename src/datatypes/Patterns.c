#include "Patterns.h"

Pattern pattern_stripe(Tuple colorA, Tuple colorB){
    Pattern newPattern;
    newPattern.a = colorA;
    newPattern.b = colorB;
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
