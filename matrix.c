#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "matrix.h"

// Our typedef structmatrix. Call with `matrix name;`
struct _matrix {
    int rows;
    int cols;
    double * data;
};

/** A macro is defined that helps withmatrix arithmetic operations. Since computers start at 0, we need to access memory that starts at the correct offset. We do this by defining our cols and rows with a '-1'
**/
#define ELEM(mtx, row, col) \
    mtx->data[(col-1) * mtx->rows + (row-1)]

// Declare ourmatrix
matrix newMatrix(int rows, int cols) {

   matrix m = (matrix) malloc(sizeof(struct _matrix));

    m->rows = rows;
    m->cols = cols;

    if (rows > 0 && cols > 0) {
        m->data = (double *) malloc(rows*cols*sizeof(double));
        //set all data to 0;
        int i;
        for (i = 0; i < rows*cols; i++) {
            m->data[i] = 0.0;
        }
    }
    else
        m->data = NULL;

    return m;
}

void deleteMatrix(matrix mtx) {
    if (mtx->data) free(mtx->data);
    free(mtx);
}

matrix copyMatrix(matrix mtx) {
    if (!mtx) return NULL;
    // make a newmatrix identicle tp the dimesnsions from (* mtx).
    matrix cp = newMatrix(mtx->rows, mtx->cols);
    // Copy the data into those cells. memcpy(to, from, nbytes). Copies nBytes to, from.
    memcpy(cp->data, mtx->data, mtx->rows * mtx->cols * sizeof(double));
    // return copy.
    return cp;
}

int setElement(matrix mtx, int row, int col, double val) {
    if (!mtx) return -1;

    if (row <= 0 || col <= 0 || row > mtx->rows || col > mtx->cols) return -2;

    ELEM(mtx, row, col) = val;
    return 0;
}

int getElement(matrix mtx, int row, int col, double * val) {
    if (!mtx || !val) return -1;

    assert (mtx->data);
    if (row <= 0 || row > mtx->rows || col <= 0 || col > mtx->cols) return -2;

    *val = ELEM(mtx, row, col);
    return 0;
}

int nRows(matrix mtx, int * n) {
    if (!mtx || !n) return -1;
    *n = mtx->rows;
    return 0;
}

int nCols(matrix mtx, int * n) {
    if (!mtx || !n) return -1;
    *n = mtx->cols;
    return 0;
}

//TODO: Maybe change return type int to void in future
int printMatrix(matrix mtx) {
    if (!mtx) return -1;

    int row, col;
    for (row = 1; row <= mtx->rows; row++) {
        for (col = 1; col <=mtx->cols; col++) {
            printf("% 6.2f ", ELEM(mtx, row, col)); //% 6.2f is a good format for printingmatrix with two decimals
        }
        printf("\n");    
    }
    return 0;
}

int transposeMatrix(matrix in, matrix out) {
    if (!in || !out) return -1;
    if (in->rows != out->cols || in->cols != out->rows) return -2;

    int row, col;
    for (row = 1; row <= in->rows; row++) {
        for (col = 1; col <= in->cols; col++) {
            ELEM(out, col, row) = ELEM(in, row, col);
        }
    }
    return 0;
}

int sumMatrix(matrix mtx1, matrix mtx2, matrix sum) {
    if (!mtx1 || !mtx2 || !sum) return -1;
    
    if (mtx1->rows != mtx2->rows ||
        mtx1->rows != sum->rows ||
        mtx1->cols != mtx2->cols ||
        mtx1->cols != sum->cols) return -2;
    
    int row, col;
    for (row = 1; row <=mtx1->rows; row++) {
        for (col = 1; col<=mtx1->cols; col++)
            ELEM(sum, row, col) = ELEM(mtx1, row, col) + ELEM(mtx2, row, col);
    }
    return 0;
}

int prodMatrix(matrix mtx1, matrix mtx2, matrix prod) {
    if (!mtx1 || !mtx2 || !prod) return -1;
    
    if (mtx1->cols != mtx2->rows ||
        mtx1->rows != prod->rows ||
        mtx2->cols != prod->cols) return -2;
    
    int row, col, k;
    for (col = 1; col <= mtx2->cols; col++) {
        for (row = 1; row <= mtx1->rows; row++) {
            double val = 0.0;
            for (k = 1; k <= mtx1->cols; k++)
                val += ELEM(mtx1, row, k) * ELEM(mtx2, k, col);
        
            ELEM(prod, row, col) = val;
        }
    }
    return 0;
}

int dotProduct(matrix v1, matrix v2, double * prod) {
    if (!v1 || !v2 || !prod) return -1;
    if (v1->cols != 1 || v2->cols != 1) return -2;
    if (v1->rows != v2->rows) return -3;

    *prod = 0;
    int i;
    for (i = 1; i <= v1->rows; i++) {
        *prod += ELEM(v1, i, 1) * ELEM(v2, i, 1);
    }
    return 0;
}

int identity(matrix mtx) {
    if (!mtx) return -1;
    if (mtx->rows != mtx->cols) return -2;
    int row, col;

    for (col = 1; col <= mtx->cols; col++) {
        for (row = 1; row <= mtx->rows; row++) {
            if (row == col) {
                ELEM(mtx, row, col) = 1.0;
            }
            else {
                ELEM(mtx, row, col) = 0.0;
            }
        }
    }
    return 0;
}

//TODO: Add integer argument to determine diagnol plane offset.
/*TODO: Add functionality to determine what type of diagnol line it will be (have it switch from negative to positive slope. Basically combine functionalities of identity() and identity2().
*/
int identity2(matrix mtx) {
    if (!mtx) return -1;
    if (mtx->rows != mtx->cols) return -2;
    int row, col, a, n;

    // Get our numerator (row*cols)
    a = (mtx->rows*mtx->cols);
    // Get the denomiator: n = 10
    n = mtx->rows;
    // Set counter
    int ctr = a / n;

    for (col = 1; col <= mtx->cols; col++) {
        for (row = 1; row <= mtx->rows; row++) {
            // Check if it is in our sequence
            if (row == ctr) {
                ELEM(mtx, row, col) = 1.0;
                ctr = ctr - 1;
            }
            else {
                ELEM(mtx, row, col) = 0.0;
            }
        }
    }
    return 0;
}

int isSquare(matrix mtx) {
    if (!mtx) return -1;
    if (mtx->rows != mtx->cols) {
        printf("\n**** Not a Squarematrix****\n");
        return -2;
    }
    else {
        return mtx && mtx->rows == mtx->cols;
    }
}

int isDiagnol(matrix mtx) {
    if (!isSquare(mtx)) return 0;
    int row, col;
    for (col = 1; col <= mtx->cols; col++) {
        for (row = 1; row <= mtx->rows; row++) {
            // if element is not a diagnol element and not 0, then it is not diagnol, so return 0
            if (row != col && ELEM(mtx, row, col) != 0.0) return 0;
        }
    }
    return 1;
}

int isUpperTriangle(matrix mtx) {
    if (!mtx) return -1;
    // Just because it isn't square, we don't need to kill the program
    if (!isSquare(mtx)) return 0;

    int row, col;
    for (col = 1; col <= mtx->cols; col++) {
        for (row = col+1; row <= mtx->rows; row++) {
            if (ELEM(mtx, row, col) != 0.0) {
                printf("\nSquare is Upper Triangle\n");
                return 0;
            }           
        }
    }
    return 1;
}

int isLowerTriangle(matrix mtx) {
    if (!mtx) return -1;
    // Just because it isn't square, we don't need to kill the program
    if (!isSquare(mtx)) return 0;

    int row, col;
    for (col = 1; col <= mtx->cols; col++) {
        for (row = col-1; row <= mtx->rows; row++) {
            if (ELEM(mtx, row, col) != 0.0) {
                //printf("\nSquare is Lower Triangle\n");
                return 0;
            }
        }
    }
    return 1;
}

int isSym_and_Square(matrix mtx) {
    if (!mtx || !isSquare(mtx)) return 0;

    matrix m = copyMatrix(mtx);
    int row, col, isSym = 1;
    for (col = 1; col <= mtx->cols; col++) {
        for (row = 1; row <= mtx->rows; row++) {
            if (ELEM(mtx, col, row) != ELEM(m, row, col)) {
                isSym = 0;
                break;
            }
        }
    }
    deleteMatrix(m);
    if (isSym == 1) return 1;
    else return 0;
}

// TODO: Protect from bad user input
matrix getRow(matrix mtx, int ro) {
    if (!mtx) return NULL;
    int row, col;
    matrix vector = newMatrix(1, mtx->cols);
    printf("\nCols is %d\n", mtx->cols);

    for (col = 1; col <= mtx->cols; col++) {
        for (row = 1; row <= mtx->rows; row++) {
            if (row == ro) {
                ELEM(vector, row, col) += ELEM(mtx, row, col);
                //printf("In func getRow(%d): ELEM = %f\n", ro, ELEM(vector, row, col));
            }
        }
    }
    return vector;
}

// TODO: Get a selected column from amatrix and return it as a new vector. printf() works and outputs correct output but return vector does not.... ???
matrix getColumn(matrix mtx, int co) {
    if (!mtx) return NULL;
    int row, col;
    matrix vector = newMatrix(mtx->rows, 1);
    printf("\nRows is %d\n", mtx->rows);

    for (col = 1; col <= mtx->cols; col++) {
        for (row = 1; row <= mtx->rows; row++) {
            if ((col == co)) {
                ELEM(vector, row, col) += ELEM(mtx, row, col);
                //printf("In func getColumn(%d): ELEM = %f\n", co, ELEM(vector, row, col));
            }
        }
    }
    return vector;
}

int diagnol(matrix v, matrix mtx) {
    if(!v || !mtx) return -1;
    int row, col;

    for (col = 1; col <= mtx->cols; col++) {
        for (row = 1; row <= mtx->rows; row++) {
            if ((row = col))
                ELEM(mtx, row, col) = ELEM(v, col, 1);
            else
                ELEM(mtx, row, col) = 0.0;
        }
    }
    return 0;
}

//TODO: Sets the element of mtx to the product that element and double s. Needs verified and debugged
int scalarProduct(double s, matrix mtx) {
    if(!s || !mtx) return -1;

    int row, col;
    double val;
    for (col = 1; col <= mtx->cols; col++) {
        for (row = 1; row <= mtx->rows; row++) {
            val += ELEM(mtx, row, col) * s;            
        }
        ELEM(mtx, row, col) = val;
    }
    return 0;
}
