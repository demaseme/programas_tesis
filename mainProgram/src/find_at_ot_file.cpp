#include "../include/disjointness.h"
void loadPoints(const int n, const int ot, vector<Point> & p);
void load_ot_file(string file, vector<int> & ots);
/*
    This program uses the exhaustive_at algorithm from disjointnes.cpp
    Receives an n. Finds the AT for that specific set in all OT.
    Skips the convex ot.
*/

int main( int argc, char * argv[]){
    if ( argc < 2 ){
        fprintf(stderr, "Usage %s n ot_file \n",argv[0] );
        exit(-1);
    }
  //RCV n ot
  int n = atoi(argv[1]);
  string ot_file_name(argv[2]);
  if ( n > 10 ){
      fprintf(stderr, "There is no data for n>10\n");
      exit(-1);
  }
  if ( n < 3 ) {
      fprintf(stderr, "There is no data for n<3\n");
      exit(-1);
  }
  vector<int> ordertypes;


  int ot_ind = 0;
  vector<Point> points;
  vector<Edge> edges;
  vector<int> startingThrackle;
  int ** dmatrix; //matrix to store the disjointness matrix. Squared matrix.
  int cols,rows;
  rows = n*(n-1)/2.0;
  cols = rows;
  dmatrix = (int **)malloc(rows * sizeof(int*));
  for(int i = 0; i < rows; i++) dmatrix[i] = (int *)malloc(cols * sizeof(int));
  load_ot_file(ot_file_name,ordertypes);
  std::chrono::high_resolution_clock::time_point totalt1 = chrono::high_resolution_clock::now();
  std::ofstream myfile;
  myfile.open ("example.csv");
  while ( ot_ind < (int)ordertypes.size() ){
      points.resize(n);
      loadPoints(n,ordertypes[ot_ind],points);
      //Load edges.
      generateAllEdges(points,edges);
      //printf("There are %d points and %d edges.\n",(int)points.size(),(int)edges.size());
      //Create disjointnes matrix
      construct_disjointness_matrix(edges,dmatrix,rows,false);
      //printf("Matrix constructed!\n");

      //exhaustive_at
      //for(int i = 0; i < n;i++) startingThrackle.push_back(i);
      //find_next_thrackle(dmatrix,cols,startingThrackle,startingThrackle,n,false);
      //printVectorInt(startingThrackle);
      vector<vector<int>>  thrackle_list;
      exhaustive_at(dmatrix, cols, n, startingThrackle, 0,0,thrackle_list);

      //myfile << "This is the first cell in the first column.\n";
      myfile << ordertypes[ot_ind] <<",\"";
      for(int i = 0; i < (int) thrackle_list.size();i++){

          for( int j = 0; j < (int) thrackle_list[i].size() ; j++){
              myfile << thrackle_list[i][j] << " ";
          }
          myfile << "\n";
      }
      myfile << "\"\n";
      //printf("AT: %d\n",minAt);
      printf("%d %d %d\n",n,ordertypes[ot_ind],minAt);
      points.clear();
      ot_ind++;
      minAt = 9999;
      //freeMatrix(dmatrix,rows);
  }
  myfile.close();
  std::chrono::high_resolution_clock::time_point totalt2 = chrono::high_resolution_clock::now();
  chrono::duration<double, std::milli> time_span_total = totalt2 - totalt1;
  cout << "It took me " << time_span_total.count() << " milliseconds.\n";
  return 1;
}

void loadPoints(const int n, const int desired_ot, vector<Point> & P){
  string file_name;
  ifstream file_h;
  int read_size;
  int ot = 0;
  if ( n == 9 ) file_name = "../../OT/otypes09.b16";
  if ( n == 10) file_name = "../../OT/otypes10.b16";
  if ( n < 9  ) file_name = "../../OT/otypes0"+to_string(n)+".b08";
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
void load_ot_file(string file_name, vector<int> & ots){
    ifstream myfile;
    int ot;
    myfile.open(file_name);
    if (!myfile.good()){
        fprintf(stderr, "Error opening file %s\n",file_name.c_str());
        exit(-1);
    }
    while ( myfile >> ot){
        ots.push_back(ot);
    }
    myfile.close();
}
