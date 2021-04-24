#include <complex.hpp>
#include <vector2.hpp>
#include <functional>

typedef std::function<complex(vector2)> Transformation;
typedef std::function<vector2(complex)> InvTransformation;

Transformation DefaultTransformation(complex scale, complex center, vector2 resolution){
    return ([=](vector2 pixel) -> complex { 
        return complex(((double(pixel.x) / resolution.x) - 0.5)/scale.real + center.real, 
                    ((double(pixel.y) / resolution.y) - 0.5)/scale.imaginary + center.imaginary); 
    });
};

InvTransformation DefaultInvTransformation (complex scale, complex center, vector2 resolution) {
    return ([=](complex num) -> vector2 { 
        return vector2(int((((num.real - center.real) * scale.real) + 0.5) * resolution.x),
                    int((((num.imaginary - center.imaginary) * scale.imaginary) + 0.5) * resolution.y));
    });
}