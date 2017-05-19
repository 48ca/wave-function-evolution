// #include <fftw3.h>
// Uncomment when necessary
#include "complex.hpp"
#include "lattice.hpp"
#include <cstdio>
#include <cstdlib>
#include "libs/handle.h"

#define DEFAULT_STEPS 100
#define DEFAULT_LATTICE_SIZE 100
#define DEFAULT_OUTFILE (char*)"out.txt"

int main(int argc, char** argv)
{

	// char* filename           = setDefaultArgument((char*)"Output filename");
	char* outputFilename     = addArgument((char*)"Output filename", TAKES_ONE_ARGUMENT, (char*)"-o", (char*)"--out");
	char* historySizeOption  = addArgument((char*)"Number of steps", TAKES_ONE_ARGUMENT, (char*)"-n", (char*)"--steps");
	char* latticeSizeOption  = addArgument((char*)"Size of lattice", TAKES_ONE_ARGUMENT, (char*)"-s", (char*)"--size");
	char* helpOption         = addArgument((char*)"Print usage", TAKES_NO_ARGUMENTS, (char*)"-h", (char*)"--help");

	int argError;
	argError = handle(argc, argv);
	if(argError) {
		fprintf(stderr, "Run `evolve --help` for more information\n");
		return argError;
	}

	if(argSet(helpOption)) {
		printUsage();
		return 0;
	}

	if(argSet(outputFilename)) {
		// Output specified
		printf("Writing output to %s\n", outputFilename);
	} else {
		free(outputFilename);
		outputFilename = DEFAULT_OUTFILE;
	}

	int steps = 0;
	// steps defines the number of times the program will evolve our lattice
	if(argSet(historySizeOption)) {
		steps = atoi(historySizeOption);
	}
	if(steps == 0) steps = DEFAULT_STEPS;
	unsigned int latticeSize = 0;
	if(argSet(latticeSizeOption)) {
		latticeSize = atoi(latticeSizeOption);
	}
	if(latticeSize == 0) latticeSize = DEFAULT_LATTICE_SIZE;

	printf("Generating a history of %d lattice states (%f MB)\n",
			steps, ((float)((sizeof(Lattice)+1000*sizeof(Complex)) * steps))/(1e6));

	Lattice* history = new Lattice[steps + 1];
	register int i;
	for(i = 0; i < steps + 1; ++i)
		history[i].initialize(0, latticeSize, 0);

	puts("Finished allocating memory");

	// Initialize

	_float timestep = .01; // Something
	// Set initial lattice (*history);

	puts("Setting initial state...");
	history->setInitialState(timestep);

	// Evolve

	puts("Evolving...");

	Lattice* prev = history;
	size_t latticeTypeSize = sizeof(Lattice);
	Lattice* curr = history + latticeTypeSize;
	for(i=0;i<steps;++i)
	{
		curr->evolve(timestep, prev);
		prev = curr;
		curr += latticeTypeSize;
	}

	FILE* f = fopen(outputFilename, "w");
	if(f == NULL)
	{
		fprintf(stderr, "Cannot write to %s\n", outputFilename);
		return 1;
	}
	for(i = 0; i < steps + 1; ++i)
	{
		history[i].writeLattice(f);
		fprintf(f, "\n");
	}

	// Analyze

	free(history);

	return 0;

}
