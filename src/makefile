Include = -I. -Igeometry -Ibitmap -Icomplex
Executable = fractals
Ouput = -o $(Executable)

all: */*.cpp */*.hpp
	g++ renderer/main.cpp -pthread $(Include) $(Ouput)

run: all
	./$(Executable)
