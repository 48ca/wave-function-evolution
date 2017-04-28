#include <string>
#include "lattice.hpp"
#include "libs/exprtk.hpp"

Lattice::Lattice()
{
	lattice = new State[N];
}
Lattice::Lattice(_float const& L, unsigned int const& N, _float const& dt)
{
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
