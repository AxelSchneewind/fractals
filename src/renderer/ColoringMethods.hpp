#pragma once
#include <functional>
#include <renderer/ColorProgression.hpp>
#include "../bitmap/bitmap_image.hpp"

typedef std::function<rgb(int)> ColoringMethod;

inline double clamp(double a, double min, double max) { 
    return (a > max ? max : (a < min ? min : a));
};


const ColoringMethod BWColorMethod = [](int value) -> rgb { 
    double intensity =  double(1024) / value;
    intensity = clamp(intensity, 0, 255);
    return make_colour(intensity, intensity, intensity);
};

const ColoringMethod StandardColorMethod = [](int value) -> rgb { 
    double intensity = double(1024) / value;
    int r = clamp(intensity, 0, 256-1);
    int g = clamp(intensity * intensity, 0, 256*256-1) / 256;
    int b = clamp(intensity * intensity * intensity, 0, 256*256*256-1) / 256 / 256;
    return make_colour(r, g, b);
};

/**
 * @brief 
 * 
 * @param count 
 * @param colors 
 * @pre colors need to be sorted by x-value from small to large
 * @return const ColoringMethod 
 */
const ColoringMethod InterpolationColorMethod(ColorProgression *colors) {
    return ([=](int value) -> rgb {
        return colors->interpolate(value);
    });
};