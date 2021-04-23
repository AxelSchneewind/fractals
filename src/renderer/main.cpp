#include <thread>
#include <string>
#include "Renderer.hpp"


bitmap_image generate(vector2 resolution, RenderMethod *renderMethod) {
    bitmap_image image(resolution.x, resolution.y);

    auto f = [](int X, int xStep, vector2 resolution, RenderMethod *renderMethod, bitmap_image *image) {
        for (int x = X; x < resolution.x; x += xStep) {
            for (int y = 0; y < resolution.y; y++) {
                image->set_pixel(x,y, renderMethod->colorAt(vector2(x,y)));
            }
        }
    };

    int threadCount = 8;
    std::thread threads[threadCount];
    for (int i = 0; i < threadCount; i++) {
        threads[i] =  std::thread(f, i, threadCount, resolution, renderMethod, &image);
    }
    for (int i = 0; i < threadCount; i++) {
        threads[i].join();
    }
    
    return image;
}


complex scale(0.4,0.4);
complex center(-0.6,0);
double escapeValue = 1000;
int maxIterations = 1024;
vector2 resolution(8192,8192);

std::string filename = "fractal";


int main () {
    Transformation transformation = DefaultTransformation(scale, center, resolution);
    CFunction function = MultiBrotFunction(2);

    //TODO create color palette class
    tuple<float, rgb> colors[] {
        tuple<float, rgb>(0.0, make_colour(0)),
        tuple<float, rgb>(10.0, make_colour(0x202050)),
        tuple<float, rgb>(20, make_colour(0x7070A5)),
        tuple<float, rgb>(40.0, make_colour(0x70A270)),
        tuple<float, rgb>(150.0, make_colour(0xA2A0A0)),
        tuple<float, rgb>(maxIterations, make_colour(0)),
    };
    ColoringMethod colorMethod = InterpolationColorMethod(6,colors);


    bitmap_image im = bitmap_image(maxIterations,1);
    for (int i = 0; i < maxIterations; i++)
    {
        im.set_pixel(i,0, colorMethod(i));
    }
    im.save_image("color_palette.bmp");

    RenderMethod* renderMethod = new StandardRenderMethod(transformation, function, maxIterations, escapeValue, colorMethod);
    bitmap_image image = generate(resolution, renderMethod);
    image.save_image(filename + ".bmp");
}