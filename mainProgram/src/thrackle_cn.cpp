#include "../include/decomposition.h"

int get_bool_ot(bool E[], int n, int k, int th_number,int desired_ot);
int cn_th(bool E[], int n);

int main(int argc, char * argv[]){
    // if ( argc < 2 ){
    //     fprintf(stderr, "Error, usage %s ot <t_decomposition>\n", argv[0]);
    //     return 0;
    // }
    int n = 5;
    //bool E[n*(n-1)/2] = { 0,1,0,0,1,1,0,1,1,0};
    n = 9;
    bool X[n*(n-1)/2];
//    73  68  59  58  33  2 - ot 80
//   79  76  73  40  22  2 - 696
//  37  33  32  29  15  2 - ot 1080
//  57  55  44  35  24  3 - ot 1287
//  101  96  93  68  33  2  - ot 12
//  100  97  96  92  33  2  - ot 52

    get_bool_ot(X,n,n,100,52);
    for ( int i = 0; i < n*(n-1)/2 ; i++){
        printf("%d ",X[i]);
    }
    printf("\n");
    cn_th(X,n);
    return 0;
}
/*
    Searches the binary file for the set size n of thrackles of size k for
    the thrackle number th_number, stores its bool data into E.
*/
int get_bool_ot(bool E[], int n, int k, int th_number,int desired_ot){
    ifstream myfile;
    int i,j,c,thrackleCounter;
    int eater = 0;
    int cols = n*(n-1)/2;
    int current_ot = 0;
    string file_n = "ths/" + to_string(n)+"_"+to_string(k)+"_All_bool.ths";
    myfile.open(file_n,ios::binary);
    if (myfile.bad()){
        fprintf(stderr, "Error opening file %s \n", file_n.c_str() );
        exit(-1);
    }
    while(current_ot != desired_ot){
      //cout << current_ot << endl;
      myfile.read( (char*)&eater,sizeof(uint16_t));//ot
      myfile.read( (char*)&eater,sizeof(uint16_t)); //number_of_t
      c = eater;
      for(i = 0; i < c; i++){
        for ( j = 0 ; j < cols ; j++){
          myfile.read( (char*)&eater,sizeof(char)); //boolean
        }
        // list of thrackles.
      }
      current_ot++;
    }
    //When we get out of this while, we're in position to read
    //the information that we actually care about.
    eater = 0;
    myfile.read( (char*)&eater,sizeof(uint16_t));//ot
    myfile.read( (char*)&eater,sizeof(uint16_t)); //number_of_t
    c = eater;
    thrackleCounter = c;
    //Go to the desired thrackle.
    for(i = 0; i < th_number; i++){
      for ( j = 0 ; j < cols ; j++){
        myfile.read( (char*)&eater,sizeof(char));
      }
    }
    eater = 0;
    for ( j = 0 ; j < cols ; j++){
      myfile.read( (char*)&eater,sizeof(char));
      E[j] = eater;
    }
    myfile.close();
    return 1;
}
/*
Calculate the crossing number of a thrackle.
E - Boolean array of edges in the thrackle. It must be of size binom(n,2).
n - The size of the point set.

It assumes that the Edges were formed in the following order.
E[0] = (0,1) {vertices 0 and 1}.
E[1] = (0,2) ... and so on.
E[2] = (0,3)
*/
int cn_th(bool E[], int n){
    int i,j,c;
    int degs[n];
    int th_size = 0;
    int ans,sum;
    for( i = 0; i < n*(n-1)/2 ; i++){
        if(E[i]) th_size++;
    }
    for( i = 0; i < n ; i++){
        degs[i] = 0;
    }
    c = 0;
    for ( i = 0; i < n; i++){
        for ( j = i+1; j < n ; j++){
            if (E[c]) {
                degs[i]++;
                degs[j]++;
            }
            c++;
        }
    }
    printf("Degree array: ");
    for( i = 0 ; i<n;i++) printf("%d ",degs[i]);
    printf("\n");
    ans = th_size*(th_size-1)/2;

    sum = 0;
    for ( i = 0; i < n; i++){
        sum+= degs[i]*(degs[i]-1)/2;
    }
    printf("%d,%d,%d\n",th_size,ans,sum);
    printf("Crossing number of given thrackle : %d\n",ans-sum);
    return ans - sum;
}
