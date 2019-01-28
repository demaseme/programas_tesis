#include "disjointness.h"

/*
    Fills the square matrix (matrix) with geometric information
    based on the disjointness of the graph.
*/
void construct_disjointness_matrix(const vector<Edge> edges,int ** matrix,const int rows){
    //This to write to matrix.
    int * ptr;
    for(int i = 0; i < (int) edges.size() ; i ++){
      cout << "Edge " << i << ":";
      printEdge(edges[i]);
    }
    for(int i = 0; i < rows; i++){
        ptr = (int * ) matrix[i];
        for(int j = 0; j < rows; j++){
            //Check if edges[i] and edges[j] are disjoint.
            //If they are, put a 1, otherwise put a 0.
            //cout << "Checking edges : " << i << " and " << j << endl;

            if (i ==1 && j == 8){
              cout << "Checking 1 and 8\n";
            }
            if(i==j){
              *ptr++ = 0;
              continue;
            }else if( crossing(edges[i],edges[j]) || share_ep(edges[i],edges[j]) ){
              *ptr++ = 0;
              if (i ==1 && j == 8){
                cout << "1 and 8 cross or share an endpoint \n";
              }
              continue;
            }else *ptr++=1;
        }
    }

    // //This to print it.
    // cout << "    ";
    // for(int i = 0; i < rows;i++){
    //     if(i>=10) cout << i << "| ";
    //     else cout << i << " | ";
    // }
    // cout << endl << endl;
    // for(int i = 0; i < rows; i++){
    //     ptr = (int * ) matrix[i];
    //     if(i>=10) cout << i << ": ";
    //     else cout << i << ":  ";
    //     for(int j = 0; j < rows; j++){
    //         cout << *ptr++ << " | ";
    //     }
    //     cout << "\n";
    // }

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
    //free ( matrix );
}
/*
    Stores the 0-positions of given row on vector (compatible);
*/
void bringEdges(int ** matrix, const int cols, const int row, vector<int> & compatible){
  for(int i = row+1; i < cols ; i++ ){
    if( matrix[row][i] == 0 ) compatible.push_back(i);
  }
}
/*
    Visits thrackles of size given which contain the edge k at the start.
*/
void construct_thrackles_matrix(int ** matrix, const int cols, const int k, const int size,int & thr_count){
    int current_level;
    int desired_level;
    int levels[size];
    int level_deepness[size-1];
    int max_minLevel;
    int * ptr;
    int tmp;
    bool flag = true;
    int last_added;
    vector<int> clae;
    for(int i = 0; i < size ; i++){
        levels[i] = -1; //Initialize levels with invalid values.
    }
    //initialize level_deepness:
    for(int i = 0; i < (size-1); i++){
      level_deepness[i] = 0;
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
    // cout << "Levels:\n";
    // for( int i = 0 ; i < size ; i++){
    //     cout << levels[i] << " ";
    // }
    // cout << endl;
    //To update max_minLevel we must find the last position where there was a 0 on row k.
    ptr = (int * ) matrix[k];
    ptr = ptr + (k+1);
    max_minLevel = 0;
    for(int i = k+1; i < cols ; i++){
        if(*ptr++ == 0 ) max_minLevel=i;
    }
    //cout << "Max_minLevel: " << max_minLevel << endl;
    //matrix[0][0] = 999;
    desired_level = size;
    current_level = 1;
    //cout << "Desired level :" << desired_level << "\n";
    //Core of the algorithm:
    while(flag){
      while(desired_level > (current_level+1)){
        // cout << "New Iteration\n";
        // cout << "Levels: \n";
        // for( int i = 0 ; i < size ; i++){
        //     cout << levels[i] << " ";
        // }
        // cout << endl;
        // cout << "Level deepness: \n";
        // for( int i = 0 ; i < size - 1 ; i++){
        //     cout << level_deepness[i] << " ";
        // }
        // cout << endl;
        // cout << "Current Level: " << current_level << endl;
        clae.clear();
        bringEdges(matrix,cols,levels[current_level],clae);
        //printf("CLAE (%d):",levels[current_level]);
        //printVectorInt(clae);
        //cout << "\n";
        tmp = clae [ level_deepness[current_level-1]];
        //printf("Current candidate :%d\n",tmp);
        if( tmp <= max_minLevel && ( ((int)clae.size() - 1) >=  level_deepness[current_level-1]) && tmp != last_added ){
          current_level++;
          //printf("puting %d in position %d\n",tmp,current_level);
          levels[current_level] = tmp;
          last_added = tmp;
          //current_level++;

        }else{
          //cout << "Current candidate " << tmp << " too high!\n";
          level_deepness [ current_level - 1 ] = 0;
          current_level--;
          if(current_level == 0 ){
            cout << "Search finished!\n";
            flag=false;
            return;
          }
          level_deepness[current_level-1]++;
       }

     }
       clae.clear();
      // cout << "Desired size reached ########################################!\n";
       //visit levels.
       //cout << "Levels:\n";
       thr_count++;
       // for(int i = 0 ; i < size ; i ++){
       //   cout << levels[i] << " ";
       // }
       // cout << endl;
       level_deepness[current_level-1] = 0;
       current_level--;
       level_deepness[current_level-1]++;

    }
}

void printArray(int array[],const int size) {
  for(int i = 0; i < size;  i++){
    cout << array[i] << " " ;
  }
  cout << endl;
}

/*
  Uses matrix information to visit all thrackles of size desired_size.
  cols - column number of matrix, it's also the number of segments on the complete graph.
*/
int get_kthrackles_of_matrix(int ** matrix, const int cols, const int desired_size, vector<vector<int>> & positions){
  int counters[desired_size+1];
  int current_size; //This will tell us when we get to a thrackle with size 'desired_size'
  int intersect;
  int i;
  int thrackle_counter = 0;
  vector<int> thracklePositions;
  //Start up counters with first 5 edges, not necessary. (Really only need 0 and 1 )
  for(i = 0; i < desired_size ; i++){
    counters[i] = i;
  }
  cout << "Starting algorithm:::::\n" << "cols:" << cols<< " desired size:" << desired_size<< "\ncounters:\n";
  printArray(counters,desired_size);
  current_size = 1;
  while ( counters[0] < (cols-desired_size) ){
    //cout << "Finding thrackles starting with " << counters[0] << endl;

    while ( current_size < desired_size ){
      intersect = 1;
      thracklePositions.clear();
      //cout << "\t Current size: " << current_size << endl;
      //printArray(counters,desired_size);
      if ( counters[current_size] >= cols ){
        current_size--;
        if(current_size < 0 ){
          return thrackle_counter; // ? Finished?
        }
        counters[current_size]++;
        continue;
      }
      for(i = 0; i < current_size ; i++ ){
        intersect &= !matrix[counters[i]][counters[current_size]];
      }
      if ( !intersect ) {
        counters[current_size]++;
      } else {
        if ( (current_size + 1) == desired_size ) {
          thrackle_counter++;
          // cout << "Thrackle found\n";
          // printArray(counters,desired_size);
          for(int p = 0; p < desired_size; p++){
            thracklePositions.push_back(counters[p]);
          }
          //thracklePositions.insert(thracklePositions.end(), counters[0], counters[desired_size]);
          positions.push_back(thracklePositions);
          counters[current_size]++;
          //cout << "\t Current size: " << current_size << endl;
          continue;
        }
        counters[current_size + 1] = counters[current_size] + 1;
        current_size++;
      }
    }
    //next round:
    counters[0]++;
    counters[1] = counters[0] + 1;
  }
  return thrackle_counter;
}