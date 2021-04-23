#pragma once
#include <functional>

#include "../bitmap/bitmap_image.hpp"

template<typename T1, typename T2>
struct tuple{ 
    T1 x; T2 y; 
    tuple(T1 x, T2 y) : x(x), y(y){} 
};

typedef std::function<rgb(int)> ColoringMethod;

inline double clamp(double a, double min, double max) { 
    return (a > max ? max : (a < min ? min : a));
};

/**
 * @brief generates a color by interpolating between the given color-value pairs
 * 
 * @param count 
 * @param colors an array of value-color tuples
 * @pre colors need to be sorted by x-value from small to large
 * @param value 
 * @return rgb 
 */
inline rgb interpolate(int count, tuple<float, rgb>* colors, float value) {
    for (int i = 0; i < count - 1; i++) {
        if(value <= colors[i + 1].x) {
            float val = value - colors[i].x;
            val= val / (colors[i+1].x - colors[i].x);
            return make_colour(colors[i].y.red + val*(colors[i + 1].y.red - colors[i].y.red),
                            colors[i].y.green + val*(colors[i + 1].y.green - colors[i].y.green),
                            colors[i].y.blue + val*(colors[i + 1].y.blue - colors[i].y.blue));
        }
    }
    return colors[count - 1].y;
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
const ColoringMethod InterpolationColorMethod(int count, tuple<float, rgb>* colors) {
    return ([=](int value) -> rgb {
        return interpolate(count, colors, value);
    });
};