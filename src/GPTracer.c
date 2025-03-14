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
	// World
	World world;
	world.light = pointlight_createPointlight(tuple_createPoint(-10, 10, -10), tuple_createColor(1, 1, 1));
	// Camera
	Mat4 viewTransform;
	mat_mat4CreateView(viewTransform, tuple_createPoint(0, 1.5, -5), tuple_createPoint(0, 1, 0), tuple_createVector(0, 1, 0));
	Camera camera = camera_createCamera(350, 250, rad(55), viewTransform);
	// Floor
	Mat4 floorScaling;
	mat_mat4CreateScaling(floorScaling, 10, 0.01f, 10);
	Material floorMat = material_createMaterial(tuple_createColor(1.0f, 0.9f, 0.9f), 0.1f, 0.9f, 0.0f, 0.0f);
	
	Sphere floor = sphere_createSphere(tuple_createPoint(0, 0, 0), 1, 0, floorScaling, floorMat);
	
	// Left wall
	Mat4 LWtr;
	mat_mat4CreateTranslation(LWtr, 0, 0, 5);
	Mat4 LWry;
	mat_mat4CreateRotation_y(LWry, -M_PI_4);
	Mat4 LWrx;
	mat_mat4CreateRotation_x(LWrx, M_PI_2);
	Mat4 LWsc;
	mat_mat4CreateScaling(LWsc, 10, 0.01f, 10);

	
	Mat4 leftWallTransform;
	mat_mat4MultiplyMat4(LWtr, LWry, leftWallTransform);
	mat_mat4MultiplyMat4(leftWallTransform, LWrx, leftWallTransform);
	mat_mat4MultiplyMat4(leftWallTransform, LWsc, leftWallTransform);
	Sphere leftWall = sphere_createSphere(tuple_createPoint(0, 0, 0), 1, 1, leftWallTransform, floorMat);
	// Right wall
	Mat4 RWtr;
	mat_mat4CreateTranslation(RWtr, 0, 0, 5);
	Mat4 RWry;
	mat_mat4CreateRotation_y(RWry, M_PI_4);
	Mat4 RWrx;
	mat_mat4CreateRotation_x(RWrx, M_PI_2);
	Mat4 RWsc;
	mat_mat4CreateScaling(RWsc, 10, 0.01f, 10);

	
	Mat4 rightWallTransform;
	mat_mat4MultiplyMat4(RWtr, RWry, rightWallTransform);
	mat_mat4MultiplyMat4(rightWallTransform, RWrx, rightWallTransform);
	mat_mat4MultiplyMat4(rightWallTransform, RWsc, rightWallTransform);
	
	Sphere rightWall= sphere_createSphere(tuple_createPoint(0, 0, 0), 1, 2, rightWallTransform, floorMat);
	// Green sphere

	Mat4 gSpheretr;
	mat_mat4CreateTranslation(gSpheretr, -0.5f, 1, 0.5f);
	Material gSphereMat = material_createMaterial(tuple_createColor(0.1f, 1, 0.5f), 0.1f, 0.7f, 0.3f, 200.0f);
	Sphere gSphere = sphere_createSphere(tuple_createPoint(0, 0, 0), 1, 3, gSpheretr, gSphereMat);

	// Small green sphere
	Mat4 smGSphereTr;
	mat_mat4CreateTranslation(smGSphereTr, 1.5f, 0.5f, -0.5f);
	Mat4 smGSphereSc;
	mat_mat4CreateScaling(smGSphereSc, 0.5f, 0.5f, 0.5f);

	Mat4 smGSphereTransform;
	mat_mat4MultiplyMat4(smGSphereTr, smGSphereSc, smGSphereTransform);
	Material smGSphereMat = material_createMaterial(tuple_createColor(0.5f, 1, 0.1f), 0.1f, 0.7f, 0.3f, 200.0f);
	Sphere smGSphere = sphere_createSphere(tuple_createPoint(0, 0, 0), 1, 4, smGSphereTransform, smGSphereMat);

	// Small yellow sphere
	Mat4 smYSphereTr;
	mat_mat4CreateTranslation(smYSphereTr, -1.5f, 0.33f, -0.75f);
	Mat4 smYSphereSc;
	mat_mat4CreateScaling(smYSphereSc, 0.33f, 0.33f, 0.33f);

	Mat4 smYSphereTransform;
	mat_mat4MultiplyMat4(smYSphereTr, smYSphereSc, smYSphereTransform);
	Material smYSphereMat = material_createMaterial(tuple_createColor(1, 0.8f, 0.1f), 0.1f, 0.7f, 0.3f, 200.0f);
	Sphere smYSphere = sphere_createSphere(tuple_createPoint(0, 0, 0), 1, 5, smYSphereTransform, smYSphereMat);




	//Final init
	world.sphereCount = 6;
	world.spheres = malloc(sizeof(Sphere) * world.sphereCount);
	world.spheres[0] = floor;
	world.spheres[1] = leftWall;
	world.spheres[2] = rightWall;
	world.spheres[3] = gSphere;
	world.spheres[4] = smGSphere;
	world.spheres[5] = smYSphere;

	Canvas canvas = camera_render(camera, world);

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