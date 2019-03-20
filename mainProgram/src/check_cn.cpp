#include "../include/decomposition.h"

int cn_arr[158817];
int load_cn();
int max_cn();
int min_cn();

int main(){
  int k = 10;
  int ot_interest[k] = {0,12,52,54,80,103,134,696,1080,1287};
  load_cn();
  printf("Max CN is : %d\nMin CN is: %d\n",max_cn(),min_cn());
  for ( int i = 0; i < k;  i++) {
    printf("For OT %d, its crossing-number is %d\n",ot_interest[i], cn_arr[ot_interest[i]]);
  }

  return 1;
}
int max_cn(){
  int max = cn_arr[0];
  for ( int i = 1; i < 158817; i++) {
    if (cn_arr[i] > max) max = cn_arr[i];
  }
  return max;
}
int min_cn(){
  int min = cn_arr[0];
  for ( int i = 1; i < 158817; i++) {
    if (cn_arr[i] < min) min = cn_arr[i];
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
