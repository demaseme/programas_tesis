#include "../include/disjointness.h"

int print_bin_file(string file_name, int );

int main(int argc, char* argv[]) {
    if ( argc <= 1 ) {
        fprintf(stderr,"Usage %s <intersection-file.ths>\n",argv[0]);
        exit(-1);
    }
    int delta = atoi(argv[2]);
    print_bin_file(argv[1], delta);
}

int print_bin_file(string filename, int delta){
    uint16_t x,y,a,b;
    int i,j;
    uint16_t size;
    uint16_t number_of_thrackles;
    uint16_t t_size;
    ifstream myfile;

    myfile.open(filename, ios::in|ios::binary|ios::ate);
    if(myfile.fail()) return 0;
    size = myfile.tellg();
    myfile.seekg(0,ios::beg);

    //First line is number of thrackles.
    myfile.read((char*) & number_of_thrackles, sizeof(uint16_t));
    //Secondly is the size of every thrackle.
    myfile.read((char*) & t_size, sizeof(uint16_t));
    //Then I know that I'll have to read t_size*4*number_of_thrackles
    printf("There are %d thrackles of size %d \n",number_of_thrackles,t_size);
    for(i = 0; i < number_of_thrackles; i++){
        printf("%d: <",i);
        for( j = 0; j < t_size; j++){
            myfile.read((char*) & x, sizeof(uint16_t));
            myfile.read((char*) & y, sizeof(uint16_t));
            myfile.read((char*) & a, sizeof(uint16_t));
            myfile.read((char*) & b, sizeof(uint16_t));
            printf(" (%d,%d %d,%d) ",x,y,a,b);
        }
        printf(">\n");
    }
    printf("Printing intersection data:\n");
    for(i =0 ; i < number_of_thrackles; i++){
        for(j= i+1; j < number_of_thrackles;j++){
            myfile.read((char*) & size, sizeof(uint16_t));
            if( size > delta) continue;
            if((i < 10) & (j < 10)) printf("%d  %d : %d\n",i,j,size);
            else if((i < 10) & (j > 10)) printf("%d %d: %d\n",i,j,size);
            else if((i > 10) & (j < 10)) printf("%d %d: %d\n",i,j,size);
            else if((i > 10) & (j > 10)) printf("%d %d: %d\n",i,j,size);
            else printf("%d %d : %d\n",i,j,size);
        }
    }
    myfile.close();
    return 1;
}
