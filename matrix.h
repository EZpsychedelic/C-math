#ifndef _MATRIX_H_
#define _MATRIX_H_

/* Type declaration */

typedef struct _matrix * matrix;

// Createsa a rows and x cols matrix with all values 0.

matrix newMatrix(int rows, int cols);

// Copies a matrix

matrix copyMatrix(matrix mtx);

// Deletes a matrix

void deleteMatrix(matrix mtx);

//Sets the (row, col) element of mtx to val. Returns 0 if successful, -1 if row or col are outside of mtx dimensions

int setElement(matrix mtx, int row, int col, double val);

// Sets the reference val to value to the (row, col) element of mtx. Returns 0 on success, -1 on null, -2 if row or col are outside dimensions of mtx

int getElement(matrix mtx, int row, int col, double * val);

// Returns the number of rows of mtx
int nRows(matrix mtx, int * n);

// Returns the number of columns on mtx
int nCols(matrix mtx, int * n);

// Prints matrix to stdout

int printMatrix(matrix mtx);

// Writes the transpose of matric into matric out. Returns 0 on success, -1 if dimensions are incompatible

int transposeMatrix(matrix in, matrix out);

// Writes the sum of matrices mtx1 and mtx2 into matrix sum. Returns 0 on success, -1 if dimensions are incompatible

int sumMatrix(matrix mtx1, matrix mtx2, matrix sum);

// Writes product of mtx1 and mtx2 into matrix prod. Returns 0 on sucess, -1 if dimensions are incompatible

int prodMatrix(matrix mtx1, matrix mtx2, matrix prod);

// Makes a diagnol vector (decline) of 1's and sets the other elements to 0
int identity(matrix mtx);

// Makes a diagnol vector (incline) of 1's and sets the other elements to 0
int identity2(matrix mtx);

// Writes the dot products of vectors v1 and v2 into referece prod. Returns 0 on success, -1 if prod is null, and -2 it either matric is not a vector, -3 if the vectors are incompatible dimensions

int dotProduct(matrix v1, matrix v2, double * prod);

// Gets a column, int co, from matrix mtx and return elements of that column into a new vector
matrix getColumn(matrix mtx, int co);

// Gets row, int ro, from matrix mtx and returns elements of that column into a new vector
matrix getRow(matrix mtx, int ro);

// Given a vector, makes it diagnol in a matrix
int diagnol(matrix v, matrix mtx);

// Given double s and a matrix, computes the scalar product (s * element)
int scalarProduct(double s, matrix mtx);

// Checks that a given matrix is square
int isSquare(matrix mtx);

// Checks that a matrix is sqaure and symmetrical
int isSym_and_Square(matrix mtx);

#endif
