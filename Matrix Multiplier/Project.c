/*-------------------------------------------------------------*\
|DESCRIPTION: Final project: complex number matrix multiplier.	|
|AUTHOR: Alex Dierks											|
|DATE: May 6, 2019												|
\*-------------------------------------------------------------*/

#pragma warning (disable: 4996)

#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "Complex.h"
#include "ProjectFunctions.h"

#define MAX_FILE_NAME_LENGTH (63)
#define TRUE (1)
#define FALSE (0)

typedef char BOOLEAN;

int main()
{
	FILE* data;
	char fileName[MAX_FILE_NAME_LENGTH + 1];
	int fileCode = 0;
	BOOLEAN retryName;
	
	int colsA = 0, rowsA = 0;
	int colsB = 0, rowsB = 0;
	int colsC = 0, rowsC = 0;

	struct Complex** A;
	struct Complex** B;
	struct Complex** C;

	do
	{
		retryName = FALSE;
		printf("Enter the name of the file containing the matrix data: ");
		fgets(fileName, MAX_FILE_NAME_LENGTH + 1, stdin); /*Will read in \n instead of \0 and leave excess on the instream.*/
		
		short i = 0;
		for (i = 0; i < MAX_FILE_NAME_LENGTH && fileName[i] != '\n'; i++);
		fileName[i] = '\0';

		data = fopen(fileName, "r");

		if (data != NULL)
		{
			char c;
			fileCode = fscanf(data, "%d %d %d%c", &rowsA, &colsA, &colsB, &c);
			rowsB = colsA;
			rowsC = rowsA;
			colsC = colsB;

			if (fileCode != EOF)
			{
				A = (struct Complex**) malloc(rowsA * sizeof(struct Complex*));
				for (short i = 0; i < rowsA; i++)
					A[i] = (struct Complex*) malloc(colsA * sizeof(struct Complex));
				
				B = (struct Complex**) malloc(rowsB * sizeof(struct Complex*));
				for (short i = 0; i < rowsB; i++)
					B[i] = (struct Complex*) malloc(colsB * sizeof(struct Complex));

				fillMatrix(A, rowsA, colsA, data);
				fillMatrix(B, rowsB, colsB, data);

				C = multiplyMatricies(A, rowsA, colsA, B, rowsB, colsB, &rowsC, &colsC);
				printf("\nThe resulting matrix was: \n");
				displayMatrix(C, rowsC, colsC);

				fclose(data);
				for (int i = 0; i < rowsA; i++)
					free(A[i]);
				free(A);
				for (int i = 0; i < rowsB; i++)
					free(B[i]);
				free(B);
				for (int i = 0; i < rowsC; i++)
					free(C[i]);
				free(C);
			}
			else
			{
				printf("Unexpected end of file, data not read.\n\n");
				fclose(data);
				retryName = TRUE;
			}
		}
		else
		{
			printf("Could not open file \"%s\".\n\n", fileName);
			retryName = TRUE;
		}
	} while (retryName);

	printf("\nEnd me. ");
	_getch();
	return 0;
}