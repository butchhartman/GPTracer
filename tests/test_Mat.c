#include "unity.h"
#include "Mat.h"

void setUp() {

}

void tearDown() {

}

void test_mat2ConstructionTest() {
	Mat2 mat = {
		{-3, 5},
		{1, -2}
	};

	TEST_ASSERT_EQUAL_FLOAT(-3, mat[0][0]);
	TEST_ASSERT_EQUAL_FLOAT(5, mat[0][1]);
	TEST_ASSERT_EQUAL_FLOAT(1, mat[1][0]);
	TEST_ASSERT_EQUAL_FLOAT(-2, mat[1][1]);
}

void test_mat3ConstructionTest() {
	Mat3 mat = {
		{-3, 5, 0},
		{1, -2, -7},
		{0, 1, 1}
	};
	TEST_ASSERT_EQUAL_FLOAT(-3, mat[0][0]);
	TEST_ASSERT_EQUAL_FLOAT(-2, mat[1][1]);
	TEST_ASSERT_EQUAL_FLOAT(1, mat[2][2]);

}

void test_mat4ConstructionTest() {
	Mat4 mat = {
		{1, 2, 3, 4},
		{5.5, 6.5, 7.5, 8.5},
		{9, 10, 11, 12},
		{13.5, 14.5, 15.5, 16.5}
	};

	TEST_ASSERT_EQUAL_FLOAT(1, mat[0][0]);
	TEST_ASSERT_EQUAL_FLOAT(4, mat[0][3]);
	TEST_ASSERT_EQUAL_FLOAT(5.5, mat[1][0]);
	TEST_ASSERT_EQUAL_FLOAT(7.5, mat[1][2]);
	TEST_ASSERT_EQUAL_FLOAT(11, mat[2][2]);
	TEST_ASSERT_EQUAL_FLOAT(13.5, mat[3][0]);
	TEST_ASSERT_EQUAL_FLOAT(15.5, mat[3][2]);

}

void test_matxCompare() {
	Mat4 mat4o = {
		{1,2,3,4},
		{5,6,7,8},
		{9,1,2,3},
		{4,5,6,7}
	};

	Mat4 mat4i = {
	{1,2,3,4},
	{5,6,7,8},
	{9,1,2,3},
	{4,5,6,7}
	};

	Mat4 mat4d = {
	{1,2,3,4},
	{5,6,8,8},
	{9,1,2,3},
	{4,5,6,7}
	};

	TEST_ASSERT_EQUAL_INT(1, mat_mat4Compare(mat4o, mat4i));
	TEST_ASSERT_EQUAL_INT(0, mat_mat4Compare(mat4o, mat4d));
	//
	Mat3 mat3o = {
	{1,2,3},
	{5,6,7},
	{9,1,2},

	};

	Mat3 mat3i = {
	{1,2,3},
	{5,6,7},
	{9,1,2},

	};

	Mat3 mat3d = {
	{1,2,3},
	{5,6,7},
	{9,1,3},
	};

	TEST_ASSERT_EQUAL_INT(1, mat_mat3Compare(mat3o, mat3i));
	TEST_ASSERT_EQUAL_INT(0, mat_mat3Compare(mat3o, mat3d));
	//
	Mat2 mat2o = {
	{1,2},
	{5,6},
	};

	Mat2 mat2i = {
	{1,2},
	{5,6},
	};

	Mat2 mat2d = {
	{1,2},
	{5,7},
	};
	TEST_ASSERT_EQUAL_INT(1, mat_mat2Compare(mat2o, mat2i));
	TEST_ASSERT_EQUAL_INT(0, mat_mat2Compare(mat2o, mat2d));
}

void test_mat_mat4MultiplyMat4() {
	Mat4 a = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 8, 7, 6},
		{5, 4, 3, 2}
	};
	Mat4 b = {
		{-2, 1, 2, 3},
		{3, 2, 1, -1},
		{4, 3, 6, 5},
		{1, 2, 7, 8}
	};
	
	Mat4 Product = {
		{20, 22, 50, 48},
		{44, 54, 114, 108},
		{40, 58, 110, 102},
		{16, 26, 46, 42}
	};

	Mat4 actualProduct = { 0 };

	mat_mat4MultiplyMat4(a, b, actualProduct);

	TEST_ASSERT_EQUAL_INT(1, mat_mat4Compare(Product, actualProduct));
}

void test_mat_mat4MultiplyTuple() {
	Mat4 a = { 
		{1, 2, 3, 4},
		{2, 4, 4 ,2},
		{8, 6, 4, 1},
		{0, 0, 0, 1}
	};

	Tuple b = tuple_createPoint(1, 2, 3);

	Tuple product = tuple_createPoint(18, 24, 33);
	Tuple actualProduct = mat_mat4MultuplyTuple(a, b);

	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(product, actualProduct));
}

void test_mat_mat4MultiplyIdentity() {
	Mat4 a = {
		{0,1,2,4},
		{1,2,4,8},
		{2,4,8,16},
		{4,8,16,32}
	};
	Mat4 b = MAT4_IDENTITY;

	Mat4 product = { 0 };
	mat_mat4MultiplyMat4(a, b, product);

	TEST_ASSERT_EQUAL_INT(1, mat_mat4Compare(a, product));

	Tuple t = tuple_createPoint(2, 3, 1);

	Tuple tp = mat_mat4MultuplyTuple(b, t);

	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(t, tp));


}

void test_mat_mat4Transpose() {
	Mat4 a = {
		{0, 9, 3, 0},
		{9, 8, 0, 8},
		{1, 8, 5, 3},
		{0, 0, 5, 8},
	};

	Mat4 transposeA = {
		{0, 9, 1, 0},
		{9, 8, 8, 0},
		{3, 0, 5, 5},
		{0, 8, 3, 8}
	};

	mat_mat4Transpose(a, a);

	TEST_ASSERT_EQUAL_INT(1, mat_mat4Compare(a, transposeA));

	Mat4 iden = MAT4_IDENTITY;
	Mat4 transident;
	mat_mat4Transpose(iden, transident);
	TEST_ASSERT_EQUAL_INT(1, mat_mat4Compare(transident, iden));
}

void test_mat_mat4Copy() {
	Mat4 mat = {
		{10, 4, 3.2 -1},
		{0, 0, 12, 67},
		{0.5, -0.2, 1, 10},
		{0, 0, 0, 100}
	};
	Mat4 matcpy = { 99 };

	mat_mat4Copy(mat, matcpy);

	TEST_ASSERT_EQUAL_INT(1, mat_mat4Compare(mat, matcpy));
}

void test_mat2FindDeterminant() {
	Mat2 testMat = {
		{1,  5},
		{-3, 2}
	};

	float determinant = mat_mat2FindDeterminant(testMat);
	TEST_ASSERT_EQUAL_FLOAT(17, determinant);
}

void test_mat3Submatrix() {
	Mat3 testMat = {
		{1, 5, 6},
		{-3, 2, 7},
		{0, 6, -3}
	};

	Mat2 expectedSubM = {
		{-3, 2},
		{0, 6}
	};

	Mat2 expectedSubM2 = {
		{1, 6},
		{0, -3}
	};

	Mat2 submatrix = {0};
	mat_mat3Submatrix(testMat, 0, 2, submatrix);

	TEST_ASSERT_EQUAL_INT(1, mat_mat2Compare(submatrix, expectedSubM));

	mat_mat3Submatrix(testMat, 1, 1, submatrix);

	TEST_ASSERT_EQUAL_INT(1, mat_mat2Compare(submatrix, expectedSubM2));
}

void test_mat4Submatrix() {
	Mat4 testMat = {
		{-6, 1, 1, 6},
		{-8, 5, 8, 6},
		{-1, 0, 8, 2},
		{-7, 1, -1, 1}
	};

	Mat3 expectedSubM = {
		{-6, 1, 6},
		{-8, 8, 6},
		{-7, -1, 1}
	};
	Mat3 submatrix = {0};

	mat_mat4Submatrix(testMat, 2, 1, submatrix);

	TEST_ASSERT_EQUAL_INT(1, mat_mat3Compare(submatrix, expectedSubM));

}

void test_mat3Minor() {
	Mat3 testMat = {
		{3, 5, 0},
		{2, -1, -7},
		{6, -1, 5}
	};

	float expectedDeterminant = 25;

	TEST_ASSERT_EQUAL_FLOAT(expectedDeterminant, mat_mat3Minor(testMat, 1, 0));
}

void test_mat3Cofactor() {
	Mat3 testMat = {
		{3, 5, 0},
		{2, -1, -7},
		{6, -1, 5}
	};

	float expectedMinor = -12;
	float expectedCofactor = -12;

	float expectedMinor2 = 25;
	float expectedCofactor2 = -25;

	TEST_ASSERT_EQUAL_FLOAT(expectedMinor, mat_mat3Minor(testMat, 0, 0));
	TEST_ASSERT_EQUAL_FLOAT(expectedCofactor, mat_mat3Cofactor(testMat, 0, 0));

	TEST_ASSERT_EQUAL_FLOAT(expectedMinor2, mat_mat3Minor(testMat, 1, 0));
	TEST_ASSERT_EQUAL_FLOAT(expectedCofactor2, mat_mat3Cofactor(testMat, 1, 0));

}

void test_mat4Minor() {
	Mat4 testMat = {
		{2, 5, 6, 7},
		{1, 2, 3, 4},
		{1, 2, 3, 4},
		{0, 0, 0, 1}
	};

	TEST_ASSERT_EQUAL_FLOAT(3, mat_mat4Minor(testMat, 1, 0));
	TEST_ASSERT_EQUAL_FLOAT(3, mat_mat4Minor(testMat, 2, 0));
	TEST_ASSERT_EQUAL_FLOAT(0, mat_mat4Minor(testMat, 0, 0));


}

void test_mat4Cofactor() {
	Mat4 testMat = {
		{2, 5, 6, 7},
		{1, 2, 3, 4},
		{1, 2, 3, 4},
		{0, 0, 0, 1}
	};

	TEST_ASSERT_EQUAL_FLOAT(-3, mat_mat4Cofactor(testMat, 1, 0));
	TEST_ASSERT_EQUAL_FLOAT(3, mat_mat4Cofactor(testMat, 2, 0));
	TEST_ASSERT_EQUAL_FLOAT(0, mat_mat4Cofactor(testMat, 0, 0));

}

void test_mat3Determinant() {
	Mat3 testMat = {
		{1, 2, 6},
		{-5, 8, -4},
		{2, 6, 4}
	};
	TEST_ASSERT_EQUAL_FLOAT(56, mat_mat3Cofactor(testMat, 0, 0));
	TEST_ASSERT_EQUAL_FLOAT(12, mat_mat3Cofactor(testMat, 0, 1));
	TEST_ASSERT_EQUAL_FLOAT(-46, mat_mat3Cofactor(testMat, 0, 2));
	TEST_ASSERT_EQUAL_FLOAT(-196, mat_mat3Determinant(testMat));

}

void test_mat4Determinant() {
	Mat4 testMat = {
		{-2, -8, 3, 5},
		{-3, 1, 7, 3},
		{1, 2, -9, 6},
		{-6, 7, 7, -9}
	};

	TEST_ASSERT_EQUAL_FLOAT(690, mat_mat4Cofactor(testMat, 0,0));
	TEST_ASSERT_EQUAL_FLOAT(447, mat_mat4Cofactor(testMat, 0,1));
	TEST_ASSERT_EQUAL_FLOAT(210, mat_mat4Cofactor(testMat, 0,2));
	TEST_ASSERT_EQUAL_FLOAT(51, mat_mat4Cofactor(testMat, 0,3));
	TEST_ASSERT_EQUAL_FLOAT(-4071, mat_mat4Determinant(testMat));

}

void test_isInversable() {
	Mat4 testMat1 = {
		{6, 4, 4, 4},
		{5, 5, 7, 6},
		{4, -9, 3, -7},
		{9, 1, 7, -6}
	};
	// determinate is not zero, inversable
	TEST_ASSERT_NOT_EQUAL_FLOAT(0, mat_mat4Determinant(testMat1));

	Mat4 testMat2 = {
		{-4, 2, -2, -3},
		{9, 6, 2, 6},
		{0, -5, 1, -5},
		{0, 0, 0, 0}
	};
	// determinate is 0, non-inversable
	TEST_ASSERT_EQUAL_FLOAT(0, mat_mat4Determinant(testMat2));
}

void test_mat4Inverse() {
	Mat4 testMat4 = {
		{-5, 2, 6, -8},
		{1, -5, 1, 8},
		{7, 7, -6, -7},
		{1, -3, 7, 4}
	};

	Mat4 expectedInv = {
		{0.21805, 0.45113, 0.24060, -0.04511},
		{-0.80827, -1.45677, -0.44361, 0.52068},
		{-0.07895, -0.22368, -0.05263, 0.19737},
		{-0.52256, -0.81391, -0.30075, 0.30639}
	};

	Mat4 testMat4Inv = {0};
	mat_mat4Inverse(testMat4, testMat4Inv);

	TEST_ASSERT_EQUAL_FLOAT(532, mat_mat4Determinant(testMat4));
	TEST_ASSERT_EQUAL_FLOAT(-160, mat_mat4Cofactor(testMat4, 2, 3));
	TEST_ASSERT_EQUAL_FLOAT(-160.0f/532.0f, testMat4Inv[3][2]);
	TEST_ASSERT_EQUAL_FLOAT(105, mat_mat4Cofactor(testMat4, 3, 2));
	TEST_ASSERT_EQUAL_FLOAT(105.0f/532.0f, testMat4Inv[2][3]);
	TEST_ASSERT_EQUAL_INT(1, mat_mat4Compare(testMat4Inv, expectedInv));


	Mat4 testMat4_2 = {
		{8, -5, 9, 2},
		{7, 5, 6, 1},
		{-6, 0, 9, 6},
		{-3, 0, -9, -4}
	};
	Mat4 expectedInv_2 = {
		{-0.15385, -0.15385, -0.28205, -0.53846},
		{-0.07692, 0.12308, 0.02564, 0.03077},
		{0.35897, 0.35897, 0.43590, 0.92308},
		{-0.69231, -0.69231, -0.76923, -1.92308}
	};
	Mat4 testMatInv_2 = {0};

	mat_mat4Inverse(testMat4_2, testMatInv_2);

	TEST_ASSERT_EQUAL_INT(1, mat_mat4Compare(expectedInv_2, testMatInv_2));

	Mat4 testMat4_3 = {
		{9, 3, 0, 9},
		{-5, -2, -6, -3},
		{-4, 9, 6, 4},
		{-7, 6, 6, 2}
	};
	Mat4 expectedInv_3 = {
		{-0.04074, -0.07778, 0.14444, -0.22222},
		{-0.07778, 0.03333, 0.36667, -0.33333},
		{-0.02901, -0.14630, -0.10926, 0.12963},
		{0.17778, 0.06667, -0.26667, 0.33333}
	};
	Mat4 testMatInv_3 = {0};
	mat_mat4Inverse(testMat4_3, testMatInv_3);

	TEST_ASSERT_EQUAL_INT(1, mat_mat4Compare(expectedInv_3, testMatInv_3));
}

void test_mat4MulInverse() {
	Mat4 a = {
		{3, -9, 7, 3},
		{3, -8, 2, -9},
		{-4, 4, 4, 1},
		{-6, 5, -1, 1}
	};

	Mat4 b = {
		{8, 2, 2, 2},
		{3, -1, 7, 0},
		{7, 0, 5, 4},
		{6, -2, 0, 5}
	};

	Mat4 binv = {0};
	mat_mat4Inverse(b, binv);

	Mat4 c = {0};
	mat_mat4MultiplyMat4(a, b, c);

	Mat4 newC = {0};
	mat_mat4MultiplyMat4(c, binv, newC);
	TEST_ASSERT_EQUAL_INT(1, mat_mat4Compare(a,  newC));
}

void test_MultiplyByTransformMatrix() {
	Mat4 translation = {0};
	mat_mat4CreateTranslation(translation, 5, -3, 2);

	Tuple point = tuple_createPoint(-3, 4, 5);

	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(tuple_createPoint(2, 1, 7), mat_mat4MultuplyTuple(translation, point)));

	Mat4 inverseTranslation = {0};
	mat_mat4Inverse(translation, inverseTranslation);

	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(tuple_createPoint(-8,7,3), mat_mat4MultuplyTuple(inverseTranslation, point)));

	Tuple vector = tuple_createVector(-3, 4, 5);

	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(vector, mat_mat4MultuplyTuple(translation, vector)));

}

void test_scalingMatrix() {
	Mat4 scalingMatrix = {0};
	mat_mat4CreateScaling(scalingMatrix, 2, 3, 4);
	Mat4 invScalingMatrix = {0};
	mat_mat4Inverse(scalingMatrix, invScalingMatrix);

	Tuple point = tuple_createPoint(-4, 6, 8);
	Tuple vector = tuple_createVector(-4, 6, 8);

	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(tuple_createPoint(-8, 18, 32), mat_mat4MultuplyTuple(scalingMatrix, point)) );
	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(tuple_createVector(-8, 18, 32), mat_mat4MultuplyTuple(scalingMatrix, vector)) );
	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(tuple_createVector(-2, 2, 2), mat_mat4MultuplyTuple(invScalingMatrix, vector)) );
}

void test_scalingReflection() {
	Mat4 reflectionMatrix = {0};
	mat_mat4CreateScaling(reflectionMatrix, -1, 1, 1);
	Tuple point = tuple_createPoint(2, 3, 4);

	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(tuple_createPoint(-2,3,4), mat_mat4MultuplyTuple(reflectionMatrix, point)));
}

void test_mat4Rotation() {
	Mat4 rotationMatrix = {0};
	Tuple point = tuple_createPoint(0,1,0);
	Tuple pointY = tuple_createPoint(0, 0, 1);

	mat_mat4CreateRotation_x(rotationMatrix, rad(45));
	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(tuple_createPoint(0, sqrtf(2.0)/2.0, sqrtf(2.0)/2.0), mat_mat4MultuplyTuple(rotationMatrix, point)) );

	mat_mat4CreateRotation_x(rotationMatrix, rad(90));	
	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(tuple_createPoint(0,0, 1), mat_mat4MultuplyTuple(rotationMatrix, point)) );

	mat_mat4CreateRotation_y(rotationMatrix, rad(45));
	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(tuple_createPoint(sqrtf(2.0)/2.0, 0, sqrtf(2.0)/2.0), mat_mat4MultuplyTuple(rotationMatrix, pointY)) );

	mat_mat4CreateRotation_y(rotationMatrix, rad(90));
	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(tuple_createPoint(1, 0, 0), mat_mat4MultuplyTuple(rotationMatrix, pointY)) );

	mat_mat4CreateRotation_z(rotationMatrix, rad(45));
	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(tuple_createPoint(-sqrtf(2.0)/2.0, sqrtf(2.0)/2.0, 0), mat_mat4MultuplyTuple(rotationMatrix, point)) );

	mat_mat4CreateRotation_z(rotationMatrix, rad(90));
	TEST_ASSERT_EQUAL_INT(1, tuple_tupleCompare(tuple_createPoint(-1, 0, 0), mat_mat4MultuplyTuple(rotationMatrix, point)) );
}

void test_mat4Shearing() {
	Mat4 shearMatrix = {0};

	mat_mat4CreateShearing(shearMatrix, 1, 0, 0, 0, 0, 0);
	Tuple point = tuple_createPoint(2, 3, 4);
	TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createPoint(5, 3, 4), mat_mat4MultuplyTuple(shearMatrix, point)));


	mat_mat4CreateShearing(shearMatrix, 0, 1, 0, 0, 0, 0);
	TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createPoint(6, 3, 4), mat_mat4MultuplyTuple(shearMatrix, point)));
	

	mat_mat4CreateShearing(shearMatrix, 0, 0, 1, 0, 0, 0);
	TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createPoint(2, 5, 4), mat_mat4MultuplyTuple(shearMatrix, point)));


	mat_mat4CreateShearing(shearMatrix, 0, 0, 0, 1, 0, 0);
	TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createPoint(2, 7, 4), mat_mat4MultuplyTuple(shearMatrix, point)));


	mat_mat4CreateShearing(shearMatrix, 0, 0, 0, 0, 1, 0);
	TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createPoint(2, 3, 6), mat_mat4MultuplyTuple(shearMatrix, point)));


	mat_mat4CreateShearing(shearMatrix, 0, 0, 0, 0, 0, 1);
	TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createPoint(2, 3, 7), mat_mat4MultuplyTuple(shearMatrix, point)));
}

void test_mat4Chaining() {
	Tuple originalPoint = tuple_createPoint(1, 0, 1);
	Mat4 rotation_x  = {0};
	mat_mat4CreateRotation_x(rotation_x, rad(90));
	Mat4 scaling = {0};
	mat_mat4CreateScaling(scaling, 5, 5, 5);
	Mat4 translation = {0};
	mat_mat4CreateTranslation(translation, 10, 5, 7);

	Tuple point2 = mat_mat4MultuplyTuple(rotation_x, originalPoint);
	Tuple point3 = mat_mat4MultuplyTuple(scaling, point2);
	Tuple point4 = mat_mat4MultuplyTuple(translation, point3);

	TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createPoint(1, -1, 0), point2));
	TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createPoint(5, -5, 0), point3));
	TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createPoint(15, 0, 7), point4));

	Tuple point5 = mat_mat4ChainMatrices(rotation_x, scaling, translation, originalPoint);
	TEST_ASSERT_TRUE(tuple_tupleCompare(tuple_createPoint(15, 0, 7), point5));
	
}

int main() {
	RUN_TEST(test_mat2ConstructionTest);
	RUN_TEST(test_mat3ConstructionTest);
	RUN_TEST(test_mat4ConstructionTest);
	RUN_TEST(test_matxCompare);
	RUN_TEST(test_mat_mat4MultiplyMat4);
	RUN_TEST(test_mat_mat4MultiplyTuple);
	RUN_TEST(test_mat_mat4MultiplyIdentity);
	RUN_TEST(test_mat_mat4Transpose);
	RUN_TEST(test_mat_mat4Copy);
	RUN_TEST(test_mat2FindDeterminant);
	RUN_TEST(test_mat3Submatrix);
	RUN_TEST(test_mat4Submatrix);
	RUN_TEST(test_mat3Minor);
	RUN_TEST(test_mat3Cofactor);
	RUN_TEST(test_mat3Determinant);
	RUN_TEST(test_mat4Determinant);
	RUN_TEST(test_mat4Minor);
	RUN_TEST(test_mat4Cofactor);
	RUN_TEST(test_mat4Inverse);
	RUN_TEST(test_mat4MulInverse);
	RUN_TEST(test_MultiplyByTransformMatrix);
	RUN_TEST(test_scalingMatrix);
	RUN_TEST(test_scalingReflection);
	RUN_TEST(test_mat4Rotation);
	RUN_TEST(test_mat4Shearing);
	RUN_TEST(test_mat4Chaining);
	return UNITY_END();
}