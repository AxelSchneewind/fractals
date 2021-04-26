#include <thread>
#include <string>
#include "RenderMethods.hpp"
#include "Renderer.hpp"



complex scale(0.4,0.4);
complex center(-0.6,0);
//complex center(0,0);
double escapeValue = 1000;
int maxIterations = 1024;
vector2 resolution(8192,8192);

std::string filename = "fractal";


int main () {
    // functions that transform pixel coordinates to complex numbers and back
    Transformation transformation = DefaultTransformation(scale, center, resolution);
    InvTransformation invTransformation = DefaultInvTransformation(scale, center, resolution);
    
    // the function that complex numbers will be iterated over
    CFunction function = ExtMultiBrotFunction(2.0, false);

    //selecting a color progression
    ColorProgression colors = pr3;
    ColoringMethod colorMethod = InterpolationColorMethod(&colors);

    // a rendering method that handles the calculations
    //RenderMethod* renderMethod = new StandardRenderMethod(transformation, function, maxIterations, escapeValue, colorMethod);
    RenderMethod* renderMethod = new TraceRenderMethod(transformation, invTransformation, function, maxIterations, escapeValue, colorMethod);    
    
    
    bitmap_image image = generate(resolution, renderMethod);
    image.save_image(filename + ".bmp");
}