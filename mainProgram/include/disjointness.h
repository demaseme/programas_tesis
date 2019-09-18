#ifndef DISJOINTNESS_H
#define DISJOINTNESS_H

#include "thrackle.h"
extern int minAt;
extern int lowAt;

void construct_disjointness_matrix(const vector<Edge> edges,int ** matrix,const int rows, bool printmatrix);
void freeMatrix(int ** matrix, const int rows);

void find_decomposition(int ** matrix,int cols, int n);
void find_cat(int** matrix, int cols, int n, vector<int> & coveredEdges, vector<int> & nextThrackle,
 int desired_size, vector<int> & startingThrackle, int at);

 void convex_antithickness(int ** matrix, int cols, int n , vector<int> thrackle, int at);
 void exhaustive_at(int** matrix, int cols, int n, vector<int> current_thrackle, int at, int mode, vector<vector<int>> & thr_list);
 //int next(int ** matrix, vector<vector<int>> descendants, vector<int> & thrackle, const vector<int> subroot, int cols, int n,int at, int mode);
 int next(int ** matrix, vector<vector<int>> descendants, vector<int> & thrackle, int cols, int n,int at, int mode);

int find_next_thrackle2(int ** matrix, vector<int> current, vector<int> & answer, int cols, bool closed);
int find_next_thrackle(int ** matrix, int cols, vector<int> currentThrackle, vector<int> & nextThrackle,int desired_size, bool openclosed);
int find_next_compatible_thrackle_anysize(int** matrix, int cols, int n, vector<int> starting, vector<int> & thrackle);
int find_next_compatible_thrackle(int ** matrix, int cols, vector<int> & foundThrackle, int desired_size,
const vector<int> & startingThrackle, bool openclosed);

void construct_thrackles_matrix(int ** matrix, const int cols, const int k, const int size,int & thr_count);
void bringEdges(int ** matrix, const int cols, const int row, vector<int> & compatible);
void printArray(int array[],const int size);
int get_kthrackles_of_matrix(int ** matrix, const int cols, const int desired_size, vector<vector<int>> & positions);
#endif
