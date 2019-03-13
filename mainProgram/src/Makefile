# This is a comment line
# Sample makefile for fraction class
proyect:
	g++ main.cpp point.cpp thrackle.cpp disjointness.cpp  -o main -Wall -fopenmp
proyect_cl:
	g++ main.cpp point.cpp thrackle.cpp disjointness.cpp  -o main -Wall -fopenmp -std=c++11
draw_program:
	g++ thrackle_drawer.cpp thrackle.cpp point.cpp gl2ps.c -o drawer -Wall -lglut -lGL -lGLU
intersection:
	g++ intersection_reader.cpp point.cpp thrackle.cpp disjointness.cpp  -o intersection_reader -Wall -fopenmp
k_inter_samp:
	g++ k_intersection_sample.cpp point.cpp thrackle.cpp disjointness.cpp  -o k_intersection_samp -Wall -fopenmp
k_inter_reader:
	g++ k_intersection_reader.cpp point.cpp thrackle.cpp disjointness.cpp  -o k_intersection_reader -Wall -fopenmp
check_antithickness:
	g++ check_at.cpp decomposition.cpp -o check_at -Wall
repetition_counter:
	g++ m_statistics.cpp decomposition.cpp -o m_statistics -Wall
int_partitions:
	g++ integer_partitions.cpp decomposition.cpp -o integer_partitions -Wall
custom_experiment:
	g++ custom_exp.cpp decomposition.cpp point.cpp thrackle.cpp disjointness.cpp -o custom_exp -Wall
k_inter_all:
	g++ k_intersection_all.cpp decomposition.cpp -o k_intersection -Wall
manual_dec:
	g++ assert_manual_decomposition.cpp decomposition.cpp -o manual_decomposition -Wall
clean:
	rm *.o frac
