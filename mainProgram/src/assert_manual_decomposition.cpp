#include "../include/decomposition.h"

/*This one is for K8*/
bool look8876(int, int &);
/*
  This is all for K9.
*/
bool look9876(int ot, int & highest_level);
bool look988(int ot, int & highest_level);
bool look988_2(int ot, int & highest_level);
bool look888(int ot, int & highest_level);
bool look777(int ot, int & highest_level);
bool look8877(int ot, int & highest_level);
void store96();
void store97();
void store98();
void store99();
void free96();
void free97();
void free98();
void free99();
bool ** mat98, ** mat99, ** mat97, **mat96;
int rows98,rows99,rows97,rows96;
int ot_thrackles[158817];//98
int ot_thrackles99[158817];
int ot_thrackles97[158817];
int ot_thrackles96[158817];
int main(){
  int ot = 0; // 3315
  int level = 0;
  int highest = 0;

  // omp_set_num_threads(2);
  // if (!omp_get_cancellation()) {
  //   printf("Cancellation variable not correctly set!\n");
  //   exit(-1);
  // }
  //store96();
  //store97();
  store98();
  store99();
  std::chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

  // #pragma omp parallel
  // {
  //   #pragma omp for
  //   for(ot = 1; ot < 158817; ot++) if( !look777(ot,highest) ) {
  //       #pragma omp cancel for
  //   };
  // }
  for(ot = 1; ot < 158817; ot++) {
      if( !look988_2(ot,highest) ) return 0;
  }
  std::chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
  chrono::duration<double, std::milli> time_span = t2 - t1;
  cout << "It took me " << time_span.count() << " milliseconds.";
   free98();
   free99();
   //free97();
  //free96();
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
  int i,j,k,l,c;
  int nedges = 28;
  int nt88,nt87,nt86;

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
  // nt87_2 = eater;
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

void free97(){
    int i;
    int **a;

    a = (int **)mat97;
    for ( i=0; i<rows97; i++ ) free( a[i] );
    free ( a );
    printf("Matrix 97 deleted!\n");

}
void free98(){
    int i;
    int **a;

    a = (int **)mat98;
    for ( i=0; i<rows98; i++ ) free( a[i] );
    free ( a );
    printf("Matrix 98 deleted!\n");

}
void free99(){
    int i;
    int **a;

    a = (int **)mat99;
    for ( i=0; i<rows99; i++ ) free( a[i] );
    free ( a );
    printf("Matrix 99 deleted!\n");

}
void free96(){
  int i;
  int **a;

  a = (int **)mat96;
  for ( i=0; i<rows96; i++ ) free( a[i] );
  free ( a );
  printf("Matrix 96 deleted!\n");

}
/*
    Reads the file of thrackles of size 7 for K_9.
    Loads its info into a big matrix called mat97.
*/
void store97(){
    string file_name = "ths/9_7_All_bool.ths";
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
        ot_thrackles97[i] = eater;
        total_rows_count += eater;
        for ( c = 0; c < eater; c++){
            data = 0;
            for ( int e = 0;  e < 36 ; e ++) file_h.read( (char*)&data,sizeof(char));
            total_rows++;
        }
    }
    file_h.close();
    file_h.open(file_name,ios::binary);
    printf("%d = %d\n",total_rows,total_rows_count );
    rows97 = total_rows;
    mat97 = (bool ** ) malloc( total_rows * sizeof(bool*));
    for(int i = 0; i < total_rows; i++) mat97[i] = (bool *)malloc(36 * sizeof(bool));
    file_h.seekg(0,file_h.beg);
    if (!file_h.good()) {
        printf("Error processing file %s\n",file_name.c_str());
        exit(-2);
    }
    for( int i = 0; i < otypes; i++){
        eater = 0;
        //Determine how many thrackles for ot=i.
        file_h.read( (char*)&eater,sizeof(uint16_t));
        eater = 0;
        file_h.read( (char*)&eater,sizeof(uint16_t));
        //printf("For OT %d there are %d thrackles of size 8.\n",i,eater);
        total_rows_count += eater;
        for ( c = 0; c < eater; c++){

            for ( int e = 0;  e < 36 ; e ++){
                file_h.read( (char*)&data,sizeof(char));
                mat97[current_row][e] = data;
            }
            current_row++;
        }
    }
    file_h.close();
    printf("Matrix 97 succesfully created and filled!\n");
    // for( int i = 0; i < 36; i++){
    //     for (int j = 0; j < 36; j++){
    //         printf("%d ", mat97[i][j]);
    //     }
    //     printf("\n");
    // }
}
/*
    Reads the file of thrackles of size 9 for K_9.
    Loads its info into a big matrix called mat99.
*/
void store99(){
    string file_name = "ths/9_9_All_bool.ths";
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
        ot_thrackles99[i] = eater;
        total_rows_count += eater;
        for ( c = 0; c < eater; c++){
            data = 0;
            for ( int e = 0;  e < 36 ; e ++) file_h.read( (char*)&data,sizeof(char));
            total_rows++;
        }
    }
    printf("%d = %d\n",total_rows,total_rows_count );
    rows99 = total_rows;
    mat99 = (bool ** ) malloc( total_rows * sizeof(bool*));
    for(int i = 0; i < total_rows; i++) mat99[i] = (bool *)malloc(36 * sizeof(bool));
    file_h.close();
    file_h.open(file_name,ios::binary);
    if (!file_h.good()) {
        fprintf(stderr, "Error processing file %s\n",file_name.c_str() );
        exit(-2);
    }
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
                mat99[current_row][e] = data;
            }
            current_row++;
        }
    }
    file_h.close();
    printf("Matrix 99 succesfully created and filled!\n");
}
/*
    Reads the file of thrackles of size 8 for K_9.
    Loads its info into a big matrix called mat98.
*/
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
        ot_thrackles[i] = eater;
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
    file_h.close();
    file_h.open(file_name,ios::binary);
    if (!file_h.good()){
        fprintf(stderr, "Error processing file %s\n", file_name.c_str() );
        exit(-2);
    }
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
    printf("Matrix 98 succesfully created and filled!\n");
    // for( int i = 36; i < 36*2; i++){
    //     for (int j = 0; j < 36; j++){
    //         printf("%d ", mat98[i][j]);
    //     }
    //     printf("\n");
    // }
}

/*
    Reads the file of thrackles of size 6 for K_9.
    Loads its info into a big matrix called mat96.
*/
void store96(){
  string file_name = "ths/9_6_All_bool.ths";
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
      ot_thrackles96[i] = eater;
      total_rows_count += eater;
      for ( c = 0; c < eater; c++){
          data = 0;
          for ( int e = 0;  e < 36 ; e ++) file_h.read( (char*)&data,sizeof(char));
          total_rows++;
      }
  }
  file_h.close();
  file_h.open(file_name,ios::binary);
  printf("%d = %d\n",total_rows,total_rows_count );
  rows96 = total_rows;
  mat96 = (bool ** ) malloc( total_rows * sizeof(bool*));
  for(int i = 0; i < total_rows; i++) mat96[i] = (bool *)malloc(36 * sizeof(bool));
  file_h.seekg(0,file_h.beg);
  if (!file_h.good()) {
      printf("Error processing file %s\n",file_name.c_str());
      exit(-2);
  }
  for( int i = 0; i < otypes; i++){
      eater = 0;
      //Determine how many thrackles for ot=i.
      file_h.read( (char*)&eater,sizeof(uint16_t));
      eater = 0;
      file_h.read( (char*)&eater,sizeof(uint16_t));
      //printf("For OT %d there are %d thrackles of size 8.\n",i,eater);
      total_rows_count += eater;
      for ( c = 0; c < eater; c++){

          for ( int e = 0;  e < 36 ; e ++){
              file_h.read( (char*)&data,sizeof(char));
              mat96[current_row][e] = data;
          }
          current_row++;
      }
  }
  file_h.close();
  printf("Matrix 96 succesfully created and filled!\n");
}
/*
    Already tested for K9.
    There are 3 thrackles of size 8 disjoint! 13 1102 1402
*/
bool look888(int ot, int & highest_level){
  int current_ot =0;
  int i;
  int nt98;
  int starting_row = 0;
  bool avoid_flag,avoid_flag2;
  bool arr[36];
  bool arr_bk1[36],arr_bk2[36],arr_bk3[36];
  nt98 = ot_thrackles[ot];
  while(current_ot != ot) {
      //printf("For OT %d there are %d thrackles.\n", current_ot, ot_thrackles[current_ot]);
      starting_row += ot_thrackles[current_ot];
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
                  avoid_flag2 = false;
                  for ( i = 0; i < 36; i++){
                      if ( arr[i] && mat98[starting_row+l3][i]){
                          avoid_flag2 = true;
                          break; //avoid
                      }
                      arr[i] |= mat98[starting_row+l3][i];
                  }
                  if (!avoid_flag2 ){
                      printf("There are 3 thrackles of size 8 disjoint! %d %d %d\n",l1,l2,l3 );
                      int onecount=0;
                      for( int jk = 0; jk < 36; jk++) {
                          if ( arr[jk] ) onecount++;
                      }
                      printf("%d=%d\n",onecount,3*8);
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
    Already tested for K9.
    There are 3 thrackles of size 7 disjoint! 0 3658 3666
*/
bool look777(int ot, int & highest_level){
    int current_ot =0;
    int i,j;
    int nt97;
    int starting_row = 0;
    bool avoid_flag,avoid_flag2;
    bool arr[36];
    bool arr_bk1[36],arr_bk2[36],arr_bk3[36];
    nt97 = ot_thrackles97[ot];
    printf("For OT %d there are %d thrackles.\n", ot, nt97);

    while(current_ot != ot) {
        printf(">>Looking<< For OT %d there are %d thrackles.\n", current_ot, ot_thrackles97[current_ot]);
        starting_row += ot_thrackles97[current_ot];
        current_ot++;
    }
    printf("Thrackles of ot %d start at row %d\n",ot, starting_row );
    for ( i = 0; i < 36; i++) arr[i] = false;
    for ( i = 0; i < 36; i++) arr_bk1[i] = arr[i];
    for( int l1 = 0; l1 < nt97; l1++ ){
        for ( i = 0; i < 36; i++) arr[i] |= mat97[starting_row+l1][i];
        for ( i = 0; i < 36; i++) arr_bk2[i] = arr[i];
        for ( int l2 = l1+1; l2 < nt97 ; l2 ++){
            for ( i = 0; i < 36; i++) {
                avoid_flag = false;
                if ( arr[i] && mat97[starting_row+l2][i] ) {
                    avoid_flag= true;

                    break;
                }
                arr[i] |= mat97[starting_row+l2][i];
            }
            if ( !avoid_flag ) {
                for ( i = 0; i < 36; i++) arr_bk3[i] = arr[i];
                for( int l3 = l2+1; l3 < nt97 ; l3 ++){
                    avoid_flag2 = false;
                    for ( i = 0; i < 36; i++){
                        if ( arr[i] && mat97[starting_row+l3][i]){
                            avoid_flag2 = true;
                            break; //avoid
                        }
                        arr[i] |= mat97[starting_row+l3][i];
                    }
                    if (!avoid_flag2 ){
                        printf("There are 3 thrackles of size 7 disjoint! %d %d %d\n",l1,l2,l3 );
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
    Already tested for K9.
    Therea re no thrackles of size 9,8,8 disjoint.
*/
bool look988_2(int ot, int & highest_level){
    int current_ot =0;

    int i;

    int nt98,nt99;
    int starting_row98 = 0;
    int starting_row99 = 0;
    bool avoid_flag,avoid_flag2;
    bool arr[36];
    bool arr_bk1[36],arr_bk2[36],arr_bk3[36];
    nt99 = ot_thrackles99[ot];
    nt98 = ot_thrackles[ot];
    while(current_ot != ot) {
        //printf("For OT %d there are %d thrackles.\n", current_ot, ot_thrackles[current_ot]);
        starting_row99 += ot_thrackles99[current_ot];
        starting_row98 += ot_thrackles[current_ot];
        current_ot++;
    }
    printf("Thrackles of ot %d start at row %d\n",ot, starting_row99 );
    for ( i = 0; i < 36; i ++) arr[i] = false;

    for ( i = 0; i < 36; i++) arr_bk1[i] = arr[i];
    for( int l1 = 0; l1 < nt99; l1++ ){
        for ( i = 0; i < 36; i++) arr[i] |= mat99[starting_row99+l1][i];
        for ( i = 0; i < 36; i++) arr_bk2[i] = arr[i];
        for ( int l2 = 0; l2 < nt98 ; l2 ++){
            for ( i = 0; i < 36; i++) {
                avoid_flag = false;
                if ( arr[i] && mat98[starting_row98+l2][i] ) {
                    avoid_flag= true;
                    break;
                };
                arr[i] |= mat98[starting_row98+l2][i];
            }
            if ( !avoid_flag ){
                for ( i = 0; i < 36; i++) arr_bk3[i] = arr[i];
                for( int l3 = l2+1; l3 < nt98 ; l3 ++){
                    avoid_flag2 = false;
                    for ( i = 0; i < 36; i++){
                        if ( arr[i] && mat98[starting_row98+l3][i]){
                            avoid_flag2 = true;
                            break; //avoid
                        }
                        arr[i] |= mat98[starting_row98+l3][i];
                    }
                    if (!avoid_flag2 ){
                        printf("There are thrackles of size 9,8,8 disjoint! %d %d %d\n",l1,l2,l3 );
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

bool look8877(int ot, int & highest_level){
    int current_ot =0;
    int i,j;
    int nt97,nt98;
    int starting_row = 0;
    int starting_row98=0;
    bool avoid_flag,avoid_flag2,avoid_flag3;
    bool arr[36];
    bool arr_bk1[36],arr_bk2[36],arr_bk3[36], arr_bk4[36];
    nt97 = ot_thrackles97[ot];
    nt98 = ot_thrackles[ot];
    printf("For OT %d there are %d thrackles.\n", ot, nt97);

    while(current_ot != ot) {
        printf(">>Looking<< For OT %d there are %d thrackles.\n", current_ot, ot_thrackles97[current_ot]);
        starting_row += ot_thrackles97[current_ot];
        starting_row98 += ot_thrackles[current_ot];
        current_ot++;
    }
    printf("Thrackles of ot %d start at row %d\n",ot, starting_row );
    for ( i = 0; i < 36; i++) arr[i] = false;
    for ( i = 0; i < 36; i++) arr_bk1[i] = arr[i];
    for( int l1 = 0; l1 < nt97; l1++ ){
        for ( i = 0; i < 36; i++) arr[i] |= mat97[starting_row+l1][i];
        for ( i = 0; i < 36; i++) arr_bk2[i] = arr[i];
        for ( int l2 = l1+1; l2 < nt97 ; l2 ++){
            for ( i = 0; i < 36; i++) {
                avoid_flag = false;
                if ( arr[i] && mat97[starting_row+l2][i] ) {
                    avoid_flag= true;

                    break;
                }
                arr[i] |= mat97[starting_row+l2][i];
            }
            if ( !avoid_flag ) {
                for ( i = 0; i < 36; i++) arr_bk3[i] = arr[i];
                for( int l3 = 0; l3 < nt98 ; l3 ++){
                    avoid_flag2 = false;
                    for ( i = 0; i < 36; i++){
                        if ( arr[i] && mat98[starting_row98+l3][i]){
                            avoid_flag2 = true;
                            break; //avoid
                        }
                        arr[i] |= mat98[starting_row98+l3][i];
                    }
                    if (!avoid_flag2 ){
                      for ( i = 0; i < 36; i++) arr_bk4[i] = arr[i];
                      for( int l4 = l3+1; l4 < nt98 ; l4 ++){
                        avoid_flag3 = false;
                        for ( i = 0; i < 36; i++){
                            if ( arr[i] && mat98[starting_row98+l4][i]){
                                avoid_flag3 = true;
                                break; //avoid
                            }
                            arr[i] |= mat98[starting_row98+l4][i];
                        }
                        if (!avoid_flag3){
                          printf("There is 8 8 7 7 disjoint. %d %d %d %d\n",l1,l2,l3,l4);
                          int onecount=0;
                          for(int q = 0; q < 36 ; q++){
                            if (arr[q]) onecount++;
                          }
                          printf("%d=%d\n",onecount,7*4);
                          return false;
                        }
                        for (i = 0; i < 36; i++) arr[i] = arr_bk4[i];
                      }
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

bool look9876(int ot, int & highest_level){
  int current_ot =0;
  int i;
  int nt98,nt99,nt97,nt96;
  int starting_row96 = 0;
  int starting_row97 = 0;
  int starting_row98 = 0;
  int starting_row99 = 0;
  bool avoid_flag,avoid_flag2,avoid_flag3;
  bool arr[36];
  bool arr_bk1[36],arr_bk2[36],arr_bk3[36],arr_bk4[36];
  nt99 = ot_thrackles99[ot];
  nt98 = ot_thrackles[ot];
  nt97 = ot_thrackles97[ot];
  nt96 = ot_thrackles96[ot];
  while(current_ot != ot) {
      //printf("For OT %d there are %d thrackles.\n", current_ot, ot_thrackles[current_ot]);
      starting_row99 += ot_thrackles99[current_ot];
      starting_row98 += ot_thrackles[current_ot];
      starting_row97 += ot_thrackles97[current_ot];
      starting_row96 += ot_thrackles96[current_ot];
      current_ot++;
  }
  for ( i = 0; i < 36; i ++) arr[i] = false;
  for ( i = 0; i < 36; i++) arr_bk1[i] = arr[i];
  for( int l1 = 0; l1 < nt99; l1++ ){
    for ( i = 0; i < 36; i++) arr[i] |= mat99[starting_row99+l1][i];
    for ( i = 0; i < 36; i++) arr_bk2[i] = arr[i];
    for ( int l2 = 0; l2 < nt98 ; l2 ++){
        for ( i = 0; i < 36; i++) {
            avoid_flag = false;
            if ( arr[i] && mat98[starting_row98+l2][i] ) {
                avoid_flag= true;
                break;
            }
            arr[i] |= mat98[starting_row98+l2][i];
        }
        if ( !avoid_flag ){
            for ( i = 0; i < 36; i++) arr_bk3[i] = arr[i];
            for( int l3 = 0; l3 < nt97 ; l3 ++){
                avoid_flag2 = false;
                for ( i = 0; i < 36; i++){
                    if ( arr[i] && mat97[starting_row97+l3][i]){
                        avoid_flag2 = true;
                        break; //avoid
                    }
                    arr[i] |= mat97[starting_row97+l3][i];
                }
                if (!avoid_flag2 ){
                    for ( i = 0; i < 36; i++) arr_bk4[i] = arr[i];
                    for( int l4 = 0; l4 < nt96 ; l4 ++){
                      avoid_flag3 = false;
                      for ( i = 0; i < 36; i++){
                          if ( arr[i] && mat96[starting_row96+l4][i]){
                              avoid_flag3 = true;
                              break; //avoid
                          }
                          arr[i] |= mat96[starting_row96+l4][i];
                      }
                      if (!avoid_flag3){
                        printf("There is a set of thrackles 9,8,7,6 disjoint. %d %d %d %d\n",l1,l2,l3,l4);
                        return false;
                      }
                      for (i = 0; i < 36; i++) arr[i] = arr_bk4[i];
                    }
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
bool look988(int ot, int & highest_level) {
    int current_ot =0;
    int eater = 0;
    int i,j;
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
