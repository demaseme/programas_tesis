#include "../include/decomposition.h"
bool ** thrackle_mat;
int nt;
/*
  Loads all thrackles of order type ot into thrackle_mat.
*/
void load_thrackles(int n, int k, int ot){
  string file_name = "ths/" + to_string(n) + "_" + to_string(k) + "_All_bool.ths";
  ifstream file_h;
  file_h.open(file_name, ios::binary);
  if (file_h.bad()){
    fprintf(stderr, "Error opening file %s\n", file_name.c_str());
    exit(-1);
  }
  int current_ot =0;
  int eater = 0;

  int ncols = n*(n-1)/2.0;
  while (current_ot != ot){
    file_h.read( (char*) &eater, sizeof(uint16_t));
    eater = 0;
    file_h.read( (char*) &nt, sizeof(uint16_t));
    for ( int i = 0 ; i < nt ; i++){
      for ( int j = 0; j < ncols; j++) {
        file_h.read( (char*) &eater, sizeof(char));
      }
    }
    current_ot++;
  }
  file_h.read( (char*) &eater, sizeof(uint16_t));
  eater = 0;
  file_h.read( (char*) &nt, sizeof(uint16_t));
  thrackle_mat = (bool ** ) malloc( nt * sizeof(bool*));
  for(int i = 0; i < nt; i++) thrackle_mat[i] = (bool *)malloc(ncols * sizeof(bool));
  for ( int i = 0 ; i < nt ; i++){
    for ( int j = 0; j < ncols; j++) {
      file_h.read( (char*) &eater, sizeof(char));
      thrackle_mat[i][j] = eater;
    }
  }
  printf("Thrackle matrix loaded\n");
}

/*
Calculate the crossing number of a thrackle.
E - Boolean array of edges in the thrackle. It must be of size binom(n,2).
n - The size of the point set.

It assumes that the Edges were formed in the following order.
E[0] = (0,1) {vertices 0 and 1}.
E[1] = (0,2) ... and so on.
E[2] = (0,3)
*/
int cn_th(bool E[], int n){
    int i,j,c;
    int degs[n];
    int th_size = 0;
    int ans,sum;
    for( i = 0; i < n*(n-1)/2 ; i++){
        if(E[i]) th_size++;
    }
    for( i = 0; i < n ; i++){
        degs[i] = 0;
    }
    c = 0;
    for ( i = 0; i < n; i++){
        for ( j = i+1; j < n ; j++){
            if (E[c]) {
                degs[i]++;
                degs[j]++;
            }
            c++;
        }
    }
    // printf("Degree array: ");
    // for( i = 0 ; i<n;i++) printf("%d ",degs[i]);
    // printf("\n");
    ans = th_size*(th_size-1)/2;

    sum = 0;
    for ( i = 0; i < n; i++){
        sum+= degs[i]*(degs[i]-1)/2;
    }
    //printf("%d,%d,%d\n",th_size,ans,sum);
    //printf("%d ",ans-sum);
    return ans - sum;
}

/*
  Prints all crossing number of every thrackle loaded into the matrix.
*/
int print_cn(int n){
    int cols = n*(n-1)/2.0;
    bool E[cols];
    for( int i = 0; i < nt ; i++){
      for ( int j = 0; j < cols ; j++) E[j] = false;
      for ( int j = 0; j < cols ; j++) E[j] = thrackle_mat[i][j];
      printf("%d %d\n",i,cn_th(E,n));

    }
    return 1;
}
int main(){
  load_thrackles(8,8,8);
  print_cn(8);
  return 0;
}
