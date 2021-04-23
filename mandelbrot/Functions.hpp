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

const CFunction ExtMultiBrotFunction(int exponent, complex constant) {
    return ([=](complex number, complex constant1) -> complex { 
        return ((number^exponent) + constant1) + constant; 
    });
};
