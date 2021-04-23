Include = -I. -Igeometry -Ibitmap -Icomplex
Executable = fractals
Ouput = -o $(Executable)

all: */*.cpp
	g++ mandelbrot/main.cpp -pthread $(Include) $(Ouput)

run:
	make all
	./$(Executable)
	gwenview ./fractal.bmp
