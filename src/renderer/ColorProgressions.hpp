#pragma once
#include <renderer/ColorProgression.hpp>


point p1[] {
    point(0.0,      make_colour(0x000000)),
    point(10.0,     make_colour(0x202050)),
    point(20,       make_colour(0x7070A5)),
    point(40.0,     make_colour(0x70A270)),
    point(150.0,    make_colour(0xA2A0A0)),
    point(1024,     make_colour(0x000000))
};
const ColorProgression pr1(6,p1);

point p2[] {
    point(0.0,      make_colour(0x000000)),
    point(50.0,     make_colour(0xFFFFFF)),
    point(1024,     make_colour(0x000000))
};
const ColorProgression pr2(3,p2);


point p3[] {
    point(0.0,      make_colour(0x000000)),
    point(100.0,    make_colour(0xCCCCCC)),
    point(10240,    make_colour(0xFFFFFF)),
    point(40960,    make_colour(0x000000))
};
const ColorProgression pr3(4,p3);



