#include <string>
#include "exprtk.hpp"
#include "lattice.hpp"

Lattice::Lattice()
{
	lattice = new State[N];
}
Lattice::Lattice(_float const& L, unsigned int const& N, _float const& dt)
{
	lattice = new State[N];
}
void Lattice::evolve()
{

}
void Lattice::evolve(_float const& dto)
{

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
