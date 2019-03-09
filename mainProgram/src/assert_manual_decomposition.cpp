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
  int i,j,k,m,c;
  int nedges = 28;
  int nt88,nt87,nt87_2,nt86;
  //Open all files.
  ifstream h88, h87, h87_2, h86;
  h88.open("ths/8_8_All_bool.ths", ios::binary);
  h87.open("ths/8_7_All_bool.ths", ios::binary);
  h87_2.open("ths/8_7_All_bool.ths", ios::binary);
  h86.open("ths/8_6_All_bool.ths", ios::binary);
  h88.seekg(0,h88.beg);
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
  for ( i = 0; i < 28; i++) arr[i] = false;

  for( i = 0; i < 28; i++) arr_bk1[i] = arr[i];
  for( i = 0 ; i < nt88; i++){
    int val = 0;
    if ( i== 0 ) printf("i=%d>1   ",i);
    for ( int c = 0; c < nedges; c++){
      h88.read( (char*)&val,sizeof(char));
      arr[c] = val;
      if(i == 0) printf("%d ",val);
    }
    if(i == 0) printf("\n");
    for ( int c = 0; c < 28; c++) arr_bk2[c] = arr[i];
    for( j = 0; j < nt87; j++){
      int val2 = 0;
      if ( j== 0 ) printf("j=%d>2   ",j);
      for ( int c = 0; c < nedges; c++){
        h87.read( (char*)&val2,sizeof(char));
        arr[c] |= val2;
        if(j == 0) printf("%d ",val2);
      }
      if(j == 0) printf("\n");
      for ( int c = 0; c < nedges; c++) arr_bk3[c] = arr[c];
      for ( k = 0 ; k < nt87_2; k++){
        int val3 = 0;
        if(k==518) printf("m=%d>3 ", k);
        for ( int c = 0; c < nedges; c++){
          h87_2.read( (char*)&val3,sizeof(char));
          arr[c] |= val3;
          if(k==518) printf("%d ",val3);
        }
        if(k==518) printf("\n");
        for ( int c = 0; c < nedges; c++) arr_bk4[c] = arr[c];
        for (m = 0 ; m < nt86; m++){
          int val4 = 0;
          if(k==518 && m == 933) printf("m=%d>4 ",m);
          for ( int p = 0; p < nedges; p++){
            h86.read( (char*)&val4,sizeof(char));
            arr[p] |= val4;
            if(k==518 &&  m==933) {
              printf("%d ",val4);
            }
          }
          if(k==518 &&  m==933) printf("\n");
          bool cover = 1;
          for( int c = 0; c < nedges; c++) cover &= arr[c];
          if (cover) {
            printf("COVERED \n");
            printf("Thrackles (%d %d %d %d)\n", i,j,k,m);
            return 1;
          }
          for ( int c = 0; c < nedges; c++) arr[c] = arr_bk4[c];
        }
        for( int c = 0; c < nedges; c++) arr[c] = arr_bk3[c];
      }
      for( int c = 0; c < nedges; c++) arr[c] = arr_bk2[c];
    }
    for( int c = 0; c < nedges; c++) arr[c] = arr_bk1[c];
  }
  // printf("Displaying %d thrackles. \n", nt88 );
  // eater = 0;
  // for(i = 0; i < nt88; i++){
  //   printf("Thrackle %d : (", i);
  //   for(j = 0; j < nedges; j++ ){
  //     h88.read( (char*)&eater,sizeof(char));
  //     printf("%d ",eater);
  //   }
  //   printf(")\n");
  // }
  h88.close();
  h87.close();
  h87_2.close();
  h86.close();
  return 1;
}
