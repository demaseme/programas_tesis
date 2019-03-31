#include "../include/disjointness.h"

/*
    Opens file of set size n, 2-sets, thrackles of size m.
*/
void read_results(int n, int k, int m);
int main(int argc, char* argv[]){
    if(argc <= 1 || argc > 4) {
        fprintf(stderr,"Usage : %s n k t_size\n",argv[0]);
        return 0;
    }
    read_results(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]));
    return 1;
}

void read_results(int set_size, int k, int t_size){
    string file_name = to_string(set_size)+"_"+to_string(k)+"_"+to_string(t_size)+"_intersections_all.dat";
    ifstream file_h;
    file_h.open(file_name,ios::binary | ios::ate);
    /*The correct way to know the size of a binary file*/
    file_h.ignore( std::numeric_limits<std::streamsize>::max() );
    std::streamsize length = file_h.gcount();
    file_h.clear();   //  Since ignore will have set eof.
    file_h.seekg( 0, std::ios_base::beg );
    if (file_h.bad()){
        fprintf(stderr, "Error opening file %s\n", file_name.c_str() );
        exit(-1);
    }
    int q = k;
    int counter =0;
    int c[q+3];
    int c_curr[q];
    int eater = 0;
    int j;
    int n = length;
    c[0] = 9999;
    for(int i=1; i < q+1; i++){
        c[i] = i-1;
    }
    c[q+1] = n;
    c[q+2] = 0;

    while (true) {
      //L2. Visit.
      //For each generated, check if it's a decomposition.
      counter++;
      printf("[");
      for(int i = q; i > 0; i--){
        c_curr[i-1] = c[i];
        printf("%d ",c_curr[i-1]);
      }
      printf("] ");
      file_h.read( (char*) &eater,sizeof(char));
      printf("%d\n",eater);
      //L3. FIND j
      j = 1;
      while( (c[j] + 1) == c[j+1] ) {
          c[j] = j - 1;
          j = j + 1;
      }
      //L4. Termination condition met?
      if (j > q) {
          break;
      }
      //L5. Update and Return to L2.
      c[j] = c[j] + 1;
    }
}
/*
void read_results(string file_name){
    ifstream myfile;
    int size;
    myfile.open(file_name, ios::binary|ios::ate);
    if(myfile.fail()) {
        fprintf(stderr,"Error opening file \n");
        return;
    }
    size = myfile.tellg();
    //printf("Bytes: %d\n",size);
    myfile.seekg(0,ios::beg);
    if( myfile.bad() ){
      fprintf(stderr, "Error processing file %s\n", file_name.c_str());
      exit(-1);
    }
    int ot,i;
    int number_of_diff_subsets,subset_size,total_cov,total_rep,max_cov;
    number_of_diff_subsets=0;
    subset_size = 0;
    total_cov = 0;
    total_rep= 0;
    max_cov = 0;

    int total_avg_cov = 0;
    int total_avg_rep = 0;
    int total_avg_max_cov = 0;
    int counter = 0;
    ot = 0;

    while(size>0){
        if(!myfile) break;
        myfile.read( (char*) &ot,sizeof(char));
        myfile.read( (char*) &number_of_diff_subsets, sizeof(char));
        size = size - 2*sizeof(char);
        printf("ORDER TYPE %d -- Number of different subsets %d\n",ot,number_of_diff_subsets);
        for(i = 0; i < number_of_diff_subsets; i++){
            myfile.read( (char*) &subset_size, sizeof(char));
            myfile.read( (char*) &total_cov, sizeof(char));
            myfile.read( (char*) &total_rep, sizeof(char));
            myfile.read( (char*) &max_cov, sizeof(char));
            counter ++;
            total_avg_cov += total_cov;
            total_avg_rep += total_rep;
            total_avg_max_cov += max_cov;
            size=size - (4*sizeof(char));
            printf("\t[subsets of size %d]\n\t" "Average covered :%d Average Repeated :%d Maximal covered: %d\n",
            subset_size,total_cov,total_rep,max_cov);
        }
        //printf("%d bytes left\n",size);
    }
    printf("From this file: TOTALS(AVG):\n Average Covered: %d\tAverage Repeated: %d\t Average Maximum Covered: %d\n",total_avg_cov/counter,
    total_avg_rep/counter, total_avg_max_cov/counter);
    myfile.close();
}
*/
