// #include <fftw3.h>
// Uncomment when necessary
#include "complex.hpp"
#include "lattice.hpp"
#include <cstdio>
#include <cstdlib>
#include "libs/handle.h"

#define DEFAULT_STEPS 1000

int main(int argc, char** argv)
{

	char* filename     = setDefaultArgument((char*)"infile");
	char* historySize  = addArgument((char*)"Number of steps", TAKES_ONE_ARGUMENT, (char*)"-n", NULL);
	char* helpOption   = addArgument((char*)"Print usage", TAKES_NO_ARGUMENTS, (char*)"-h", (char*)"--help");

	int argError;
	argError = handle(argc, argv);
	if(argError) {
		fprintf(stderr, "Run `evolve --help` for more information");
		return argError;
	}

	if(argSet(helpOption)) {
		printUsage();
		return 0;
	}

	if(argSet(filename)) {
		// Lattice file specified
	}

	int steps = 0;
	// steps defines the number of times the program will evolve our lattice
	if(argSet(historySize)) {
		steps = atoi(historySize);
	}
	if(steps == 0) steps = DEFAULT_STEPS;

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
