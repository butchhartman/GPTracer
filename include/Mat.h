#pragma once
#include "CommonOperations.h"
#include "Tuple.h"

#define MAT4_IDENTITY { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} }

typedef float Mat2[2][2];
typedef float Mat3[3][3];
typedef float Mat4[4][4];

int mat_mat2Compare(Mat2 mat1, Mat2 mat2);
int mat_mat3Compare(Mat3 mat1, Mat3 mat2);
int mat_mat4Compare(Mat4 mat1, Mat4 mat2);

float mat_mat2FindDeterminant(Mat2 mat);

void mat_mat3Submatrix(Mat3 source, int row, int column, Mat2 dest);
float mat_mat3Minor(Mat3 source, int row, int column);
float mat_mat3Cofactor(Mat3 source, int row, int column);
float mat_mat3Determinant(Mat3 source);

void mat_mat4MultiplyMat4(Mat4 mat1, Mat4 mat2, Mat4 dest);
Tuple mat_mat4MultuplyTuple(Mat4 mat, Tuple tuple);
void mat_mat4Transpose(Mat4 mat, Mat4 dest);
void mat_mat4Copy(Mat4 source, Mat4 dest);
void mat_mat4Print(Mat4 mat);
void mat_mat4Submatrix(Mat4 source, int row, int column, Mat3 dest);
float mat_mat4Determinant(Mat4 source);
float mat_mat4Cofactor(Mat4 source, int row, int column);
float mat_mat4Minor(Mat4 source, int row, int column);
void mat_mat4Inverse(Mat4 source, Mat4 dest);

void mat_mat4CreateTranslation(Mat4 dest, float x, float y, float z);
void mat_mat4CreateScaling(Mat4 dest, float x, float y, float z);

void mat_mat4CreateRotation_x(Mat4 dest, float angle);
void mat_mat4CreateRotation_y(Mat4 dest, float angle);
void mat_mat4CreateRotation_z(Mat4 dest, float angle);

void mat_mat4CreateShearing(Mat4 dest, float xpy, float xpz, float ypx, float ypz, float zpx, float zpy);

Tuple mat_mat4ChainMatrices(Mat4 rotation, Mat4 scaling, Mat4 translation, Tuple tuple);

void mat_mat4CreateView(Mat4 dest, Tuple from, Tuple to, Tuple up);