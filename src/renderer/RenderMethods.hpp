#pragma once
#include "../bitmap/bitmap_image.hpp"
#include "../geometry/vector2.hpp"
#include "ColoringMethods.hpp"
#include <renderer/ColorProgressions.hpp>
#include "Functions.hpp"
#include "Transformation.hpp"
#include <functional>


class RenderMethod {
public:
    virtual void calculate(vector2 pixel, bitmap_image *image) = 0;
    virtual void postProcess(vector2 pixel, bitmap_image *image) = 0;
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
            if(value.absolute() >= escapeValue) {
                return i;
            }
            value = function(value,constant);
        }
        return maxIterations;
    }
public:
    StandardRenderMethod(Transformation transformation, CFunction function, int maxIterations, double escapeValue, ColoringMethod colorMethod) : transformation(transformation), function(function), maxIterations(maxIterations), escapeValue(escapeValue), colorMethod(colorMethod) {};

    void calculate(vector2 pixel, bitmap_image *image) {
        int result = countIterations(transformation(pixel));
        image->set_pixel(pixel.x, pixel.y, make_colour(result));
    }

    void postProcess(vector2 pixel, bitmap_image *image) {
        image->set_pixel(pixel.x,pixel.y, colorMethod(to_int(image->get_pixel(pixel.x,pixel.y))));
    }
};



class TraceRenderMethod : public RenderMethod {
private:
    Transformation transformation;
    InvTransformation invTransformation;

    CFunction function;
    int maxIterations;
    double escapeValue;

    ColoringMethod colorMethod;

    void iterate(vector2 pixel, bitmap_image *image) {
        complex constant = transformation(pixel);

        complex botLeft = transformation(vector2(0,0));
        complex topRight = transformation(vector2(image->width(),image->height()));

        complex value = function(complex(0,0),constant);
        for (int i = 1; i < maxIterations; i++) {
            value = function(value,constant);
            if(value.real > topRight.real || value.real < botLeft.real || 
                value.imaginary > topRight.imaginary || value.imaginary < botLeft.imaginary) {
                break;
            }
            vector2 tracePixel = invTransformation(value);
            rgb newColor = make_colour(to_int(image->get_pixel(tracePixel.x, tracePixel.y)) + 1);
            image->set_pixel(tracePixel.x, tracePixel.y, newColor);
        }
    }
public:
    TraceRenderMethod(Transformation transformation, InvTransformation invTransformation, CFunction function, int maxIterations, double escapeValue, ColoringMethod colorMethod) : transformation(transformation), invTransformation(invTransformation), function(function), maxIterations(maxIterations), escapeValue(escapeValue), colorMethod(colorMethod) {};

    void calculate(vector2 pixel, bitmap_image *image) {
        iterate(pixel, image);
    }

    void postProcess(vector2 pixel, bitmap_image *image) {
        image->set_pixel(pixel.x,pixel.y, colorMethod(to_int(image->get_pixel(pixel.x,pixel.y))));
    }
};