#ifndef DISJOINTNESS_H
#define DISJOINTNESS_H

#include "thrackle.h"

void construct_disjointness_matrix(const vector<Edge> edges,int ** matrix,const int rows, bool printmatrix);
void freeMatrix(int ** matrix, const int rows);

void construct_thrackles_matrix(int ** matrix, const int cols, const int k, const int size,int & thr_count);
void bringEdges(int ** matrix, const int cols, const int row, vector<int> & compatible);
void printArray(int array[],const int size);
int get_kthrackles_of_matrix(int ** matrix, const int cols, const int desired_size, vector<vector<int>> & positions);
#endif
