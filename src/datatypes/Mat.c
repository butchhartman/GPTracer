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

void mat_mat4MultiplyMat4(Mat4 mat1, Mat4 mat2, Mat4 dest)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			(dest)[i][j] = mat1[i][0] * mat2[0][j] +
						  mat1[i][1] * mat2[1][j] +
						  mat1[i][2] * mat2[2][j] +
						  mat1[i][3] * mat2[3][j];
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

void mat_mat4Inverse(Mat4 source, Mat4 dest) {
	if (mat_mat4Determinant(source) == 0) {
		return;
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float cof = mat_mat4Cofactor(source, i, j);
			dest[j][i] = cof / mat_mat4Determinant(source);
		}
	}
}
