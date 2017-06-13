// #include <fftw3.h>
// Uncomment when necessary
#include "complex.hpp"
#include "lattice.hpp"
#include "state.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "libs/handle.h"
#include "defaults.hpp"

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
	char* modeOption         = addArgument((char*)"Mode option", TAKES_ONE_ARGUMENT, (char*)"-m", (char*)"--mode");

	int mode = SCHRODINGER;

	if(!strcmp(argv[0], "./evolvewv") || !strcmp(argv[0], "evolvewv"))
		mode = CLASSICAL;

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

	if(argSet(modeOption)) {
		if(mode == CLASSICAL) {
			fprintf(stderr, "Ignoring mode option\n");
		}
		if(!strcmp(modeOption, "s") || !strcmp(modeOption, "schrodinger"))
			mode = SCHRODINGER;
		else if(!strcmp(modeOption, "c") || !strcmp(modeOption, "classical"))
			mode = CLASSICAL;
	}

	switch(mode) {
		case SCHRODINGER:
			puts("Running Schrodinger...");
			break;
		case CLASSICAL:
			puts("Running classical...");
			break;
	}

	generateDefaults(mode);

	// Now we start real command line argument parsing

	if(!argSet(outputFilename)) {
		free(outputFilename);
		outputFilename = defaults.outFile;
	}

	long steps = 0;
	// steps defines the number of times the program will evolve our lattice
	if(argSet(historySizeOption)) {
		steps = atoi(historySizeOption);
	}
	if(steps == 0) steps = defaults.steps;

	int latticeSize = 0;
	if(argSet(latticeSizeOption)) {
		latticeSize = atoi(latticeSizeOption);
	}
	if(latticeSize == 0) latticeSize = defaults.latticeSize;

	_float latticeWidth = 0;
	if(argSet(latticeWidthOption)) {
		latticeWidth = (_float)(atof(latticeWidthOption));
	}
	if(latticeWidth <= 0) latticeWidth = defaults.latticeWidth;

	_float timestep = 0;
	if(argSet(timestepOption)) {
		timestep = (_float)(atof(timestepOption));
	}
	if(timestep <= 0) timestep = defaults.timestep;

	_float waveWidth = 0;
	if(argSet(waveWidthOption)) {
		waveWidth = (_float)(atof(waveWidthOption));
	}
	if(waveWidth <= 0) waveWidth = defaults.waveWidth;

	int waveWrite = 0;
	if(argSet(waveWriteOption)) {
		waveWrite = atoi(waveWriteOption);
	}
	if(waveWrite <= 0) waveWrite = defaults.waveWrite;

	// printf("Generating a history of %d lattice states (%f MB)\n",
	//  steps, ((float)((sizeof(Lattice)+latticeSize*(sizeof(State)+sizeof(Complex))) * steps))/(1e6));

	free(waveWriteOption);
	free(waveWidthOption);
	free(timestepOption);
	free(latticeWidthOption);
	free(latticeSizeOption);
	free(historySizeOption);

	Lattice* history = new Lattice[steps + 1];

	// Initialize

	// Set initial lattice (*history);

	puts("Setting initial state...");
	history->initialize(latticeWidth, latticeSize);
	switch(mode) {
		case CLASSICAL:
			history->setInitialStateClassical(waveWidth);
			break;
		case SCHRODINGER:
			history->setInitialStateSchrodinger(waveWidth);
			break;
	}

	// Evolve

	printf("Will evolve for %ld steps\n", steps);
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

	printf("Writing to %s\n", outputFilename);

	fprintf(f, "--- mode;%s;options;", mode == SCHRODINGER ? "schrodinger" : "classical");
	fprintf(f,"n:%ld;", steps);
	fprintf(f,"u:%d;", waveWrite);
	fprintf(f,"o:%s;", outputFilename);
	fprintf(f,"s:%d;", latticeSize);
	char b[128];
	printFloat(b, waveWidth);
	fprintf(f,"g:%s;", b);
	printFloat(b, latticeWidth);
	fprintf(f,"w:%s;", b);
	printFloat(b, timestep);
	fprintf(f,"t:%s;", b);
	fprintf(f,"\n");

	register long i;
	for(i=0;i<steps;++i)
	{
		next = &(history[1+i]);
		next->initialize(latticeWidth, latticeSize);

		switch(mode) {
			default:
			case SCHRODINGER:
				curr->evolveSchrodinger(timestep, next);
				break;
			case CLASSICAL:
				curr->evolveClassical(timestep, next);
				break;
		}

		if(i % waveWrite == 0) {
			switch(mode) {
				default:
				case SCHRODINGER:
					history[i].writeLatticeSchrodinger(f);
					break;
				case CLASSICAL:
					history[i].writeLatticeClassical(f);
					break;

			}
			fprintf(f, "\n");
		}

		char prob[128];
		if(mode == SCHRODINGER) {
			printFloat(prob, curr->prob);
		}

		delete [] curr->lattice;
		curr = next;

		switch(mode) {
			default:
			case SCHRODINGER:
				printf("\rSteps: %09ld (%7.4f%%): prob %s", i, (float)i*100.0/steps, prob);
				break;
			case CLASSICAL:
				printf("\rSteps: %09ld (%7.4f%%)", i, (float)i*100.0/steps);
				break;
		}
		fflush(stdout);
	}
	printf("\n");

	// Analyze

	return 0;

}
