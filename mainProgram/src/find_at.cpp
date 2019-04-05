#include "../include/disjointness.h"
void loadPoints(const int n, const int ot, vector<Point> & p);


int main( int argc, char * argv[]){
    if ( argc < 3 ){
        fprintf(stderr, "Usage %s n ot\n",argv[0] );
        exit(-1);
    }
  //RCV n ot
  int n = atoi(argv[1]);
  if ( n > 10 ){
      fprintf(stderr, "There is no data for n>10\n");
      exit(-1);
  }
  int desired_ot = atoi(argv[2]);
  vector<Point> points;
  vector<Edge> edges;
  vector<int> startingThrackle;
  int ** dmatrix; //matrix to store the disjointness matrix. Squared matrix.
  int cols,rows;
  rows = n*(n-1)/2.0;
  cols = rows;
  dmatrix = (int **)malloc(rows * sizeof(int*));
  for(int i = 0; i < rows; i++) dmatrix[i] = (int *)malloc(cols * sizeof(int));

  points.resize(n);
  loadPoints(n,desired_ot,points);
  //Load edges.
  generateAllEdges(points,edges);
  //Create disjointnes matrix
  construct_disjointness_matrix(edges,dmatrix,rows,true);
  printf("Matrix constructed!\n");
  //exhaustive_at
  //for(int i = 0; i < n;i++) startingThrackle.push_back(i);
  //find_next_thrackle(dmatrix,cols,startingThrackle,startingThrackle,n,false);
  //printVectorInt(startingThrackle);
  exhaustive_at(dmatrix, cols, n, startingThrackle, 0,0);
  printf("AT: %d\n",minAt);
  return 1;
}

void loadPoints(const int n, const int desired_ot, vector<Point> & P){
  string file_name;
  ifstream file_h;
  int read_size;
  int ot = 0;
  if ( n == 9 ) file_name = "../../OT/otypes09.b16";
  if ( n == 10) file_name = "../../OT/otypes10.b16";
  else file_name = "../../OT/otypes0"+to_string(n)+".b08";
  file_h.open(file_name,ios::binary);
  if ( file_h.bad() ){
    fprintf(stderr, "Error opening file %s\n", file_name.c_str());
    exit(-1);
  }
  int x = 0;
  int y = 0;
  read_size = sizeof(char);
  if (n>8) read_size = sizeof(uint16_t);
  while (ot != desired_ot){
    for( int i = 0; i < n ;  i++){
      x = 0; y = 0;
      file_h.read( (char*) &x, read_size);
      file_h.read( (char*) &y, read_size);
    }
    ot ++;
  }
  for( int i = 0; i < n ;  i++){
    x = 0; y = 0;
    file_h.read( (char*) &x, read_size);
    file_h.read( (char*) &y, read_size);
    P[i].x = x;
    P[i].y = y;
  }
}
