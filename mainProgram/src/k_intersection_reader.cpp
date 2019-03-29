#include "../include/disjointness.h"
#include "../include/globals.h"
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include <cmath>
#include <cstring>

int g_q;
int opt;
int ot_number = 0; // starting from 0.
//bool draw_flag;
bool one_ot_flag= false;
Point *vPoints;
int k;  //Thrackle size we're looking for
int otypes; //Number of order types for a file
int npuntos;
string otfile_str;
vector<int> otlist;
int ** matrix; //matrix to store the disjointness matrix.
int thrackleCounter;
vector<Point> vec; //Here we store the points that will be read.
vector<Edge> edges; //Here we store the (n take 2) edges of the complete graph
vector<Thrackle> foundThrackles; //Here we store the thrackles of size k.
vector<vector<int>> positions; // Each element of this vector, is a list of positions of edges which together are a thrackle.

void read_results(string file_name);
int main(int argc, char* argv[]){
    if(argc <= 1 || argc > 2) {
        fprintf(stderr,"Usage : %s <file_name.dat>\n",argv[0]);
        return 0;
    }
    read_results(argv[1]);
    return 1;
}

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
