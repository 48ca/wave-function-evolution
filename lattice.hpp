#ifndef LATTICE_H
#define LATTICE_H

#include <string>
#include "complex.hpp"
#include "libs/exprtk.hpp"
#include <cstdio>

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
};

class Lattice
{
public:
	Lattice();
	Lattice(_float const& L,
		unsigned int const& N,
		_float const& dt);

	void initialize(_float const& L,
		unsigned int const& N,
		_float const& dt);

	State* lattice;
	unsigned int latticeSize;

	_float L;
	unsigned int N;
	_float dt;

	void evolve();
	void evolve(_float const& dto, Lattice* const& outputLattice);

	void setInitialState(_float);

	int writeLattice(FILE* f);
};

#endif // LATTICE_H
