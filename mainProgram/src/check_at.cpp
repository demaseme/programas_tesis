#include "../include/decomposition.h"

int ** bool_th_mat ;

int main(int argc, char * argv[]){
    int opt;
    int ot;
    int one_ot_flag = false;
    int otypes,rows,cols,n,t;
    ot = 0;
    while ((opt = getopt(argc,argv, "t:")) != -1 ){
        switch(opt){
            case 't':
                ot = atoi(optarg);
                one_ot_flag = true;
                break;
            default:
                fprintf(stderr, "Usage %s <number of points> [-t order-type]\n",argv[0] );
                exit(EXIT_FAILURE);
        }
    }
    if (optind+1 >= argc) {
        fprintf(stderr, "Expected argument after options\n");
        exit(EXIT_FAILURE);
    }
    // if (argc <= 2 || argc > 3){
    //     fprintf(stderr, "Usage %s <number of points> <order_type> <anti-thickness check> ", argv[0]);
    //     return -1;
    // }
    n = atoi(argv[optind]);
    optind++;
    t = atoi(argv[optind]);
    cols = n*(n-1)/2.0;


    switch(n){
    case 3:
        otypes = 1; break;
    case 4:
        otypes = 2; break;
    case 5:
        otypes = 3; break;
    case 6:
        otypes = 16; break;
    case 7:
        otypes = 135; break;
    case 8:
        otypes = 3315; break;
    case 9:
        otypes = 158817; break;
    case 10:
        otypes = 14309547; break;
    default:
        fprintf(stderr,"No existe base de datos para n>10\n"); exit(-1);
    }


    int **a;
    int nexperiments = n - floor(sqrt(2*n + 0.25) - 0.5) - 2;
    int bounded_ats[nexperiments];

    for(auto i = 0; i < otypes; i++) {
        bounded_ats[i] = 9999;
    }
    while( ot < otypes){
        cout << "Working with ot " << ot << endl;
        rows = count_thrackles(n,n,ot);
        //int check[4] = {25,21,10,0};
        cout << "Cols :" << cols << endl;
        cout << "Rows :" << rows << endl;

        //Populate the matrix.
        bool_th_mat = (int **)malloc(rows * sizeof(int*));
        for(int i = 0; i < rows; i++) bool_th_mat[i] = (int *)malloc(cols * sizeof(int));

        load_thrackles(n,n,ot,bool_th_mat);
        if (!rows || rows < t) {
            if (one_ot_flag) break;
            ot++;
            continue;
        }
        //printMatrix(bool_th_mat,rows,cols);
        if( is_atk_upper(rows, n, ot, t, bool_th_mat) ) {
            printf("K_%d order type %d has anti-thickness at most: %d\n",n,ot,t);
            bounded_ats[ot] = t;
        }
        //Free matrix rows.
        a = (int **)bool_th_mat;
        for(int i = 0; i < rows; i++) free(a[i]);
        cout << "Rows freed\n";
        if (one_ot_flag) break;
        ot++;
    }
  free(a);

  return 1;
}
