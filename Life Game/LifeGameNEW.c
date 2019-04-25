/*-----------------------------*\
|DESCRIPTION: The Game of Life.	|
|CLASS: COSC 1420.S01			|
|AUTHOR: Alex Dierks			|
|DATE: March 3, 2019			|
\*-----------------------------*/

#pragma warning (disable: 4996)

#include <conio.h> /*Needed for _kbhit. On Linux/Mac, this is something else.*/
#include <stdio.h>
#include <stdlib.h> /*Used for system().*/
#include <memory.h>
#include <time.h> /*Includes the system normal time clock.*/

#define ROWS 60
#define COLS 60
#define MAX_ROWS (ROWS + 2) /*Adds one row to the very top and very bottom of the board to add a safe zone for faster neighbor checking. Use () for safety in later code.*/
#define MAX_COLS (COLS + 2) /*Adds one column to the very top and bottom of the board to add a safe zone for faster neighbor checking.*/
#define DEAD 0
#define LIVE 1
#define DYING 2
#define CREATE 3
#define TINY char

int main()
{
	TINY board[MAX_ROWS][MAX_COLS];
	for (short i = 0; i < (MAX_ROWS * MAX_COLS); i++)
		board[0][i] = 0;

	short waitTime;
	short row, col;
	char dummy;

	printf(" THE GAME OF LIFE\nEnter a time delay (in seconds): ");
	scanf("%d%c", &waitTime, &dummy);
	if (waitTime <= 0)
	{
		waitTime *= -1;
		if (waitTime == 0)
			waitTime++;
		printf("%d %s. Got it.\n", waitTime, ((waitTime == 1)? "second" : "seconds"));
	}

	printf("\nWould you like to choose coordinates manually (1),\n or randomly populate by %c of board (2) ? : ", '%');
	scanf("%c", &dummy);

	if (dummy == '1') /*Start getting coords.*/
	{
		scanf("%c", &dummy); /*Absorb previous Enter key.*/
		printf("\nEnter coords (0 - 59) of living cells.\nUse -1 -1 to finish, -2 -2 to undo.\n     Format: x y\n");
		short prevRow = -1, prevCol = -1;
		do
		{
			printf("Enter Coord: ");
			scanf("%d %d%c", &row, &col, &dummy);
			if (row == -2 && col == -2)
			{
				if ((prevRow == -1) && (prevCol == -1))
				{
					printf("Nothing could be automatically undone.\nManually enter the coord you want undone: ");
					scanf("%d %d%c", &row, &col, &dummy);
					if (row > (ROWS - 1) || row < 0 || col >(COLS - 1) || col < 0) /*If row or column are out of bounds...*/
						printf("Out of bounds.\n");
					else
						board[col + 1][row + 1] = DEAD;
				}
				else
				{
					board[prevCol + 1][prevRow + 1] = DEAD; /*The previous row and column have already been checked, so this is fine.*/
					printf("%d %d removed.\n", prevRow, prevCol);
					prevRow = -1;
					prevCol = -1;
				}
			}

			else if ((row == -1) && (col == -1)); /*Catch the exit condition so that the following doesn't get triggered.*/
			else if (row > (ROWS - 1) || row < 0 || col > (COLS - 1) || col < 0) /*If row or column are out of bounds...*/
				printf("Out of bounds.\n");
			else /*Else, it was inside le box.*/
			{
				prevRow = row;
				prevCol = col;
				board[col + 1][row + 1] = LIVE;
			}
		} while ((row != -1) && (col != -1));
	}
	else /*Randomly populate coordinates.*/
	{
		short numInit;

		printf("\nEnter %c of the board you want populated (do not type the %c sign): ", '%', '%');
		scanf("%c%d%c", &dummy, &numInit, &dummy);  /*Absorb Enter key before and after.*/
		numInit = (ROWS * COLS) * ((double)numInit / 100);
		srand(time(0));

		for (short i = 0; i < numInit; i++)
		{
			row = rand() % ROWS; /*% gets the remainder, which is going to be less than the divisor.*/
			col = rand() % COLS;
			board[col + 1][row + 1] = LIVE; /*+1 to keep it off of the dead boarder.*/
		}
	}

	short neighbors;
	time_t genWait = time(0);
	for (unsigned int gen = 0; ; gen++)
	{
		system("cls"); /*Clears the screen for Windows. On Mac/Unix, it's "clear".*/
		printf("\tGENERATION %d\t\tPress anything to quit.\n", gen);
		/*Print le board.*/
		for (row = 1; row <= ROWS; row++)
		{
			for (col = 1; col <= COLS; col++)
				printf("%c", board[row][col] ? '*' : ' '); /*#2Slik4U*/
			printf("\n");
		}

		for (row = 1; row <= ROWS; row++)
		{
			for (col = 1; col <= COLS; col++)
			{
				neighbors = 0;
				for (TINY i = -1; i < 2; i++)
				{
					if ((board[row - 1][col + i] == LIVE) || (board[row - 1][col + i] == DYING)) /*Above cell.*/
						neighbors++;
					if ((board[row + 1][col + i] == LIVE) || (board[row + 1][col + i] == DYING)) /*Below cell.*/
						neighbors++;
				}

				if ((board[row][col - 1] == LIVE) || (board[row][col - 1] == DYING)) /*On this row.*/
					neighbors++;
				if ((board[row][col + 1] == LIVE) || (board[row][col + 1] == DYING))
					neighbors++;

				if (neighbors > 4)
					board[row][col] = DYING;
				else if (neighbors == 3)
					board[row][col] = CREATE;
				else if (neighbors < 2)
				{
					if (board[row][col] == LIVE)
						board[row][col] = DYING;
				}
			}
		}

		/*Update the cells waiting to be created or killed.*/
		for (row = 1; row <= ROWS; row++)
		{
			for (col = 1; col <= COLS; col++)
			{
				if (board[row][col] == CREATE)
					board[row][col] = LIVE;
				else if (board[row][col] == DYING)
					board[row][col] = DEAD;
			}
		}

		genWait = time(0) + waitTime;
		while ((time(0) < genWait) && !_kbhit());
		if (_kbhit())
		{
			exit(0);
		}
	}

	return 0;
}