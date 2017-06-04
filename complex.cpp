#include "complex.hpp"
#include <cstdio>

#define PRINT_BUFFER_SIZE 128

Complex::Complex()
{
	raw = 0;
}
Complex::Complex(_float const& r)
{
	raw = r;
}
Complex::Complex(_float const& r, _float const& i)
{
	this->re(r);
	this->im(i);
}
Complex::Complex(_complex const& z)
{
	raw = z;
}

Complex Complex::operator~(void)
{
#ifndef USING_QUADMATH
	return Complex(std::conj(raw));
#else
	return Complex(~raw);
#endif
}
_float Complex::re() const
{
#ifndef USING_QUADMATH
	return raw.real();
#else
	return __real__ raw;
#endif
}
void Complex::re(_float const& r)
{
#ifndef USING_QUADMATH
	raw.real(r);
#else
	__real__ raw = r;
#endif
}

_float Complex::im() const
{
#ifndef USING_QUADMATH
	return raw.imag();
#else
	return __imag__ raw;
#endif
}
void Complex::im(_float const& r)
{
#ifndef USING_QUADMATH
	raw.imag(r);
#else
	__imag__ raw = r;
#endif
}

_float Complex::magsq() const
{
	Complex cpy(raw);
	return (~cpy * cpy).re();
}
_float Complex::mag() const
{
#ifndef USING_QUADMATH
	return sqrt(this->magsq());
#else
	return sqrtq(this->magsq());
#endif
}

void Complex::print() const
{

#ifndef USING_QUADMATH

	printf("%.20Le + %.20Lei\n", Re(raw), Im(raw));

#else

	int width = 20;

	char real_buf[PRINT_BUFFER_SIZE];
	char im_buf[PRINT_BUFFER_SIZE];
	quadmath_snprintf(real_buf, PRINT_BUFFER_SIZE, "%#*.20Qe", width, Re(raw));
	quadmath_snprintf(im_buf, PRINT_BUFFER_SIZE, "%#*.20Qe", width, Im(raw));
	printf("%s + %si\n", real_buf, im_buf);

#endif

}

void printFloat(_float f) const
{

#ifndef USING_QUADMATH

	printf("%Lf\n", f);

#else

	int width = 20;

	char real_buf[PRINT_BUFFER_SIZE];
	quadmath_snprintf(real_buf, PRINT_BUFFER_SIZE, "%#*.20Qe", width, f);
	printf("%s\n", real_buf);

#endif

}

void Complex::printCompact(FILE* f) const
{

#ifndef USING_QUADMATH

	fprintf(f, "%.20Le + %.20Lei", Re(raw), Im(raw));

#else

	int width = 20;

	char real_buf[PRINT_BUFFER_SIZE];
	char im_buf[PRINT_BUFFER_SIZE];
	quadmath_snprintf(real_buf, PRINT_BUFFER_SIZE, "%#*.20Qe", width, Re(raw));
	quadmath_snprintf(im_buf, PRINT_BUFFER_SIZE, "%#*.20Qe", width, Im(raw));
	fprintf(f, "%s + %si", real_buf, im_buf);

#endif

}

void Complex::operator=(Complex const& other)
{
	this->raw = other.raw;
}

void Complex::operator+=(Complex const& other)
{
	this->raw += other.raw;
}

void Complex::operator-=(Complex const& other)
{
	this->raw -= other.raw;
}
void Complex::operator*=(Complex const& other)
{
	this->raw *= other.raw;
}
void Complex::operator/=(Complex const& other)
{
	this->raw /= other.raw;
}
void Complex::operator^=(Complex const& other)
{
#ifndef USING_QUADMATH
	this->raw = std::pow(this->raw, other.raw);
#else
	this->raw = cpowq(this->raw, other.raw);
#endif
}

/** Arithmetic for bulit-in types **/
Complex operator+ (const _complex& s, const Complex& c)
{
	return Complex(c.raw + s);
}
Complex operator- (const _complex& s, const Complex& c)
{
	return Complex(c.raw - s);
}
Complex operator* (const _complex& s, const Complex& c)
{
	return Complex(c.raw * s);
}
Complex operator/ (const _complex& s, const Complex& c)
{
	return Complex(c.raw / s);
}
Complex operator^ (const _complex& s, const Complex& c)
{
	return c^Complex(s);
}

/** Arithmetic for Complex type **/
Complex operator+ (const Complex& a, const Complex& b)
{
	return Complex(a.raw + b.raw);
}
Complex operator- (const Complex& a, const Complex& b)
{
	return Complex(a.raw - b.raw);
}
Complex operator* (const Complex& a, const Complex& b)
{
	return Complex(a.raw * b.raw);
}
Complex operator/ (const Complex& a, const Complex& b)
{
	return Complex(a.raw / b.raw);
}
Complex operator^ (const Complex& a, const Complex& b)
{
#ifndef USING_QUADMATH
	return Complex(std::pow(a.raw, b.raw));
#else
	return Complex(cpowq(a.raw, b.raw));
#endif
}

#ifdef USING_QUADMATH
_complex RawComplex_I = 0 + csqrtq(-1);
#endif
