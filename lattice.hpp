#ifndef LATTICE_H
#define LATTICE_H

#include <string>
#include "complex.hpp"

class State
{
public:
	Complex state;
	State();
	State(_float const& xi, std::string const& expr, std::string const& expi);
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

	void evolve(_float const& dto, Lattice* const& outputLattice);
};

#endif // LATTICE_H
