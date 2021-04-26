#pragma once

#include <float.h>
#include <string>
#include <math.h>


constexpr long double EULERS_NUMBER = 2.7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274274663919320030599218174135;
constexpr long double PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446;


struct complex {
    long double real;
    long double imaginary;

    complex(long double real, long double imaginary);
    
    inline complex conjugate();
    inline complex operator!();

    inline complex operator+(complex number);
    inline complex operator-(complex number);
    inline complex operator*(complex number);
    inline complex operator/(complex number);
    inline complex operator^(complex exponent);

    inline complex operator+(long double number); 
    inline complex operator-(long double number);      
    inline complex operator*(long double number);
    inline complex operator^(long double exponent);
    //inline complex operator^(int number);


    inline long double absolute();
    inline long double argument();

    std::string to_string();
};

complex::complex(long double real, long double imaginary) : real(real), imaginary(imaginary) {}


inline complex complex::conjugate(){
    return complex(real, -imaginary);
}
inline complex complex::operator!() {
    return complex(real, -imaginary);
}
inline complex complex::operator+(complex number) {
    return complex(real + number.real, imaginary + number.imaginary);
}
inline complex complex::operator-(complex number) {
    return complex(real - number.real, imaginary - number.imaginary);
}
inline complex complex::operator*(complex number) {
    return complex(real * number.real - imaginary * number.imaginary,
        real * number.imaginary + imaginary * number.real);
}
inline complex complex::operator/(complex number) {
    return complex( (real*number.real + imaginary*number.imaginary)/(number.real * number.real + number.imaginary * number.imaginary),
                    (-real*number.imaginary + imaginary*number.real)/(number.real * number.real + number.imaginary * number.imaginary));
}
inline complex complex::operator^(complex exponent) {
    long double arg = argument();
    long double abs = absolute();
    long double factor = pow(abs,exponent.real) * pow(EULERS_NUMBER,-exponent.imaginary * arg);
    return complex(factor * cosf64x(exponent.real * arg + exponent.imaginary + logf64x(abs)),
                    factor * sinf64x(exponent.real * arg + exponent.imaginary * logf64x(abs)));
}


inline complex complex::operator+(long double number) {
    return complex(real + number, imaginary);
}      
inline complex complex::operator-(long double number) {
    return complex(real - number, imaginary);
}      
inline complex complex::operator*(long double number) {
    return complex(real * number, imaginary * number);
}
/*
inline complex complex::operator^(int number) {
    complex result = complex(1,0);
    for(int i = 0; i < number; i++) {
        result = result * (*this);
    }
    return result;
}*/
inline complex complex::operator^(long double exponent) {
    long double arg = argument();
    long double radius = pow(absolute(), exponent);
    return complex(radius * cosf64x(exponent*arg), radius * sinf64x(exponent*arg));
}

inline long double complex::absolute() { 
    return sqrt(pow(real, 2) + pow(imaginary, 2));
}
inline long double complex::argument() {
    return atan2f64x(imaginary, real);
}

std::string complex::to_string() {
    return std::to_string(real) + " + " + std::to_string(imaginary) + "i";
}

#define c(re,im) (complex(re,im))