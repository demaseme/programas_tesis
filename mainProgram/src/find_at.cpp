#include "../include/disjointness.cpp"

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
  int desired_ot = argv[2];
  //Load edges.
  
  //Create disjointnes matrix
  //exhaustive_at
  return 1;
}
