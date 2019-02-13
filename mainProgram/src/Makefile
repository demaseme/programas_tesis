# This is a comment line
# Sample makefile for fraction class
proyect:
	g++ main.cpp point.cpp thrackle.cpp disjointness.cpp  -o main -Wall -fopenmp
draw_program:
	g++ thrackle_drawer.cpp thrackle.cpp point.cpp gl2ps.c -o drawer -Wall -lglut -lGL -lGLU
intersection:
	g++ intersection_reader.cpp point.cpp thrackle.cpp disjointness.cpp  -o intersection_reader -Wall -fopenmp
clean:
	rm *.o frac
