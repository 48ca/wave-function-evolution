#ifndef LATTICE_H
#define LATTICE_H

#include <string>
#include "complex.hpp"
#include <cstdio>
#include "state.hpp"

class Lattice
{
	public:
		Lattice();
		Lattice(_float const& L,
				int const& N);

		~Lattice();

		void initialize(_float const& L,
				int const& N);

		State* lattice;

		int latticeSize;

		_float latticeWidth;
		_float prob;
		_float time;
		_float energy;

		void normalize();
		void probability();

		void evolveSchrodinger(_float const& dto, Lattice* const& outputLattice);
		void evolveClassical(_float const& dto, Lattice* const& outputLattice);

		void setInitialStateSchrodinger(_float);
		void setInitialStateClassical(_float);

		int writeLatticeSchrodinger(FILE* f);
		int writeLatticeClassical(FILE* f);
};

#endif // LATTICE_H
