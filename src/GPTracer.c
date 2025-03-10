#include "GPTracer.h"

void tick(Environment e, Projectile *p) {
	p->position = tuple_tupleAdd(p->position, p->velocity);
	p->velocity = tuple_tupleAdd(tuple_tupleAdd(p->velocity, e.gravity), e.wind);

	printf("Projectile position : ");
		tuple_tuplePrint(p->position);
	//printf("Projectile velocity : ");
	//tuple_tuplePrint(p->velocity);
}

int main() {
	Projectile cannonball = { tuple_createPoint(0, 1, 0), tuple_tupleMuls(tuple_vectorNormalize(tuple_createVector(1, 1, 0)), 50) };
	Environment world = { tuple_createVector(0, -0.1, 0), tuple_createVector(-0.01, 0, 0) };

	while (cannonball.position.y > 0 ) {
		tick(world, &cannonball);
	}

	return 0;
}