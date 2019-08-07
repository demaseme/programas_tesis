#include "../include/decomposition.h"

int cn_arr[158817];
int load_cn();
int max_cn();
int min_cn(int &);
void printcn_range(int l, int r);
int main(){

  int ot_convexat[8] = {0,8,12,54,80,696,1080,1287};
  int ot_higherat[11] = {8,1074,1268,4777,4888,17539,17967,17977,17982,18601,74934 };
  load_cn();
  printcn_range(36, 40);
  // int min_index = 0;
  // int mincn = min_cn(min_index);
  // printf("minimal cn %d, index is %d\n",mincn,min_index);
  // printf("Max CN is : %d\nMin CN is: %d\n",max_cn(),min_cn());
  // for ( int i = 0; i < 8;  i++) {
  //   printf("For OT %d, its crossing-number is %d\n",ot_convexat[i], cn_arr[ot_convexat[i]]);
  // }
  // printf("Now printing the ones that cover but don't acquire minimal at.\n");
  // for ( int i = 0; i < 11;  i++) {
  //   printf("For OT %d, its crossing-number is %d\n",ot_higherat[i], cn_arr[ot_higherat[i]]);
  // }
  return 1;
}
int max_cn(){
  int max = cn_arr[0];
  for ( int i = 1; i < 3315; i++) {
    if (cn_arr[i] > max) max = cn_arr[i];
  }
  return max;
}
int min_cn(int & index){
  int min = cn_arr[0];
  //int s_min = cn_arr[1];
  for ( int i = 1; i < 158817; i++) {
    if (cn_arr[i] < min){
        min = cn_arr[i];
        index = i;
    }

  }
  return min;
}
int load_cn(){
  string file_name = "../../OT/crossn09.b08";
  ifstream fileh;
  fileh.open(file_name,ios::binary);
  int eater;
  if (! fileh.good()) {
    fprintf(stderr, "Error opening file %s \n", file_name.c_str());
    exit(-1);
  }
  for ( int i = 0 ; i < 158817 ; i++){
    eater = 0;
    fileh.read( (char*)&eater, sizeof(char));
    cn_arr[i] = eater;
  }
  return 1;
}

void printcn_range(int l, int r){
    for ( int i = 0; i < 158817 ; i ++){
        if ( cn_arr[i] >= l && cn_arr[i] <= r){
            printf("%d %d \n",i,cn_arr[i]);
        }
    }
}
