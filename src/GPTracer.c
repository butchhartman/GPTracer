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
	clock_t mathTime = clock();
	World w; 

	Pointlight light = pointlight_createPointlight(tuple_createPoint(-10, 10, -10), tuple_createColor(1, 1, 1));
	Shape plane = shape_createDefaultShape(0, Plane);
	Shape sphere = shape_createDefaultShape(1, Sphere);
	Shape sphere2 = shape_createDefaultShape(2, Sphere);
	Shape sphere3 = shape_createDefaultShape(3, Sphere);
	Shape sphere4 = shape_createDefaultShape(4, Sphere);

	Mat4 sTr;
	mat_mat4CreateTranslation(sTr, 0, 1.5f, 3);
	mat_mat4Copy(sTr, sphere.transform);
	mat_mat4CreateTranslation(sTr, 3.2f, 1.2f, -2);
	mat_mat4Copy(sTr, sphere2.transform);
	mat_mat4CreateTranslation(sTr, -4.6f, 1.8f, 1.2f);
	mat_mat4Copy(sTr, sphere3.transform);
	mat_mat4CreateTranslation(sTr, -2.2f, 2.2f, -1.2f);
	mat_mat4Copy(sTr, sphere4.transform);

	Material floorMat = material_createMaterial(tuple_createColor(1.0f, 0.95f, 0.95f), 0.1f, 0.9f, 0.1f, 200.0f);
	plane.material = floorMat;

	Material material = material_createMaterial(tuple_createColor(0, 1, 1), 0.1f, 0.9f, 0.9f, 150.0f);
	sphere.material = material;
	sphere2.material = material;
	sphere3.material = material;
	sphere4.material = material;

	Mat4 rx;
	mat_mat4CreateRotation_x(rx, rad(90));
	mat_mat4CreateTranslation(sTr, 0, 0, 7);
	Shape wall = shape_createDefaultShape(5, Plane);
	wall.material = floorMat;
	mat_mat4MultiplyMat4(sTr, rx, wall.transform);
	
	w.light = light;
	w.objectCount = 6;
	w.objects = malloc(sizeof(Shape) * w.objectCount);
	w.objects[0] = plane;
	w.objects[1] = sphere;
	w.objects[2] = sphere2;
	w.objects[3] = sphere3;
	w.objects[4] = sphere4;
	w.objects[5] = wall;

	Mat4 viewMatrix;
	mat_mat4CreateView(viewMatrix, tuple_createPoint(0, 6.3f, -7.5), tuple_createPoint(0, 1.6f, 0), tuple_createVector(0, 1, 0));

	Camera camera = camera_createCamera(1280, 720, rad(55), viewMatrix);

	Canvas canvas =	camera_render(camera, w);
	double endMathTime = (double)(clock() - mathTime) / CLOCKS_PER_SEC;
	printf("Program took %f seconds to compute rendering calculations", endMathTime);
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