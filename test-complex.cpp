#include "complex.hpp"
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

	printf("Testing conjugate operator...\n");

	int r = 3;
	int i = 4;
	printf("Should read: %d - %di\n", r , i);
	Complex conj(r, i);
	(~conj).print();

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
	Complex_I.print();

	printf("Testing complex multiplication...\n");
	printf(">>> Should read -1: ");
	(Complex_I*Complex_I).print();

	printf("Testing Euler's equation...\n");
	printf(">>> Should read 0: ");
	((Complex(M_E)^(Complex_I * M_PI)) + 1).print();


	return 0;

}

int main(int argc, char** argv)
{

	old_complex(argc, argv);

}
