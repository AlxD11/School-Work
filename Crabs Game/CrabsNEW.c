/*-----------------------------*\
|DESCRIPTION: Basic Craps Game.	|
|CLASS: COSC 1420.S01			|
|AUTHOR: Alex Dierks			|
|DATE: March 25, 2019			|
\*-----------------------------*/

#pragma warning (disable: 4996)

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef char boolean;
#define TRUE 1
#define FALSE 0

char rollDie();
char rollPair();
boolean restart();

int main()
{
	double winnings = 50;
	double bet;
	char roll;
	char dummy;
	boolean quit = FALSE;

	srand(time(0));

	printf("\t\tWELCOME TO\nTHE CRAPPIEST CRAPS GAME YOU'LL EVER EXPERIENCE\n");

	do
	{
		printf("\nYou have $%.2lf.\n", winnings);
		printf("Place a bet: ");
		scanf("%lf%c", &bet, &dummy);
		while (bet < 0 || bet > winnings)
		{
			if (bet < 0)
				printf("You can't bet negative money.\n\nPlace a legal bet: ");
			else
				printf("You don't have that much.\n\nPlace a legal bet: ");
			scanf("%lf%c", &bet, &dummy);
		}

		roll = rollPair();
		printf("Roll: %d\n\n", roll);
		switch (roll)
		{
			case 7:
			case 11:
			{
				printf("WINNER!!\n");
				winnings += bet;
				break;
			}
			
			case 2:
			case 3:
			case 12:
			{
				printf("Insta-lose.\n");
				winnings -= bet;
				break;
			}

			default:
			{
				char point = roll;
				boolean exitPoint = FALSE;

				do
				{
					printf("Point: %d\nPress anything to roll.\nRoll: ", point);
					_getch();
					roll = rollPair();
					printf("%d\n\n", roll);

					if (roll == point)
					{
						printf("WINNER!!\n");
						winnings += bet;
						exitPoint = TRUE;
					}
					else if (roll == 7)
					{
						printf("Insta-lose.\n");
						winnings -= bet;
						exitPoint = TRUE;
					}
				} while (!exitPoint);

				break;
			}
		}

		if (winnings > 0)
		{
			printf("Winnings: $%.2lf.\n", winnings);
			quit = restart();
		}
		else
		{
			printf("Winnings: $%.2lf.\nYou lost! Better luck next time.\n", winnings);
			quit = TRUE;
		}

	} while (!quit);

	printf("Thanks for playing!\n\nPress anything to continue...");
	_getch();
	return 0;
}

char rollDie()
{
	return (rand() % 6) + 1;
}

char rollPair()
{
	return rollDie() + rollDie();
}

boolean restart()
{
	char c, dummy;
	printf("\nRoll again? No (N), yes (anything else): ");
	scanf("%c%c", &c, &dummy);
	return (c == 'N' || c == 'n');
}