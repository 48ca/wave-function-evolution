// #include <fftw3.h>
// Uncomment when necessary
#include "complex.hpp"
#include "lattice.hpp"
#include "state.hpp"
#include <cstdio>
#include <cstdlib>
#include "libs/handle.h"

#define DEFAULT_STEPS 100000
#define DEFAULT_LATTICE_SIZE 500
#define DEFAULT_LATTICE_WIDTH 30.0
#define DEFAULT_WAVE_WIDTH 1.0
#define DEFAULT_OUTFILE (char*)"outqu.txt"
#define DEFAULT_TIMESTEP 0.005
#define DEFAULT_WAVE_WRITE 400

int main(int argc, char** argv)
{

	// char* filename           = setDefaultArgument((char*)"Output filename");
	char* outputFilename     = addArgument((char*)"Output filename", TAKES_ONE_ARGUMENT, (char*)"-o", (char*)"--out");
	char* historySizeOption  = addArgument((char*)"Number of steps", TAKES_ONE_ARGUMENT, (char*)"-n", (char*)"--steps");
	char* latticeSizeOption  = addArgument((char*)"Size of lattice", TAKES_ONE_ARGUMENT, (char*)"-s", (char*)"--size");
	char* latticeWidthOption = addArgument((char*)"Width of lattice", TAKES_ONE_ARGUMENT, (char*)"-w", (char*)"--width");
	char* waveWidthOption    = addArgument((char*)"Width of the wave", TAKES_ONE_ARGUMENT, (char*)"-g", (char*)"--gauss");
	char* waveWriteOption    = addArgument((char*)"Waves until write", TAKES_ONE_ARGUMENT, (char*)"-u", (char*)"--wuw");
	char* timestepOption     = addArgument((char*)"Timestep", TAKES_ONE_ARGUMENT, (char*)"-t", (char*)"--timestep");
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

	int latticeSize = 0;
	if(argSet(latticeSizeOption)) {
		latticeSize = atoi(latticeSizeOption);
	}
	if(latticeSize == 0) latticeSize = DEFAULT_LATTICE_SIZE;

	_float latticeWidth = 0;
	if(argSet(latticeWidthOption)) {
		latticeWidth = (_float)(atof(latticeWidthOption));
	}
	if(latticeWidth <= 0) latticeWidth = DEFAULT_LATTICE_WIDTH;

	_float timestep = 0;
	if(argSet(timestepOption)) {
		timestep = (_float)(atof(timestepOption));
	}
	if(timestep <= 0) timestep = DEFAULT_TIMESTEP;

	_float waveWidth = 0;
	if(argSet(waveWidthOption)) {
		waveWidth = (_float)(atof(waveWidthOption));
	}
	if(waveWidth <= 0) waveWidth = DEFAULT_WAVE_WIDTH;

	int waveWrite = 0;
	if(argSet(waveWriteOption)) {
		waveWrite = atoi(waveWriteOption);
	}
	if(waveWrite <= 0) waveWrite = DEFAULT_WAVE_WRITE;

	// printf("Generating a history of %d lattice states (%f MB)\n",
	//  steps, ((float)((sizeof(Lattice)+latticeSize*(sizeof(State)+sizeof(Complex))) * steps))/(1e6));

	Lattice* history = new Lattice[steps + 1];

	puts("Finished allocating memory");

	// Initialize

	// Set initial lattice (*history);

	puts("Setting initial state...");
	history->initialize(latticeWidth, latticeSize);
	history->setInitialStatequ(waveWidth); // wave width

	// Evolve

	puts("Evolving...");
	printf("Writing every %d evolutions\n", waveWrite);

	Lattice* curr = &(history[0]);
	Lattice* next = NULL;
	printf("\n");


	FILE* f = fopen(outputFilename, "w");
	if(f == NULL)
	{
		fprintf(stderr, "Cannot write to %s\n", outputFilename);
		return 1;
	}

	register int i;
	for(i=0;i<steps;++i)
	{
		next = &(history[1+i]);
		next->initialize(latticeWidth, latticeSize);

		curr->evolvequ(timestep, next);

		if(i % waveWrite == 0) {
			history[i].writeLattice(f);
			fprintf(f, "\n");
		}

		char prob[128];
		printFloat(prob, curr->prob);

		delete [] curr->lattice;
		curr = next;

		printf("\rSteps: %09d : prob %s", i, prob);
		fflush(stdout);
	}
	printf("\n");

	// Analyze

	return 0;

}
