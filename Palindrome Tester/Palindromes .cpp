/*-----------------------------------------*\
|	DESCRIPTION: The palindrome program.	|
|	CLASS:		 COSC 1436.S02				|
|	AUTHOR:		 Alex Ray					|
|	DATE:		 September 25, 2017			|
\*-----------------------------------------*/

#include <iostream>
#include <cstring>
#include <limits>

using namespace std;

const int INPUT_SIZE = 80;
char input[INPUT_SIZE + 1];
char firstHalf[(INPUT_SIZE / 2) + 1]; //40 chars + one \0 (that will have to be added).
char secondHalf[(INPUT_SIZE / 2) + 1]; //40 chars + one \0 (that will have to be added).
bool restart = true;
bool isPalindrome = true;

int main()
{
	cout << "PALINDROME TESTER" << endl;
	cout << "END - quit" << endl;

	while (restart)
	{
		firstHalf[0] = '\0'; //"Clear" arrays of junk or previous input by just cutting them off at the first slot.
		secondHalf[0] = '\0';
		cout << "Enter a line of text: ";
		cin.getline(input, INPUT_SIZE + 1);

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<long long>::max(), '\n'); //Ignore entered characters untill a newline or the max value of a long long has been reached.
			cout << "Ya done goofed." << endl;
		}
		else if (!(input[0] == 'E' && input[1] == 'N' && input[2] == 'D' && input[3] == '\0')) //!(strcmp("END", input) == 0)
		{
			int size = 0; //= strlen(input);
			while (input[size] != '\0')
			{
				size++;
			}

			//The size check in cin takes care of checking for the size agin here, but I'm doing it anyway because index out of bounds sUCKS.
			if ((size > 0) && (size <= INPUT_SIZE)) //If the input contains at least one displayabe character and does not exceed the max array size...
			{
				int maxIndex = size - 1; //Since indexes end at one less than the size, -1 disables the index from returning \0.
				int halfwayPoint;

				if (!(size % 2) == 0) //If odd...
				{
					halfwayPoint = maxIndex / 2;
					for (int i1 = 0, i2 = maxIndex; (i1 < halfwayPoint) && (i2 > halfwayPoint); i1++, i2--)
					{
						//Keep off the halfwayPoint, because it's the middle char and does not affect the palindrome.
						firstHalf[i1] = input[i1];
						secondHalf[i1] = input[i2];
					}
				}
				else //If even...
				{
					halfwayPoint = size / 2;
					for (int i1 = 0, i2 = maxIndex; (i1 < halfwayPoint) && (i2 >= halfwayPoint); i1++, i2--)
					{
						firstHalf[i1] = input[i1];
						secondHalf[i1] = input[i2];
					}
				}

				firstHalf[halfwayPoint] = '\0'; //Sets the last char to the end of string character.
				secondHalf[halfwayPoint] = '\0';
				isPalindrome = true;

				int i = 0;
				while (firstHalf[i] != '\0') //Make the first half lowercase.
				{
					switch (firstHalf[i])
					{
					case 'A': firstHalf[i] = 'a'; break;
					case 'B': firstHalf[i] = 'b'; break;
					case 'C': firstHalf[i] = 'c'; break;
					case 'D': firstHalf[i] = 'd'; break;
					case 'E': firstHalf[i] = 'e'; break;
					case 'F': firstHalf[i] = 'f'; break;
					case 'G': firstHalf[i] = 'g'; break;
					case 'H': firstHalf[i] = 'h'; break;
					case 'I': firstHalf[i] = 'i'; break;
					case 'J': firstHalf[i] = 'j'; break;
					case 'K': firstHalf[i] = 'k'; break;
					case 'L': firstHalf[i] = 'l'; break;
					case 'M': firstHalf[i] = 'm'; break;
					case 'N': firstHalf[i] = 'n'; break;
					case 'O': firstHalf[i] = 'o'; break;
					case 'P': firstHalf[i] = 'p'; break;
					case 'Q': firstHalf[i] = 'q'; break;
					case 'R': firstHalf[i] = 'r'; break;
					case 'S': firstHalf[i] = 's'; break;
					case 'T': firstHalf[i] = 't'; break;
					case 'U': firstHalf[i] = 'u'; break;
					case 'V': firstHalf[i] = 'v'; break;
					case 'W': firstHalf[i] = 'w'; break;
					case 'X': firstHalf[i] = 'x'; break;
					case 'Y': firstHalf[i] = 'y'; break;
					case 'Z': firstHalf[i] = 'z'; break;
					}
					i++;
				}

				i = 0;
				while (secondHalf[i] != '\0') //Make the second half lowercase, too.
				{
					switch (secondHalf[i])
					{
					case 'A': secondHalf[i] = 'a'; break;
					case 'B': secondHalf[i] = 'b'; break;
					case 'C': secondHalf[i] = 'c'; break;
					case 'D': secondHalf[i] = 'd'; break;
					case 'E': secondHalf[i] = 'e'; break;
					case 'F': secondHalf[i] = 'f'; break;
					case 'G': secondHalf[i] = 'g'; break;
					case 'H': secondHalf[i] = 'h'; break;
					case 'I': secondHalf[i] = 'i'; break;
					case 'J': secondHalf[i] = 'j'; break;
					case 'K': secondHalf[i] = 'k'; break;
					case 'L': secondHalf[i] = 'l'; break;
					case 'M': secondHalf[i] = 'm'; break;
					case 'N': secondHalf[i] = 'n'; break;
					case 'O': secondHalf[i] = 'o'; break;
					case 'P': secondHalf[i] = 'p'; break;
					case 'Q': secondHalf[i] = 'q'; break;
					case 'R': secondHalf[i] = 'r'; break;
					case 'S': secondHalf[i] = 's'; break;
					case 'T': secondHalf[i] = 't'; break;
					case 'U': secondHalf[i] = 'u'; break;
					case 'V': secondHalf[i] = 'v'; break;
					case 'W': secondHalf[i] = 'w'; break;
					case 'X': secondHalf[i] = 'x'; break;
					case 'Y': secondHalf[i] = 'y'; break;
					case 'Z': secondHalf[i] = 'z'; break;
					}
					i++;
				}

				for (int i = 0; i <= (INPUT_SIZE / 2) + 1; i++) //(stricmp(firstHalf, secondHalf) == 0)
				{
					if ((firstHalf[i] == '\0' || secondHalf[i] == '\0') && (firstHalf[i] != secondHalf[i]))
					{
						isPalindrome = false;
						break;
					}
					else if (firstHalf[i] != secondHalf[i])
					{
						isPalindrome = false;
						break;
					}
					else if (firstHalf[i] == '\0' && secondHalf[i] == '\0')
					{
						break;
					}
				}

				cout << input << (isPalindrome ? " is a palindrome." : " isn't a palindrome.") << endl;
			}
			else if (size == 0)
				cout << "Is this a trick question? Actually enter some characters." << endl;
			else
				cout << "That was too long. The max is 80 characters." << endl; //Will never display but I don't care.
		}
		else //input was END
			restart = false;
	}

	return 0;
}