#ifndef DECOMPOSITION_H
#define DECOMPOSITION_H

/*
Header for decomposition related functions.
*/
#include "thrackle.h"

void t_combinations(int n, int k);
int count_repetitions(int ** bool_th_mat, int th_index[], int ncols, int nthrs, int setsize);
void count_repetitions_all(int ** bool_th_mat, int rows, int k, int setsize, int m_arr[2]);
bool mat_union_covers(int ** bool_th_mat, int cols, int rows);


int is_decomposition(int th_index[], int n_ths, int ** bool_th_mat, int cols);
bool is_atk_upper(int n_th, int setsize, int ot, int k, int ** bool_th_mat);

int load_thrackles(int set_size, int t_size,int desired_ot, int ** bool_th_mat);
int count_thrackles(int set_size, int t_size,int desired_ot);

void writeResults(ofstream & myfile, int ot, int th_set_size, int m_min, int m_max);
void freeMatrix(int ** matrix, const int rows);
void printMatrix(int ** matrix, int rows, int cols);

#endif
