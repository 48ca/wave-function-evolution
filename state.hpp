#ifndef STATE_H
#define STATE_H

#include "complex.hpp"

// acts as both schrodinger and classical state

class State
{
	public:
		Complex state;
		State();
		_float prob();

		_float value;
		_float dot;
};
#endif //state. i guess.
