#include "../include/decomposition.h"
int cat(int n){
    return ( n - floor(sqrt(2*n + 1/4.0) - 1/2.0));
}
int main(int argc, char * argv[]){

    if (argc == 1 || argc > 2){
        fprintf(stderr, "Usage: %s <n>\n",argv[0] );
        exit(-1);
    }
    int n = atoi(argv[1]);
    int size = (n*(n-1)/2.0) + 1;
    int a[size];
    int max_size = cat(n)-1;
    int max_val = n;
    cout << size-1 << " " << max_size << " " << max_val << endl;
    //generate_integer_partitions( size,  a, print_integer_partition);
    generate_integer_partitions_constrained(size,max_size,max_val, a, print_integer_partition);
    return 1;
}
