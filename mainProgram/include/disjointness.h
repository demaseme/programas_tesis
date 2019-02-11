#ifndef DISJOINTNESS_H
#define DISJOINTNESS_H

#include "thrackle.h"
extern int minAt;

void construct_disjointness_matrix(const vector<Edge> edges,int ** matrix,const int rows, bool printmatrix);
void freeMatrix(int ** matrix, const int rows);

void find_decomposition(int ** matrix,int cols, int n);
void find_cat(int** matrix, int cols, int n, vector<int> & coveredEdges, vector<int> & nextThrackle,
 int desired_size, vector<int> & startingThrackle, int at);

 void convex_antithickness(int ** matrix, int cols, int n , vector<int> & coveredEdges, vector<int> starting, int at);

int find_next_thrackle(int ** matrix, int cols, vector<int> currentThrackle, vector<int> & nextThrackle,int desired_size, bool openclosed);
int find_next_compatible_thrackle_anysize(int** matrix, int cols, int n, vector<int> coveredEdges, vector<int> starting, vector<int> & thrackle);
int find_next_compatible_thrackle(int ** matrix, int cols, vector<int> coveredEdges, vector<int> & foundThrackle, int desired_size,
const vector<int> & startingThrackle, bool openclosed);

void construct_thrackles_matrix(int ** matrix, const int cols, const int k, const int size,int & thr_count);
void bringEdges(int ** matrix, const int cols, const int row, vector<int> & compatible);
void printArray(int array[],const int size);
int get_kthrackles_of_matrix(int ** matrix, const int cols, const int desired_size, vector<vector<int>> & positions);
#endif
