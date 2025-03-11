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
	Canvas canvas = canvas_createCanvas(1000, 500);

	Tuple drawColor = tuple_createColor(0.8, 0.2, 0.2);
	Projectile cannonball = { tuple_createPoint(0, 1, 0), tuple_tupleMuls(tuple_vectorNormalize(tuple_createVector(1, 1.6, 0)), 10) };
	Environment world = { tuple_createVector(0, -0.1, 0), tuple_createVector(-0.01, 0, 0) };

	while (cannonball.position.y > 0) {
		tick(world, &cannonball);

		if (cannonball.position.y <= 0 || cannonball.position.x >= canvas.width || cannonball.position.y > canvas.height) {
			printf("Canvas bound reached, exiting loop.\n");
			break;
		}

		canvas_writePixel(&canvas, drawColor, (int)cannonball.position.x, canvas.height - (int)cannonball.position.y);
	}

	int datalength;
	ppm_writePPM(canvas_canvasToPPM(canvas, &datalength));

	return 0;
}