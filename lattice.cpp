#include <string>
#include "lattice.hpp"
#include "constants.hpp"
#include <cstdio>

Lattice::Lattice()
{
	latticeSize = 0;
	lattice = NULL;
}
Lattice::Lattice(_float const& L, unsigned int const& N, _float const& dt)
{
	latticeSize = N;
	lattice = new State[N];
}
void Lattice::initialize(_float const& L, unsigned int const& N, _float const& dt)
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
		Complex d2dx2( ( lattice[i+1].state + lattice[i-1].state - 2 * lattice[i].state ) / dto / dto );
		_float dbdt = HBAR/(2 * m) * d2dx2.re();
		_float dadt = -HBAR/(2 * m) * d2dx2.im();
		outputLattice->lattice[i].state = Complex(
				lattice[i].state.re() + dadt,
				lattice[i].state.im() + dbdt
		);
	}
}
void Lattice::evolve()
{
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
	_complex xavg = .5 * latticeSize;
	_complex p = 1;
	register unsigned int i;
	_complex x;
	for(i=0;i<latticeSize;++i)
	{
		x = _complex(i);
		lattice[i].state = Complex(1 / Sqrt(2 * M_PI * dx * dx) * Exp( -(x - xavg) * (x - xavg) / ( dx * dx ) + RawComplex_I * p * x / HBAR));
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
