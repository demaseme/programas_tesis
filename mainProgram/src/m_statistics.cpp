#include "../include/decomposition.h"

//This program runs statistics to find the maximum m (repeated edges)
//For each order type of given n.
//And then for each decomposition of size [2,cat(K_n)] found.

int ** bool_th_mat ;

int main(int argc, char * argv[]){
  if (argc <= 1 || argc > 2){
    fprintf(stderr, "Usage %s <n>\n", argv[0] );
    exit(-1);
  }

  int **a;
  int m_arr[2] = {99,-1};
  int n,k,otypes,start,end,rows,cols;
  int ot = 1;
  n = atoi(argv[1]);
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
  start = n - floor(sqrt(2.0*n + (1.0/4.0)) - (1.0/2.0));
  end = 2;
  cout << start << " -> " << end << endl;
  string file_name = "m_" + to_string(n) + "stats.dat";
  ofstream myfile;
  myfile.open(file_name);

  /*
    Use K_n_statistics.dat information to know which otypes is worth to visit.
  */
  vector<int> otypes_vec;
  //otypes_vec.push_back(1287);
  select_otypes(n,otypes_vec);
  for(auto i = otypes_vec.begin(); i != otypes_vec.end(); ++i){
    printf("%d \n",*i);
  }

  auto i = otypes_vec.begin();

  //++i; //Avoid OT 0 - convex.

  while ( i != otypes_vec.end() ){
    ot = *i;
    cout << "Working with ot " << ot << endl;
    rows = count_thrackles(n,n,ot);
    //int check[4] = {25,21,10,0};
    cout << "Cols :" << cols << endl;
    cout << "Rows :" << rows << endl;
    if (!rows){
      ++i;
      continue;
    }
    //Populate the matrix.
    bool_th_mat = (int **)malloc(rows * sizeof(int*));
    for(int i = 0; i < rows; i++) bool_th_mat[i] = (int *)malloc(cols * sizeof(int));

    load_thrackles(n,n,ot,bool_th_mat);
    //printMatrix(bool_th_mat,rows,cols);
    // if (!mat_union_covers(bool_th_mat,cols,rows)){
    //   ++i;
    //   a = (int **)bool_th_mat;
    //   for(int i = 0; i < rows; i++) free(a[i]);
    //   //cout << "Rows freed\n";
    //   continue;
    // }
    //cout << "OT " << ot << " max thrackles cover\n";

    k = start;

    printf("Number of Thrackles: %d\n",rows );
    while(k > 2){
      printf("Looking for a decomposition of size %d\n",k);
      if (rows < k){ k--; continue;}
      count_repetitions_all(bool_th_mat, rows, k, n,m_arr);

      if( m_arr[0] == 99 ) {
          printf("\tNo decomposition of size %d found.\n",k);
          k = 2;
          continue;
      }
      else {
        printf("\tThrackle set size : %d, min_repetitions: %d, max_repetitions: %d\n",k,m_arr[0],m_arr[1]);
        writeResults(myfile,ot,k,m_arr[0],m_arr[1]);
      }
      k--;
    }

    ++i;
    a = (int **)bool_th_mat;
    for(int i = 0; i < rows; i++) free(a[i]);
    //<cout << "Rows freed\n";
  }
  free(a);
  myfile.close();
  return 1;
}
