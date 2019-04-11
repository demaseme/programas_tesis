#include "../include/disjointness.h"
#include <unistd.h>
int minAt(9999);
int lowAt(0);


vector<int> coveredEdges;
vector<int> lastInsertedThrackle;
vector<vector<int>> thrackle_list;

void exhaustive_at(int** matrix, int cols, int n, vector<int> current_thrackle, int at, int mode){
  vector<vector<int>> local_desc;
  //if (at > lowAt) lowAt = at;
  //if (mode==1) if( at > 0 && (int)current_thrackle.size() != n - (at-1)) return;
   if( at >= minAt) return;
   //if(at == 1 && (int) current_thrackle.size() < n) return;
   //cout << " ##### Printing recursion data #####\n";
   //cout << "[core] current thrackle :"; printVectorInt(current_thrackle);
   usleep(000000);
   //cout << " [core] this level at : " << at << endl;
  if ( (int) coveredEdges.size() == cols ) {
    if (at < minAt) minAt = at;
    cout << "[core] Current minimal AT: " << minAt << endl;
    return;
  }
  else {
    while(true){
     //cout << "\t Covered edges "; printVectorInt(coveredEdges);

      vector<int> thrackle;
      //if(at<=1) {
        //cout << "[core] attemping to find child of ";
        //printVectorInt(current_thrackle);
      //}
      int val = next(matrix,local_desc,thrackle,cols,n,at,mode);
      if ( !val ) return;

      local_desc.push_back(thrackle);
      //if( at >= 0 ) {printf("[core %d] Found thrackle : ",at); printVectorInt(thrackle);}
      int_thrackle_union(coveredEdges,thrackle,coveredEdges);
      exhaustive_at(matrix, cols, n, thrackle, at+1,mode);
      //cout << "[core] Deleting thrackle from coveredEdges "; printVectorInt(thrackle);
      //if (coveredEdges.size() < thrackle.size() ) cout << "ATTENTION\n";
      int_thrackle_diff(coveredEdges,thrackle,coveredEdges);

    }
  }
}


int next(int ** matrix, vector<vector<int>> descendants, vector<int> & thrackle, int cols, int n, int at, int mode){

  //Finds next thrackle based on the complement of covered edges
  //and the thrackles in descendants (avoiding them),
  //stores result in thrackle, if no thrackle is found NULL is stored in thrackle

  //First step is to define the size of the thrackle to be found.
  vector<int> missing_edges;
  vector<int> local_thrackle;
  vector<int> intersection;

  int i,k,val;
  bool alldifferent = true;
  bool intersection_is_empty = false;
  bool flag = true;
  //To do this we obtain the complement of coveredEdges
  //then if its size exceeds n, we cap k to n.
  int_thrackle_complement(coveredEdges,cols,missing_edges);
  //cout << "\t [next] Missing edges size: " << missing_edges.size(); cout << endl;
  // if (mode == 1 && at>0) {
  //   k = n - (at);
  //   if ( k > (int)missing_edges.size()) return 0;
  // }else{
  //     if( (int)missing_edges.size() > n ) k = n;
  //     else k = (int) missing_edges.size();
  //    if ( ((int)missing_edges.size() - k >= 0 ) && ((at+1) >= minAt )) {
  //      //cout << "\t [next] skipping \n";
  //      return 0;
  //    }
  //   }
  k = (int) missing_edges.size();
  if ( k > n && at==0) k = n;
  if ( k > n && at > 0 ) k = n - 1;
 //Before looking for next, we ask if it's worth to keep going down that branch.
 // Current covered edges = {0,1,2,3,4,5,6}, looking for a thrackle of size k.
 // In the best case we'll find p other k-thrackles until we cover all the edges.
 // if at+p > minAt, it's not worth to explore that branch so we return 0.
 int p=1;
 int ce=coveredEdges.size(); //Size of covered edges.
 //int best_case_at = at;
 //printf("\t [next] Value of k: %d\n",k);
 while ( k*p + ce < cols ) p++;
 if ( (at + p) >= minAt ){
  //  printf("\t [next] Would find %d thrackles of size %d. At would be %d. Return 0.\n",p,k,at+p);
    return 0;
 }
 vector<int> starting_thrackle(missing_edges.begin(),missing_edges.begin()+k);

  //The only case were we want a thrackle of size n is when there are 0 covered edges. This is: there are n missing edges.

  // cout << "\t [next] Missing edges "; printVectorInt(missing_edges);
  // cout << "\t [next] Covered edges "; printVectorInt(coveredEdges);
  // cout << "\t [next] Finding next thrackle of size " << k << endl;
  // cout << "\t [next] Descendants : \n";
  // for(int j = 0; j < (int)descendants.size(); j++){
  //   cout << "\t"; printVectorInt(descendants[j]);
  // }

  //This external while will break (return) when :
  // a) we found a thrackle and it's diffeerent to all descendats and covers some missing edges.
  // b) we didn't find any thrackle of size bigger than 0 such that it's different to all descendats and covers missing_edges

  while(true){
    usleep(000000);
    //Then we attemp to find a thrackle with those conditions.

    // printf("missing: ");
    // printVectorInt(missing_edges);
    // printf(" local_thrackle: ");
    // printVectorInt(local_thrackle);
    // printf(" k: %d \n",k);
   //val = find_next_thrackle(matrix,cols,missing_edges,local_thrackle,k,flag);
    val = find_next_thrackle2(matrix,starting_thrackle,local_thrackle,cols,flag);
    //cout << "Result of val " << val << endl;
    //cout << " \t [next] thrackle found "; printVectorInt(local_thrackle);
    if( !val && (mode == 1) ) {
      //cout << "[next] No thrackle of size " << k << " found.\n";
      return 0;
    }
    while(!val) {
      //If we didn't find it, we attemp to find one with a smaller k;
      k--;
      if(k == 0) break;
      p=1;
     //printf("\t [next-while] Value of k: %d\n",k);
      while ( k*p + ce <= cols ) p++;
      if ( (at + p) >= minAt ){
    //     printf("\t [next-while] Would find %d thrackles of size %d. At would be %d. Return 0.\n",p,k,at+p);
         return 0;
      }

      //If we reduce the size we must start from the original missing edges.
      int_thrackle_complement(coveredEdges,cols,missing_edges);
      // cout << "in next() \n";
    // cout << "\t\t[next] in while - Finding next thrackle of size " << k << endl;
     //cout << "\t\t[next] in while - Missing edges "; printVectorInt(missing_edges);
     //val = find_next_thrackle(matrix,cols,missing_edges,local_thrackle,k,true);
     starting_thrackle.clear();
     starting_thrackle.insert(starting_thrackle.begin(),missing_edges.begin(),missing_edges.begin()+k);
     val = find_next_thrackle2(matrix,starting_thrackle,local_thrackle,cols,true);

    }
    //The while will break either when we find a thrackle or k = 0 (so we didn't find a thrackle).
    if(k == 0) {
      return 0;
    }
    else {
      // cout << "\t [next] Found Child: "; printVectorInt(local_thrackle);
      // //If we found a thrackle we must check that its intersection with the covered edges is empty
      // cout << "\t [next] checking if intersection with covered edges is empty \n";
      // cout << "\t [next] covered edges: "; printVectorInt(coveredEdges);
      intersection_is_empty = false;
      int_thrackle_intersection(coveredEdges,local_thrackle,intersection);
      if (intersection.empty()) intersection_is_empty = true;
      //cout << "\t [next] Is intersection empty? : " << intersection_is_empty << endl;
      //cout << "\t [next] checking if found thrackle is one of descendants\n";

      //If we found a thrackle, we must check that it's not equal to any of the descendants
      alldifferent = true;
      for(i = 0; i < (int) descendants.size() ; i++){
        //cout << "\t [next] comparing thrackles: \n\t" ;
        //printVectorInt(local_thrackle); cout << "\t and \n\t"; printVectorInt(descendants[i]);
        alldifferent &= int_thrackle_areDifferent(local_thrackle,descendants[i]);
        // cout << "\t ################################\n";
        // cout << "\tAre they different? " << alldifferent << endl;
        if (!alldifferent) break;
      }
      if (alldifferent && intersection_is_empty) {
        thrackle = local_thrackle;
        return 1;
      }

      missing_edges = local_thrackle;
      //If it's one of the descendats, we want to find the next available thrackle
      //to avoid looping, we put the flag to false so that find_next_thrackle procedure
      //starts looking in next sequence.
      //cout << "\t[next] External While Iteration\n";
      if( !intersection_is_empty ) flag = false;
      if( intersection_is_empty && !alldifferent) flag = false;
      if( !intersection_is_empty && descendants.empty()) flag = false;
      starting_thrackle = local_thrackle;
      //cout << "\t[next] Search from starting sequence? " << flag << endl;
    }
  }
}


int find_next_thrackle2(int ** matrix, vector<int> current, vector<int> & answer, int cols, bool closed) {
  int intersect = 1;
  int i,j;
  vector<int> start = current;
  int size = (int)start.size();
  if (closed ){
    for( i = 0; i < size ; i++ ){
      for( j = i+1; j < size ; j++){
        intersect &= !matrix[start[i]][start[j]];
      }
    }
    if (intersect){
      answer = start;
      return 1;
    }
  }
  i = 0; intersect = 1;
  //Find the smallest j that must be increased.
  int minj = 9999;
  while ( i < size ){
    j = i+1;
    while ( j < size && intersect ){
      intersect &= !matrix[start[i]][start[j]];
    //  printf("Compared %d,%d: %d\n",start[i],start[j],intersect);
      if ( intersect ) j++;
    }
    intersect = true;
    if (j < minj) minj = j;
    i++;
  }
//  printf("Smallest j : %d\n",minj);
  j = minj;
  if (j == size ) {
    //This means that starting sequence current is a thrackle, but we're in open interval mode.
    j--;
    start[j]++;
  }
  while(true){
    usleep(000000);
    if ( !intersect ) start[j]++;
    // printf("j = %d\n",j);
    // printf("Intersect %d\n",intersect);
    // cout << "start : "; printVectorInt(start);

    if (start[j] > (cols-1) ){
      //cout << j << " Edge doesn't exist.\n";
      j--;
      if ( j < 0 ) return 0;
      start[j]++;
      start[j+1] = start[j] + 1;
      intersect = 1;
      continue;
    }
    i = 0; intersect = 1;
    while (i < j && intersect) {
      intersect &= !matrix[start[i]][start[j]];
      i++;
    }
    if(intersect){
      //cout << "Intersection of " << j << " edge.\n";
      if ( ( j + 1) < size ){
        start[j+1] = start[j] + 1;
      } else{
        break;
      }
      j++;
    }
  }
  answer = start;
  return 1;
}
/*
    Finds next thrackle based on current thrackle information and the disjointness matrix.
    openclosed - true : It starts looking after current sequence.
    openclosed - fals : It starts looking in current sequence.
*/
int find_next_thrackle(int ** matrix, int cols, vector<int> currentThrackle, vector<int> & nextThrackle,int desired_size, bool openclosed){
    //int desired_size = (int)currentThrackle.size();
    int counters[desired_size+1];
    int current_size;
    int intersect;
    int i,j;
    nextThrackle.clear();
    // nextThrackle.resize(desired_size);
    for( i = 0; i < desired_size; i++){
        counters[i] = currentThrackle[i];
    }
    //if closed search do not consider starting thrackle.  closed search : openclosed = true
    if ( openclosed  ){
      //Check if current sequence is a thrackle, if it's not, continue normally.
      //cout << "\t\t[next_thrackle] Checking from starting sequence " ; printArray(counters,desired_size);
      intersect = 1;
      for (i = 0; i < desired_size; i++){
        for(j = i+1; j < desired_size; j++){
            intersect &= !matrix[counters[i]][counters[j]];
        }
      }
      if(intersect){
        for(i = 0; i < desired_size;i++){
          nextThrackle.push_back(counters[i]);
        }
        return 1;
      }
    }
    intersect = 1;
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
            //cout << "\t\t[next thrackle] Checking matrix positions " << counters[i] << " and " << counters[current_size] << endl;
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
    // if( nextThrackle.size() == lastInsertedThrackle.size() ){
    //   intersect = 1;
    //   for(i = 0; i < (desired_size); i++){
    //     intersect &= ( nextThrackle[i] == lastInsertedThrackle[i]);
    //   }
    //   if(intersect) return 0; //Thrackles are the same, so there's no next thrackle
    // }
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
