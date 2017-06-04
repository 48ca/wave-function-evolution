#include <string>
#include "lattice.hpp"
#include "constants.hpp"
#include <cstdio>
#include <iostream>

Lattice::Lattice()
{
	latticeSize = 0;
	lattice = NULL;
	prob = 0;
}
Lattice::Lattice(_float const& L, unsigned int const& N)
{
	latticeSize = N;
	lattice = new State[N];
	prob = 0;
}
void Lattice::initialize(_float const& L, unsigned int const& N)
{
	latticeSize = N;
	lattice = new State[N];
	prob = 0;
}
void Lattice::evolve(_float const& dto, Lattice* const& outputLattice)
{
	register unsigned int i;

#pragma omp parallel for
	for(i=1; i<latticeSize-1; ++i)
	{
		// No potential
		Complex d2dx2( ( lattice[i+1].state + lattice[i-1].state - lattice[i].state * 2 ) );
		_float dbdt = d2dx2.re();
		_float dadt = 0 - d2dx2.im();
		outputLattice->lattice[i].state = Complex(
				lattice[i].state.re() + dto*dadt,
				lattice[i].state.im() + dto*dbdt
				);
	}
	outputLattice->normalize();
}
void Lattice::normalize()
{
	this->probability();
	register unsigned int i;
	_float div = Re(Sqrt(prob));

#pragma omp parallel for
	for(i=1; i<latticeSize-1; ++i)
	{
		lattice[i].state /= div;
	}
}
void Lattice::probability()
{
	prob = 0.0;
	register unsigned int i;
	for(i=1; i<latticeSize-1; ++i)
	{
		prob += lattice[i].prob();
	}
	prob = prob/latticeSize;
}
Lattice::~Lattice()
{
	delete [] lattice;
}

State::State()
{

}
_float State::prob()
{
	return state.magsq();
}
void Lattice::setInitialState(_float dx)
{
	register unsigned int i;

	_float latticeWidth = 1.0;

#pragma omp parallel for
	for(i=0;i<latticeSize;++i)
	{
		_float x = (i - latticeSize/2) * latticeWidth;
		_float amp = Re(Exp(-1 * x*x / (2 * dx *  dx))) * 1 / Re(Sqrt(Sqrt(PI) * dx));
		lattice[i].state = Complex(amp * Re(Cos((x - 1000)*1000)), amp * Re(Sin((x - 1000)*1000)));
		// lattice[i].state = Complex(amp);
		// lattice[i].state.print();
	}
	this->normalize();
}
int Lattice::writeLattice(FILE* f)
{
	register unsigned int i;
	for(i=0;i<latticeSize-1;++i)
	{
		lattice[i].state.printCompact(f);
		fprintf(f,",");
	}
	lattice[latticeSize-1].state.printCompact(f);
	return 0;
}
