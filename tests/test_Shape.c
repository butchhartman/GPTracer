#include "unity.h"
#include "Ray.h"
#include "Shape.h"

void setUp() {

}

void tearDown() {

}

// void test_createSphere() {
//     Material mat = material_createMaterial(tuple_createColor(1, 0, 0), 0.1f, 0.9f, 0.9f, 200.0f);
//     Sphere newSphere1 = sphere_createSphere(tuple_createPoint(0, 1, 0), 1, 0, NULL, mat);

//    TEST_ASSERT_TRUE(tuple_tupleCompare(newSphere1.origin, tuple_createPoint(0, 1, 0))); 
//    TEST_ASSERT_EQUAL(1, newSphere1.radius);
//    TEST_ASSERT_EQUAL(0, newSphere1.instanceID);
// }

// void test_sphereDefaultTransform() {
//     Material mat = material_createMaterial(tuple_createColor(1, 0, 0), 0.1f, 0.9f, 0.9f, 200.0f);
//     Mat4 expected = MAT4_IDENTITY;
//     Sphere newSphere = sphere_createSphere(tuple_createPoint(0, 0, 0), 1, 0, NULL, mat);
//     TEST_ASSERT_TRUE(mat_mat4Compare(expected, newSphere.transform));
// }

// void test_sphereSetTransform(){
//     Material mat = material_createMaterial(tuple_createColor(1, 0, 0), 0.1f, 0.9f, 0.9f, 200.0f);
//     Mat4 expected;
//     mat_mat4CreateTranslation(expected, 2, 3, 4);
//     Sphere newSphere = sphere_createSphere(tuple_createPoint(0, 0, 0), 1, 0, NULL,mat);
//     sphere_setTransform(&newSphere, expected);
//     TEST_ASSERT_TRUE(mat_mat4Compare(expected, newSphere.transform));
// }

// void test_sphereCreateTransform() {
//     Material mat = material_createMaterial(tuple_createColor(1, 0, 0), 0.1f, 0.9f, 0.9f, 200.0f);
//     Mat4 expected;
//     mat_mat4CreateTranslation(expected, 2, 3, 4);
//     Sphere newSphere = sphere_createSphere(tuple_createPoint(0, 0, 0), 1, 0, expected, mat);
//     TEST_ASSERT_TRUE(mat_mat4Compare(expected, newSphere.transform));
// }

// void test_sphereNormalAt() {
//     Material mat = material_createMaterial(tuple_createColor(1, 0, 0), 0.1f, 0.9f, 0.9f, 200.0f);
//     Sphere s = sphere_createSphere(tuple_createPoint(0, 0, 0), 1, 0, NULL, mat);
//     Tuple nx = sphere_normalAt(s, tuple_createPoint(1, 0, 0));
//     Tuple ny = sphere_normalAt(s, tuple_createPoint(0, 1, 0));
//     Tuple nz = sphere_normalAt(s, tuple_createPoint(0, 0, 1));
//     Tuple nn = sphere_normalAt(s, tuple_createPoint(sqrtf(3)/3.0,  sqrtf(3)/3.0,  sqrtf(3)/3.0));

//     TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(1, 0, 0), nx));
//     TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0, 1, 0), ny));
//     TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0, 0, 1), nz));
//     TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(sqrtf(3)/3.0,  sqrtf(3)/3.0,  sqrtf(3)/3.0), nn));
//     TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(sqrtf(3)/3.0,  sqrtf(3)/3.0,  sqrtf(3)/3.0), tuple_vectorNormalize(nn)));
// }
// void test_sphereNormalAtTransformed() {
//     Material mat = material_createMaterial(tuple_createColor(1, 0, 0), 0.1f, 0.9f, 0.9f, 200.0f);
//     Sphere s = sphere_createSphere(tuple_createPoint(0,0,0), 1, 0, NULL, mat);
//     Mat4 translation;
//     mat_mat4CreateTranslation(translation, 0, 1, 0);
//     sphere_setTransform(&s, translation);

//     Tuple n = sphere_normalAt(s, tuple_createPoint(0, 1.70711f, -0.70711f));

//     TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0, 0.70711f, -0.70711f), n));

//     Mat4 scale;
//     Mat4 rotation;
//     Mat4 composite;
//     mat_mat4CreateScaling(scale, 1, 0.5f, 1);
//     mat_mat4CreateRotation_z(rotation, M_PI/5.0f);
//     mat_mat4MultiplyMat4(scale, rotation, composite);

//     sphere_setTransform(&s, composite);

//     Tuple n2 = sphere_normalAt(s, tuple_createPoint(0, sqrtf(2.0f)/2.0f, -sqrtf(2.0f)/2.0f));

//     TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0, 0.97014f, -0.24254), n2));
// }

// void test_sphereMaterial() {
//     Material mat = material_createMaterial(tuple_createColor(1, 0, 0), 1.0f, 10.0f, 5.0f, 100.0f);
//     Sphere sp = sphere_createSphere(tuple_createPoint(0, 0, 0), 1, 0, NULL, mat);

//     TEST_ASSERT_EQUAL_FLOAT(1.0f, sp.material.ambient);
//     TEST_ASSERT_EQUAL_FLOAT(10.0f, sp.material.diffuse);
//     TEST_ASSERT_EQUAL_FLOAT(5.0f, sp.material.specular);
//     TEST_ASSERT_EQUAL_FLOAT(100.0f, sp.material.shininess);
// }

void test_DefaultShapeTransform() {
    Mat4 identity = MAT4_IDENTITY;
    Shape s = shape_createDefaultShape(0, Sphere);
    TEST_ASSERT_TRUE(mat_mat4Compare(s.transform, identity));
}

void test_DefaultShapeAssignTransform() {
    Mat4 translation; 
    mat_mat4CreateTranslation(translation,2, 3, 4);

    Shape s = shape_createDefaultShape(0, Sphere);
    mat_mat4Copy(translation, s.transform);
    TEST_ASSERT_TRUE(mat_mat4Compare(s.transform, translation));
}

void test_DefaultShapeMaterial() {
    Material testmat = material_createMaterial(tuple_createColor(1, 1, 1), 0.1f, 0.9f, 0.9f, 200.0f, 0.0f);

    Shape s = shape_createDefaultShape(0, Sphere);

    TEST_ASSERT_TRUE(tuple_tupleCompare(s.material.surfaceColor, testmat.surfaceColor));
    TEST_ASSERT_EQUAL_FLOAT(s.material.ambient, 0.1f);
    TEST_ASSERT_EQUAL_FLOAT(s.material.diffuse, 0.9f);
    TEST_ASSERT_EQUAL_FLOAT(s.material.specular, 0.9f);
    TEST_ASSERT_EQUAL_FLOAT(s.material.shininess, 200.0f);
}

void test_DefaultShapeAssignMaterial() {

    Material testmat = material_createMaterial(tuple_createColor(1, 1, 1), 1, 1, 1, 1, 0.0f);

    Shape s = shape_createDefaultShape(0, Sphere);
    s = shape_assignMaterial(s, testmat);
    TEST_ASSERT_EQUAL_FLOAT(s.material.ambient, 1);
    TEST_ASSERT_EQUAL_FLOAT(s.material.diffuse, 1);
    TEST_ASSERT_EQUAL_FLOAT(s.material.specular, 1);
    TEST_ASSERT_EQUAL_FLOAT(s.material.shininess, 1);
}

// These should technically go in ray or intersection but whateva
void test_intersectingScaledShapeRay() {
    Ray r = ray_createRay(tuple_createPoint(0, 0, -5), tuple_createVector(0, 0, 1));
    Shape testShape = shape_createDefaultShape(0, Sphere);

    Mat4 Scaling;
    mat_mat4CreateScaling(Scaling, 2, 2, 2);
    mat_mat4Copy(Scaling, testShape.transform);
    
    int length;
    Intersection *xs; 
    Ray transformedRay = ray_rayShapeIntersect(r, testShape, &xs, &length);

    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createPoint(0, 0, -2.5f), transformedRay.origin));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0, 0, 0.5f), transformedRay.direction));
}

void test_intersectingTranslatedShapeRay() {
    Ray r = ray_createRay(tuple_createPoint(0, 0, -5), tuple_createVector(0, 0, 1));
    Shape testShape = shape_createDefaultShape(0, Sphere);

    Mat4 translated;
    mat_mat4CreateTranslation(translated, 5, 0, 0);
    mat_mat4Copy(translated, testShape.transform);

    int length;
    Intersection *xs; 
    Ray transformedRay = ray_rayShapeIntersect(r, testShape, &xs, &length);

    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createPoint(-5, 0, -5), transformedRay.origin));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0, 0, 1), transformedRay.direction));

}

void test_shapeNormalAtTranslated() {
    Shape testShape = shape_createDefaultShape(0, Sphere);

    Mat4 translated;
    mat_mat4CreateTranslation(translated, 0, 1, 0);
    mat_mat4Copy(translated, testShape.transform);
    
    Tuple n = shape_normalAt(testShape, tuple_createPoint(0, 1.70711f, -0.70711f));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0, 0.70711f, -0.70711f), n));

}

void test_shapeNormalAtTransformed() {

    Shape testShape = shape_createDefaultShape(0, Sphere);

    Mat4 scaled;
    mat_mat4CreateScaling(scaled, 1, 0.5f, 1);
    Mat4 rotated; 
    mat_mat4CreateRotation_z(rotated, M_PI/5.0f);

    Mat4 transform;
    mat_mat4MultiplyMat4(scaled, rotated, transform);

    mat_mat4Copy(transform, testShape.transform);
    
    Tuple n = shape_normalAt(testShape, tuple_createPoint(0, sqrtf(2)/2.0f, -sqrtf(2)/2.0f));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0, 0.97014f, -0.24255), n));
}

void test_planeNormalAt() {
    Shape p = shape_createDefaultShape(0, Plane);

    Tuple n1 = shape_normalAt(p, tuple_createPoint(0, 0, 0));
    Tuple n2 = shape_normalAt(p, tuple_createPoint(10, 0, -10));
    Tuple n3 = shape_normalAt(p, tuple_createPoint(-5, 0, 150));

    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0, 1, 0), n1));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0, 1, 0), n2));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0, 1, 0), n3));

}

void test_planeParallelRay() {
    Shape p = shape_createDefaultShape(0, Plane);

    Ray r = ray_createRay(tuple_createPoint(0, 10, 0), tuple_createVector(0, 0, 1));

    int length;
    Intersection *xs;
    ray_rayShapeIntersect(r, p, &xs, &length);

    TEST_ASSERT_TRUE(isnan(xs[0].t));
}

void test_planeCoplanarRay() {
    Shape p = shape_createDefaultShape(0, Plane);

    Ray r = ray_createRay(tuple_createPoint(0, 0, 0), tuple_createVector(0, 0, 1));

    int length;
    Intersection *xs;
    ray_rayShapeIntersect(r, p, &xs, &length);

    TEST_ASSERT_TRUE(isnan(xs[0].t));
}

void test_planeRayAbove() {
    Shape p = shape_createDefaultShape(10, Plane);

    Ray r = ray_createRay(tuple_createPoint(0, 1, 0), tuple_createVector(0, -1, 0));

    int length;
    Intersection *xs;
    ray_rayShapeIntersect(r, p, &xs, &length);

    TEST_ASSERT_EQUAL_INT(1, length);
    TEST_ASSERT_EQUAL_INT(1, xs[0].t);
    TEST_ASSERT_TRUE(xs[0].object .instanceID == p.instanceID);
}

void test_planeRayBelow() {
    Shape p = shape_createDefaultShape(10, Plane);

    Ray r = ray_createRay(tuple_createPoint(0, -1, 0), tuple_createVector(0, 1, 0));

    int length;
    Intersection *xs;
    ray_rayShapeIntersect(r, p, &xs, &length);

    TEST_ASSERT_EQUAL_INT(1, length);
    TEST_ASSERT_EQUAL_INT(1, xs[0].t);
    TEST_ASSERT_TRUE(xs[0].object .instanceID == p.instanceID);
}

void test_rayIntersectCube() {
    Shape cube = shape_createDefaultShape(0, Cube);

    Ray r;
    int xsLength;
    Intersection *xs;
    for (int i = 0; i < 7; i++) {
        switch (i)
        {
        case 0:
           r = ray_createRay(tuple_createPoint(5, 0.5f, 0), tuple_createVector(-1, 0, 0));
            ray_rayCubeIntersect(r, cube, &xs, &xsLength);
            TEST_ASSERT_EQUAL_INT(2, xsLength);
            TEST_ASSERT_EQUAL_FLOAT(4, xs[0].t);
            TEST_ASSERT_EQUAL_FLOAT(6, xs[1].t);
            free(xs);
            break;
       
        case 1:
            r = ray_createRay(tuple_createPoint(-5, 0.5f, 0), tuple_createVector(1, 0, 0));
            ray_rayCubeIntersect(r, cube, &xs, &xsLength);
            TEST_ASSERT_EQUAL_INT(2, xsLength);
            TEST_ASSERT_EQUAL_FLOAT(4, xs[0].t);
            TEST_ASSERT_EQUAL_FLOAT(6, xs[1].t);
            free(xs);
            break;
        
        case 2:
            r = ray_createRay(tuple_createPoint(0.5f, 5, 0), tuple_createVector(0, -1, 0));
            ray_rayCubeIntersect(r, cube, &xs, &xsLength);
            TEST_ASSERT_EQUAL_INT(2, xsLength);
            TEST_ASSERT_EQUAL_FLOAT(4, xs[0].t);
            TEST_ASSERT_EQUAL_FLOAT(6, xs[1].t);
            free(xs);
            break;
        
        case 3:
            r = ray_createRay(tuple_createPoint(0.5f, -5, 0), tuple_createVector(0, 1, 0));
            ray_rayCubeIntersect(r, cube, &xs, &xsLength);
            TEST_ASSERT_EQUAL_INT(2, xsLength);
            TEST_ASSERT_EQUAL_FLOAT(4, xs[0].t);
            TEST_ASSERT_EQUAL_FLOAT(6, xs[1].t);
            free(xs);
            break;

        case 4:
            r = ray_createRay(tuple_createPoint(0.5f, 0, 5), tuple_createVector(0, 0, -1));
            ray_rayCubeIntersect(r, cube, &xs, &xsLength);
            TEST_ASSERT_EQUAL_INT(2, xsLength);
            TEST_ASSERT_EQUAL_FLOAT(4, xs[0].t);
            TEST_ASSERT_EQUAL_FLOAT(6, xs[1].t);
            free(xs);
            break;
        
        case 5:
            r = ray_createRay(tuple_createPoint(0.5f, 0, -5), tuple_createVector(0, 0, 1));
            ray_rayCubeIntersect(r, cube, &xs, &xsLength);
            TEST_ASSERT_EQUAL_INT(2, xsLength);
            TEST_ASSERT_EQUAL_FLOAT(4, xs[0].t);
            TEST_ASSERT_EQUAL_FLOAT(6, xs[1].t);
            free(xs);
            break;

        case 6:
            r = ray_createRay(tuple_createPoint(0, 0.5f, 0), tuple_createVector(0, 0, 1));
            ray_rayCubeIntersect(r, cube, &xs, &xsLength);
            TEST_ASSERT_EQUAL_INT(2, xsLength);
            TEST_ASSERT_EQUAL_FLOAT(-1, xs[0].t);
            TEST_ASSERT_EQUAL_FLOAT(1, xs[1].t);
            free(xs);
            break;
    
        default:
            break;
        }
    }

}

void test_rayCubeMiss() {
    Shape cube = shape_createDefaultShape(0, Cube);
    Ray r;
    int xsLength;
    Intersection *xs;

for (int i = 0; i < 6; i++) {
        switch (i)
        {
        case 0:
           r = ray_createRay(tuple_createPoint(-2, 0, 0), tuple_createVector(0.2673f, 0.5345f, 0.8018f));
            ray_rayCubeIntersect(r, cube, &xs, &xsLength);
            TEST_ASSERT_EQUAL_INT(2, xsLength);
            TEST_ASSERT_EQUAL_FLOAT(NAN, xs[0].t);
            TEST_ASSERT_EQUAL_FLOAT(NAN, xs[1].t);
            free(xs);
            break;
       
        case 1:
            r = ray_createRay(tuple_createPoint(0, -2, 0), tuple_createVector(0.8018f, 0.2673f, 0.5345f));
            ray_rayCubeIntersect(r, cube, &xs, &xsLength);
            TEST_ASSERT_EQUAL_INT(2, xsLength);
            TEST_ASSERT_EQUAL_FLOAT(NAN, xs[0].t);
            TEST_ASSERT_EQUAL_FLOAT(NAN, xs[1].t);
            free(xs);
            break;
        
        case 2:
            r = ray_createRay(tuple_createPoint(0, 0, -2), tuple_createVector(0.5345f, 0.8018f, 0.2674f));
            ray_rayCubeIntersect(r, cube, &xs, &xsLength);
            TEST_ASSERT_EQUAL_INT(2, xsLength);
            TEST_ASSERT_EQUAL_FLOAT(NAN, xs[0].t);
            TEST_ASSERT_EQUAL_FLOAT(NAN, xs[1].t);
            free(xs);
            break;
        
        case 3:
            r = ray_createRay(tuple_createPoint(2, 0, 2), tuple_createVector(0, 0, -1));
            ray_rayCubeIntersect(r, cube, &xs, &xsLength);
            TEST_ASSERT_EQUAL_INT(2, xsLength);
            TEST_ASSERT_EQUAL_FLOAT(NAN, xs[0].t);
            TEST_ASSERT_EQUAL_FLOAT(NAN, xs[1].t);
            free(xs);
            break;

        case 4:
            r = ray_createRay(tuple_createPoint(0, 2, 2), tuple_createVector(0, -1, 0));
            ray_rayCubeIntersect(r, cube, &xs, &xsLength);
            TEST_ASSERT_EQUAL_INT(2, xsLength);
            TEST_ASSERT_EQUAL_FLOAT(NAN, xs[0].t);
            TEST_ASSERT_EQUAL_FLOAT(NAN, xs[1].t);
            free(xs);
            break;
        
        case 5:
            r = ray_createRay(tuple_createPoint(2, 2, 0), tuple_createVector(-1, 0, 0));
            ray_rayCubeIntersect(r, cube, &xs, &xsLength);
            TEST_ASSERT_EQUAL_INT(2, xsLength);
            TEST_ASSERT_EQUAL_FLOAT(NAN, xs[0].t);
            TEST_ASSERT_EQUAL_FLOAT(NAN, xs[1].t);
            free(xs);
            break;

        default:
            break;
        }
    }
}

void test_cubeNormal() {
    Shape cube = shape_createDefaultShape(0, Cube);
    Tuple normal;
    for (int i = 0; i < 7; i++) {

        switch(i) {
            case 0:
                normal = shape_cubeNormalAt(cube, tuple_createPoint(1, 0.5f, -0.8f));
                TEST_ASSERT_TRUE(tuple_tupleCompare(normal, tuple_createVector(1, 0, 0)));
                break;

            case 1:
                normal = shape_cubeNormalAt(cube, tuple_createPoint(-1, 0.2f, 0.9f));
                TEST_ASSERT_TRUE(tuple_tupleCompare(normal, tuple_createVector(-1, 0, 0)));
                break;

            case 2:
                normal = shape_cubeNormalAt(cube, tuple_createPoint(-0.4f, 1, -0.1f));
                TEST_ASSERT_TRUE(tuple_tupleCompare(normal, tuple_createVector(0, 1, 0)));
                break;

            case 3:
                normal = shape_cubeNormalAt(cube, tuple_createPoint(0.3f, -1, -0.7f));
                TEST_ASSERT_TRUE(tuple_tupleCompare(normal, tuple_createVector(0, -1, 0)));
                break;

            case 4:
                normal = shape_cubeNormalAt(cube, tuple_createPoint(-0.6f, 0.3f, 1));
                TEST_ASSERT_TRUE(tuple_tupleCompare(normal, tuple_createVector(0, 0, 1)));
                break;

            case 5:
                normal = shape_cubeNormalAt(cube, tuple_createPoint(0.4f, 0.4f, -1));
                TEST_ASSERT_TRUE(tuple_tupleCompare(normal, tuple_createVector(0, 0, -1)));
                break;

            case 6:
                normal = shape_cubeNormalAt(cube, tuple_createPoint(1, 1, 1));
                TEST_ASSERT_TRUE(tuple_tupleCompare(normal, tuple_createVector(1, 0, 0)));
                break;

            case 7:
                normal = shape_cubeNormalAt(cube, tuple_createPoint(-1, -1, -1));
                TEST_ASSERT_TRUE(tuple_tupleCompare(normal, tuple_createVector(-1, 0, 0)));
                break;

            default:
                break;
        }
    }
}

void test_cylinderMiss() {
    Shape cyl = shape_createDefaultShape(0, Cylinder);
    Tuple direction;
    Ray r;
    int length;
    Intersection *xs;

    direction = tuple_vectorNormalize(tuple_createVector(0, 1, 0));
    r = ray_createRay(tuple_createPoint(1, 0, 0), direction);
    ray_rayCylinderIntersect(r, cyl, &xs, &length);
    TEST_ASSERT_EQUAL_INT(2, length);
    TEST_ASSERT_TRUE(isnan(xs[0].t));
    TEST_ASSERT_TRUE(isnan(xs[1].t));
    free(xs);

    direction = tuple_vectorNormalize(tuple_createVector(0, 1, 0));
    r = ray_createRay(tuple_createPoint(0, 0, 0), direction);
    ray_rayCylinderIntersect(r, cyl, &xs, &length);
    TEST_ASSERT_EQUAL_INT(2, length);
    TEST_ASSERT_TRUE(isnan(xs[0].t));
    TEST_ASSERT_TRUE(isnan(xs[1].t));
    free(xs);

    direction = tuple_vectorNormalize(tuple_createVector(1, 1, 1));
    r = ray_createRay(tuple_createPoint(0, 0, -5), direction);
    ray_rayCylinderIntersect(r, cyl, &xs, &length);
    TEST_ASSERT_EQUAL_INT(2, length);
    TEST_ASSERT_TRUE(isnan(xs[0].t));
    TEST_ASSERT_TRUE(isnan(xs[1].t));
    free(xs);

}

void test_cylinderHit() {
    Shape cyl = shape_createDefaultShape(0, Cylinder);
    Tuple direction;
    Ray r;
    int length;
    Intersection *xs;

    direction = tuple_vectorNormalize(tuple_createVector(0, 0, 1));
    r = ray_createRay(tuple_createPoint(1, 0, -5), direction);
    ray_rayCylinderIntersect(r, cyl, &xs, &length);
    TEST_ASSERT_EQUAL_INT(2, length);
    TEST_ASSERT_TRUE(xs[0].t == 5);
    TEST_ASSERT_TRUE(xs[1].t == 5);
    free(xs);

    direction = tuple_vectorNormalize(tuple_createVector(0, 0, 1));
    r = ray_createRay(tuple_createPoint(0, 0, -5), direction);
    ray_rayCylinderIntersect(r, cyl, &xs, &length);
    TEST_ASSERT_EQUAL_INT(2, length);
    TEST_ASSERT_TRUE(xs[0].t == 4);
    TEST_ASSERT_TRUE(xs[1].t == 6);
    free(xs);

    direction = tuple_vectorNormalize(tuple_createVector(0.1f, 1, 1));
    r = ray_createRay(tuple_createPoint(0.5f, 0, -5), direction);
    ray_rayCylinderIntersect(r, cyl, &xs, &length);
    TEST_ASSERT_EQUAL_INT(2, length);
    TEST_ASSERT_EQUAL_FLOAT(6.80798f, xs[0].t);
    TEST_ASSERT_EQUAL_FLOAT(7.08872, xs[1].t );
    free(xs);
}

void test_cylinderNormals() {
    Shape cyl = shape_createDefaultShape(0, Cylinder);
    Tuple n;

    n = shape_cylinderNormalAt(cyl, tuple_createPoint(1, 0, 0));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(1, 0 ,0), n));
    
    n = shape_cylinderNormalAt(cyl, tuple_createPoint(0, -5, -1));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0, 0 ,-1), n));

    n = shape_cylinderNormalAt(cyl, tuple_createPoint(0, -2, 1));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(0, 0 ,1), n));

    n = shape_cylinderNormalAt(cyl, tuple_createPoint(-1, 1, 0));
    TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createVector(-1, 0 ,0), n));
}

void test_cylinderMinMaxBounds() {
    Shape cyl = shape_createDefaultShape(0, Cylinder);
    TEST_ASSERT_TRUE(cyl.minimum == -INFINITY);
    TEST_ASSERT_TRUE(cyl.maximum ==  INFINITY);
}

void test_cylinderTruncated() {
    Shape cyl = shape_createDefaultShape(0, Cylinder);
    cyl.minimum = 1;
    cyl.maximum = 2;

    Tuple direction;
    Ray r;
    int length;
    Intersection *xs;

    direction = tuple_vectorNormalize(tuple_createVector(0.1f, 1, 0));
    r = ray_createRay(tuple_createPoint(0, 1.5f, 0), direction);
    ray_rayCylinderIntersect(r, cyl, &xs, &length);
    TEST_ASSERT_EQUAL_INT(2, length);
    TEST_ASSERT_TRUE(isnan(xs[0].t));
    TEST_ASSERT_TRUE(isnan(xs[1].t));

    direction = tuple_vectorNormalize(tuple_createVector(0, 0, 1));
    r = ray_createRay(tuple_createPoint(0, 3, -5), direction);
    ray_rayCylinderIntersect(r, cyl, &xs, &length);
    TEST_ASSERT_EQUAL_INT(2, length);
    TEST_ASSERT_TRUE(isnan(xs[0].t));
    TEST_ASSERT_TRUE(isnan(xs[1].t));

    direction = tuple_vectorNormalize(tuple_createVector(0, 0, 1));
    r = ray_createRay(tuple_createPoint(0, 0, -5), direction);
    ray_rayCylinderIntersect(r, cyl, &xs, &length);
    TEST_ASSERT_EQUAL_INT(2, length);
    TEST_ASSERT_TRUE(isnan(xs[0].t));
    TEST_ASSERT_TRUE(isnan(xs[1].t));

    direction = tuple_vectorNormalize(tuple_createVector(0, 0, 1));
    r = ray_createRay(tuple_createPoint(0, 2, -5), direction);
    ray_rayCylinderIntersect(r, cyl, &xs, &length);
    TEST_ASSERT_EQUAL_INT(2, length);
    TEST_ASSERT_TRUE(isnan(xs[0].t));
    TEST_ASSERT_TRUE(isnan(xs[1].t));

    direction = tuple_vectorNormalize(tuple_createVector(0, 0, 1));
    r = ray_createRay(tuple_createPoint(0, 1, -5), direction);
    ray_rayCylinderIntersect(r, cyl, &xs, &length);
    TEST_ASSERT_EQUAL_INT(2, length);
    TEST_ASSERT_TRUE(isnan(xs[0].t));
    TEST_ASSERT_TRUE(isnan(xs[1].t));

    direction = tuple_vectorNormalize(tuple_createVector(0, 0, 1));
    r = ray_createRay(tuple_createPoint(0, 1.5f, -2), direction);
    ray_rayCylinderIntersect(r, cyl, &xs, &length);
    TEST_ASSERT_EQUAL_INT(2, length);
    TEST_ASSERT_TRUE(!isnan(xs[0].t));
    TEST_ASSERT_TRUE(!isnan(xs[1].t));
}

void test_cylindersCanBeClosed() {
    Shape cyl = shape_createDefaultShape(0, Cylinder);
    TEST_ASSERT_EQUAL_INT(0, cyl.closed);
}

void test_cylinderCapped() {
    Shape cyl = shape_createDefaultShape(0, Cylinder);
    cyl.minimum = 1;
    cyl.maximum = 2;
    cyl.closed = 1;
    Tuple direction;
    Ray r;
    int length;
    Intersection *xs;

    direction = tuple_vectorNormalize(tuple_createVector(0, -1, 0));
    r = ray_createRay(tuple_createPoint(0, 3, 0), direction);
    ray_rayCylinderIntersect(r, cyl, &xs, &length);
    TEST_ASSERT_EQUAL_INT(2, length);
    TEST_ASSERT_TRUE(!isnan(xs[0].t));
    TEST_ASSERT_TRUE(!isnan(xs[1].t));
    free(xs);

    direction = tuple_vectorNormalize(tuple_createVector(0, -1, 2));
    r = ray_createRay(tuple_createPoint(0, 3, -2), direction);
    ray_rayCylinderIntersect(r, cyl, &xs, &length);
    TEST_ASSERT_EQUAL_INT(2, length);
    TEST_ASSERT_TRUE(!isnan(xs[0].t));
    TEST_ASSERT_TRUE(!isnan(xs[1].t));
    free(xs);

    direction = tuple_vectorNormalize(tuple_createVector(0, -1, 1));
    r = ray_createRay(tuple_createPoint(0, 4, -2), direction);
    ray_rayCylinderIntersect(r, cyl, &xs, &length);
    TEST_ASSERT_EQUAL_INT(2, length);
    TEST_ASSERT_TRUE(!isnan(xs[0].t));
    TEST_ASSERT_TRUE(!isnan(xs[1].t));
    free(xs);

    direction = tuple_vectorNormalize(tuple_createVector(0, 1, 2));
    r = ray_createRay(tuple_createPoint(0, 0, -2), direction);
    ray_rayCylinderIntersect(r, cyl, &xs, &length);
    TEST_ASSERT_EQUAL_INT(2, length);
    TEST_ASSERT_TRUE(!isnan(xs[0].t));
    TEST_ASSERT_TRUE(!isnan(xs[1].t));
    free(xs);

    direction = tuple_vectorNormalize(tuple_createVector(0, 1, 1));
    r = ray_createRay(tuple_createPoint(0, -1, -2), direction);
    ray_rayCylinderIntersect(r, cyl, &xs, &length);
    TEST_ASSERT_EQUAL_INT(2, length);
    TEST_ASSERT_TRUE(!isnan(xs[0].t));
    TEST_ASSERT_TRUE(!isnan(xs[1].t));
    free(xs);

}

void test_cylinderCapNormals() {
    Shape cyl = shape_createDefaultShape(0, Cylinder);
    cyl.minimum = 1;
    cyl.maximum = 2;
    cyl.closed = 1;

    Tuple n;

    n = shape_cylinderNormalAt(cyl, tuple_createPoint(0, 1, 0));
    TEST_ASSERT_TRUE(tuple_tupleCompare(n, tuple_createVector(0, -1, 0)));

    n = shape_cylinderNormalAt(cyl, tuple_createPoint(0.5f, 1, 0));
    TEST_ASSERT_TRUE(tuple_tupleCompare(n, tuple_createVector(0, -1, 0)));

    n = shape_cylinderNormalAt(cyl, tuple_createPoint(0, 1, 0.5f));
    TEST_ASSERT_TRUE(tuple_tupleCompare(n, tuple_createVector(0, -1, 0)));

    n = shape_cylinderNormalAt(cyl, tuple_createPoint(0, 2, 0));
    TEST_ASSERT_TRUE(tuple_tupleCompare(n, tuple_createVector(0, 1, 0)));

    n = shape_cylinderNormalAt(cyl, tuple_createPoint(0.5f, 2, 0));
    TEST_ASSERT_TRUE(tuple_tupleCompare(n, tuple_createVector(0, 1, 0)));

    n = shape_cylinderNormalAt(cyl, tuple_createPoint(0, 2, 0.5f));
    TEST_ASSERT_TRUE(tuple_tupleCompare(n, tuple_createVector(0, 1, 0)));
}

void test_rayIntersectCone() {
    Shape shape = shape_createDefaultShape(0, Cone);
    Tuple direction;
    Ray r;
    int length;
    Intersection *xs;


    direction = tuple_vectorNormalize(tuple_createVector(0, 0, 1));
    r = ray_createRay(tuple_createPoint(0, 0, -5), direction);
    ray_rayConeIntersect(r, shape, &xs, &length);
    TEST_ASSERT_EQUAL_INT(4, length);
    TEST_ASSERT_EQUAL_FLOAT(5, xs[0].t);
    TEST_ASSERT_EQUAL_FLOAT(5, xs[1].t);
    free(xs);

    direction = tuple_vectorNormalize(tuple_createVector(1, 1, 1));
    r = ray_createRay(tuple_createPoint(0, 0, -5), direction);
    ray_rayConeIntersect(r, shape, &xs, &length);
    TEST_ASSERT_EQUAL_INT(4, length);
    TEST_ASSERT_EQUAL_FLOAT(8.66025f, xs[0].t);
    TEST_ASSERT_EQUAL_FLOAT(8.66025f, xs[1].t);
    free(xs);

    direction = tuple_vectorNormalize(tuple_createVector(-0.5f, -1, 1));
    r = ray_createRay(tuple_createPoint(1, 1, -5), direction);
    ray_rayConeIntersect(r, shape, &xs, &length);
    TEST_ASSERT_EQUAL_INT(4, length);
    TEST_ASSERT_EQUAL_FLOAT(4.55006f, xs[0].t);
    TEST_ASSERT_EQUAL_FLOAT(49.44994f, xs[1].t);
    free(xs);
}

void test_coneRayParallel() {
    Shape shape = shape_createDefaultShape(0, Cone);
    Tuple direction = tuple_vectorNormalize(tuple_createVector(0, 1, 1));
    Ray r = ray_createRay(tuple_createPoint(0, 0, -1), direction);
    int length;
    Intersection *xs;

    ray_rayConeIntersect(r, shape, &xs, &length);
    TEST_ASSERT_EQUAL_FLOAT(4, length);
    TEST_ASSERT_EQUAL_FLOAT(0.35355f, xs[0].t);
    TEST_ASSERT_TRUE(isnan(xs[1].t));

}

void test_coneEndCaps() {
    Shape shape = shape_createDefaultShape(0, Cone);
    shape.minimum = -0.5f;
    shape.maximum = 0.5f;
    shape.closed = 1;
    
    Tuple direction;
    Ray r;
    int length;
    Intersection *xs;

    direction = tuple_vectorNormalize(tuple_createVector(0, 1, 0));
    r = ray_createRay(tuple_createPoint(0, 0, -5), direction);
    ray_rayConeIntersect(r, shape, &xs, &length);
    TEST_ASSERT_EQUAL_FLOAT(4, length);
    TEST_ASSERT_TRUE(isnan(xs[0].t));
    TEST_ASSERT_TRUE(isnan(xs[1].t));
    TEST_ASSERT_TRUE(isnan(xs[2].t));
    TEST_ASSERT_TRUE(isnan(xs[3].t));
    free(xs);
    direction = tuple_vectorNormalize(tuple_createVector(0, 1, 1));
    r = ray_createRay(tuple_createPoint(0, 0, -0.25f), direction);
    ray_rayConeIntersect(r, shape, &xs, &length);
    TEST_ASSERT_EQUAL_FLOAT(4, length);
    TEST_ASSERT_TRUE(!isnan(xs[0].t));
    TEST_ASSERT_TRUE(isnan(xs[1].t));
    TEST_ASSERT_TRUE(isnan(xs[2].t));
    TEST_ASSERT_TRUE(!isnan(xs[3].t));
    free(xs);
    direction = tuple_vectorNormalize(tuple_createVector(0, 1, 0));
    r = ray_createRay(tuple_createPoint(0, 0, -0.25f), direction);
    ray_rayConeIntersect(r, shape, &xs, &length);
    TEST_ASSERT_EQUAL_FLOAT(4, length);
    TEST_ASSERT_TRUE(!isnan(xs[0].t));
    TEST_ASSERT_TRUE(!isnan(xs[1].t));
    TEST_ASSERT_TRUE(!isnan(xs[2].t));
    TEST_ASSERT_TRUE(!isnan(xs[3].t));
    free(xs);
}

void test_coneNormalAt() {
    Shape cone = shape_createDefaultShape(0, Cone);
    Tuple n;

    n = shape_coneNormalAt(cone, tuple_createPoint(0, 0, 0));
    TEST_ASSERT_TRUE(tuple_tupleCompare(n, tuple_createVector(0 ,0 ,0)));

    n = shape_coneNormalAt(cone, tuple_createPoint(1, 1, 1));
    TEST_ASSERT_TRUE(tuple_tupleCompare(n, tuple_createVector(1 ,-sqrtf(2.0f) ,1)));
    
    n = shape_coneNormalAt(cone, tuple_createPoint(-1, -1, 0));
    TEST_ASSERT_TRUE(tuple_tupleCompare(n, tuple_createVector(-1 ,1 ,0)));
}

int main() {
    RUN_TEST(test_DefaultShapeMaterial);
    RUN_TEST(test_DefaultShapeAssignMaterial);
    RUN_TEST(test_DefaultShapeTransform);
    RUN_TEST(test_DefaultShapeAssignTransform);
    RUN_TEST(test_intersectingTranslatedShapeRay);
    RUN_TEST(test_intersectingScaledShapeRay);
    RUN_TEST(test_shapeNormalAtTranslated);
    RUN_TEST(test_shapeNormalAtTransformed);
    RUN_TEST(test_planeCoplanarRay);
    RUN_TEST(test_planeNormalAt);
    RUN_TEST(test_planeParallelRay);
    RUN_TEST(test_planeRayAbove);
    RUN_TEST(test_planeRayBelow);
    RUN_TEST(test_rayIntersectCube);
    RUN_TEST(test_rayCubeMiss);
    RUN_TEST(test_cubeNormal);
    RUN_TEST(test_cylinderMiss);
    RUN_TEST(test_cylinderHit);
    RUN_TEST(test_cylinderNormals);
    RUN_TEST(test_cylinderMinMaxBounds);
    RUN_TEST(test_cylinderTruncated);
    RUN_TEST(test_cylindersCanBeClosed);
    RUN_TEST(test_cylinderCapped);
    RUN_TEST(test_cylinderCapNormals);
    RUN_TEST(test_rayIntersectCone);
    RUN_TEST(test_coneRayParallel);
    RUN_TEST(test_coneEndCaps);
    RUN_TEST(test_coneNormalAt);
    return UNITY_END();
}