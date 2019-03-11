#include "../include/decomposition.h"

bool look8876(int );
int main(){
  look8876(1);
}

/*
  For K_8, we know cat(K_8) = 5. So we try to find a decomposition
  of size 4. We know that 8+7+7+6 = binom(8,2) so we look for this one.
  A thrackle of size 8(max), a thrackle of size 7, 6 and 5.

  We have the files 8_8_All_bool.ths, 8_7_All_bool.ths, 8_6_All_bool.ths

  We also know that for K_8 there are 3315 order types.
*/

bool look8876(int ot){
  int current_ot = 0;
  int eater = 0;
  int i,j,k,l,m,c;
  int nedges = 28;
  int nt88,nt87,nt87_2,nt86;

  //Open all files.
  ifstream h88, h87, h87_2, h86;
  h88.open("ths/8_8_All_bool.ths", ios::binary);
  h87.open("ths/8_7_All_bool.ths", ios::binary);
  h87_2.open("ths/8_7_All_bool2.ths", ios::binary);
  h86.open("ths/8_6_All_bool.ths", ios::binary);
  h88.seekg(0,h88.beg);
  h87.seekg(0,h87.beg);
  h87_2.seekg(0,h87_2.beg);
  h86.seekg(0,h86.beg);

  if (!h88.good() || !h87.good() || !h86.good()) {
    fprintf(stderr, "Error opening thrackle file!!\n");
    exit(-1);
  }
  if( !h87_2.good() ) {
    fprintf(stderr, "Error opening H87_2 thrackle file!!\n");
    exit(-1);
  }
  while (current_ot != ot){
    h88.read( (char*)&eater,sizeof(uint16_t));//ot
    h88.read( (char*)&eater,sizeof(uint16_t)); //number_of_t
    c = eater;
    for(i = 0; i < c; i++){
      for ( j = 0 ; j < nedges ; j++){
        h88.read( (char*)&eater,sizeof(char)); //boolean
      }
    }
    h87.read( (char*)&eater,sizeof(uint16_t));//ot
    h87.read( (char*)&eater,sizeof(uint16_t)); //number_of_t
    c = eater;
    for(i = 0; i < c; i++){
      for ( j = 0 ; j < nedges ; j++){
        h87.read( (char*)&eater,sizeof(char)); //boolean
      }
    }
    h87_2.read( (char*)&eater,sizeof(uint16_t));//ot
    h87_2.read( (char*)&eater,sizeof(uint16_t)); //number_of_t
    c = eater;
    for(i = 0; i < c; i++){
      for ( j = 0 ; j < nedges ; j++){
        h87_2.read( (char*)&eater,sizeof(char)); //boolean
      }
    }
    h86.read( (char*)&eater,sizeof(uint16_t));//ot
    h86.read( (char*)&eater,sizeof(uint16_t)); //number_of_t
    c = eater;
    for(i = 0; i < c; i++){
      for ( j = 0 ; j < nedges ; j++){
        h86.read( (char*)&eater,sizeof(char)); //boolean
      }
    }
    current_ot++;
  }
  eater = 0;
  h88.read( (char*)&eater,sizeof(uint16_t));//ot
  h88.read( (char*)&eater,sizeof(uint16_t)); //number_of_t
  nt88 = eater;
  printf("For OT %d there are %d thracklese of size 8.\n",ot, nt88 );
  eater = 0;
  h87.read( (char*)&eater,sizeof(uint16_t));//ot
  h87.read( (char*)&eater,sizeof(uint16_t)); //number_of_t
  nt87 = eater;
  printf("For OT %d there are %d thracklese of size 7.\n",ot, nt87 );
  eater = 0;
  h87_2.read( (char*)&eater,sizeof(uint16_t));//ot
  h87_2.read( (char*)&eater,sizeof(uint16_t)); //number_of_t
  nt87_2 = eater;
  printf("For OT %d there are %d thracklese of size 7.\n",ot, nt87_2 );
  eater = 0;
  h86.read( (char*)&eater,sizeof(uint16_t));//ot
  h86.read( (char*)&eater,sizeof(uint16_t)); //number_of_t
  nt86 = eater;
  printf("For OT %d there are %d thracklese of size 6.\n",ot, nt86 );
  eater = 0;
  bool arr[28];
  bool arr_bk4[28];
  bool arr_bk3[28];
  bool arr_bk2[28];
  bool arr_bk1[28];
  bool arr88[nt88][28];
  bool arr87[nt87][28];
  bool arr86[nt86][28];

  for ( i = 0; i < 28; i++) arr[i] = false;
  //Fill the matrices of thrackles.
  bool val;
  for (j = 0 ; j < nt88 ; j++ ) {
    for( i = 0 ; i < 28 ; i++){
      h88.read( (char*) & val, sizeof(char));
      arr88[j][i] = val;
    }
  }
  for (j = 0 ; j < nt87 ; j++ ) {
    for( i = 0 ; i < 28 ; i++){
      h87.read( (char*) & val, sizeof(char));
      arr87[j][i] = val;
    }
  }
  for (j = 0 ; j < nt86 ; j++ ) {
    for( i = 0 ; i < 28 ; i++){
      h86.read( (char*) & val, sizeof(char));
      arr86[j][i] = val;
    }
  }
  h88.close();
  h87.close();
  h87_2.close();
  h86.close();

  for(i=0; i < 28 ; i ++) arr_bk1[i] = arr[i];
  for( int l1 = 0; l1 < nt88 ; l1++) {
    for( i = 0 ; i < 28 ; i++) arr[i] |= arr88[l1][i];
    for( i = 0 ; i < 28 ; i++) arr_bk2[i] = arr[i];
    for( int l2 = 0; l2 < nt87 ; l2++) {
      for( j = 0 ; j < 28 ; j++) {
        if ( arr[j] == arr87[l2][j] ) avoid_flag = true;
        arr[j] |= arr87[l2][j];
      }
      if (!avoid_flag) {
        for( j = 0 ; j < 28 ; j++) arr_bk3[j] = arr[j];
        for( int l3 = 0 ; l3 < nt87 ; l3++) {
          for( k = 0 ; k < 28 ; k++) arr[i] |= arr87[l3][k];
          for( k = 0 ; k < 28 ; k++) arr_bk4[k] = arr[k];
          for( int l4 = 0 ; l4 < nt86 ; l4++ ){
            for( l = 0 ; l < 28 ; l++) arr[l] |= arr86[l4][l];
            //Check if arr[l] cotains only 1s.
            bool covering = true;
            for( l = 0 ; l < 28 ; l++) covering &= arr[l];
            if ( covering ) {
              printf("Covers \n");
              return 1;
            }
            for( l = 0 ; l < 28 ; l++) arr[l] = arr_bk4[l];
          }
          for( k = 0 ; k < 28 ; k++) arr[k] = arr_bk3[k];
        }
      }
      for( j = 0 ; j < 28 ; j++) arr[j] = arr_bk2[j];
    }
    for( i = 0 ; i < 28 ; i++) arr[i] = arr_bk1[i];
  }
  return 0;
}
