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
	// steps defines the number of times the program will evolve our lattice

	printf("Generating a history of %d lattice states (%f MB)\n",
			steps, ((float)((sizeof(Lattice)+1000*sizeof(Complex)) * steps))/(1e6));

	Lattice* history = new Lattice[steps + 1];

	// Initialize

	_float timestep = 0.01; // Something
	// Set initial lattice (*history);

	// Evolve

	puts("Evolving...");

	register int i;
	Lattice* prev = history;
	size_t latticeSize = sizeof(Lattice);
	Lattice* curr = history + latticeSize;
	for(i=0;i<steps;++i)
	{
		curr->evolve(timestep, prev);
		prev = curr;
		curr += latticeSize;
	}

	// Analyze

	free(history);

	return 0;

}
