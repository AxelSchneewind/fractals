Include = -Isrc -Isrc/geometry -Isrc/bitmap -Isrc/complex
Executable = fractals
Ouput = -o $(Executable)

bitmap: src/bitmap/bitmap_image.hpp
	g++ src/bitmap/bitmap_image.hpp

all: src/*/*.cpp src/*/*.hpp
	g++ src/renderer/main.cpp -pthread $(Include) $(Ouput) -Ofast

debug: */*.cpp */*.hpp
	g++ src/renderer/main.cpp -pthread $(Include) $(Ouput) -g
	gdb fractals

run: all
	./$(Executable)
	
save: run
	convert fractal.bmp fractal.png
	#mv images/fractal.png
	rm fractal.bmp
	gwenview images/fractal.png