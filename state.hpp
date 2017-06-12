#ifndef STATE_H
#define STATE_H

#include "complex.hpp"

// acts as both schrodinger and classical state

typedef struct wave {
	_float phi;
	_float derivative;
} Wave;

class State
{
	public:
		State();
		_float prob();

		union {
			Complex state;
			Wave wave;
		};
};
#endif //state. i guess.
