#ifndef LATTICE_H
#define LATTICE_H

#include "complex.hpp"

class State
{
public:
	Complex state;
	State();
	inline _float prob();
	void evolve(_float const& dt);
};

class Lattice
{
public:
	Lattice();
	Lattice(_float const& L,
		unsigned int const& N,
		_float const& dt);

	State* lattice;

	_float L;
	unsigned int N;
	_float dt;
};

#endif // LATTICE_H
