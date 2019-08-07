#include "../include/decomposition.h"
#include <random>
int main(int argc, char* argv[]){
    if( argc < 4 ) {
        fprintf(stderr, "Usage %s n random_ot_quantity banned_ot_file\n",argv[0] );
        exit(-1);
    }
    int otsize[8]={1,2,3,16,135,3315,158817,14309547};
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    string file_name(argv[3]);
    int max_range = otsize[n-3];
    //Read the file and save all its content on an array

    ifstream myfile;
    int ot = 0;
    int ln = 0;

    myfile.open(file_name);
    if (myfile.bad() or !myfile.good()){
        fprintf(stderr, "Error opening file %s\n", file_name.c_str());
        exit(-1);
    }
    while(myfile >> ot) ln++;
    myfile.close();
    int banned[ln];
    ln = 0;
    myfile.open(file_name);
    while(myfile >> ot) banned[ln++] = ot;
    sort(banned,banned+ln);
    std::default_random_engine generator(9); //9 is the seed,
    std::uniform_int_distribution<int> distribution(0,max_range);
    int p[k];
    //Generate k numbers in the range of 0 to max_range.
    //If the generated number is the same of an ot in the given file, ignore it.
    for (int i=0; i<k; ++i) {
        int number = distribution(generator);
        while(binary_search(banned,banned+ln,number) || number == 0) number = distribution(generator);
        p[i]= number;
    }
    for (int i = 0; i < k ; i++)
        printf("%d\n",p[i]);
    return 0;
}
