#include "Mat.h"

int mat_mat2Compare(Mat2 mat1, Mat2 mat2)
{
	int equal = 1;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			

			if (floatCompare(mat1[i][j], mat2[i][j]) == 0) {
				equal = 0;
				return equal;
			}

		}
	}
	return equal;
}

int mat_mat3Compare(Mat3 mat1, Mat3 mat2)
{
	int equal = 1;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {


			if (floatCompare(mat1[i][j], mat2[i][j]) == 0) {
				equal = 0;
				return equal;
			}

		}
	}
	return equal;
}

int mat_mat4Compare(Mat4 mat1, Mat4 mat2)
{
	int equal = 1;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {


			if (floatCompare(mat1[i][j], mat2[i][j]) == 0) {
				equal = 0;
				//printf("NOT EQUAL AT %d, %d; EXPECTED %f, GOT %f\n", i, j, mat1[i][j], mat2[i][j]);
				return equal;
			}

		}
	}
	return equal;
}

float mat_mat2FindDeterminant(Mat2 mat)
{
    return (mat[0][0]) * (mat[1][1]) - (mat[0][1]) * (mat[1][0]);
}

void mat_mat3Submatrix(Mat3 source, int row, int column, Mat2 dest)
{
	int subRow = 0;
	int subColumn = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == row) {
				subRow +=1;
				break;
			}
			if (j == column) {
				subColumn += 1;
				continue;
			}
			dest[i-subRow][j-subColumn] = source[i][j];
		//	printf("VAL : %f\n", dest[i-subRow][j-subColumn]);
		}
		//subRow += 1;
		subColumn = 0;
	}
}

float mat_mat3Minor(Mat3 source, int row, int column)
{
    Mat2 subMatrix = {0};
	mat_mat3Submatrix(source, row, column, subMatrix);
	return mat_mat2FindDeterminant(subMatrix);
}

float mat_mat3Cofactor(Mat3 source, int row, int column)
{
	if (isOdd((row+column)) == 1) {
		return -mat_mat3Minor(source, row, column);
	} 
	else {
		return mat_mat3Minor(source, row, column);
	}
}

float mat_mat3Determinant(Mat3 source)
{
    return source[0][0]*mat_mat3Cofactor(source,0,0) + 
	 	  source[0][1]*mat_mat3Cofactor(source,0,1)  + 
		  source[0][2]*mat_mat3Cofactor(source,0,2) ;
}
// dest can be one of the components
void mat_mat4MultiplyMat4(Mat4 mat1, Mat4 mat2, Mat4 dest)
{
	Mat4 copy1;
	mat_mat4Copy(mat1, copy1);
	Mat4 copy2;
	mat_mat4Copy(mat2, copy2);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			(dest)[i][j] = copy1[i][0] * copy2[0][j] +
						  copy1[i][1] * copy2[1][j] +
						  copy1[i][2] * copy2[2][j] +
						  copy1[i][3] * copy2[3][j];
		}
	}
}

Tuple mat_mat4MultuplyTuple(Mat4 mat, Tuple tuple){
	// this fucking sucks
	float tupleMembers[4];
	for (int i = 0; i < 4; i++) {
		tupleMembers[i] = mat[i][0] * *tuple_tupleGetMember(tuple, 0) +
												 mat[i][1] * *tuple_tupleGetMember(tuple, 1) +
											 	 mat[i][2] * *tuple_tupleGetMember(tuple, 2) +
												 mat[i][3] * *tuple_tupleGetMember(tuple, 3);
		//printf("PROD TUP: %f\n", tupleMembers[i]);
	}
	Tuple t = { tupleMembers[0], tupleMembers[1], tupleMembers[2], tupleMembers[3] };
	return t;
}
// the source can be the same as dest
void mat_mat4Transpose(Mat4 mat, Mat4 dest) {
	Mat4 copy;
	mat_mat4Copy(mat, copy);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			dest[j][i] = copy[i][j];
		}
	}
}

void mat_mat4Copy(Mat4 source, Mat4 dest)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			dest[i][j] = source[i][j];
		}
	}
}

void mat_mat4Print(Mat4 mat)
{
	for (int i = 0; i < 4; i++) {
		printf("( ");
		for (int j = 0; j < 4; j++) {
			printf("%.2f ", mat[i][j]);
		}
		printf(")\n");
	}
}

void mat_mat4Submatrix(Mat4 source, int row, int column, Mat3 dest)
{
	int subRow = 0;
	int subColumn = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == row) {
				subRow +=1;
				break;
			}
			if (j == column) {
				subColumn += 1;
				continue;
			}
			dest[i-subRow][j-subColumn] = source[i][j];
			//printf("M4VAL : %f\n", dest[i-subRow][j-subColumn]);
		}
		//subRow += 1;
		subColumn = 0;
	}
}

float mat_mat4Determinant(Mat4 source)
{
    return source[0][0]*mat_mat4Cofactor(source, 0, 0) + 
	source[0][1]*mat_mat4Cofactor(source, 0, 1) + 
	source[0][2]*mat_mat4Cofactor(source, 0, 2) + 
	source[0][3]*mat_mat4Cofactor(source, 0, 3);
}

float mat_mat4Cofactor(Mat4 source, int row, int column)
{
	if (isOdd( (row + column) ) == 1) {
		return -mat_mat4Minor(source, row, column);
	} 
	else {
		return mat_mat4Minor(source, row, column);
	}
}

float mat_mat4Minor(Mat4 source, int row, int column)
{
	Mat3 submatrix = {0};
	mat_mat4Submatrix(source, row, column, submatrix);

    return mat_mat3Determinant(submatrix);
}
// source can be the same as dest.
void mat_mat4Inverse(Mat4 source, Mat4 dest) {
	if (mat_mat4Determinant(source) == 0) {
		return;
	}
	Mat4 temp;
	mat_mat4Copy(source, temp);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float cof = mat_mat4Cofactor(temp, i, j);
			dest[j][i] = cof / mat_mat4Determinant(temp);
		}
	}
}

void mat_mat4CreateTranslation(Mat4 dest, float x, float y, float z){
	Mat4 translationMatrix = MAT4_IDENTITY;
	translationMatrix[0][3] = x;	
	translationMatrix[1][3] = y;
	translationMatrix[2][3] = z;
	mat_mat4Copy(translationMatrix, dest);
}

void mat_mat4CreateScaling(Mat4 dest, float x, float y, float z){
	Mat4 scalingMatrix = MAT4_IDENTITY;
	scalingMatrix[0][0] = x;
	scalingMatrix[1][1] = y;
	scalingMatrix[2][2] = z;
	mat_mat4Copy(scalingMatrix, dest);
}

void mat_mat4CreateRotation_x(Mat4 dest, float angle){
	Mat4 rotationMatrix_x = MAT4_IDENTITY;
	rotationMatrix_x[1][1] = cosf(angle);
	rotationMatrix_x[1][2] = -sinf(angle);

	rotationMatrix_x[2][1] = sinf(angle);
	rotationMatrix_x[2][2] = cosf(angle);
	
	mat_mat4Copy(rotationMatrix_x, dest);
}

void mat_mat4CreateRotation_y(Mat4 dest, float angle){
	Mat4 rotationMatrix_y = MAT4_IDENTITY;
	rotationMatrix_y[0][0] = cosf(angle);
	rotationMatrix_y[0][2] = sinf(angle);

	rotationMatrix_y[2][0] = -sinf(angle);
	rotationMatrix_y[2][2] = cosf(angle);

	mat_mat4Copy(rotationMatrix_y, dest);
}

void mat_mat4CreateRotation_z(Mat4 dest, float angle){
	Mat4 rotationMatrix_z = MAT4_IDENTITY;

	rotationMatrix_z[0][0] = cosf(angle);
	rotationMatrix_z[0][1] = -sinf(angle);

	rotationMatrix_z[1][0] = sinf(angle);
	rotationMatrix_z[1][1] = cosf(angle);

	mat_mat4Copy(rotationMatrix_z, dest);

}

void mat_mat4CreateShearing(Mat4 dest, float xpy, float xpz, float ypx, float ypz, float zpx, float zpy){
	Mat4 shearingMatrix = MAT4_IDENTITY;

	shearingMatrix[0][1] = xpy;
	shearingMatrix[0][2] = xpz;
	
	shearingMatrix[1][0] = ypx;
	shearingMatrix[1][2] = ypz;

	shearingMatrix[2][0] = zpx;
	shearingMatrix[2][1] = zpy;
	
	mat_mat4Copy(shearingMatrix, dest);
}

Tuple mat_mat4ChainMatrices(Mat4 rotation, Mat4 scaling, Mat4 translation, Tuple tuple){
	Mat4 cb = {0};
	Mat4 cba = {0};

	mat_mat4MultiplyMat4(translation, scaling, cb);
	mat_mat4MultiplyMat4(cb, rotation, cba);

	Tuple finalPoint = mat_mat4MultuplyTuple(cba, tuple);
    return finalPoint;
}

void mat_mat4CreateView(Mat4 dest, Tuple from, Tuple to, Tuple up){
	Tuple forward = tuple_vectorNormalize(tuple_tupleSub(to, from));
	Tuple upn = tuple_vectorNormalize(up);
	Tuple left = tuple_vectorCross(forward, upn);
	Tuple trueUp = tuple_vectorCross(left, forward);
	
	Mat4 orientation = {{left.x, left.y, left.z, 0},
						{trueUp.x, trueUp.y, trueUp.z, 0},
						{-forward.x, -forward.y, -forward.z, 0},
						{0, 0, 0, 1}};
	Mat4 translation;
	mat_mat4CreateTranslation(translation, -from.x, -from.y, -from.z);
	mat_mat4MultiplyMat4(orientation, translation, orientation);

	mat_mat4Copy(orientation, dest);
}
