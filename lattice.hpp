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

		void normalize();
		void probability();

		void evolvequ(_float const& dto, Lattice* const& outputLattice);
		void evolvewv(_float const& dto, Lattice* const& outputLattice);

		void setInitialStatequ(_float);
		void setInitialStatewv(_float);
		int writeLattice(FILE* f);
};

#endif // LATTICE_H
