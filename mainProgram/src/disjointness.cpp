#include "../include/disjointness.h"

/*
    Finds the size of the smaller decomposition based on disjointness matrix info
*/
void find_decomposition(int ** matrix, int cols, int n){
    vector<int> currentThrackle;
    vector<int> nextThrackle;
    vector<int> auxiliarThrackle;
    vector<int> coveredEdges;
    vector<int> startingThrackle;
    vector<vector<int>> foundThrackles;
    int currentLevel;
    int val;
    int i,j;
    //Find first thrackle of size n
    //To find first thrackle of size n, initialize the current thrackle
    //With values of 0,1,2,...(n-1).
    // currentThrackle.resize(n);
    // for(i = 0; i < n ; i ++) currentThrackle[i] = i;
    // //Check if 0,1,2,... is not a thrackle just in case.
    // intersect = 1;
    // for(i = 0; i < n; i++){
    //     for(j = i+1; j < n; j++){
    //         intersect &= !matrix[currentThrackle[i]][currentThrackle[j]];
    //     }
    // }
    // if (!intersect) find_next_thrackle(matrix, cols, currentThrackle, nextThrackle,n);
    // foundThrackles.push_back(nextThrackle);
    // cout << "Starting thrackle of size " << n  <<endl;
    // printVectorInt(nextThrackle);
    // int_thrackle_union(coveredEdges,nextThrackle,coveredEdges);
    int k;
    int cat,mincat;
    cat = 0;
    mincat = 9999;
    k = n;
    currentLevel = -1;


    while((int) coveredEdges.size() < cols) {
      if( cat+1 >= mincat) {
          //No use in keep searching, the results will be of same antithickness or worse
          k++;
          int_thrackle_diff(coveredEdges,foundThrackle[currentLevel],coveredEdges);
          startingThrackle = foundThrackle[currentLevel];
          foundThrackles.erase(foundThrackles.begin()+currentLevel);
          currentLevel--;
      }
      val = find_next_compatible_thrackle(matrix,cols,coveredEdges,nextThrackle, k, startingThrackle);
      if ( val ) {
        int_thrackle_union(coveredEdges,nextThrackle,coveredEdges);
        foundThrackles.push_back(nextThrackle);
        currentLevel++;
        cat = (int)foundThrackles.size();
      }
      k--;
      if(k < 1) k = 1;
    }
    if (cat < mincat) mincat=cat;
    cout << "Covered edges \n";
    printVectorInt(coveredEdges);
    cout << "convex anti thickness: " << cat << endl;
    cout << "Current level: " << currentLevel << endl;
    cout << "Number of thrackles : " << foundThrackles.size() << endl;
    //Discard current level thrackle and update coveredEdges
    cout << "Eliminating thrackle " ; printVectorInt(foundThrackles[currentLevel]);
    int_thrackle_diff(coveredEdges,foundThrackles[currentLevel],coveredEdges);
    foundThrackles.erase(foundThrackles.begin()+currentLevel);
    currentLevel--;
    //Father of current level must be erased too, because we will check with its brothers next iteration.
    cout << "Eliminating thrackle " ; printVectorInt(foundThrackles[currentLevel]);
    int_thrackle_diff(coveredEdges,foundThrackles[currentLevel],coveredEdges);
    startingThrackle = foundThrackles[currentLevel]; //To check with its brothers.
    foundThrackles.erase(foundThrackles.begin()+currentLevel); //Erased from current thrackle list.

    cout << "Number of thrackles : " << foundThrackles.size() << endl;
    cout << "Covered edges \n"; printVectorInt(coveredEdges);
    cout << "Next iteration will start from thrackle: "; printVectorInt(startingThrackle);
    //Go up a level.
    currentLevel--;


    //D1:
    //Discard last found thrackle (smaller size) [reduces level to - 1]
    //Find next thrackle q of current level.
    //D2:
    //If q and found thrackles cover the complete n graph. -> antithickness is less than before
      //update antithickness.
      //repeat D1
    //Else:
        //find next thrackle q of current level.
        //repeat D2
}

/*
  Given a list of already covered edges, find next thrackle of desired_size, whose intersection  with it is empty .
*/
int find_next_compatible_thrackle(int ** matrix, int cols, vector<int> coveredEdges, vector<int> & nextThrackle, int desired_size,
const vector<int> & startingThrackle ){

  int indexCurrentT = 0;
  int indexNextT = 0;
  int intersect;
  int val;
  bool flag_size_achieved = false;
  vector<int> foundThrackle;
  vector<int> C;
  nextThrackle.clear();
  nextThrackle.resize(desired_size);
  //Find a starting point.
  //With cols we know there are from 0 to cols-1 edges.
  for(int i = 0; i < cols ; i++){
      if( !coveredEdges.empty() && coveredEdges[indexCurrentT] == i) indexCurrentT++;
      else{
          //cout << "Copying " << i << " into starting point\n";
          nextThrackle[indexNextT] = i;
          indexNextT++;
          //cout << "indexNextT: " << indexNextT << endl;
          if(indexNextT == desired_size) {flag_size_achieved = true; cout << "achieved size\n"; break; }
      }
  }
  if (!flag_size_achieved) return 0; // There's no thrackle of that size with those edges.
  cout << "Starting point: \n" ;
  printVectorInt(nextThrackle);
  //Check if starting point is already a thrackle.
  intersect = 1;
  for(int i = 0; i < desired_size; i++){
      for(int j = i+1; j < desired_size; j++){
          intersect &= !matrix[nextThrackle[i]][nextThrackle[j]];
      }
  }
  if ( startingThrackle.empty() ) {
      cout << "No starting thrackle provided\n";
      //If it's not a thrackle find one of the desired size starting from there.
      if (!intersect) val = find_next_thrackle(matrix, cols, nextThrackle, foundThrackle,desired_size);
      else foundThrackle = nextThrackle;
  } else {
      val  = find_next_thrackle(matrix,cols,startingThrackle,foundThrackle,desired_size);
    }
      if ( !val ) return 0; //No next thrackle!
      do{
        int_thrackle_intersection(coveredEdges,foundThrackle,C);
        if( C.empty() ) {
          nextThrackle = foundThrackle;
          return 1;
        }
        nextThrackle.clear();
      }
      while( find_next_thrackle( matrix, cols, foundThrackle, foundThrackle, desired_size ) );

  return 0; // False value
}
/*
    Given a thrackle, find next thrackle of size desired_size, whose intersection is empty.
*/
int find_next_comptabile_thrackle(int ** matrix, int cols, vector<int> currentThrackle, vector<int> & nextThrackle,int desired_size){


    int indexCurrentT = 0;
    int indexNextT = 0;
    int intersect;
    int val;
    vector<int> foundThrackle;
    vector<int> C;
    nextThrackle.clear();
    nextThrackle.resize(desired_size);

    //Find a starting point.
    //With cols we know there are from 0 to cols-1 edges.
    for(int i = 0; i < cols ; i++){
        //printf(" i %d | indexCurrentT %d | currentThrackle[%d]:%d\n",
        //  i,indexCurrentT,indexCurrentT,currentThrackle[indexCurrentT]);
        if(currentThrackle[indexCurrentT] == i) indexCurrentT++;
        else{
            //cout << "Copying " << i << " into starting point\n";
            nextThrackle[indexNextT] = i;
            indexNextT++;
            //cout << "indexNextT: " << indexNextT << endl;
            if(indexNextT == desired_size) break;
        }
    }
  //  cout << "Starting point \n";
    //printVectorInt(nextThrackle);
    //Check if starting point is already a thrackle.
    intersect = 1;
    for(int i = 0; i < desired_size; i++){
        for(int j = i+1; j < desired_size; j++){
            intersect &= !matrix[nextThrackle[i]][nextThrackle[j]];
        }
    }
    //If it's not a thrackle find one of the desired size starting from there.
    if (!intersect) val = find_next_thrackle(matrix, cols, nextThrackle, foundThrackle,desired_size);
    else foundThrackle = nextThrackle;
    if ( !val ) return 0; //No next thrackle!
    //cout << "Found thrackle \n";
  //  printVectorInt(foundThrackle);
    // Up to here both currentThrackle and foundThrackle are thrackles, however the intersection must be checked.
    //A new thrackle must be found until intersection is empty!
    // if(intersectionInt(nextThrackle,foundThrackle) is empty ) return foundThrackle
    // else find_next_thrackle .
    do{
      int_thrackle_intersection(currentThrackle,foundThrackle,C);
      if( C.empty() ) {
        nextThrackle = foundThrackle;
        return 1;
      }
      nextThrackle.clear();
    }
    while( find_next_thrackle( matrix, cols, foundThrackle, nextThrackle, desired_size ) );
    return 0;
}
/*
    Finds next thrackle based on current thrackle information and the disjointness matrix.
*/
int find_next_thrackle(int ** matrix, int cols, vector<int> currentThrackle, vector<int> & nextThrackle,int desired_size){
    //int desired_size = (int)currentThrackle.size();
    int counters[desired_size+1];
    int current_size;
    int intersect;
    int i ;
    for( i = 0; i < desired_size; i++){
        counters[i] = currentThrackle[i];
    }
    counters[desired_size-1]++;
    current_size = desired_size-1;
    while( current_size < desired_size ){
        //printf("Current size %d\n",current_size);
        //printArray(counters,desired_size);
        if (counters[current_size] >= cols) {
            current_size --;
            if(current_size < 0 ){
                return 0; //There is no next thrackle! return FALSE value
            }
            counters[current_size]++;
            continue;
        }
        intersect = 1;
        for(i = 0; i < current_size; i++){
            intersect &= !matrix[counters[i]][counters[current_size]];
        }
        if (!intersect){
            counters[current_size]++;
        }else{
            counters[current_size + 1] = counters[current_size] + 1;
            current_size++;
        }
    }
    //Since we only go out of the while loop when we acquire a new thrackle
    //we fill up the nextThrackle vector with the current counters info.
    for(i = 0; i < desired_size;i++){
        nextThrackle.push_back(counters[i]);
    }
    return 1; //Positive value = TRUE value, thrackle found!
}
/*
    Fills the square matrix (matrix) with geometric information
    based on the disjointness of the graph.
*/
void construct_disjointness_matrix(const vector<Edge> edges,int ** matrix,const int rows, bool printmatrix){
    //This to write to matrix.
    int * ptr;
    // for(int i = 0; i < (int) edges.size() ; i ++){
    //   cout << "Edge " << i << ":";
    //   printEdge(edges[i]);
    // }
    for(int i = 0; i < rows; i++){
        ptr = (int * ) matrix[i];
        for(int j = 0; j < rows; j++){
            //Check if edges[i] and edges[j] are disjoint.
            //If they are, put a 1, otherwise put a 0.
            //cout << "Checking edges : " << i << " and " << j << endl;
            if(i==j){
              *ptr++ = 0;
              continue;
            }else if( crossing(edges[i],edges[j]) || share_ep(edges[i],edges[j]) ){
              *ptr++ = 0;
              continue;
            }else *ptr++=1;
        }
    }

    //This to print it.
    if (!printmatrix) return;
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
 // int key,key2;
 // bool tfound = false;
  vector<int> thracklePositions;
  //Start up counters with first 5 edges, not necessary. (Really only need 0 and 1 )
  for(i = 0; i < 2 ; i++){
    counters[i] = i;
  }
  for(i = 2; i <= desired_size ; i++){
      counters[i] = 0;
  }
  // cout << "Starting algorithm:::::\n" << "cols:" << cols<< " desired size:" << desired_size<< "\ncounters:\n";
  // printArray(counters,desired_size);
  current_size = 1;
  while ( counters[0] < cols ){
    //cout << "Finding thrackles starting with " << counters[0] << endl;
    //cin >> key;
    while ( current_size < desired_size ){
      intersect = 1;
      thracklePositions.clear();
      //cout << "\t [211] Current size: " << current_size << endl;
      //printArray(counters,desired_size);

      if ( counters[current_size] >= cols ){
        current_size--;
        //if (current_size == 0) break;
        if(current_size < 0 ){
        //    current_size = 0;
        //    continue;
          //   cout << "####### FINISHED ON LINE 215 ##### \n";
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
          // cout << "Thrackle found\n\t";
          // printArray(counters,desired_size);
          // cin >> key2;
          // tfound = true;
          for(int p = 0; p < desired_size; p++){
            thracklePositions.push_back(counters[p]);
          }
          //thracklePositions.insert(thracklePositions.end(), counters[0], counters[desired_size]);
          positions.push_back(thracklePositions);
          counters[current_size]++;
          //cout << "\t [240] Current size: " << current_size << endl;
          continue;
        }
        //cout << "[247] Increasing thrackle!\n";
        counters[current_size + 1] = counters[current_size] + 1;
        current_size++;
      }
    }
    //next round:
    //nextr:
    //cout << "Increasing counters[0]\n";
    counters[0]++;
    counters[1] = counters[0] + 1;
    //cout << "Current size: " << current_size << endl;
  }
  //cout << "##############################Finished##########################################\n";
  return thrackle_counter;

}
