/*-----------------------------------------*\
|	DESCRIPTION: Game of Life simulation.	|
|	CLASS:		 COSC 1436.S02				|
|	AUTHOR:		 Alex Ray					|
|	DATE:		 October 2, 2017			|
\*-----------------------------------------*/

#include <iostream>
#include <cstring> //Contains <string.h>, IS NOT <string>.
#include <conio.h> //Handles _putch, _kbhit, and _getch stuff.
#include <memory.h> //For memset.
#include <time.h> //Can get the clock.

using namespace std;

//Prototypes.
void initBoard();
void printBoard();
void runGeneration();

const bool DEBUG = false;
time_t delay = 2; //Time in seconds to delay the next generation. time_t is an unsigned long long.
const int BOARD_SIZE = 60;
const int BOARD_SIZE_ACTUAL = BOARD_SIZE + 2; //Includes the border.
const int INPUT_SIZE = 4; //Includes room for "Yes\0".
char board[BOARD_SIZE_ACTUAL][BOARD_SIZE_ACTUAL]; //[Rows][Columns]
char input[INPUT_SIZE];
int coords[2]; //Holds previously entered coordinates so they can be undone.
int row, col, gen;
int currentTime;
bool canUndo = false;
bool restart = true;

int main()
{
	while (restart)
	{
		restart = true;
		row = col = gen = 0;
		memset(input, '\0', INPUT_SIZE * sizeof(char));
		memset(coords, 0, 2 * sizeof(int));
		initBoard();
		cout << "\"THE GAME OF LIFE\"" << endl;
		cout << "Enter some initial living cells, in the form of row column (space separator)." << endl;
		cout << "The board goes from 1 to 60." << endl;
		cout << "-1 -1 - start the simulation." << endl;
		cout << "0 0   - undo last entry" << endl;

		cout << "\nEnter a time delay (in whole seconds): ";
		cin >> delay;
		while (delay < 0 || cin.fail()) //If they enter a negative time or cin fails...
		{
			cout << "\nEnter a time delay (in POSITIVE whole seconds): ";
			cin >> delay;
		}

//---------------------------------------------------------- ENTERING LIVING CELLS ----------------------------------------------------------//
		while (!(row == -1 && col == -1))
		{
			if (DEBUG) cout << "DEBUG: (main) Main loop restarting..." << endl;
			cout << "Living Coordinate: ";
			cin >> row >> col;
			if (row == -1 && col == -1) //Print a debug statement and get out of the loop.
			{
				if (DEBUG) cout << "DEBUG: Running simulation..." << endl;
			}
			else if (row == 0 && col == 0) //Erase last coordinate.
			{
				if (!canUndo)
					cout << "There was nothing to undo." << endl;
				else //Get previous coordinates and set them back to nothing.
				{
					board[coords[0]][coords[1]] = ' ';
					canUndo = false;
					printBoard();
					cout << "Last entry undone." << endl;
				}
			}
			else if (row <= BOARD_SIZE && col <= BOARD_SIZE && row >= 1 && col >= 1)
			{
				if (DEBUG) cout << "DEBUG: (main) Coords were within board..." << endl;
				coords[0] = row;
				coords[1] = col;
				board[coords[0]][coords[1]] = '*';
				canUndo = true;
				printBoard(); //Display board after each valid entry.
			}
			else
			{
				cout << "That was out of bounds." << endl;
				canUndo = false;
			}
		}

// -------------------------------------------------------- RUNNING BOARD GENERATIONS --------------------------------------------------------//
		if ((row == -1 && col == -1))
		{
			system("cls");
			cout << "Generation " << gen << "\tPress any key to quit." << endl;
			printBoard(); //Make the first generation appear instantly.
			while (!_kbhit())
			{
				currentTime = time(0);
				while (time(0) < (currentTime + delay)) //Hang up the processor to delay running the next generations.
				{
					if (_kbhit())
						break;
				}
				if (_kbhit())
					break;
				else
					runGeneration();
			}
		}
		cout << "Program ended." << endl;

// ----------------------------------------------------------- ASKING FOR REPLAY ------------------------------------------------------------//
		if (restart)
		{
			cout << "Would you like to play again? Y/N: ";
			cin >> input;
			restart = !cin.fail() && (_stricmp("Y", input) == 0 || _stricmp("Yes", input) == 0);
		}
	}
	return 0;
}

void initBoard()
{
	memset(board, ' ', BOARD_SIZE_ACTUAL * BOARD_SIZE_ACTUAL * sizeof(char));
	for (int i = 0; i < BOARD_SIZE_ACTUAL; i++) //Create visual border.
	{
		//Use (char)221, not '\221'.
		//[Up/Down][Left/Right]
		board[i][0] = (char)221; //Left
		board[i][BOARD_SIZE_ACTUAL - 1] = (char)222; //Right
		board[0][i] = (char)220; //Top
		board[BOARD_SIZE_ACTUAL - 1][i] = (char)223; //Bottom
	}
}

void printBoard()
{
	if (DEBUG) cout << "DEBUG: (printBoard) Printing board..." << endl;
	for (int r = 0; r < BOARD_SIZE_ACTUAL; r++) //For indexes 0 - 61...
	{
		for (int c = 0; c < BOARD_SIZE_ACTUAL; c++)
			cout << board[r][c];
		cout << endl;
	}
}

void runGeneration()
{
	if (DEBUG) cout << "DEBUG: (runGeneration) Running generation..." << endl;
	for (int r = 1; r <= BOARD_SIZE; r++) //For indexes 1 - 60...
	{
		for (int c = 1; c <= BOARD_SIZE; c++)
		{
			//Check each cell's neighbors.
			int neighbors = 0;
			for (int i = -1; i <= 1; i++) //-1, 0, 1.
			{
				if ((board[r - 1][c + i] == '*') || (board[r - 1][c + i] == '-')) //Check the top row.
					neighbors++;
				if ((board[r + 1][c + i] == '*') || (board[r + 1][c + i] == '-')) //Check the bottom row.
					neighbors++;
			}
			if ((board[r][c - 1] == '*') || (board[r][c - 1] == '-')) //Check the left cell.
				neighbors++;
			if ((board[r][c + 1] == '*') || (board[r][c + 1] == '-')) //Check the right cell.
				neighbors++;

			//Determine what happens to each cell.
			//MUST INCLUDE check for the previous state.
			if ((neighbors == 3) && (board[r][c] == ' '))
				board[r][c] = '+'; //Cell not there about to exist.
			else if ((board[r][c] == '*') && ((neighbors >= 4) || (neighbors <= 1)))
				board[r][c] = '-'; //Cell already there about to die.
		}
	}
	//Change all temporary characters to permanent ones.
	for (int r = 1; r <= BOARD_SIZE; r++) //For indexes 1 - 60...
	{
		for (int c = 1; c <= BOARD_SIZE; c++)
		{
			if (board[r][c] == '+')
				board[r][c] = '*';
			else if (board[r][c] == '-')
				board[r][c] = ' ';
		}
	}
	gen++;
	system("cls");
	cout << "Generation " << gen << "\tPress any key to quit." << endl;
	printBoard();
}