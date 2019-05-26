/*-------------------------------------------------------------*\
|DESCRIPTION: Final project: complex number matrix multiplier.	|
|AUTHOR: Alex Dierks											|
|DATE: May 6, 2019												|
\*-------------------------------------------------------------*/

#ifndef PROJECT_FUNCTIONS_H
#define PROJECT_FUNCTIONS_H

int fillMatrix(struct Complex** matrix, const int rows, const int cols, const FILE* data);
void displayMatrix(const struct Complex** matrix, const int rows, const int cols);

struct Complex** multiplyMatricies(const struct Complex** matrixA, const int rowsA, const int colsA, const struct Complex** matrixB, const int rowsB, const int colsB, int* rowsC, int* colsC);
struct Complex* dotProduct(const struct Complex** matrixA, const struct Complex** matrixB, const int colsA, const int rowOfA, const int colOfB);

#endif