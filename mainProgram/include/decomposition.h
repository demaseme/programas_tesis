#ifndef DECOMPOSITION_H
#define DECOMPOSITION_H

/*
Header for decomposition related functions.
*/
#include "thrackle.h"

void t_combinations(int n, int k);

int is_decomposition(int th_index[], int n_ths, int ** bool_th_mat, int cols);
bool is_atk_upper(int n_th, int setsize, int ot, int k, int ** bool_th_mat);

int load_thrackles(int set_size, int t_size,int desired_ot, int ** bool_th_mat);
int count_thrackles(int set_size, int t_size,int desired_ot);

void freeMatrix(int ** matrix, const int rows);
void printMatrix(int ** matrix, int rows, int cols);

#endif
