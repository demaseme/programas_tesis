#include "../include/otclass.hpp"
#include "../include/decomposition.h"
OrderType * ots;
int * cn_arr;
int ots_size;

void load_ordertypes(int , int );
int load_cn(int n, int total_ots);
bool sortcnfun(OrderType t1, OrderType t2);
int main(int argc, char * argv[]){
  if (argc < 2 ){
    fprintf(stderr, "Usage %s <n>\n", argv[0] );
    exit(-1);
  }
  int n = atoi(argv[1]);
  load_ordertypes(n,n);
  //Sort them by number of thrackles.
  vector<OrderType> vots (ots,ots+ots_size);
  std::sort(std::begin(vots), std::end(vots));
  for ( int i = 0; i < ots_size; i++){
    printf("%d %d %d\n",vots[i].number,vots[i].nthrackles,vots[i].cn);
  }
  printf("==================\n");
  //Sorthem by cn
  std::sort(std::begin(vots), std::end(vots),sortcnfun);
  for ( int i = 0; i < ots_size; i++){
    printf("%d %d %d\n",vots[i].number,vots[i].nthrackles,vots[i].cn);
  }
  free(cn_arr);
  free(ots);
  return 1;
}
void load_ordertypes(const int n, const int k){
  int ot_sizes[8] = {1,2,3,16,135,3315,158817,14309547};
  int total_ots = ot_sizes[n-3];
  ots_size = total_ots;
  ots = (OrderType*)malloc( total_ots * sizeof(OrderType));
  cn_arr = (int*)malloc( total_ots * sizeof(int));
  load_cn(n,total_ots);
  printf("OTS array created\n");

  string file_name = "data/K_" + to_string(n) +"_"+ to_string(k) + "_statistics.dat";
  ifstream file_h;
  file_h.open(file_name);
  if (file_h.bad() || !file_h.good()){
    fprintf(stderr, "Error opening file %s\n", file_name.c_str());
    exit(-1);
  }
  file_h.ignore(10000,'\n');
  int i,th_count,eat,cover;

  while(file_h >> i >> th_count >> eat >> cover){

    ots[i].number = i;
    ots[i].nthrackles = th_count;
    ots[i].cn = cn_arr[i];

  }

}

int load_cn(int n, int total_ots){
  string file_name;
  if (n < 10) file_name = "../../OT/crossn0"+to_string(n)+".b08";
  else file_name = "../../OT/crossn"+to_string(n)+".b08";
  ifstream fileh;
  fileh.open(file_name,ios::binary);
  int eater;
  if (! fileh.good()) {
    fprintf(stderr, "Error opening file %s \n", file_name.c_str());
    exit(-1);
  }
  for ( int i = 0 ; i < total_ots ; i++){
    eater = 0;
    fileh.read( (char*)&eater, sizeof(char));
    cn_arr[i] = eater;
  }
  fileh.close();
  return 1;
}

bool sortcnfun(OrderType t1, OrderType t2){
    return (t1.cn > t2.cn);
}
