/*-----------------------------------------------------*\
|	DESCRIPTION: One crappy game of craps.				|
|	CLASS:		 COSC 1436.S02							|
|	AUTHOR:		 Alex Ray								|
|	DATE:		 October 22, 2017						|
\*-----------------------------------------------------*/

#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

using namespace std;

void init();
int throwDie();
double readDouble();
bool wasRuleCommand();
void printRules();
void promptRestart(bool&, double money);

double money = 50.0, bet = 0.0;
int die1, die2, dieTotal, point;
int wins = 0, losses = 0;
bool restart = true, retry = true;
bool rules = false;

int main()
{
	init();
	while (restart)
	{
		cout << "WELCOME TO CRAPPY CRAPS" << endl;
		cout << "R - view rules" << endl;
		cout << "Wins:   " << wins << endl;
		cout << "Losses: " << losses << endl;
		cout << "Money: $" << money << endl;
		cout << "Place Bet: ";
		bet = readDouble();
		while (bet < 0 || bet > money && !wasRuleCommand())
		{
			cout << "Invalid bet!" << endl;
			cout << "Place Bet: ";
			bet = readDouble();
		}
		if (!wasRuleCommand())
		{
			cout << "\nYou threw " << (die1 = throwDie()) << " and " << (die2 = throwDie()) << endl;
			cout << "Total: " << (dieTotal = die1 + die2) << endl;
			if (dieTotal == 7 || dieTotal == 11)
			{
				cout << "WIN! Money: " << (money += bet) << endl;
				promptRestart(restart, money);
				wins++;
			}
			else if (dieTotal == 2 || dieTotal == 3 || dieTotal == 12)
			{
				cout << "LOSE! Money: " << (money -= bet) << endl;
				promptRestart(restart, money);
				losses++;
			}
			else
			{
				point = dieTotal;
				retry = true;
				while (retry)
				{
					cout << "\nPoint: " << point << endl;
					cout << "You threw " << (die1 = throwDie()) << " and " << (die2 = throwDie()) << endl;
					cout << "Total: " << (dieTotal = die1 + die2) << endl;
					if (point == dieTotal)
					{
						cout << "WIN! Money: " << (money += bet) << endl;
						promptRestart(restart, money);
						retry = false;
						wins++;
					}
					else if (dieTotal == 7)
					{
						cout << "LOSE! Money: " << (money -= bet) << endl;
						promptRestart(restart, money);
						retry = false;
						losses++;
					}
				}
			}
			system("cls");
		}
		else
		{
			cout << "Press any key to return to game." << endl;
			_getch();
			cout << endl;
		}
	}
	cout << "Thanks for playing!" << endl;
	system("pause");
	return 0;
}

void init()
{
	srand(time(0));
}

int throwDie() //Returns 1 - 6 with even probabilities
{
	return (rand() % 6) + 1;
}

/*@author Professor Slater
Hand copied because that's how I learn.*/
static void backspace() //"static" here means this function can only be used in this file, i.e. it is private.
{
	_putch('\b');
	_putch(' ');
}

/*@author Professor Slater
Hand copied because that's how I learn.
Modified to accept commands and not allow negatives or more than 2 decimal places.*/
double readDouble()
{
	char c;
	bool digits = false;
	int fraction = 0;
	double num = 0.0;
	rules = false;

	while (!isspace(c = static_cast <char> (_getch()))) //isspace returns true for ' ', '\t', '\n', '\v' vertical tab, '\f' feed, and return '\r'.
	{
		switch (c)
		{
			case '.':
				if (!rules) //Prevent more typing if there is an r or R, or the fraction would go into the 1,000's place.
				{
					if (fraction == 0)
						fraction = 1;
					else
						c = '\a';
				}
				else
					c = '\a';
				_putch(c);
				break;
			case '\b':
				if (fraction > 0) //If there is a decimal point...
				{
					backspace();
					fraction /= 10; //Make the decimal 10X larger.
					if (fraction > 0) //If there is still a decimal point after backspacing...
					{
						num = static_cast <int> (num * fraction);
						num /= fraction;
					}
				}
				else if (digits)
				{
					backspace();
					num = static_cast <int> (num) / 10;
					if (num == 0.0)
					{
						digits = false;
					}
				}
				else if (rules)
				{
					backspace();
					rules = false;
				}
				else
					c = '\a'; //BEEP.
				_putch(c);
				break;
			case 'R':
			case 'r':
				if (!rules && !digits) //Prevent more typing if there is an r or R.
				{
					rules = true;
					_putch(c);
				}
				else
					_putch('\a');
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if (!rules && ((fraction * 10) <= 100)) //Prevent more typing if there is an r or R, or the fraction would go into the 1,000's place.
				{
					digits = true;
					if (fraction > 0) //If there is a decimal point...
					{
						fraction *= 10; //Make the decimal 10X smaller.
						num = num + ((c - '0') / static_cast <double> (fraction));
					}
					else
						num = (num * 10.0) + (c - '0');
					_putch(c);
				}
				else
					_putch('\a');
				break;
			default: c = '\a'; _putch(c); //Do a beep.
		}
	}
	if (c == '\r')
		c = '\n';
	_putch(c);
	if (rules)
		printRules();
	return num;
}

/*@return True if the R/r rule command was used.*/
bool wasRuleCommand()
{
	return rules;
}

void printRules()
{
	cout << "\nRULES OF CRAPS:" << endl;
	cout << "Role two dice. If your total is 7 or 11, you win!" << endl;
	cout << "If your total is 2, 3, or 12, you lose." << endl;
	cout << "If your total is anything else, you must role again to try and get that same value (called your \"point\"),\nand if during this time you get a 7, you lose." << endl;
	cout << "If during that time you get anything other than your point, you must keep rolling." << endl;
	cout << "Finally, make bets! If you win, you earn what you bet. Else, you loose it." << endl;
	cout << "Enjoy this crappy version of craps!\n" << endl;
}

void promptRestart(bool &restart, double money)
{
	if (money == 0)
	{
		cout << "You're out of money!" << endl;
		restart = false;
		cout << "Press any key to quit to game." << endl;
		_getch();
		cout << endl;
	}
	else
	{
		char input;
		cout << "Throw again? Y/N: ";
		cin >> input;
		if (cin.fail())
			cin.ignore(100, '\n');
		if (!(input == 'Y' || input == 'y'))
			restart = false;
	}
}