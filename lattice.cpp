#include <string>
#include "lattice.hpp"
#include "constants.hpp"
#include <cstdio>

Lattice::Lattice()
{
	latticeSize = 0;
	lattice = NULL;
}
Lattice::Lattice(_float const& L, unsigned int const& N)
{
	latticeSize = N;
	lattice = new State[N];
}
void Lattice::initialize(_float const& L, unsigned int const& N)
{
	latticeSize = N;
	lattice = new State[N];
}
void Lattice::evolve(_float const& dto, Lattice* const& outputLattice)
{
	register unsigned int i;
	const _float m = 1;
	for(i=1; i<latticeSize-1; ++i)
	{
		// No potential
		Complex d2dx2( ( lattice[i+1].state + lattice[i-1].state - 2 * lattice[i].state ) );
		_float dbdt = 2 * d2dx2.re();
		_float dadt = 2 * d2dx2.im();
		outputLattice->lattice[i].state = Complex(
				lattice[i].state.re() + dadt,
				lattice[i].state.im() + dbdt
		);
	}
	outputLattice->normalize();
}
void Lattice::normalize()
{
	_float prob = this->probability();
	register unsigned int i;
	for(i=1; i<latticeSize-1; ++i)
	{
		lattice[i].state /= prob;
	}
}
_float Lattice::probability()
{
	register _float prob = 0.0;
	register unsigned int i;
	for(i=1; i<latticeSize-1; ++i)
	{
		prob += lattice[i].prob();
	}
	return prob;
}
Lattice::~Lattice()
{
	delete [] lattice;
}

State::State()
{

}
State::State(_float const& xi, std::string const& expr, std::string const& expi)
{

}
_float State::prob()
{
	return state.magsq();
}
void Lattice::setInitialState(_float dx)
{
	register unsigned int i;
	_float x;
	_float amp;

	_float latticeWidth = 1.0;

	for(i=0;i<latticeSize;++i)
	{
		x = (i - latticeSize/2) * latticeWidth;
		amp = Re(Exp(-1 * x*x / (2 * dx *  dx))) * 1 / Re(Sqrt(Sqrt(M_PI) * dx));
		lattice[i].state = Complex(amp * Re(Cos((x - 1000)*1000)), amp * Re(Sin((x - 1000)*1000)));
		// lattice[i].state = Complex(amp);
		// lattice[i].state.print();
	}
}
int Lattice::writeLattice(FILE* f)
{
	register unsigned int i;
	for(i=0;i<latticeSize;++i)
	{
		lattice[i].state.printCompact(f);
		fprintf(f,",");
	}

	return 0;
}
