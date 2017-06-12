#include "state.hpp"
#include "complex.hpp"

State::State()
{
	state = Complex(0);
	wave.derivative = 0;
	wave.phi = 0;
}
_float State::prob()
{
	return state.magsq();
}
