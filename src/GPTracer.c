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

	if (argc > 0) {
		for (int i = 0; i < argc; i++) {
			printf("%s", argv[i]);
		
			if (strcmp("--pickleRick", argv[i]) == 0) {
				printf("lol\n");
			}
		}
	}

	Canvas canvas = canvas_createCanvas(250, 250);
	Tuple drawColor = tuple_createColor(0.8f, 0.2f, 0.2f);

	Sphere sphere = sphere_createSphere(tuple_createPoint(0,0,0), 1, 0, NULL);

	Mat4 scaling;
	Mat4 skew;
	Mat4 trasnform;

	// mat_mat4CreateScaling(scaling, 0.6, 1.2, 1);
	// mat_mat4CreateShearing(skew, 1, 0, 0, 0, 0, 0);

	// mat_mat4MultiplyMat4(skew, scaling, trasnform);

	// sphere_setTransform(&sphere, trasnform);


	float wall_z = 10;
	float wall_size = 7;
	float pixel_size = wall_size/((float)canvas.width);
	float half = wall_size / 2.0f;

	Tuple rayOrigin = tuple_createPoint(0, 0, -5);

	for (int i = 0; i < canvas.height; i++) {
		float world_y = half - pixel_size * i; // Converts canvas-space height coordinates(0 to -250) to world space coordinates (3.5 to -3.5)

		for (int j = 0; j < canvas.width; j++){
			float world_x = -half + pixel_size * j; // Converts canvas-space width coordinates (0 to 250) to world space coordinates(-3.5, 3.5)

			Tuple position = tuple_createPoint(world_x, world_y, wall_z);

			Ray r = ray_createRay(rayOrigin, tuple_vectorNormalize(tuple_tupleSub(position, rayOrigin)));
			Intersection xss[2];
			ray_raySphereIntersect(r, sphere, xss);
			
			Intersection xs = intersection_determineHit(xss, 2);
			if(!isnan(xs.t)) {
				canvas_writePixel(&canvas, drawColor, j, i);
			}
		}

	}

	int length;
	ppm_writePPM(canvas_canvasToPPM(canvas, &length));



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