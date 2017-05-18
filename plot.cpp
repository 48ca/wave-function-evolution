#include "lattice.hpp"
#include <mgl2/mgl.h>

int plot(const Lattice& l)
{
	mglGraph gr;
	gr.FPlot("sin(px*x)");
	gr.WriteFrame("test.png");
}
