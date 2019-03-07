# This is a comment line
# Sample makefile for fraction class
proyect:
	g++ main.cpp point.cpp thrackle.cpp disjointness.cpp  -o main -Wall -fopenmp
draw_program:
	g++ thrackle_drawer.cpp thrackle.cpp point.cpp gl2ps.c -o drawer -Wall -lglut -lGL -lGLU
intersection:
	g++ intersection_reader.cpp point.cpp thrackle.cpp disjointness.cpp  -o intersection_reader -Wall -fopenmp
k_inter:
	g++ k_intersection.cpp point.cpp thrackle.cpp disjointness.cpp  -o k_intersection -Wall -fopenmp
k_inter_reader:
	g++ k_intersection_reader.cpp point.cpp thrackle.cpp disjointness.cpp  -o k_intersection_reader -Wall -fopenmp
check_antithickness:
	g++ check_at.cpp decomposition.cpp -o check_at -Wall
repetition_counter:
	g++ m_statistics.cpp decomposition.cpp -o m_statistics -Wall
int_partitions:
	g++ integer_partitions.cpp decomposition.cpp -o integer_partitions -Wall
clean:
	rm *.o frac
