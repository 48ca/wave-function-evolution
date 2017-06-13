#include <string>
#include "lattice.hpp"
#include "constants.hpp"
#include "state.hpp"
#include <cstdio>
#include <iostream>

Lattice::Lattice()
{
	latticeSize = 0;
	lattice = NULL;
	prob = 0;
	time = 0;
}
Lattice::Lattice(_float const& L, int const& N)
{
	latticeWidth = L;
	latticeSize = N;
	lattice = new State[N];
	prob = 0;
	time = 0;
}

void Lattice::initialize(_float const& L, int const& N)
{
	latticeWidth = L;
	latticeSize = N;
	lattice = new State[N];
	prob = 0;
	time = 0;
}

void Lattice::normalize()
{
	this->probability();
	register int i;
	_float div = Re(Sqrt(prob));

#ifdef USING_OPENMP
#pragma omp parallel for
#endif
	for(i=1; i<latticeSize-1; ++i)
	{
		lattice[i].state.raw /= div;
	}
}
void Lattice::probability()
{
	prob = 0.0;
	register int i;
	for(i=1; i<latticeSize-1; ++i)
	{
		prob += lattice[i].prob();
	}
	prob = latticeWidth*prob/latticeSize;
}
Lattice::~Lattice()
{
	delete [] lattice;
}


/*********************
 **** SCHRODINGER ****
 ********************/

void Lattice::setInitialStateSchrodinger(_float dx)
{
	register int i;

#ifdef USING_OPENMP
#pragma omp parallel for
#endif
	for(i=1;i<latticeSize-1;++i)
	{
		//_float xinit = 125;
		//_float delta = latticeWidth/latticeSize;
		_float x = ((_float)(i) - latticeSize/2) * latticeWidth/(_float)(latticeSize);
		_float amp = Re(Exp(-1 * (x)*(x) / (2 * dx * dx)));
		_float wav = .5;
		lattice[i].state = Complex(amp * Re(Cos((2*x*PI/wav))), amp * Re(Sin((2*x*PI/wav))));
		// lattice[i].state = Complex(amp);
		// lattice[i].state.print();
	}
	lattice[0].state = Complex(0);
	lattice[latticeSize-1].state = Complex(0);

	this->normalize();
}

void Lattice::evolveSchrodinger(_float const& dto, Lattice* const& outputLattice)
{
	register int i;
	time += dto;

#ifdef USING_OPENMP
#pragma omp parallel for
#endif
	for(i=1; i<latticeSize-1; ++i)
	{
		// No potential
		_complex d2dx2 = lattice[i+1].state.raw + lattice[i-1].state.raw - lattice[i].state.raw * (_complex)2.0;
		outputLattice->lattice[i].state = Complex(
				lattice[i].state.re() - dto*Im(d2dx2),
				lattice[i].state.im() + dto*Re(d2dx2)
				);
	}
	outputLattice->lattice[0].state = Complex(0);
	outputLattice->lattice[latticeSize-1].state = Complex(0);

	outputLattice->normalize();
}

int Lattice::writeLatticeSchrodinger(FILE* f)
{
	register int i;
	for(i=0;i<latticeSize-1;++i)
	{
		lattice[i].state.printCompact(f);
		fprintf(f,",");
	}
	lattice[latticeSize-1].state.printCompact(f);
	return 0;
}


/*********************
 ***** CLASSICAL *****
 ********************/

void Lattice::evolveClassical(_float const& dto, Lattice* const& outputLattice)
{
	register int i;
	energy = 0;
	time += dto;
	//register _float delxsq = (latticeWidth/((_float)(latticeSize)))*(latticeWidth/((_float)(latticeSize)));

#ifdef USING_OPENMP
#pragma omp parallel for
#endif
	for(i=1; i<latticeSize-1; ++i)
	{
		_float d2dx2 = (lattice[i+1].wave.phi + lattice[i-1].wave.phi - lattice[i].wave.phi * 2);
		outputLattice->lattice[i].wave.phi = lattice[i].wave.phi + 1.0 * dto * lattice[i].wave.derivative;
		outputLattice->lattice[i].wave.derivative = lattice[i].wave.derivative + 1.0 * dto * d2dx2;
		if(!(i==1)) {
			energy += (outputLattice->lattice[i].wave.derivative)*(outputLattice->lattice[i].wave.derivative)
			+ (outputLattice->lattice[i].wave.phi - outputLattice->lattice[i-1].wave.phi)*(outputLattice->lattice[i].wave.phi - outputLattice->lattice[i-1].wave.phi);
		}
	}
	outputLattice->lattice[0].wave.phi = 0;
	outputLattice->lattice[latticeSize-1].wave.phi = 0;
	outputLattice->lattice[0].wave.derivative = 0;
	outputLattice->lattice[latticeSize-1].wave.derivative = 0;
}

void Lattice::setInitialStateClassical(_float dx)
{
	register int i;

#ifdef USING_OPENMP
#pragma omp parallel for
#endif
	for(i=1;i<latticeSize-1;++i)
	{
		_float x0 = (_float)(latticeWidth)/2;
		_float x = (_float)(i) * latticeWidth/(_float)(latticeSize);
		_float phi = Re(Exp(0 - (x - x0)*(x - x0) / (2.0 * dx * dx)));
		// _float phi = Re(Sin(PI*(x-x0)));
		_float derivative = (x - x0) / (dx * dx) * Re(Exp(0 - (x - x0)*(x - x0) / (2.0 * dx * dx) ));
		lattice[i].wave.phi = phi;
		lattice[i].wave.derivative = derivative;
	}
	lattice[0].wave.phi = 0;
	lattice[latticeSize-1].wave.phi = 0;
	lattice[0].wave.derivative = 0;
	lattice[latticeSize-1].wave.derivative = 0;
}

int Lattice::writeLatticeClassical(FILE* f)
{
	register int i;
	char buf[128];
	for(i=0;i<latticeSize-1;++i)
	{
		printFloat(buf, lattice[i].wave.phi);
		fprintf(f,"%s;",buf);
		printFloat(buf, lattice[i].wave.derivative);
		fprintf(f,"%s,",buf);
	}
	printFloat(buf, lattice[latticeSize-1].wave.phi);
	fprintf(f,"%s;",buf);
	printFloat(buf, lattice[latticeSize-1].wave.derivative);
	fprintf(f,"%s,",buf);
	return 0;
}
