#pragma once

#include <float.h>
#include <string>

struct complex {
    long double real;
    long double imaginary;

    complex(long double real, long double imaginary);
    
    complex operator_();

    complex operator+(complex number);
    complex operator-(complex number);
    complex operator*(complex number);
    complex operator^(complex number);

    complex operator+(long double number); 
    complex operator-(long double number);      
    complex operator*(long double number);
    complex operator^(int number);

    long double abs();

    std::string to_string();
};

complex::complex(long double real, long double imaginary) : real(real), imaginary(imaginary) {}

complex complex::operator_() {
    return complex(real, -imaginary);
}
complex complex::operator+(complex number) {
    return complex(real + number.real, imaginary + number.imaginary);
}
complex complex::operator-(complex number) {
    return complex(real - number.real, imaginary - number.imaginary);
}
complex complex::operator*(complex number) {
    return complex(real * number.real - imaginary * number.imaginary,
        real * number.imaginary + imaginary * number.real);
}

complex complex::operator^(complex number) {

}



complex complex::operator+(long double number) {
    return complex(real + number, imaginary);
}      
complex complex::operator-(long double number) {
    return complex(real - number, imaginary);
}      
complex complex::operator*(long double number) {
    return complex(real * number, imaginary * number);
}

complex complex::operator^(int number) {
    complex result = complex(1,0);
    for(int i = 0; i < number; i++) {
        result = result * (*this);
    }
    return result;
}

long double complex::abs() { return sqrt(pow(real,2) + pow(imaginary,2));}


std::string complex::to_string() {
    return std::to_string(real) + " + " + std::to_string(imaginary) + "i";
}

#define c(re,im) (complex(re,im))