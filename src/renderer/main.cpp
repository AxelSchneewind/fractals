#include <thread>
#include <string>
#include "RenderMethods.hpp"
#include "Renderer.hpp"



complex scale(0.4,0.4);
complex center(-0.6,0);
double escapeValue = 1000;
int maxIterations = 1024;
vector2 resolution(8192,8192);

std::string filename = "fractal";


int main () {
    // functions that transform pixel coordinates to complex numbers and back
    Transformation transformation = DefaultTransformation(scale, center, resolution);
    InvTransformation invTransformation = DefaultInvTransformation(scale, center, resolution);
    
    // the function that complex numbers will be iterated over
    CFunction function = MultiBrotFunction(4);

    //selecting a color progression
    ColorProgression colors = pr3;
    ColoringMethod colorMethod = InterpolationColorMethod(&colors);


    // generates an image from the chosen coloring method, for debugging purposes
    bitmap_image im = bitmap_image(maxIterations,1);
    for (int i = 0; i < maxIterations; i++) {
        im.set_pixel(i,0, colorMethod(i));
    }
    im.save_image("color_palette.bmp");


    // a rendering method that handles the calculations
    //RenderMethod* renderMethod = new StandardRenderMethod(transformation, function, maxIterations, escapeValue, colorMethod);
    RenderMethod* renderMethod = new TraceRenderMethod(transformation, invTransformation, function, maxIterations, escapeValue, colorMethod);    
    
    
    bitmap_image image = generate(resolution, renderMethod);
    image.save_image(filename + ".bmp");
}