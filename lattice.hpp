#ifndef LATTICE_H
#define LATTICE_H

#include <string>
#include "complex.hpp"
#include <cstdio>

class State
{
	public:
		Complex state;
		State();
		inline _float prob();
};

class Lattice
{
	public:
		Lattice();
		Lattice(_float const& L,
				unsigned int const& N);

		~Lattice();

		void initialize(_float const& L,
				unsigned int const& N);

		State* lattice;
		unsigned int latticeSize;

		_float latticeWidth;
		_float prob;

		void normalize();
		void probability();

		void evolve(_float const& dto, Lattice* const& outputLattice);

		void setInitialState(_float);

		int writeLattice(FILE* f);
};

#endif // LATTICE_H
