#include "../include/decomposition.h"

//This program runs statistics to find the maximum m (repeated edges)
//For each order type of given n.
//And then for each decomposition of size [2,cat(K_n)] found.

int main(int argc, char * argv[]){
  if (argc <= 1 || argc > 2){
    fprintf(stderr, "Usage %s <n>\n", argv[0] );
    exit(-1);
  }

  int n,k,otypes,start,end;
  n = atoi(argv[1]);

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
  start = 2;
  end = n - floor(sqrt(2*n + (1/4.0)) - (1/2.0));
  cout << start << " -> " << end << endl; 

  return 1;
}
