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
}
Lattice::Lattice(_float const& L, int const& N)
{
	latticeWidth = L;
	latticeSize = N;
	lattice = new State[N];
	prob = 0;
}
void Lattice::initialize(_float const& L, int const& N)
{
	latticeWidth = L;
	latticeSize = N;
	lattice = new State[N];
	prob = 0;
}
void Lattice::evolvequ(_float const& dto, Lattice* const& outputLattice)
{
	register int i;

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
void Lattice::evolvewv(_float const& dto, Lattice* const& outputLattice)
{
	register int i;
	//register _float delxsq = (latticeWidth/((_float)(latticeSize)))*(latticeWidth/((_float)(latticeSize)));

#ifdef USING_OPENMP
#pragma omp parallel for
#endif
	for(i=1; i<latticeSize-1; ++i)
	{
		_float d2dx2 = (lattice[i+1].phi + lattice[i-1].phi - lattice[i].phi * 2);
		outputLattice->lattice[i].phi = lattice[i].phi + 1.0 * dto * lattice[i].derivative;
		outputLattice->lattice[i].derivative = lattice[i].derivative + 1.0 * dto * d2dx2;
	}
	outputLattice->lattice[0].phi = 0;
	outputLattice->lattice[latticeSize-1].phi = 0;
	outputLattice->lattice[0].derivative = 0;
	outputLattice->lattice[latticeSize-1].derivative = 0;
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
void Lattice::setInitialStatequ(_float dx)
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
void Lattice::setInitialStatewv(_float dx)
{
	register int i;

#ifdef USING_OPENMP
#pragma omp parallel for
#endif
	for(i=1;i<latticeSize-1;++i)
	{
		_float x0 = (_float)(latticeWidth)/2;
		_float x = (_float)(i) * latticeWidth/(_float)(latticeSize);
		_float phi = Re(Exp(0 - (x - x0)*(x - x0) / (2 * dx * dx)));
		// _float phi = Re(Sin(PI*(x-x0)));
		_float derivative = (x - x0) / (dx * dx) * Re(Exp(0 - (x - x0)*(x - x0) / (2 * dx * dx) ));
		lattice[i].phi = phi;
		lattice[i].derivative = derivative;
	}
	lattice[0].phi = 0;
	lattice[latticeSize-1].phi = 0;
	lattice[0].derivative = 0;
	lattice[latticeSize-1].derivative = 0;
}
int Lattice::writeLattice(FILE* f)
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
int Lattice::writeLatticewv(FILE* f)
{
	register int i;
	char buf[128];
	for(i=0;i<latticeSize-1;++i)
	{
		printFloat(buf, lattice[i].phi);
		fprintf(f,"%s;",buf);
		printFloat(buf, lattice[i].derivative);
		fprintf(f,"%s,",buf);
	}
	printFloat(buf, lattice[latticeSize-1].phi);
	fprintf(f,"%s;",buf);
	printFloat(buf, lattice[latticeSize-1].derivative);
	fprintf(f,"%s,",buf);
	return 0;
}
