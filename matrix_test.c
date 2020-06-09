/* This is the unit test for our Matrix API */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "matrix.h"


int main() {
	matrix A, Ac, B, c, d, M, ct, mdp, id, id2, S, rS, cS;
	double dp;
	
	// Test newMatrix() and setElement by creating our first Matrix	
	A = newMatrix(3, 3);
	setElement(A, 1, 1, 1.0);
	setElement(A, 1, 2, .25);
	setElement(A, 1, 3, -.1);
    setElement(A, 2, 1, .5);
	setElement(A, 2, 2, .4);
	setElement(A, 2, 3, 2.5);
	setElement(A, 3, 2, .5);
	setElement(A, 3, 3, .5);
    setElement(A, 3, 1, 3);
	
	printf("Matrix A:\n");
	printMatrix(A);
	
	// Test copyMatrix()
	Ac = copyMatrix(A);
	printf("\nCopy of Matrix A:\n");
	printMatrix(Ac);

	B = newMatrix(3, 3);
	setElement(B, 1, 1, 5.5);
	setElement(B, 2, 2, 2.5);
	setElement(B, 3, 1, 1.5);
	
	printf("\nMatrix B:\n");
	printMatrix(B);
	
	//
	c = newMatrix(3, 1);
	setElement(c, 1, 1, 1.0);
	setElement(c, 3, 1, 1.0);
	printf("\nVector c:\n");
	printMatrix(c);

	d =  newMatrix(3, 1);
	setElement(d, 2, 1, 1.0);
	setElement(d, 3, 1, 1.0);
	printf("\nVector d:\n");
	printMatrix(d);
	
	// Test transposeMatrix()
	M = newMatrix(3, 3);
	transposeMatrix(A, M);
	printf("\nA' :\n");
	printMatrix(M);

	// Test transposeMatrix()
	ct = newMatrix(1, 3);
	transposeMatrix(c, ct);
	printf("\nc' :\n");
	printMatrix(ct);

	// Test sum
	sumMatrix(A, B, M);
	printf("\nA + B:\n");
	printMatrix(M);
	
	// Test product
	prodMatrix(A, B, M);
	printf("\nA * B:\n");
	printMatrix(M);
	
	// Test getElement
	mdp = newMatrix(1, 1);
	prodMatrix(ct, d, mdp);
	getElement(mdp, 1, 1, &dp);
	printf("\nDot product (1): %.2f\n", dp);
	
	// Test dotProduct
	dotProduct(c, d, &dp);
	printf("\nDot product (2): %.2f\n", dp);

	prodMatrix(A, c, d);
	printf("\nA * c:\n");
	printMatrix(d);
	
    // Test identity
    id = newMatrix(10, 10);
    identity(id); //changes data of matrix 'id'    
    printf("\nIdentity\n");
    if (isSquare(id)) printf("\tMatrix is square\n");
    printMatrix(id);

    // Test other functions
    id2 = newMatrix(10, 10);
    identity2(id2);
    printf("\nIdentity 2\n");
    printMatrix(id2);
    //if (isUpperTriangle(id2)) printf("\tTriangle is Upper");
    //if (isLowerTriangle(id2)) printf("\tTriangle is Lower");

    S = newMatrix(3, 3);
    setElement(S, 1, 1, 1);
    setElement(S, 1, 2, 2);
    setElement(S, 1, 3, 4);
    setElement(S, 2, 1, 1);
    setElement(S, 2, 2, 2);
    setElement(S, 2, 3, 1);
    setElement(S, 3, 1, 5);
    setElement(S, 3, 2, 4.5);
    setElement(S, 3, 3, 2.4);
    if (isSym_and_Square(S) == 1) printf("\nS returned 1\n");

    // Get row or column
    int row = 2;
    int column = 3;
    printf("\nMatrix S\n");
    printMatrix(S);
    printf("\n");
    rS = getRow(S, row);
    printMatrix(rS);
    printf("\nMatrix S\n");
    printMatrix(S);
    cS = getColumn(S, column);
    printMatrix(cS);

	deleteMatrix(A);
	deleteMatrix(Ac);
	deleteMatrix(B);
	deleteMatrix(c);
	deleteMatrix(d);
	deleteMatrix(M);
	deleteMatrix(ct);
	deleteMatrix(mdp);
    deleteMatrix(id);
    deleteMatrix(id2);
	deleteMatrix(S);
    deleteMatrix(rS);
    deleteMatrix(cS);

	return 0;
}
