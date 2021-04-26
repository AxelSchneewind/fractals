#pragma once
#include <functional>

#include "../complex/complex.hpp"
#include "../geometry/vector2.hpp"

typedef std::function<complex(complex,complex)> CFunction;

const CFunction MandelBrotFunction() { 
    return ([](complex number, complex constant) -> complex { 
        return (number^2) + constant; 
    });
};

const CFunction MultiBrotFunction(int exponent) {
    return ([=](complex number, complex constant) -> complex { 
        return (number^exponent) + constant; 
    });
};

const CFunction ExtMultiBrotFunction(float exponent, bool conjugate) {
    if(conjugate) {
        return ([=](complex number, complex constant) -> complex { 
            return ((number.conjugate())^exponent) + constant; 
        });
    } else {
        return ([=](complex number, complex constant) -> complex { 
            return (number^exponent) + constant; 
        });
    }
};

const CFunction Exponential(complex base, bool conjugate) {
    if(conjugate) {
        return ([=](complex number, complex constant) -> complex { 
            return (complex(base)^(number.conjugate())) + constant; 
        });
    } else {
        return ([=](complex number, complex constant) -> complex { 
            return (complex(base)^number) + constant; 
        });
    }
}