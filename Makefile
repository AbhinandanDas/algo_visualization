all: compile link

compile:
	g++ -c bubbleSort.cpp -Isrc/include

link:
	g++ bubbleSort.o -o bubbleSort -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system
