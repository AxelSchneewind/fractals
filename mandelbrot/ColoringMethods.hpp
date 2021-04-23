#pragma once
#include <functional>
#include "../bitmap/bitmap_image.hpp"

#define clamp(a, min, max) (a > max ? max : (a < min ? min : a))

typedef std::function<rgb_t(int)> ColoringMethod;

const ColoringMethod BWColorMethod = [](int value) -> rgb_t { 
    double intensity =  double(1024) / value;
    intensity = clamp(intensity, 0, 255);
    return make_colour(intensity, intensity, intensity);
};

const ColoringMethod StandardColorMethod = [](int value) -> rgb_t { 
    double intensity = double(1024) / value;
    int r = clamp(intensity, 0, 256-1);
    int g = clamp(intensity * intensity, 0, 256*256-1) / 256;
    int b = clamp(intensity * intensity * intensity, 0, 256*256*256-1) / 256 / 256;
    return make_colour(r, g, b);
};
/*rgb_t interpolate(rgb_t color1, rgb_t color2, double value) {
    return make_colour( color1.red + value * (color2.red - color1.red),
                        color1.green + value * (color2.green - color1.green),
                        color1.blue + value * (color2.blue - color1.blue));
};*/