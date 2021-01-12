all: mazes mazeDisplay
	gcc -o mazes mazes.o mazeDisplay.o -lX11
mazes: mazes.c graphSet.h mazeDisplay.h
	gcc -c mazes.c -g
mazeDisplay: mazeDisplay.c graphSet.h mazeDisplay.h
	gcc -c mazeDisplay.c

