#ifndef LATTICE_H
#define LATTICE_H

#include <string>
#include "complex.hpp"
#include "libs/exprtk.hpp"

class State
{
public:
	Complex state;
	State();
	State(_float const& x, std::string const& expra, std::string const& expia);
	
	inline _float prob();
	
	_float xi;
	exprtk::symbol_table<_float> expr;
	exprtk::symbol_table<_float> expi;
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

	void evolve();
	void evolve(_float const& dto, Lattice* const& outputLattice);
	void evolve();
};

#endif // LATTICE_H
