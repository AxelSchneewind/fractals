#pragma once

#include <bitmap/bitmap_image.hpp>
#include <iostream>

template<typename T1, typename T2>
struct tuple{ 
    T1 x; T2 y; 
    tuple(T1 x, T2 y) : x(x), y(y) {} 
};

typedef tuple<float, rgb> point;

class ColorProgression{
private:
    int count;
    point *colors;
public:
    ColorProgression(int count, tuple<float, rgb>* colors) : count(count), colors(colors) {
        for (int i = 0; i < count - 1; i++) {
            if(colors[i].x > colors[i+1].x) {
                throw;
            }
        }
    }

    int getCount() { return count; } 


    inline int linearInterpolate(int y1, int y2, float x) {
        return int(y1 + (y2 - y1) * x);
    }
    rgb interpolate(float value)  {
        for (int i = 0; i < count - 1; i++) {
            if(value <= colors[i + 1].x) {
                float val = value - colors[i].x;
                val = val / (colors[i+1].x - colors[i].x);
                return make_colour(linearInterpolate(colors[i].y.red, colors[i + 1].y.red, val),
                                linearInterpolate(colors[i].y.green, colors[i + 1].y.green, val),
                                linearInterpolate(colors[i].y.blue, colors[i + 1].y.blue, val));
            }
        }
        return colors[count - 1].y;
    };
};