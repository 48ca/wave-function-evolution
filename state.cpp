#include "state.hpp"
#include "complex.hpp"

State::State()
{
	state = Complex(0);
	derivative = 0;
	phi = 0;
}
_float State::prob()
{
	return state.magsq();
}
