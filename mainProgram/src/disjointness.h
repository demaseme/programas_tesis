#ifndef DISJOINTNESS_H
#define DISJOINTNESS_H

#include "thrackle.h"

void construct_disjointness_matrix(const vector<Edge> edges,int ** matrix, const int rows);
void freeMatrix(int ** matrix, const int rows);
void construct_thrackles_matrix(int ** matrix, const int cols, const int k, const int size);
#endif
