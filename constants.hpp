#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "complex.hpp"

_float HBAR = 1.054571800e-34;
// _float HBAR = 1;
#ifndef USING_QUADMATH
_float PI = M_PI;
#else
_float PI = M_PIq;
#endif

#endif // CONSTANTS_H
