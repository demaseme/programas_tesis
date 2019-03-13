#include "../include/decomposition.h"
#include "../include/disjointness.h"
int load_custom_file(string, vector<Point> & );
void findRandomMaxThrackles(vector<Thrackle> & , vector<Edge> &, int, int);

/*
  MAY NOT BE VIABLE FOR N=20, there are binom( binom(20 2) 20) = 5.48 x 10^26 possible combinations. 548 septillions.
*/
int main(int argc, char * argv[]){
  vector<Point> P;
  vector<Edge> E;
  vector<vector<int>> positions; // Each element of this vector, is a list of positions of edges which together are a thrackle.
  int n, rows, cols, thrackleCounter,k;
  int ** matrix;

  load_custom_file("points_20.dat",P);
  n = (int) P.size();
  k = n;
  rows = cols = n*(n-1)/2.0;
  printf("There are %d edges.\n",cols);
  matrix = (int **)malloc(rows * sizeof(int*));
  for(int i = 0; i < rows; i++) matrix[i] = (int *)malloc(cols * sizeof(int));
  generateAllEdges(P,E);
  findRandomMaxThrackles(E,n);
  thrackleCounter = 0;
  std::chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
  construct_disjointness_matrix(E,matrix,rows,false);
  thrackleCounter=get_kthrackles_of_matrix(matrix,rows,k,positions);
  cout << "There are " << thrackleCounter << " thrackles of size " << k << endl;
  std::chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
  chrono::duration<double, std::milli> time_span = t2 - t1;
  cout << "It took me " << time_span.count() << " milliseconds.";
  cout << std::endl;

  return 1;
}

/*
    Finds k thrackles by randomly choosing n edges, then checking if they form a thrackle.
    Stores found thrackles on vector<Thrackle> T.
*/
findRandomMaxThrackles(vector<Thrackle> & T,vector<Edge> E, int n, int k){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    vector<Edge> local_e = E;
    vector<Edge> candidate;

    while(T.size() < k){
        candidate.clear();
        shuffle(local_e.begin(),local_e.end(),default_random_engine(seed));
        //Choose first n.
        for(int i = 0; i < n; i++){
            candidate.push_back(local_e[i]);
        }
        if ( isThrackle(candidate) ) {
            Thrackle tmp;
            tmp.edges = candidate;
            T.push_back(tmp);
        }
    }
}
/*
  Opens a custom point file, and creates its N_K_All.ths and N_K_All_bool.ths
  The custom file is a text file where the first line indicates
  how many coordinates does the file describe. Then each coordinate is in one row.
  Stores in reference vector v_point.
*/
int load_custom_file(string filename, vector<Point> & v_point){
  ifstream file;
  int x,y,eat;
  file.open(filename);
  if (!file.good()) {
    fprintf(stderr, "Error opening %s\n",filename.c_str() );
    return 0;
  }
  file >> eat;
  v_point.resize(eat);
  for(int i = 0; i < eat; i++){
    file >> x >> y;
    v_point[i].x = x;
    v_point[i].y = y;
  }
  file.close();
  return 1;
}
