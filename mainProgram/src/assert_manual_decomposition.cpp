#include "../include/decomposition.h"

bool look8876(int, int &);
bool look988(int ot, int & highest_level);
bool look888(int ot, int & highest_level);
void store98();
void free98();
bool ** mat98;
int rows98;
int ot_thackles[158817];
int main(){
  int ot = 1; // 3315
  int level = 0;
  int highest = 0;
  bool canceled = false;
  omp_set_num_threads(2);
  if (!omp_get_cancellation()) {
    printf("Cancellation variable not correctly set!\n");
    exit(-1);
  }
  store98();
  std::chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

  #pragma omp parallel
  {
    #pragma omp for
    for(ot = 1; ot < 158817; ot++) if( !look888(ot,highest) ) {
        #pragma omp cancel for
    };
  }
  std::chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
  chrono::duration<double, std::milli> time_span = t2 - t1;
  cout << "It took me " << time_span.count() << " milliseconds.";
  free98();
  // while(ot < 3315) {
  //   bool state = look8876(ot,level);
  //   ot++;
  //   if (highest < level) highest = level;
  //   if (state) break;
  // }
  // int dec[5] = {9,8,8,8,3};
  // omp_set_num_threads(4);
  // if (!omp_get_cancellation()) {
  //   printf("Cancellation variable not correctly set!\n");
  //   exit(-1);
  // }
  // #pragma omp parallel
  // {
  //   #pragma omp for nowait
  //   for ( ot = 1; ot < 158817; ot++) {
  //       printf("Thread %d working with ot %d\n",omp_get_thread_num(),ot);
  //       if (canceled){
  //       #pragma omp cancel for
  //     }
  //       if (!look988(ot,level)) {
  //         canceled = true;
  //       }
  //   }
  //}
  //printf("Highest level was %d\n", highest );
  return 1;
}

/*
  For K_8, we know cat(K_8) = 5. So we try to find a decomposition
  of size 4. We know that 8+7+7+6 = binom(8,2) so we look for this one.
  A thrackle of size 8(max), a thrackle of size 7, 6 and 5.

  We have the files 8_8_All_bool.ths, 8_7_All_bool.ths, 8_6_All_bool.ths

  We also know that for K_8 there are 3315 order types.
*/

bool look8876(int ot, int & highest_level){
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
  //printf("For OT %d there are %d thracklese of size 8.\n",ot, nt88 );
  eater = 0;
  h87.read( (char*)&eater,sizeof(uint16_t));//ot
  h87.read( (char*)&eater,sizeof(uint16_t)); //number_of_t
  nt87 = eater;
  //printf("For OT %d there are %d thracklese of size 7.\n",ot, nt87 );
  eater = 0;
  h87_2.read( (char*)&eater,sizeof(uint16_t));//ot
  h87_2.read( (char*)&eater,sizeof(uint16_t)); //number_of_t
  nt87_2 = eater;
  //printf("For OT %d there are %d thracklese of size 7.\n",ot, nt87_2 );
  eater = 0;
  h86.read( (char*)&eater,sizeof(uint16_t));//ot
  h86.read( (char*)&eater,sizeof(uint16_t)); //number_of_t
  nt86 = eater;
  //printf("For OT %d there are %d thracklese of size 6.\n",ot, nt86 );
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
  bool avoid_flag,avoid_flag2;
  for(i=0; i < 28 ; i ++) arr_bk1[i] = arr[i];
  for( int l1 = 0; l1 < nt88 ; l1++) {
    for( i = 0 ; i < 28 ; i++) arr[i] |= arr88[l1][i];
    for( i = 0 ; i < 28 ; i++) arr_bk2[i] = arr[i];
    for( int l2 = 0; l2 < nt87 ; l2++) {
      avoid_flag = false;
      for( j = 0 ; j < 28 ; j++) {
        if ( arr[j] == arr87[l2][j] && arr[j]  ) avoid_flag = true;
        arr[j] |= arr87[l2][j];
      }
      if (!avoid_flag) {
          if (highest_level < 2) highest_level = 2;
        for( j = 0 ; j < 28 ; j++) arr_bk3[j] = arr[j];
        for( int l3 = 0 ; l3 < nt87 ; l3++) {
          avoid_flag2 = false;
          for( k = 0 ; k < 28 ; k++) {
            if ( arr[k] == arr87[l3][k] && arr[k] ) avoid_flag2 = true;
            arr[k] |= arr87[l3][k];
          }
          if (!avoid_flag2) {
             if( highest_level < 3 ) highest_level = 3;
            for( k = 0 ; k < 28 ; k++) arr_bk4[k] = arr[k];
            for( int l4 = 0 ; l4 < nt86 ; l4++ ){
              for( l = 0 ; l < 28 ; l++) arr[l] |= arr86[l4][l];
              //Check if arr[l] cotains only 1s.
              bool covering = true;
              for( l = 0 ; l < 28 ; l++) covering &= arr[l];
              if ( covering ) {
                if( highest_level < 4) highest_level = 4;
                printf("Covers \n");
                return 1;
              }
              for( l = 0 ; l < 28 ; l++) arr[l] = arr_bk4[l];
            }
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
/*
    For this we try to store a matrix of 36 cols and K rows where
    K is the number of thrackles of size 8 for all OT
*/
void free98(){
    int i;
    int **a;

    a = (int **)mat98;
    for ( i=0; i<rows98; i++ ) free( a[i] );
    free ( a );
    printf("Matrix 98 deleted!\n");

}
void store98(){
    string file_name = "ths/9_8_All_bool.ths";
    ifstream file_h;
    file_h.open(file_name, ios::binary);
    int eater=0;
    int data = 0;
    int c = 0;
    int total_rows = 0;
    int total_rows_count = 0;
    int current_row = 0;
    int otypes = 158817;
    if (!file_h.good()) {
        fprintf(stderr, "Error opening file %s\n", file_name.c_str() );
        exit(-1);
    }
    for( int i = 0; i < otypes; i++){
        eater = 0;
        //Determine how many thrackles for ot=i.
        file_h.read( (char*)&eater,sizeof(uint16_t));
        eater = 0;
        file_h.read( (char*)&eater,sizeof(uint16_t));
        ot_thackles[i] = eater;
        total_rows_count += eater;
        for ( c = 0; c < eater; c++){
            data = 0;
            for ( int e = 0;  e < 36 ; e ++) file_h.read( (char*)&data,sizeof(char));
            total_rows++;
        }
    }
    printf("%d = %d\n",total_rows,total_rows_count );
    rows98 = total_rows;
    mat98 = (bool ** ) malloc( total_rows * sizeof(bool*));
    for(int i = 0; i < total_rows; i++) mat98[i] = (bool *)malloc(36 * sizeof(bool));
    file_h.seekg(0,file_h.beg);

    for( int i = 0; i < otypes; i++){
        eater = 0;
        //Determine how many thrackles for ot=i.
        file_h.read( (char*)&eater,sizeof(uint16_t));
        eater = 0;
        file_h.read( (char*)&eater,sizeof(uint16_t));
        //printf("For OT %d there are %d thrackles of size 8.\n",i,eater);
        total_rows_count += eater;
        for ( c = 0; c < eater; c++){
            data = 0;
            for ( int e = 0;  e < 36 ; e ++){
                file_h.read( (char*)&data,sizeof(char));
                mat98[current_row][e] = data;
            }
            current_row++;
        }
    }
    file_h.close();
    printf("Matrix succesfully created and filled!\n");
    // for( int i = 36; i < 36*2; i++){
    //     for (int j = 0; j < 36; j++){
    //         printf("%d ", mat98[i][j]);
    //     }
    //     printf("\n");
    // }
}
bool look888(int ot, int & highest_level){
  int current_ot =0;
  int eater = 0;
  int i,j,k;
  int nedges =36;
  int nt98;
  int starting_row = 0;
  bool avoid_flag,avoid_flag2;
  bool arr[36];
  bool arr_bk1[36],arr_bk2[36],arr_bk3[36];
  nt98 = ot_thackles[ot];
  while(current_ot != ot) {
      //printf("For OT %d there are %d thrackles.\n", current_ot, ot_thackles[current_ot]);
      starting_row += ot_thackles[current_ot];
      current_ot++;
  }
  printf("Thrackles of ot %d start at row %d\n",ot, starting_row );
  for ( i = 0; i < 36; i ++) arr[i] = false;

  for ( i = 0; i < 36; i++) arr_bk1[i] = arr[i];
  for( int l1 = 0; l1 < nt98; l1++ ){
      for ( i = 0; i < 36; i++) arr[i] |= mat98[starting_row+l1][i];
      for ( i = 0; i < 36; i++) arr_bk2[i] = arr[i];
      for ( int l2 = l1+1; l2 < nt98 ; l2 ++){
          for ( i = 0; i < 36; i++) {
              avoid_flag = false;
              if ( arr[i] && mat98[starting_row+l2][i] ) {
                  avoid_flag= true;
                  break;
              };
              arr[i] |= mat98[starting_row+l2][i];
          }
          if ( !avoid_flag ) {
              for ( i = 0; i < 36; i++) arr_bk3[i] = arr[i];
              for( int l3 = l2+1; l3 < nt98 ; l3 ++){
                  avoid_flag = false;
                  for ( i = 0; i < 36; i++){
                      if ( arr[i] && mat98[starting_row+l3][i]){
                          avoid_flag2 = true;
                          break; //avoid
                      }
                      arr[i] |= mat98[starting_row+l3][i];
                  }
                  if (!avoid_flag2 ){
                      printf("There are 3 thrackles of size 8 disjoint! %d %d %d\n",l1,l2,l3 );
                      return false;
                  }
                  for (i = 0; i < 36; i++) arr[i] = arr_bk3[i];
              }
          }
          for (i = 0; i < 36; i++) arr[i] = arr_bk2[i];
      }
      for (i = 0; i < 36; i++) arr[i] = arr_bk1[i];
  }
  return true;

}
/*
    This is for K9 decompositions of integer 36.
    9 + 8 + 8 + 8 + 3
    9 + 8 + 8 + 7 + 4
    9 + 8 + 8 + 6 + 5
    9 + 8 + 7 + 7 + 5
    9 + 8 + 7 + 6 + 6

    Returns false if there is a pair of thrackles of size
    9 and 8 and 8 such that their intersection is empty.
*/
bool look988(int ot, int & highest_level) {
    int current_ot =0;
    int eater = 0;
    int i,j,k;
    int nedges =36;
    int nt99, nt98;
    int c = 0;
    ifstream h99, h98;

    h99.open("ths/9_9_All_bool.ths",ios::binary);
    h98.open("ths/9_8_All_bool.ths",ios::binary);
    if ( !h99.good() || !h98.good()){
        fprintf(stderr, "Error opening thrackle file!\n");
        exit(-1);
    }
    while ( current_ot != ot ){
        h99.read ( (char* ) & eater, sizeof(uint16_t));
        h99.read ( (char* ) & eater, sizeof(uint16_t));
        c = eater;
        for ( i = 0; i < c ; i++ ) {
            for ( j = 0; j < nedges; j++){
                h99.read( (char*) &eater, sizeof(char));
            }
        }
        h98.read ( (char* ) & eater, sizeof(uint16_t));
        h98.read ( (char* ) & eater, sizeof(uint16_t));
        c = eater;
        for ( i = 0; i < c ; i++ ) {
            for ( j = 0; j < nedges; j++){
                h98.read( (char*) &eater, sizeof(char));
            }
        }
        current_ot++;
    }
    eater = 0;
    h99.read ( (char* ) & eater, sizeof(uint16_t));
    h99.read ( (char* ) & eater, sizeof(uint16_t));
    nt99 = eater;
    eater = 0;
    h98.read ( (char* ) & eater, sizeof(uint16_t));
    h98.read ( (char* ) & eater, sizeof(uint16_t));
    nt98 = eater;
    bool arr[36];
    bool arr_bk1[36];
    bool arr_bk2[36];
    bool arr_bk3[36];
    bool arr99[nt99][36];
    bool arr98[nt98][36];
    for ( i = 0; i < 28; i++) arr[i] = false;
    //Fill the matrices of thrackles.
    bool val;
    for (j = 0 ; j < nt99 ; j++ ) {
      for( i = 0 ; i < 36 ; i++){
        h99.read( (char*) & val, sizeof(char));
        arr99[j][i] = val;
      }
    }
    for (j = 0 ; j < nt98 ; j++ ) {
      for( i = 0 ; i < 36 ; i++){
        h98.read( (char*) & val, sizeof(char));
        arr98[j][i] = val;
      }
    }
    h99.close();
    h98.close();
    bool avoid_flag, avoid_flag2;

    //printf("Working with ot %d \n", ot);
    for( i = 0; i < 36; i++) arr_bk1[i] = arr[i];
    //Copy i-th thrackle of size 9.
    for ( int l1 = 0; l1 < nt99; l1++) {
        for( i = 0; i < 36; i++){
            arr[i] |= arr99[l1][i];
        }
        //Back up current arr.
        for( i = 0; i < 36; i++) arr_bk2[i] = arr[i];
        //Copy i-th thrackle of size 8.
        for( int l2 = 0; l2 < nt98; l2++){
            avoid_flag = false;
            for( i = 0; i < 36; i++) {
                if( arr[i] && arr98[l2][i]) avoid_flag = true;
                arr[i] |= arr98[l2][i];
            }
            if( !avoid_flag ){
                //Go down one level.
                //Back up current arr.
                for( i = 0; i < 36; i++) arr_bk3[i] = arr[i];
                //Copy i-th thrackle of size 8.
                for( int l3 = l2+1; l3 < nt98; l3++){
                    avoid_flag2 = false;
                    for( i = 0 ; i < 36; i++){
                        if ( arr[i] && arr98[l3][i] ) avoid_flag2 = true;
                        arr[i] |= arr98[l3][i];
                    }
                    if ( !avoid_flag2 ) {
                        printf("There is a triad of thrackles 9,8,8 disjoint %d %d %d\n",l1,l2,l3);
                        return false;
                    }
                    //Prepare arr for next iteration.
                    for( i = 0; i < 36; i++) arr[i] = arr_bk3[i];
                }
            }
            //Prepare arr for next iteration.
            for( i = 0; i < 36; i++) arr[i] = arr_bk2[i];
        }
        //Prepare arr for next iteration.
        for( i = 0; i < 36; i++) arr[i] = arr_bk1[i];
    }
    return true;
}
