#include "../include/decomposition.h"
int count_thrackles(int set_size, int t_size,int desired_ot){
  string file_name;
  file_name = "ths/"+to_string(set_size)+"_"+to_string(t_size)+"_All_bool.ths";
  ifstream myfile;
  int thrackleCounter;
  int current_ot = 0;
  int i,j,c;
  int cols = set_size*(set_size-1)/2.0; //COMMENTARIO
  //cout << "Opening " << file_name << endl;
  myfile.open(file_name, ios::binary);
  myfile.seekg(0,myfile.beg);
  if(!myfile.is_open()) {
    fprintf(stderr, "Error opening thrackle boolean file %s\n", file_name.c_str());
    exit(-1);
  }
  //foundThrackles.clear();
  int eater = 0;
  while(current_ot != desired_ot){
  //  cout << current_ot << endl;
    myfile.read( (char*)&eater,sizeof(uint16_t));//ot
    myfile.read( (char*)&eater,sizeof(uint16_t)); //number_of_t
    c = eater;
    //cout << "Skipping " << c << " thrackles\n";
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
  //cout << "Arrived at ot " << desired_ot << endl;
  myfile.read( (char*)&eater,sizeof(uint16_t));//ot
  myfile.read( (char*)&eater,sizeof(uint16_t)); //number_of_t
  c = eater;
  thrackleCounter = c;
  //printf("There are %d thrackles.\n", thrackleCounter );
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
  //cout << "Opening " << file_name << endl;
  myfile.open(file_name, ios::binary);
  myfile.seekg(0,myfile.beg);
  if(!myfile.is_open()) {
    fprintf(stderr, "%s\n", "Error loading thrackle boolean file\n");
    exit(-1);
  }
  //foundThrackles.clear();
  int eater = 0;
  while(current_ot != desired_ot){
    //cout << current_ot << endl;
    myfile.read( (char*)&eater,sizeof(uint16_t));//ot
    myfile.read( (char*)&eater,sizeof(uint16_t)); //number_of_t
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
  myfile.read( (char*)&eater,sizeof(uint16_t));//ot
  myfile.read( (char*)&eater,sizeof(uint16_t)); //number_of_t
  c = eater;
  thrackleCounter = c;
  //cout << "Reading " << thrackleCounter << " thrackles\n";
  for(i = 0; i < thrackleCounter; i++){
    Thrackle tmp_thrackle;
    for ( j = 0 ; j < cols ; j++){
      eater = 0;
      myfile.read( (char*)&eater,sizeof(char)); //boolean
      // tmp_thrackle.edge_bool.push_back(eater);
      bool_th_mat[i][j] = eater;
    }
    // foundThrackles.push_back(tmp_thrackle);

  }
  myfile.close();
  return 1;
}

/*
  Chooses ordertypes which union of thrackles covers the graph.
  Used by m_statistics.cpp
*/
void select_otypes(int n, vector<int> & otypes_vec){
  //Search for K_n_statistics.dat.
  ifstream myfile;
  string file_name = "K_" + to_string(n) + "_"+ to_string(n) +"_statistics.dat";
  myfile.open(file_name);
  if (!myfile.good()){
    fprintf(stderr, "Unable to open statistics file %s\n",file_name.c_str());
    exit(-1);
  }
  int i, eat, cover;
  myfile.ignore(10000,'\n');
  while(myfile >> i >> eat >> eat >> cover){
    if ( cover == 1) otypes_vec.push_back(i);
  }
}
void select_otypes_withmax_rnd(int n, vector<int> & otypes_vec){
  //Search for K_n_statistics.dat.
  ifstream myfile;
  string file_name = "K_" + to_string(n) + "_"+ to_string(n) +"_statistics.dat";
  myfile.open(file_name);
  if (!myfile.good()){
    fprintf(stderr, "Unable to open statistics file %s\n",file_name.c_str());
    exit(-1);
  }
  int i, eat, cover;
  myfile.ignore(10000,'\n');
  while(myfile >> i >> eat >> eat >> cover){
    if ( cover == 1) otypes_vec.push_back(i);
  }
}
//Returns true if union of found thrackles cover K_n graph
bool mat_union_covers(int ** bool_th_mat, int cols, int rows){
  int i,j;
  for(i = 0 ; i < cols; i++) {
    bool has_edge_i = 0;
    for( j = 0 ; j < rows; j++){
      has_edge_i |= bool_th_mat[j][i];
    }
    if (!has_edge_i) return false;
  }
  return true;
}

bool check_empty_q_intersection_all(int ** bool_th_mat, int rows, int q, int setsize){
  int c[q+3];
  int c_curr[q];
  int j,m;
  int n = rows;
  int cols = setsize*(setsize-1)/2.0;
  c[0] = 9999;
  for(int i=1; i < q+1; i++){
      c[i] = i-1;
  }
  c[q+1] = n;
  c[q+2] = 0;

  while (true) {
    //L2. Visit.
    //For each generated, check if it's a decomposition.
    //usleep(100000);
    //printf("Checking ");
    for(int i = q; i > 0; i--){

      c_curr[i-1] = c[i];

    //  printf(" %d ",c[i]);
    }
    //printf("Couting reps\n" );
    m = count_repetitions(bool_th_mat,c_curr,cols,q,setsize);
    //Write to file if m is empty. <c_curr> m
    if(m == 0) {
        for(int i = q; i > 0; i--){
          printf(" %d ",c[i]);
        }
        printf("\n");
        return true;
    }
    //L3. FIND j
    j = 1;
    while( (c[j] + 1) == c[j+1] ) {
        c[j] = j - 1;
        j = j + 1;
    }
    //L4. Termination condition met?
    if (j > q) {
        //std::cout << res << " combinations\n";
        break;
    }
    //L5. Update and Return to L2.
    c[j] = c[j] + 1;
  }
  printf("No %d-intersection empty\n",q);
  return false;
}
/*
  Forms all q-sets of [0...rows], then, for each tuple
  calculates its intersection size, then writes it to
  myfile.
*/
void calculate_q_intersection_all(int ** bool_th_mat, int rows, int q, int setsize, ofstream & myfile){
  int counter =0;
  int c[q+3];
  int c_curr[q];
  int j,m;
  int n = rows;
  int cols = setsize*(setsize-1)/2.0;
  c[0] = 9999;
  for(int i=1; i < q+1; i++){
      c[i] = i-1;
  }
  c[q+1] = n;
  c[q+2] = 0;

  while (true) {
    //L2. Visit.
    //For each generated, check if it's a decomposition.
    //usleep(100000);
    //printf("Checking ");
    counter++;
    //printf("Analyzing set number %d\n",counter);
    for(int i = q; i > 0; i--){

      c_curr[i-1] = c[i];

    //  printf(" %d ",c[i]);
    }
    //printf("Couting reps\n" );
    m = count_repetitions(bool_th_mat,c_curr,cols,q,setsize);
    myfile.write( (char*) &m,sizeof(char)); // Write only the size of the intersection.

    //L3. FIND j
    j = 1;
    while( (c[j] + 1) == c[j+1] ) {
        c[j] = j - 1;
        j = j + 1;
    }
    //L4. Termination condition met?
    if (j > q) {
        //std::cout << res << " combinations\n";
        break;
    }
    //L5. Update and Return to L2.
    c[j] = c[j] + 1;
  }
}


/*

  Take all sets of thrackles of size th_set_size.
  For each one of those that it's an actual decomposition:
    count repetiions

*/
void count_repetitions_all(int ** bool_th_mat, int rows, int k, int setsize, int m_arr[2]){
  //Generate the k_combinations.
  //int counter =0;
  int c[k+3];
  int c_curr[k];
  int j;
  int n = rows;
  int cols = setsize*(setsize-1)/2.0;
  int m_min = 99;
  int m_max = -1;
  int m_cur = 0;
  c[0] = 9999;
  for(int i=1; i < k+1; i++){
      c[i] = i-1;
  }
  c[k+1] = n;
  c[k+2] = 0;

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
      //printf("Decomposition found : ");
      for(int i = k; i > 0; i--){
        printf("%d ",c_curr[i-1]);
      }
      printf("\n");
      //usleep(1000000);

      m_cur = count_repetitions(bool_th_mat,c_curr,cols,k,setsize);
      if( m_cur > m_max) {
        m_max = m_cur;
        // for(int i = k; i > 0; i--){
        //   printf(" %d ",c[i]);
        // }
        // printf("\n");
      }
      if( m_cur < m_min) m_min = m_cur;

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
  m_arr[0] = m_min;
  m_arr[1] = m_max;
}
/*
    From given thrackle list count how many edges are repeated
    pairwise.
*/
int count_repetitions(int ** bool_th_mat, int th_index[], int ncols, int nthrs, int setsize){
    int i,j;
    int edge_i_count;
    int m = 0;

    //printf("cols %d, thrs: %d, setsize: %d\n",ncols,nthrs,setsize);
    for (i = 0; i < ncols; i++){
        edge_i_count = 0;
        for( j = 0 ; j < nthrs; j++ ){
          //printf("Checking %d,%d\n",i,j);
            if (bool_th_mat[th_index[j]][i]){
                edge_i_count++;
            }
        }
        if (edge_i_count > 1){
          m++;
        }
    }
    // printf("Number of repeated edges: %d\n"
    // "Total of edges in this set of thrackles %d\n", m, (nthrs*setsize - m));
    return m;
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
      usleep(1000000);
      //printf("Decomposition found : ");
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
  int edgecounter = 0;
  for( i = 0; i < cols ; i++){
    has_edge_i = 0;
    for( j = 0; j < n_ths ; j++) {
      //cout << "Checking matrix position " << th_index[j] << "," << i << endl;
      has_edge_i |= bool_th_mat[th_index[j]][i];
    }
    has_all_edges &= has_edge_i;
    if (!has_all_edges) return 0;
    edgecounter++;
  }
  //printf("Has %d / %d edges.",cols,edgecounter);
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
    //usleep(1000000);
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

/*
    Returns true if all items of a[] are less or equal than max_val
    and if the occurrence of max_val is unique.
*/
bool is_partition_valid(int a[], int size, int max_val){
    int c=0;
    for( int i = 1; i < size; i++){
        if(a[i] > max_val) return false;
        if(a[i] == max_val) c++;
        if (c > 1) return false;
    }
    return true;
}

void print_integer_partition(int size, int a[]) {
  for (int i = 1; i < size; ++i) {
    if (a[i] == 0)
      break;
    if (i != 1)
      printf(" + ");
    printf("%" "u", a[i]);
  }
  printf("\n");
}
void generate_integer_partitions_constrained(int size, int max_size, int max_val, int a[], void (*visit)(int, int*)) {
    int n = size - 1;
    if (n == 0) {
        visit(size, a); // visit empty partition
        return;
    }
    //P1
    a[0] = 0;
    int m = 1;
    for ( ; ; ) { //P2
        a[m] = n;
        //while( a[m] > max_val) a[m]--;
        int q = m - (n == 1);
        for ( ; ; ) {
            if  ( (m == max_size) && is_partition_valid(a,m+1,max_val)) visit(m+1, a); //P3
            if (a[q] == 2) { //P4
                a[q] = 1;
                q -= 1;
                m += 1;
                a[m] = 1;
                continue; // goto P3
            }
            else {
                if (q == 0)
                return;//P5
                int x = a[q] - 1;
                // cout << "Inserting " << x << endl;
                a[q] = x;
                for (n = m - q + 1, m = q + 1; x < n; m += 1, n -= x) a[m] = x;//P6
                break; // goto P2
          }
        }
    }
}

void generate_integer_partitions(int size, int a[], void (*visit)(int, int*)) {
    int n = size - 1;
    if (n == 0) {
        visit(size, a); // visit empty partition
        return;
    }
    //P1
    a[0] = 0;
    int m = 1;
    for ( ; ; ) { //P2
        a[m] = n;
        int q = m - (n == 1);
        for ( ; ; ) {
            visit(m+1, a); //P3
            if (a[q] == 2) { //P4
                a[q] = 1;
                q -= 1;
                m += 1;
                a[m] = 1;
                continue; // goto P3
            }
            else {
                if (q == 0)
                return;//P5
                int x = a[q] - 1;
                a[q] = x;
                for (n = m - q + 1, m = q + 1; x < n; m += 1, n -= x) a[m] = x;//P6
                break; // goto P2
          }
        }
    }
}

void writeResults(ofstream & myfile, int ot, int th_set_size, int m_min, int m_max){
  myfile << ot << " " ;
  myfile << th_set_size << " ";
  myfile << m_min << " ";
  myfile << m_max << " " << endl;
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
void freeMatrix_dec(int ** matrix, const int rows){
  int i;
  int **a;
  a = (int **)matrix;
  for ( i=0; i<rows; i++ ) free( a[i] );
  free ( a );
}
