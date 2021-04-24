Include = -I. -Igeometry -Ibitmap -Icomplex
Executable = fractals
Ouput = -o $(Executable)

bitmap: bitmap/bitmap_image.hpp
	g++ bitmap/bitmap_image.hpp

all: bitmap */*.cpp */*.hpp
	g++ renderer/main.cpp -pthread $(Include) $(Ouput) -Ofast

debug: bitmap */*.cpp */*.hpp
	g++ renderer/main.cpp -pthread $(Include) $(Ouput) -g
	gdb

run: all
	./$(Executable)
	
save: run
	convert fractal.bmp fractal.png
	mv fractal.png ../
	rm fractal.bmp