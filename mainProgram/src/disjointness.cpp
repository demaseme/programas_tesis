#include "disjointness.h"

/*
    Fills the square matrix (matrix) with geometric information
    based on the disjointness of the graph.
*/
void construct_disjointness_matrix(const vector<Edge> edges,int ** matrix,const int rows){
    //This to write to matrix.
    int * ptr;

    for(int i = 0; i < rows; i++){
        ptr = (int * ) matrix[i];
        for(int j = 0; j < rows; j++){
            //Check if edges[i] and edges[j] are disjoint.
            //If they are, put a 1, otherwise put a 0.
            if(i==j) *ptr++ = 0;
            else if( crossing(edges[i],edges[j]) || share_ep(edges[i],edges[j]) ) *ptr++ = 0;
            else *ptr++=1;
        }
    }

    //This to print it.
    cout << "    ";
    for(int i = 0; i < rows;i++){
        if(i>=10) cout << i << "| ";
        else cout << i << " | ";
    }
    cout << endl << endl;
    for(int i = 0; i < rows; i++){
        ptr = (int * ) matrix[i];
        if(i>=10) cout << i << ": ";
        else cout << i << ":  ";
        for(int j = 0; j < rows; j++){
            cout << *ptr++ << " | ";
        }
        cout << "\n";
    }

}

/*
    Frees matrix matrix of size rows
    Matrix must be squared
*/
void freeMatrix(int ** matrix, const int rows){
    int i;
    int **a;

    a = (int **)matrix;
    for ( i=0; i<rows; i++ ) free( a[i] );
    free ( a );
    free ( matrix );
}

/*
    Visits thrackles of size given which contain the edge k at the start.
*/
void construct_thrackles_matrix(int ** matrix, const int cols, const int k, const int size) {
    int current_level;
    int desired_level;
    int levels[size];
    int level_deepness[size-1];
    int max_minLevel;
    int * ptr;
    for(int i = 0; i < size ; i++){
        levels[i] = -1; //Initialize levels with invalid values.
    }
    //We must initialize levels. First element of levels is of course k.
    //Second element of levels is the first column index which has a 0 on row k in matrix.
    //This index must be different than k, indeed it must be higher.
    levels[0] = k;

    ptr = (int *) matrix[k];
    for(int i = k+1; i < cols; i++){
        if(*ptr++ == 0){
            levels[1] = i;
            break;
        }
    }
    cout << "Levels:\n";
    for( int i = 0 ; i < size ; i++){
        cout << levels[i] << " ";
    }
    cout << endl;
    //To update max_minLevel we must find the last position where there was a 0 on row k.
    ptr = (int * ) matrix[k];
    ptr = ptr + (k+1);
    max_minLevel = 0;
    for(int i = k+1; i < cols ; i++){
        if(*ptr++ == 0 ) max_minLevel=i;
    }
    cout << "Max_minLevel: " << max_minLevel << endl;
    matrix[0][0] = 999;

    //Core of the algorithm:
    // while(desired_level > (current_level+1)){
    //      clae = bringEdges(levels[current_level]);
    //      if (clae [ level_deepness[current_level-1]] <= max_minLevel){
    //          levels[++current_level] = clae [level_deepness [current_level-1]];
    //      } else {
    //          level_deepness [ current_level ] = 0;
    //          current_level--;
    //          level_deepness[current_level-1]++;
    //      }
    //  }
     //visit levels.
     // level_deepness[current_level] = 0;
     // current_level--;
     // level_deepness[current_level-1]++;
    //}

}
