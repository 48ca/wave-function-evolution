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

}
void Lattice::evolve()
{
	for(unsigned i=0; i<N; ++i){lattice[i].evolve(dt);}
}

State::State()
{

}
State::State(_float const& xi, std::string const& expr, std::string const& expi)
{

}
void State::evolve(_float const& dt)
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
	register unsigned int i, x;
	for(i=0;i<latticeSize;++i)
	{
		x = i;
		lattice[i].state = Complex(1 / Sqrt(2 * M_PI * dx * dx) * Exp( -(x - xavg) * (x - xavg) / ( dx * dx ) + RawComplex_I * p * x / HBAR));
		lattice[i].state.print();
	}
}
