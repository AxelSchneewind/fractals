#pragma once
#include "../bitmap/bitmap_image.hpp"
#include "../geometry/vector2.hpp"
#include "ColoringMethods.hpp"
#include "Functions.hpp"
#include "Transformation.hpp"
#include <functional>


class RenderMethod {
public:
    virtual rgb_t colorAt(vector2 pixel) = 0;
};


class StandardRenderMethod : public RenderMethod {
private:
    Transformation transformation;

    CFunction function;
    int maxIterations;
    double escapeValue;

    ColoringMethod colorMethod;

    int countIterations(complex constant) {
        complex value = function(complex(0,0),constant);
        for (int i = 1; i < maxIterations; i++) {
            if(value.abs() >= escapeValue) {
                return i;
            }
            value = function(value,constant);
        }
        return maxIterations;
    }
public:
    StandardRenderMethod(Transformation transformation, CFunction function, int maxIterations, double escapeValue, ColoringMethod colorMethod) : transformation(transformation), function(function), maxIterations(maxIterations), escapeValue(escapeValue), colorMethod(colorMethod) {};

    rgb_t colorAt(vector2 pixel) {
        int result = countIterations(transformation(pixel));
        return colorMethod(result);
    }
};