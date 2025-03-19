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
	int width, height = 0;
	width = 100; height = 100;
	if (argc > 1) {
		for (int i = 0; i < argc; i++) {
			if (strcmp(argv[i], "-h") == 0) {
				width = atoi(argv[i+1]);
			}

			if (strcmp(argv[i], "-w") == 0) {
				height = atoi(argv[i+1]);
			}

		}
	}

	if (height == 0 || width == 0) {
		return -1;
	}

	clock_t mathTime = clock();
	World w; 

	Pointlight light = pointlight_createPointlight(tuple_createPoint(-4, 10, -10), tuple_createColor(1, 1, 1));
	w.light = light;

	Shape plane = shape_createDefaultShape(0, Plane);
	Shape plane1 = shape_createDefaultShape(1, Plane);
	Shape plane2 = shape_createDefaultShape(2, Plane);
	Shape plane3 = shape_createDefaultShape(7, Plane);
	Shape sphere = shape_createDefaultShape(3, Sphere);
	Shape sphere2 = shape_createDefaultShape(4, Sphere);
	Shape sphere3 = shape_createDefaultShape(5, Sphere);
	Shape sphere4 = shape_createDefaultShape(6, Sphere);

	Pattern pat = pattern_createPattern(COLOR_WHITE, COLOR_BLACK, Checker);
	plane.material.pattern = pat;
	plane.material.reflective = 0.10f;
	plane1.material.pattern = pat;
	plane2.material.pattern = pat;
	plane3.material.pattern = pat;

	Mat4 wall1Rx;
	Mat4 wall1Tz;
	Mat4 wall1Transform;

	mat_mat4CreateRotation_x(wall1Rx, rad(90));
	mat_mat4CreateTranslation(wall1Tz, 0, 0, 5);
	mat_mat4MultiplyMat4(wall1Tz,wall1Rx , wall1Transform);
	mat_mat4Copy(wall1Transform, plane1.transform);


	Mat4 wall2Rx;
	Mat4 wall2Tz;
	Mat4 wall2Transform;

	mat_mat4CreateRotation_z(wall2Rx, rad(90));
	mat_mat4CreateTranslation(wall2Tz, -5, 0, 0);
	mat_mat4MultiplyMat4(wall2Tz,wall2Rx , wall2Transform);
	mat_mat4Copy(wall2Transform, plane2.transform);


	Mat4 ceilTransl;
	mat_mat4CreateTranslation(ceilTransl, 0, 15, 0);
	mat_mat4Copy(ceilTransl, plane3.transform);

	Mat4 sphere1sc;
	mat_mat4CreateScaling(sphere1sc, 0.5, 0.5, 0.5);
	Mat4 sphere1tr;
	mat_mat4CreateTranslation(sphere1tr, -2, 2, 0.0f);
	Mat4 sphere1Tr;
	mat_mat4CreateTranslation(sphere1Tr, 0, 2, 0);




	mat_mat4Copy(sphere1Tr, sphere.transform);
	sphere.material.surfaceColor = tuple_createColor(0, 0, 0);
	sphere.material.specular = 0.0f;
	sphere.material.shininess = 0.0f;
	sphere.material.diffuse = 0.0f;
	sphere.material.ambient = 0.0f;
	sphere.material.reflective = 1.0f;
	sphere.material.transparency = 1.0f;
	sphere.material.refractiveIndex = 1.50f;
	// pure glass marbles need all their color removed

	Mat4 s2Tr;
	mat_mat4MultiplyMat4(sphere1tr, sphere1sc,  s2Tr);
	mat_mat4Copy(s2Tr, sphere2.transform);
	sphere2.material.surfaceColor = tuple_createColor(1, 0, 0);



	w.objectCount = 6;
	w.objects = malloc(w.objectCount * sizeof(Shape));
	w.objects[0] = plane1;
	w.objects[1] = plane2;
	plane.material.refractiveIndex = 1.5f;
	w.objects[2] = plane;
	w.objects[3] = plane3;
	w.objects[4] = sphere;
	w.objects[5] = sphere2;
	Mat4 viewMatrix;
	mat_mat4CreateView(viewMatrix, tuple_createPoint(-4.5f, 2.0f,  0.76f), tuple_createPoint(0, 1, 0), tuple_createVector(0, 1, 0));

	Camera camera = camera_createCamera(height, width, rad(55), viewMatrix);

	Canvas canvas =	camera_render(camera, w);

	free(w.objects);

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