#include "GPTracer.h"

void tick(Environment e, Projectile *p) {
	p->position = tuple_tupleAdd(p->position, p->velocity);
	p->velocity = tuple_tupleAdd(tuple_tupleAdd(p->velocity, e.gravity), e.wind);

	printf("Projectile position : ");
		tuple_tuplePrint(p->position);
	//printf("Projectile velocity : ");
	//tuple_tuplePrint(p->velocity);
}
/*
* Rotation matrices ALWAYS rotate the point in reference to the origin (0,0,0). 
* Therefore, for the clock implementation below, the point starts at (0, 30, 0) and is rotated along the z axis (negatively)
* and no other translation needs to take place because the rotation is about the origin.
* The translation after the rotation is to move the points from coordinate space to canvas space.
*/
int main(int argc, char* argv[]) {
	World w = world_createDefault();

	Pointlight light = pointlight_createPointlight(tuple_createPoint(-10, 10, -10), tuple_createColor(1, 1, 1));

	w.light = light;

	Mat4 viewMatrix;
	mat_mat4CreateView(viewMatrix, tuple_createPoint(0, 0, -3.5), tuple_createPoint(0, 0, 0), tuple_createVector(0, 1, 0));

	Camera camera = camera_createCamera(250, 250, rad(55), viewMatrix);

	Canvas canvas =	camera_render(camera, w);

	printf("Writing to file...\n");
	clock_t start_time = clock();
	int length;
	ppm_writePPM(canvas_canvasToPPM(canvas, &length));
	double elapsedTime = (double)(clock() - start_time) / CLOCKS_PER_SEC;
	printf("Program took %f seconds to write to PPM", elapsedTime);


	// for (int i = 0; i < 12; i++) {
	// 	Mat4 rotationMatrix = {0};
	// 	Mat4 translationMatrix = {0};
	// 	Tuple point = tuple_createPoint(0, (float)(canvas.width/2 * 0.8f), 0);

	// 	mat_mat4CreateRotation_z(rotationMatrix, rad((float)(-30 * i)));
	// 	mat_mat4CreateTranslation(translationMatrix, (float)(canvas.width/2), (float)(canvas.height/2), 0);

	// 	point = mat_mat4MultuplyTuple(rotationMatrix, point);
	// 	point = mat_mat4MultuplyTuple(translationMatrix, point);

	// 	canvas_writePixel(&canvas, drawColor, (int)point.x, canvas.height - (int)point.y);
	// }

//	Projectile cannonball = { tuple_createPoint(0, 1, 0), tuple_tupleMuls(tuple_vectorNormalize(tuple_createVector(1, 1.4, 0)), 11.05) };
//	Environment world = { tuple_createVector(0, -0.1, 0), tuple_createVector(-0.01, 0, 0) };
//
//	while (cannonball.position.y > 0) {
//		tick(world, &cannonball);
//
//		if (cannonball.position.y <= 0 || cannonball.position.x >= canvas.width || cannonball.position.y > canvas.height) {
//			printf("Canvas bound reached, exiting loop.\n");
//			break;
//		}
//
//		canvas_writePixel(&canvas, drawColor, (int)cannonball.position.x, canvas.height - (int)cannonball.position.y);
//	}
//
//	int datalength;
//	ppm_writePPM(canvas_canvasToPPM(canvas, &datalength));
//
	return 0;
}