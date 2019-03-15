#include "../include/decomposition.h"

/*
  This program tells when a
  there exists a q-intersection of thrackles of same size
  that is empty for any order type.
*/
int ** bool_th_mat ;
int main(int argc, char * argv[]){
  if (argc != 4){
    fprintf(stderr, "Usage %s <Set size n> <Set size q> <Thrackles size k>\n", argv[0] );
    exit(-1);
  }
  int **a;
  int n,q,k,otypes,rows,cols;
  int ot = 1;
  n = atoi(argv[1]);
  q = atoi(argv[2]);
  k = atoi(argv[3]);
  cols = n*(n-1)/2.0;
  switch(n){
    case 3:
        otypes = 1; break;
    case 4:
        otypes = 2; break;
    case 5:
        otypes = 3; break;
    case 6:
        otypes = 16; break;
    case 7:
        otypes = 135; break;
    case 8:
        otypes = 3315; break;
    case 9:
        otypes = 158817; break;
    case 10:
        otypes = 14309547; break;
    default:
        fprintf(stderr,"No existe base de datos para n>10\n"); exit(-1);
  }
  string file_name = to_string(n) + "_" + to_string(q) + "_"+ to_string(k) + "_intersections_empty.dat";
  ofstream myfile;
  bool value_of_truth;
  myfile.open(file_name);
  while (ot < otypes) {
    //printf("Working with OT %d\n", ot);
    rows = count_thrackles(n,k,ot);
    //printf("There are %d thrackles.\n",rows);
    if ( !rows ) {
      ot++;
      continue;
    }
    //Populate the matrix.
    bool_th_mat = (int **)malloc(rows * sizeof(int*));
    for(int i = 0; i < rows; i++) bool_th_mat[i] = (int *)malloc(cols * sizeof(int));
    load_thrackles(n,k,ot,bool_th_mat);
    //printf("Thrackles loaded!\n");
    //printMatrix(bool_th_mat,rows,cols);


    printf("Working with OT %d\n",ot);
    value_of_truth = check_empty_q_intersection_all(bool_th_mat,rows,q,n);
    if ( value_of_truth ){
      a = (int **)bool_th_mat;
      for(int i = 0; i < rows; i++) free(a[i]);
      myfile << ot <<  " " << rows << " " << value_of_truth << endl;
      break;
    }
    a = (int **)bool_th_mat;
    for(int i = 0; i < rows; i++) free(a[i]);
    ot++;

  }
  free(a);
  myfile.close();
  return 1;
}
