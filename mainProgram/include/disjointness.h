#ifndef DISJOINTNESS_H
#define DISJOINTNESS_H

#include "thrackle.h"

void construct_disjointness_matrix(const vector<Edge> edges,int ** matrix,const int rows, bool printmatrix);
void freeMatrix(int ** matrix, const int rows);

void find_decomposition(int ** matrix,int cols, int n);
int find_next_thrackle(int ** matrix, int cols, vector<int> currentThrackle, vector<int> & nextThrackle,int desired_size);
int find_next_comptabile_thrackle(int ** matrix, int cols, vector<int> currentThrackle, vector<int> & nextThrackle,int desired_size);
int find_next_compatible_thrackle(int **, int cols, vector<int> coveredEdges, vector<int> & nextThrackle, int desired_size); 
void construct_thrackles_matrix(int ** matrix, const int cols, const int k, const int size,int & thr_count);
void bringEdges(int ** matrix, const int cols, const int row, vector<int> & compatible);
void printArray(int array[],const int size);
int get_kthrackles_of_matrix(int ** matrix, const int cols, const int desired_size, vector<vector<int>> & positions);
#endif
