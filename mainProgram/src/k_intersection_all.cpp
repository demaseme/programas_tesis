#include "../include/decomposition.h"

/*
  This program receives n,q,k.
  Chooses all the q-sets of thrackles of size k.
  Then calculates its intersection.
  Writes results into a file named n_q_k_intersections_all.dat
  Makes use of n_k_All_bool.ths
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
  string file_name = to_string(n) + "_" + to_string(q) + "_"+ to_string(k) + "_intersections_all.dat";
  ofstream myfile;
  myfile.open(file_name, ios::binary);
  if (!myfile.good()){
    fprintf(stderr, "Error creating file %s\n",file_name.c_str() );
    exit(-1);
  }
  while (ot < otypes) {

    rows = count_thrackles(n,k,ot);
    printf("Working with OT %d there are %d thrackles.\n",ot,rows);

    if ( !rows || rows < q) {
      ot++;
      continue;
    }
    //Populate the matrix.
    bool_th_mat = (int **)malloc(rows * sizeof(int*));
    for(int i = 0; i < rows; i++) bool_th_mat[i] = (int *)malloc(cols * sizeof(int));
    load_thrackles(n,k,ot,bool_th_mat);

    calculate_q_intersection_all(bool_th_mat,rows,q,n,myfile);
    a = (int **)bool_th_mat;
    for(int i = 0; i < rows; i++) free(a[i]);
    ot++;
  }
  //free(a);
  myfile.close();
  return 1;
}
