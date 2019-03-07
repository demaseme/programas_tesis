#include "../include/decomposition.h"

int main(int argc, char * argv[]){

    if (argc == 1 || argc > 3){
        fprintf(stderr, "Usage: %s <n>\n",argv[0] );
        exit(-1);
    }

    int size = atoi(argv[1]) + 1;
    int a[size];
    int max_size = atoi(argv[2]);
    //generate_integer_partitions( size,  a, print_integer_partition);
    generate_integer_partitions_constrained(size,max_size,max_val, a, print_integer_partition);
    return 1; 
}
