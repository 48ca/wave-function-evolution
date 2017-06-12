#include "complex.hpp"

// Modes
#define SCHRODINGER 1
#define CLASSICAL 2

struct defaults {
	long steps;
	long latticeSize;
	_float latticeWidth;
	_float waveWidth;
	char* outFile;
	_float timestep;
	int waveWrite;

} defaults;

void generateDefaults(int mode)
{
	switch(mode) {
		default:
		case SCHRODINGER:
			defaults.steps = 125000;
			defaults.latticeSize = 1000;
			defaults.latticeWidth = 50.0;
			defaults.waveWidth = 1.0;
			defaults.outFile = (char*)"outqu.txt";
			defaults.timestep = 0.005;
			defaults.waveWrite = 300;
			break;

		case CLASSICAL:
			defaults.steps = 100000;
			defaults.latticeSize = 1000;
			defaults.latticeWidth = 10.0;
			defaults.waveWidth = .6;
			defaults.outFile = (char*)"outwv.txt";
			defaults.timestep = 0.01;
			defaults.waveWrite = 500;
			break;
	}
}
