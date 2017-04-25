// #include <fftw3.h>
// Uncomment when necessary
#include "complex.hpp"
#include "lattice.hpp"
#include <cstdio>
#include <cstdlib>

int main(int argc, char** argv)
{

	if(argc < 2) {
		puts("usage: evolve <number of steps>");
		return 1;
	}

	const int steps = atoi(argv[1]);

	printf("Generating a history of %d lattice states (%f MB)\n",
			steps, ((float)((sizeof(Lattice)+1000*sizeof(Complex)) * steps))/(1e6));
	Lattice* history = new Lattice[steps];

	// Initialize
	//
	// Evolve
	//
	// Analyze

	free(history);

    return 0;

}
