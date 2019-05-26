/*-------------------------------------------------------------*\
|DESCRIPTION: Final project: complex number matrix multiplier.	|
|AUTHOR: Alex Dierks											|
|DATE: May 6, 2019												|
\*-------------------------------------------------------------*/

#pragma warning (disable: 4996)

#include <stdio.h>
#include <malloc.h>

#include "Complex.h"
#include "ProjectFunctions.h"

/*Loads the matrix with data from the file.
Returns the last code gotten from fscanf().*/
int fillMatrix(struct Complex** matrix, const int rows, const int cols, const FILE* data)
{
	int scanCode;
	char dummy;

	for (int r = 0; r < rows; r++)
		for (int c = 0; c < cols; c++)
		{
			scanCode = fscanf(data, "(%lf %lf)%c", &matrix[r][c].real, &matrix[r][c].i, &dummy);
		}

	return scanCode;
}

/*This function IS NOT responsible for cleaning up the returned Complex** it dynamically allocates!*/
struct Complex** multiplyMatricies(const struct Complex** matrixA, const int rowsA, const int colsA, const struct Complex** matrixB, const int rowsB, const int colsB, int* rowsC, int* colsC)
{
	*rowsC = rowsA;
	*colsC = colsB;
	
	struct Complex** C = (struct Complex**) malloc((*rowsC) * sizeof(struct Complex*));
	for (int i = 0; i < (*rowsC); i++)
		C[i] = (struct Complex*) malloc((*colsC) * sizeof(struct Complex));

	for (int rowOfA = 0; rowOfA < rowsA; rowOfA++)
	{
		for (int colOfB = 0; colOfB < colsB; colOfB++)
		{
			C[rowOfA][colOfB] = *dotProduct(matrixA, matrixB, colsA, rowOfA, colOfB);
		}
	}

	return C;
}

struct Complex* dotProduct(const struct Complex** matrixA, const struct Complex** matrixB, const int colsA, const int rowOfA, const int colOfB)
{
	struct Complex temp;
	struct Complex product;
	product.real = 0;
	product.i = 0;

	for (int i = 0; i < colsA; i++) /*Going across matrixA / down matrixB.*/
	{
		temp = multiply(&matrixA[rowOfA][i], &matrixB[i][colOfB]);
		product = add(&product, &temp);
	}

	return &product;
}

void displayMatrix(const struct Complex** matrix, const int rows, const int cols)
{
	int r, c;

	for (r = 0; r < rows; r++)
	{
		printf("%c", 186);
		for (c = 0; c < cols; c++)
		{
			printf(" [");
			display(&matrix[r][c]);
			printf("]");
		}
		printf("%c\n", 186);
	}
}