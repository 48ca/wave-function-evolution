#include "lattice.hpp"

Lattice::Lattice()
{
	lattice = new State[N];
}
Lattice::Lattice(_float const& L, unsigned int const& N, _float const& dt)
{
	lattice = new State[N];
}

State::State()
{

}
void State::evolve(_float const& dt)
{

}
_float State::prob()
{
	return state.magsq();
}
