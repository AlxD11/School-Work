/*-------------------------------------------------------------*\
|DESCRIPTION: Final project: complex number matrix multiplier.	|
|AUTHOR: Alex Dierks											|
|DATE: May 6, 2019												|
\*-------------------------------------------------------------*/

#ifndef COMPLEX_H
#define COMPLEX_H

struct Complex
{
	long double real;
	long double i;
};

struct Complex add(const struct Complex* num1, const struct Complex* num2);
struct Complex subtract(const struct Complex* num1, const struct Complex* num2);
struct Complex multiply(const struct Complex* num1, const struct Complex* num2);
struct Complex divide(const struct Complex* num1, const struct Complex* num2);

struct Complex read();
void display(const struct Complex* num);
void displayln(const struct Complex* num);

#endif