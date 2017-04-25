#include "lattice.hpp"

Lattice::Lattice(_float const& L, unsigned int const& N, _float const& dt)
{
	State* lattice = new State[N];
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
