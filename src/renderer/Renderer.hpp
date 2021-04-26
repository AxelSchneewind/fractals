#pragma once

#include "RenderMethods.hpp"
#include <thread>


auto rowCalculation(std::function<void(int, int, bitmap_image*)> function, bitmap_image *image, int Y, int yStep) {
    return [=]() -> void {
        for (int y = Y; y < image->height(); y += yStep) {  
            for (int x = 0; x < image->width(); x++) {
                function(x, y, image);
            }
            std::cout << "Thread: " << Y << " finished line: " << y << std::endl;
        }
    };
}

void compute(std::function<void(int, int, bitmap_image*)> function, bitmap_image *image) {
    int threadCount = 8;
    std::thread threads[threadCount];
    for (int i = 0; i < threadCount; i++) {
        threads[i] = std::thread(rowCalculation(function, image, i, threadCount));
    }
    for (int i = 0; i < threadCount; i++) {
        threads[i].join();
    }
}

void calculate(vector2 resolution, RenderMethod *renderMethod, bitmap_image *image) {
    compute(
        [=](int x, int y, bitmap_image *im)-> void { renderMethod->calculate(vec2(x,y), im); }, 
        image);
}

void postProcess(vector2 resolution, RenderMethod *renderMethod, bitmap_image *image) {
    compute(
        [=](int x, int y, bitmap_image *im)-> void { renderMethod->postProcess(vec2(x,y), im); }, 
        image);
}



bitmap_image generate(vector2 resolution, RenderMethod *renderMethod) {
    bitmap_image image(resolution.x, resolution.y);

    calculate(resolution, renderMethod, &image);
    postProcess(resolution, renderMethod, &image);
    
    return image;
}
