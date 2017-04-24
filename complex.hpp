#ifndef COMPLEX_WRAPPER_H
#define COMPLEX_WRAPPER_H

#ifndef USING_QUADMATH

#include <complex>

typedef std::complex<long double> _complex;
typedef long double _float;

#define Re(Z) Z.real()
#define Im(Z) Z.imag()

#else

#include <quadmath.h>

typedef __complex128 _complex;
typedef __float128 _float;

#define Re(Z) __real__ Z
#define Im(Z) __imag__ Z

#endif

class Complex
{

	/*
	 * Class to abstract complex arithmetic
	 */

public:
	_complex raw;

	Complex();
	Complex(_float const&);
	Complex(_float const&, _float const&);
	Complex(_complex const&);

	void print() const;

	_float magsq() const;
	_float mag() const;

	/* Component assignments */
	inline _float re() const;
	void re(_float const&);
	inline _float im() const;
	void im(_float const&);

	void operator=  (const Complex&);
	void operator+= (const Complex&);
	void operator-= (const Complex&);
	void operator*= (const Complex&);
	void operator/= (const Complex&);
	void operator^= (const Complex&);

	Complex operator~ (void);

	friend Complex operator+ (const Complex&, const Complex&);
	friend Complex operator- (const Complex&, const Complex&);
	friend Complex operator* (const Complex&, const Complex&);
	friend Complex operator/ (const Complex&, const Complex&);
	friend Complex operator^ (const Complex&, const Complex&);

	friend Complex operator+ (const _complex&, const Complex&);
	friend Complex operator- (const _complex&, const Complex&);
	friend Complex operator* (const _complex&, const Complex&);
	friend Complex operator/ (const _complex&, const Complex&);
	friend Complex operator^ (const _complex&, const Complex&);

};

const Complex Complex_I = Complex(0, 1);

#endif // COMPLEX_WRAPPER_H
