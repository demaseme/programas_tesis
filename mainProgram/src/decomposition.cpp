#include "../include/decomposition.h"
int count_thrackles(int set_size, int t_size,int desired_ot){
  string file_name;
  file_name = "ths/"+to_string(set_size)+"_"+to_string(t_size)+"_All_bool.ths";
  ifstream myfile;
  int thrackleCounter;
  int current_ot = 0;
  int i,j,c;
  int cols = set_size*(set_size-1)/2.0;
  cout << "Opening " << file_name << endl;
  myfile.open(file_name, ios::binary);
  myfile.seekg(0,myfile.beg);
  if(!myfile.is_open()) {
    fprintf(stderr, "%s\n", "Error opening thrackle boolean file\n");
    return 0;
  }
  //foundThrackles.clear();
  int eater = 0;
  while(current_ot != desired_ot){
    //cout << current_ot << endl;
    myfile.read( (char*)&eater,sizeof(char));//ot
    myfile.read( (char*)&eater,sizeof(char)); //number_of_t
    c = eater;
    for(i = 0; i < c; i++){
      for ( j = 0 ; j < cols ; j++){
        myfile.read( (char*)&eater,sizeof(char)); //boolean
      }
      // list of thrackles.
    }
    current_ot++;
  }
  //When we get out of this while, we're in position to read
  //the information that we actually care about.
  eater = 0;
  myfile.read( (char*)&eater,sizeof(char));//ot
  myfile.read( (char*)&eater,sizeof(char)); //number_of_t
  c = eater;
  thrackleCounter = c;
  myfile.close();
  return thrackleCounter;
}
int load_thrackles(int set_size, int t_size,int desired_ot, int ** bool_th_mat){
  string file_name;
  file_name = "ths/"+to_string(set_size)+"_"+to_string(t_size)+"_All_bool.ths";
  ifstream myfile;
  int thrackleCounter;
  int current_ot = 0;
  int i,j,c;
  int cols = set_size*(set_size-1)/2.0;
  cout << "Opening " << file_name << endl;
  myfile.open(file_name, ios::binary);
  myfile.seekg(0,myfile.beg);
  if(!myfile.is_open()) {
    fprintf(stderr, "%s\n", "Error opening thrackle boolean file\n");
    return 0;
  }
  //foundThrackles.clear();
  int eater = 0;
  while(current_ot != desired_ot){
    //cout << current_ot << endl;
    myfile.read( (char*)&eater,sizeof(char));//ot
    myfile.read( (char*)&eater,sizeof(char)); //number_of_t
    c = eater;
    for(i = 0; i < c; i++){
      for ( j = 0 ; j < cols ; j++){
        myfile.read( (char*)&eater,sizeof(char)); //boolean
      }
      // list of thrackles.
    }
    current_ot++;
  }
  //When we get out of this while, we're in position to read
  //the information that we actually care about.
  eater = 0;
  myfile.read( (char*)&eater,sizeof(char));//ot
  myfile.read( (char*)&eater,sizeof(char)); //number_of_t
  c = eater;
  thrackleCounter = c;
  cout << "Reading " << thrackleCounter << " thrackles\n";
  for(i = 0; i < thrackleCounter; i++){
    Thrackle tmp_thrackle;
    for ( j = 0 ; j < cols ; j++){
      myfile.read( (char*)&eater,sizeof(char)); //boolean
      // tmp_thrackle.edge_bool.push_back(eater);
      bool_th_mat[i][j] = eater;
    }
    // foundThrackles.push_back(tmp_thrackle);

  }
  myfile.close();
  return 1;
}



bool is_atk_upper(int n_th, int setsize, int ot, int k, int ** bool_th_mat){
  //Generate the k_combinations.
  int c[k+3];
  int c_curr[k];
  int j;
  int n = n_th;
  int cols = setsize*(setsize-1)/2.0;
  c[0] = 9999;
  for(int i=1; i < k+1; i++){
      c[i] = i-1;
  }
  c[k+1] = n;
  c[k+2] = 0;
  cout << "HELLO\n";
  while (true) {

    //L2. Visit.
    //For each generated, check if it's a decomposition.
    //usleep(100000);
    //printf("Checking ");
    for(int i = k; i > 0; i--){
      c_curr[i-1] = c[i];
      //printf(" %d ",c[i]);
    }
    //printf("k=%d,cols = %d\n",k,cols);
    //If one is a decomposition return true.
    if( is_decomposition(c_curr,k,bool_th_mat,cols) ){
      printf("Decomposition found : ");
      for(int i = k; i > 0; i--){
        printf("%d ",c[i]);
      }
      printf("\n");
      return 1;
    } else {
    //  printf("It ain't.\n");
    }
    //L3. FIND j
    j = 1;
    while( (c[j] + 1) == c[j+1] ) {
        c[j] = j - 1;
        j = j + 1;
    }
    //L4. Termination condition met?
    if (j > k) {
        //std::cout << res << " combinations\n";
        break;
    }
    //L5. Update and Return to L2.
    c[j] = c[j] + 1;
  }
  //If finished return false.
  return false;
}
/*
  Given an array of indexes of thrackles, and the matrix of boolean info of thrackles.
  Tells you whether or not th_index[] is a decomposition of the complete graph of n vertices.
*/
int is_decomposition(int th_index[], int n_ths, int ** bool_th_mat, int cols){
  //vector<vector<int>> T;
  int i,j;
  // //Populate T.
  // for (i = 0; i < n_ths; i++){
  //   vector<int> t;
  //   for( j = 0; j < cols; j++){
  //     if( bool_th_mat[th_index[i]][j] ) t.push_back(j);
  //   }
  //   T.push_back(t);
  // }
  int has_edge_i = 0;
  int has_all_edges = 1;
  for( i = 0; i < cols ; i++){
    has_edge_i = 0;
    for( j = 0; j < n_ths ; j++) {
      //cout << "Checking matrix position " << th_index[j] << "," << i << endl;
      has_edge_i |= bool_th_mat[th_index[j]][i];
    }
    //printf("\t Has edge %d\n",i);
    has_all_edges &= has_edge_i;
    if (!has_all_edges) return 0;
  }
  return 1;
}

/*
  Visits all t-sets of the set (0,1,2,...n-1).
  Do not modify, take it as a guide to make other
  algorithms that need the t-sets of [0,n-1].
*/
void t_combinations(int n, int t){
  int c[t+3];
  int j;
  c[0] = 9999;
  for(int i=1; i < t+1; i++){
      c[i] = i-1;
  }
  c[t+1] = n;
  c[t+2] = 0;
  while (true) {
    usleep(1000000);
    //L2. Visit. Here we check if current combination is a thrackle or nah.
    for(int i = t; i > 0; i--){
      printf(" %d ",c[i]);
    }
    printf("\n");
    //L3. FIND j
    j = 1;
    while( (c[j] + 1) == c[j+1] ) {
        c[j] = j - 1;
        j = j + 1;
    }
    //L4. Termination condition met?
    if (j > t) {
        //std::cout << res << " combinations\n";
        break;
    }
    //L5. Update and Return to L2.
    c[j] = c[j] + 1;
  }
}



void printMatrix(int ** matrix, int rows, int cols){
  int * ptr;
  cout << "    ";
  for(int i = 0; i < cols;i++){
      if(i>=10) cout << i << "| ";
      else cout << i << " | ";
  }
  cout << endl << endl;
  for(int i = 0; i < rows; i++){
      ptr = (int * ) matrix[i];
      if(i>=10) cout << i << ": ";
      else cout << i << ":  ";
      for(int j = 0; j < cols; j++){
          cout << *ptr++ << " | ";
      }
      cout << "\n";
  }
}
void freeMatrix(int ** matrix, const int rows){
  int i;
  int **a;
  a = (int **)matrix;
  for ( i=0; i<rows; i++ ) free( a[i] );
  free ( a );
}
