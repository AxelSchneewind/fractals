#include <complex.hpp>
#include <vector2.hpp>
#include <functional>

typedef std::function<complex(vector2)> Transformation;

Transformation DefaultTransformation(complex scale, complex center, vector2 resolution){
    return ([=](vector2 pixel) -> complex { 
        return complex(((double(pixel.x) / resolution.x) - 0.5)/scale.real + center.real, 
                    ((double(pixel.y) / resolution.y) - 0.5)/scale.imaginary + center.imaginary); 
    });
};