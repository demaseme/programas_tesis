#include<iostream>
#include<vector>
#include <ctime>
#include <ratio>
#include <chrono>
#include <unistd.h>
/*
Based off Art of computer programming - Volume 4a Fascicle 2 Generating all combinations
Algorithm T (Lexicographic combinations).
*/
//Visits all t-combinations of set {0,1,2...n-1}
void combinations(int n, int t){
  //T1. Initialize c_j = j-1 for j in [1,t]
  std::vector<int> c;
  int j,x;
  for(j = 0; j < t; j++){
    c.push_back(j);
  }
  //then set c_{t+1} = n and c{t+2} = 0 and j = t;
  c.push_back(n);
  c.push_back(0);
  j = t;
  while(true){
    //Steps T2 through T6 execute until termination condition is met. (T5)

    while(true) {
      //T2. Visit combination c_tc_{t-1}...c_0.
      std::cout << "Starting T2. j="<<j<<std::endl;
      for(auto i = c.begin(); i != c.end() - 2; i++){
        std::cout << *i << " ";
      }
      std::cout << std::endl;
      //Then, if j>0, set x = j and goto step T6.
      if( (j) > 0) {
        x = j+1;
        std::cout << "Starting T6. j="<<j<<std::endl;
        //T6.   c_j = x, j = j -1 return to T2.
        c[j] = x;
        j = j - 1;
      } else {
        //T3. If c_1 + 1 < c_2 set c_1 = c_1 + 1 and return to T2. Else set j=2.
        std::cout << "Starting T3. j="<<j<<std::endl;
        if( (c[0] + 1) < c[1] ){
          c[0] = c[0] + 1;
        } else {
          j = 1;
          break; //Goto step T4.
        }
      }
    }
    //T4. Set c_{j-1} = j-1 and x = c_j + 1. If x = c_{j+1}, set j = j+1 and repeat until x < c_{j+1}
    std::cout << "Starting T4. j="<<j<<std::endl;
    do{
      c[j-1] = j - 1;
      x = c[j-1] + 1;
      if( x == c[j] - 1 ){
        j = j + 1;
      } else{
        break;
      }
    } while( x >= c[j] );
    //T5.
    std::cout << "Starting T5. j="<<j<<std::endl;
    if( (j) > t - 1 ) break;
  }
}

void badcombinations(int n, int t){
  std::vector<int> c;
  int j,x;
  c.push_back(-9999);
  for(j = 0; j < t; j++){
    c.push_back(j);
  }
  //then set c_{t+1} = n and c{t+2} = 0 and j = t;
  c.push_back(n);
  c.push_back(0);
  j = t;

  t2:
    for(int i = t; i > 0; i--){
      std::cout << c[i] << " ";
    }
    std::cout << std::endl;
    if (j > 0){
      x = j ;
      goto t6;
    }
  t3:
    if( (c[1] + 1) < c[2]){
      c[1] = c[1] + 1;
      goto t2;
    } else{
      j = 2;
    }
  t4:
      c[j-1] = j-1;
      x = c[j] + 1;
      if( (c[j + 1] ) == x){
        j = j + 1;
        if(x >= c[j+1]) goto t4;
      }
  t5:
    if ( j > t ) return ;
  t6:
    c[j] = x;
    j = j - 1;
    goto t2;
}

//works.
void badcombinations2(int n, int t){
  std::vector<int> c;
  int j,x;
  long res = 0;
  c.push_back(-9999);
  for(j = 0; j < t; j++){
    c.push_back(j);
  }
  //then set c_{t+1} = n and c{t+2} = 0 and j = t;
  c.push_back(n);
  c.push_back(0);
  j = t;
  l2:
    res ++;
    // for(int i = t; i > 0; i--){
    //   std::cout << c[i] << " ";
    // }
    // std::cout << std::endl;
  l3:
    j = 1;
    while((c[j] + 1) == c[j+1]){
      c[j]= j - 1;
      j = j + 1;
    }
  l4:
    if(j>t) {
      std::cout << res << std::endl;
      return ;

    }
  l5:
    c[j] = c[j] + 1;
    goto l2;
}

int main(int argc,char * argv[]){
  if(argc == 1){
    fprintf(stderr,"Usage: %s n t \n",argv[0]);
    exit(-1);
  }
  int n,t;
  n = atoi(argv[1]);
  t = atoi(argv[2]);
//  badcombinations(n,t);
  std::cout << " ====================== \n";
  std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  badcombinations2(n,t);
  std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> time_span = t2 - t1;
  std::cout << "It took me " << time_span.count() << " milliseconds.";
  std::cout << std::endl;
  return 0;
}
