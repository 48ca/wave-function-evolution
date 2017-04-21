#include "complex.hpp"
#include <quadmath.h>
#include <cstdio>
#include <cmath>

int old_complex(int argc, char** argv)
{

	printf("Testing complex number printing...\n");

	int a = 60;
	int b = 125;
	printf("Should read: %d + %di\n", a, b);
	Complex co(a, b);
	co.print();
	printf("Done\n");

	printf("Testing complex number addition...\n");

	int c = 720;
	int d = 230;

	Complex ca1(a, b);
	Complex ca2(c, d);
	Complex ca3;

	ca1.print();
	ca2.print();
	printf(">>> Summed together: ");
	ca3 = ca1+ca2;
	ca3.print();
	ca3 += ca2;
	ca3.print();
	ca3 -= (ca1 + ca2 * 2);
	printf(">>> Should read 0: ");
	ca3.print();

	printf("Testing use of I...\n");
	I.print();

	printf("Done\n");

	printf("Testing complex multiplication...\n");
	printf(">>> Should read -1: ");
	(I*I).print();

	printf("Testing Euler's equation...\n");
	printf(">>> Should read -1: ");
	(Complex(M_E)^(I * M_PI) + 1).print();


	return 0;

}

int main(int argc, char** argv)
{

	__complex128 a = 0;
	__real__ a = M_E;
	__complex128 b = 0;
	__imag__ b = 1;
	__complex128 c = cpowq(a, b * M_PI);

	Complex(__real__ c, __imag__ c).print();

}