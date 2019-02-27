#include "../include/decomposition.h"

int ** bool_th_mat ;

int main(int argc, char * argv[]){
  if (argc <= 1 || argc > 4){
    fprintf(stderr, "Usage %s <number of points> <order_type> <anti-thickness check> ", argv[0]);
    return -1;
  }

  int n,t,ot;
  n = atoi(argv[1]);
  ot = atoi(argv[2]);
  t = atoi(argv[3]);
  int cols = n*(n-1)/2.0;
  int rows = count_thrackles(n,n,ot);
  int check[4] = {25,21,10,0};
  cout << "Cols :" << cols << endl;
  cout << "Rows :" << rows << endl;
  //Populate the matrix.
  bool_th_mat = (int **)malloc(rows * sizeof(int*));
  for(int i = 0; i < rows; i++) bool_th_mat[i] = (int *)malloc(cols * sizeof(int));
  load_thrackles(n,n,ot,bool_th_mat);
  printMatrix(bool_th_mat,rows,cols);

  if( is_atk_upper(rows, n, ot, t, bool_th_mat) ) {
    printf("K_%d order type %d has anti-thickness at most: %d\n",n,ot,t);
  }

  freeMatrix(bool_th_mat,rows);
  return 1;
}
