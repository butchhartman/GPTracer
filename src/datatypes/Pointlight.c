#include "Pointlight.h"

Pointlight pointlight_createPointlight(Tuple position, Tuple intensity){
    Pointlight newpl;
    newpl.position = position;
    newpl.intensity = intensity;
    return newpl;
}
