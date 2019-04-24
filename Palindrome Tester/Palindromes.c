/*-------------------------------------*\
|DESCRIPTION: The palindrome tester.	|
|CLASS: COSC 1420.S01					|
|AUTHOR: Alex Dierks					|
|DATE: February 25, 2019				|
\*-------------------------------------*/

#pragma warning (disable: 4996)

#include <conio.h>
#include <ctype.h> /*For tolower()*/
#include <stdio.h>

int main()
{
	char line[81];
	char wasEND;
	char isPalindrome;
	short numChars; /*The number of readable characters for line.*/

	printf("PALINDROME TESTER\n");
	printf("Case insensitive. Do not enter more than 80 characters.\nType END to quit.\n\n");

	do
	{
		printf("\nEnter somethin': ");
		fgets(line, 81, stdin); /*Ends the C-String with \n, NOT \0.*/
		wasEND = (line[0] == 'E' && line[1] == 'N' && line[2] == 'D' && line[3] == '\n');

		if (!wasEND)
		{
			isPalindrome = 1;
			for (numChars = 0; line[numChars] != '\n'; numChars++);
			line[numChars] = '\0'; /*Replace the \n with \0.*/

			/*If the C-string has an odd number of readable characters, the one in the middle does not matter.*/
			for (short i = 0; i < (numChars / 2); i++)
			{
				if (tolower(line[i]) != tolower(line[(numChars - 1) - i])) /*Last usable index is numChars - 1.*/
					isPalindrome = 0; /*If at any point the characters do not match, it is not a palindrome.*/
			}

			printf("%s was %sa palindrome.\n", line, (isPalindrome? "" : "not "));
		}
	} while (!wasEND);

	printf("\nPress anything to exit. ");
	_getch();
	return 0;
}