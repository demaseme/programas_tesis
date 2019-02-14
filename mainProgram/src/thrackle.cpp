#include "../include/thrackle.h"
//
// float alto;
// float ancho; //Used by opengl

bool share_ep(Edge e_1, Edge e_2){
    return (e_1.v1 == e_2.v1 || e_1.v1 == e_2.v2 || e_1.v2 == e_2.v1 || e_1.v2 == e_2.v2);
}

int area(Point a, Point b, Point c){
	long r = (long)(b.x - a.x) * (long)(c.y - a.y) - (long)(c.x - a.x) * (long)(b.y - a.y);

	return r > 0;
}

int izquierda(Point a, Point b, Point c){
	return area(a, b, c) > 0;
}

int Xor(int x, int y){
	return !x ^ !y;
}

int crossing(Edge s1, Edge s2){
	Point a = s1.v1, b = s1.v2, c = s2.v1, d = s2.v2;

	return Xor(izquierda(a, b, c), izquierda(a, b, d)) && Xor(izquierda(c,d,a), izquierda(c,d,b));
}
// bool crossing(Edge e_1, Edge e_2){
//   //Check if endpoints of e_2 are in different
//   //semiplanes defined by e_1
//   int ori1 = orientation(e_1.v1,e_1.v2,e_2.v1);
//   int ori2 = orientation(e_1.v1,e_1.v2,e_2.v2);
//   int ori3 = orientation(e_2.v1,e_2.v2,e_1.v1);
//   int ori4 = orientation(e_2.v1,e_2.v2,e_1.v2);
//   if (ori1 != ori2 && ori3 != ori4){
//       // printf("The following edges cross: \n");
//       // printEdge(e_1);
//       // printEdge(e_2);
//       // printf("===========================\n");
//       return true;
//   }
//   return false;
// }

/*
Function that finds all thrackles of size k.
It creates every combination of k edges for the given edge set.
Then it evaluates whether that set of k edges is a thrackle or not.
Combinations are found based on Knuth algorithm.
Input:
    vector<Edge> edge - The edges of the complete graph.
    int k             - The size of the thrackles to be found.
    long comboCtr     - A counter for the number of combinations of size k found.
    vector<Thrackle> foundThrackles - A vector to store the found thrackles

DEPRECATE - HORRIBLY SLOW FOR 10 POINTS
*/
void findThrackles_size(const vector<Edge> edges, int k, long & comboCtr, vector<Thrackle> & foundThrackles){
    //Find the combinations of size k for a set of size edges.size();
    int n;
    n = (int) edges.size(); //for 10 points this variable is equal to 45.
    //L1. Initialize.
    std::vector<int> c;
    int j;
    vector<Edge> tmp_edges;
    Thrackle tmp_thrackle;
    //long res;
    c.push_back(-9999); //Sentinel.
    for(int i=0; i < k; i++){
        c.push_back(i);
    }
    c.push_back(n);
    c.push_back(0);
    comboCtr = 0;

    while(true){
        //L2. Visit. Here we check if current combination is a thrackle or nah.

        for(int i = k; i > 0; i--){
            //cout << c[i] << " ";
            tmp_edges.push_back(edges[c[i]]);
        }
        //cout << endl;

        if(isThrackle(tmp_edges)){
            tmp_thrackle.edges = tmp_edges;
            foundThrackles.push_back(tmp_thrackle);
        }
        tmp_edges.clear(); // Clean up for next iteration.
        comboCtr++; //Increase counter of combinations.

        //L3. FIND j
        j = 1;
        while( (c[j] + 1) == c[j+1] ) {
            c[j] = j - 1;
            j = j + 1;
        }
        //L4. Termination condition met?
        if (j > k) {
            //std::cout << res << " combinations\n";
            break;
        }
        //L5. Update and Return to L2.
        c[j] = c[j] + 1;
    }
}

// The main function that prints all combinations of
// size r in arr[] of size n. This function mainly
// uses combinationUtil()
//DEPRECATE - HORRIBLY SLOW FOR 10 POINTS
void k_Combination(vector<Edge> arr, int r, vector<vector<Edge>> & combinations,
   int & counter, int & thrackleCounter, vector<Thrackle> & foundThrackles){
    cout << "Finding combinations and thrackles!\n";

    // A temporary array to store all combination
    // one by one
    vector<Edge> data;
    data.resize(r);
    // Print all combination using temprary array 'data[]'
    combinationUtil(arr, r, 0, data, 0, combinations, counter, thrackleCounter, foundThrackles);

}
/* arr[]  ---> Input Array
   n      ---> Size of input array
   r      ---> Size of a combination to be printed
   index  ---> Current index in data[]
   data[] ---> Temporary array to store current combination
   i      ---> index of current element in arr[]     */
void combinationUtil(vector<Edge> arr, int r,int index, vector<Edge> data, int i,
  vector<vector<Edge>> & combinations, int & counter, int & thrackleCounter, vector<Thrackle> & foundThrackles){
    int n = (int) arr.size();
    // Current cobination is ready, store it
    vector<Edge> tmp;
    Thrackle tmp_thrackle;
    if (index == r) {
        for (int j = 0; j < r; j++){
            tmp.push_back(data[j]);
          }
        //printf("\n");
        //combinations.push_back(tmp);
        //
        counter++;

        if(isThrackle(tmp)){
          thrackleCounter++;
          tmp_thrackle.edges = tmp;
          foundThrackles.push_back(tmp_thrackle);
          //cout<< thrackleCounter << "\n";
          //printThrackle(tmp_thrackle);

        }
        tmp.clear();
        return;
    }
    // When no more elements are there to put in data[]
    if (i >= n)
        return;
    // current is included, put next at next location
    data[index] = arr[i];
    combinationUtil(arr, r, index + 1, data, i + 1, combinations,counter, thrackleCounter, foundThrackles);
    // current is excluded, replace it with next
    // (Note that i+1 is passed, but index is not
    // changed)
    combinationUtil(arr, r, index, data, i + 1,combinations, counter, thrackleCounter, foundThrackles);

}

/*
    This function tells whether or not an edge belongs to a Thrackle. Should be O(1).
    This requires the edges to have its tag initialized when building (n 2) edges.
*/
bool edge_in_thrackle(const Edge a, const Thrackle A){
    return A.edge_bool[a.tag];
}
//Returns true if edge a is in set A.
//Returns false otherwise, it's O(E)
bool edge_in(Edge a, vector<Edge> A){
  for(auto i = A.begin(); i < A.end() ; i++) {
    if(a == *i) return true;
  }
  return false;
}
/*
  Performs the union of Thrackles A and B,
  Needs the edge_bool vector initialized to work.
  Puts the positions of the edges in result vector.
  This algorithm is O(n)
*/
void thrackle_union(const Thrackle A, const Thrackle B, vector<int> result ){
  vector<int> edgesA;
  vector<int> edgesB;
  int i,j,k;
  for (i = 0; i < (int) A.edge_bool.size(); i++) if(A.edge_bool[i]) edgesA.push_back(i);
  for (i = 0; i < (int) B.edge_bool.size(); i++) if(B.edge_bool[i]) edgesB.push_back(i);
  while( i < (int) edgesA.size() && j < (int) edgesB.size() ){
    if( edgesA[i] < edgesB[j] ) {
      //Put it in result, increase only i.
      result.push_back(edgesA[i]);
      i++;
      continue;
    }
    if( edgesA[i] == edgesB[j] ){
      //Put in in result, increase both.
      result.push_back(edgesA[i]);
      i++; j++;
      continue;
    }
    else {
      result.push_back(edgesB[i]);
      j++;
      continue;
    }
  }
  if (i < (int)edgesA.size() ){
    //j finished but i didn't. Push the rest of A from i to end.
    for(k = i; k < (int)edgesA.size();k++) result.push_back(edgesA[k]);
  }
  if (j < (int)edgesB.size() ){
    //i finished but j didn't. Push the rest of B from j to end.
    for(k = j; k < (int)edgesB.size();k++) result.push_back(edgesA[k]);
  }
}
/*
  Performs the intersection of the edges of A and B.
  Needs the edge_bool vector initialized to work.
  Puts the positions of the edges in result vector.
  This is a O(n) algorithm.
*/
void thrackle_intersection(const Thrackle A, const Thrackle B, vector<int> & result ){
  vector<int> edgesA;
  vector<int> edgesB;
  int i,j;
  for (i = 0; i < (int) A.edge_bool.size(); i++) if(A.edge_bool[i]) edgesA.push_back(i);
  for (i = 0; i < (int) B.edge_bool.size(); i++) if(B.edge_bool[i]) edgesB.push_back(i);
  i=0;
  j=0;
  while( i < (int)edgesA.size() && j < (int)edgesB.size() ){
    if( edgesA[i] < edgesB[j] ) {
      //Not in intersection, i increases.
      i++;
      continue;
    }
    if( edgesA[i] == edgesB[j] ) {
      //In intersection, both indexes increase.
      result.push_back(edgesA[i]);
      i++; j++;
      continue;
    }
    if( edgesA[i] > edgesB[j] ) {
      //not in intersection, j increases.
      j++;
      continue;
    }
  }
}


void minimal_thrackle_intersection(const vector<Thrackle> thrackles,int &result){
  int minimal;
  minimal = 9999; //This value is accepted for this project max is 10.
  vector<int> currentIntersection;
  for(unsigned int i = 0; i < thrackles.size(); i++){
    for(unsigned int j = i+1; j < thrackles.size(); j++){
      //Compare thrackles i and j and update minimal if their intersection is
      //smaller than current minimal value.
      thrackle_intersection(thrackles[i],thrackles[j],currentIntersection);
      if( (int) currentIntersection.size() < minimal){
        minimal = currentIntersection.size();
        if (minimal == 0) { cout << "Intersection is NULL on thrackles " << i << " and " << j << endl;}
      }
      currentIntersection.clear();
    }
  }
  result = minimal;
  //cout << "Smaller intersection size is : " << minimal << endl;
}

//Performs  pairwise intersection and writes each result on a file
void thrackle_real_intersection_wrt(const vector<Thrackle> T, int current_ot, int set_size, int t_size){
    ofstream myfile;
    string file_name = "ths/" + to_string(set_size) + "/" + to_string(current_ot) + "_realintersize" + ".ths";
    system( ("mkdir -p ths/" + to_string(set_size)).c_str() );
    myfile.open(file_name, ios::out | ios::binary);
    int number_of_thrackles = (int)T.size();
    int i,j;

    myfile.write( (char*) &number_of_thrackles,sizeof(uint16_t));
    myfile.write( (char*) &t_size, sizeof(uint16_t));

    for(i = 0; i < number_of_thrackles; i++){
      for(j = 0; j < t_size ; j++){
        myfile.write( (char*) &(T[i].edges[j].v1.x),sizeof(uint16_t));
        myfile.write( (char*) &(T[i].edges[j].v1.y),sizeof(uint16_t));
        myfile.write( (char*) &(T[i].edges[j].v2.x),sizeof(uint16_t));
        myfile.write( (char*) &(T[i].edges[j].v2.y),sizeof(uint16_t));
      }
    }
    unsigned int current_inter_size =0;
    vector<int> currentIntersection;
    for(unsigned int i = 0; i < T.size(); i++){
      for(unsigned int j = i+1; j < T.size(); j++){
        thrackle_intersection(T[i],T[j],currentIntersection);
        current_inter_size = currentIntersection.size();
        // myfile.write( (char*) &i , sizeof(uint16_t));
        // myfile.write( (char*) &j , sizeof(uint16_t));
        myfile.write( (char*) &current_inter_size , sizeof(uint16_t));
        currentIntersection.clear();
      }
    }
    myfile.close();
}

void thrackle_intersection_all(const vector<Thrackle> T, int & result){
  if (T.empty()) {
    result = 0;
    return;
  }
  if (T.size() == 1) {
      result = 0;
      return ;
  }
  //cout << "NUMBER OF EDGES: " << T[0].edge_bool.size() << endl;

  int count;
  int minimal;
  count = 0;
  minimal = 45;
  int i,k;
  #pragma omp parallel for private(count,k) shared(minimal)
      for(i = 0; i < (int) T.size() ; i++){
          //printf("Thread number %d, i:%d\n",omp_get_thread_num(),i);
          for(int j = i+1; j < (int) T.size(); j++ ){
              //printf("Thread number %d i:%d, j:%d\n",omp_get_thread_num(),i,j);
              vector<bool> res((int)T[0].edge_bool.size(),true);
              bool_thrackle_intersection(T[i],T[j],res);
              for(k = 0; k < (int)res.size() ; k++){
            //      printf("Thread number %d i:%d, j:%d k:%d\n",omp_get_thread_num(),i,j,k);
                  if (res[k]) count++;
              }
              if (count < minimal) {minimal = count;}
              if (minimal == 0 ) { cout << "no intersection between thrackles " << i << " and " << j << endl; result =minimal;}
              count = 0;
              // for(int m = 0; m < (int)res.size() ; m++){
              //     res[m] = true;
              // }
          }
      }

  result = minimal;
//  cout << "OUTING T INTERSECTION ALL\n";
  //Here we can choose to print it or return it. :)
}
// Returns true if representation of thrackles A and B are different. False otherwise
bool int_thrackle_areDifferent(vector<int>A, vector<int> B){
  if( A.size() != B.size() ) return true;
  for( int i = 0; i < (int) A.size() ; i++){
    if (A[i] != B[i]) return true;
  }
  return false;
}
void int_thrackle_complement(vector<int> A, int maxVal, vector<int> & C){
  int pos;
  bool setb[maxVal];
  C.clear();
  for(pos = 0; pos < maxVal ; pos++){
    setb[pos] = false;
  }
  for(pos = 0 ; pos < (int)A.size() ; pos++){
    setb[A[pos]] = true;
  }
  for(pos = 0; pos < maxVal ; pos++){
    if(!setb[pos]) C.push_back(pos);
  }
}
void int_thrackle_diff(vector<int>A,vector<int>B, vector<int> & C){
    unsigned int i,j;
    // cout << "clearing C\n";
    C.clear();
    i = 0; j= 0;
    while ( i < A.size() && j < B.size() ){
        //printf("i %d, j %d",i,j);
        if ( A[i] < B[j] ){
            C.push_back(A[i]);
            i++;
            continue;
        }

        if ( A[i] == B[j] ) {
            i++; j++;
            continue;
        }
        if ( A[i] > B[j] ){
            // C.push_back(A[i]);
            j++;
            continue;
        }
    }
    if ( i < A.size() ){
        while( i < A.size() ){
            C.push_back(A[i]);
            i++;
        }
    } else if (j < B.size() ) {
        while( j < B.size() ){
            C.push_back(B[j]);
            j++;
        }
    }
}
/*
  Performs the union of 2 thrackle representation,
  each thrackle is represted with a list of integers
  lexicographically ordered.
  Leaves result in C. O(n)
*/
void int_thrackle_union(vector<int> A, vector<int> B, vector<int> & C){
  int i,j;
  i = 0; j=0;
  if ( A.empty() ) {C = B; return;}
  if ( B.empty() ) {C = A; return;}
  C.clear();
  while(i < (int) A.size() && j < (int) B.size()){

    if ( A[i] < B[j] ){
      C.push_back(A[i]);
      i++;
      continue;
    }
    if ( A[i] == B[j] ) {

      C.push_back(A[i]);
        i++; j++;
      continue;
    }
    if ( A[i] > B[j] ) {

      C.push_back(B[j]);
        j++;
      continue;
    }
  }
  // B was bigger
  if ( j < (int)B.size() ) {
  //  cout << "B was bigger\n";
    while ( j < (int) B.size() ){

      C.push_back(B[j]);
      j++;
    }
  }
  else if (i < (int)A.size() ) {
    while ( i < (int)A.size() ) {

      C.push_back(A[i]);
        i++;
    }
  }

}
/*
  Performs the intersection of 2 thrackle representation,
  each thrackle is represented with a list of integers
  lexicographically ordered.
  Leaves the result on C.
*/
void int_thrackle_intersection(vector<int> A, vector<int>B, vector<int> & C){
  int i,j;
  C.clear();
  i = 0;
  j = 0;
  if ( A.empty() || B.empty() ) return;
  while( i < (int) A.size() && j < (int)B.size()) {
    if( A[i] < B[j] ) {
      i++;
      continue;
    }
    if( A[i] == B[j] ) {

      C.push_back(A[i]);
        i++; j++;
      continue;
    }
    if( A[i] > B[j] ) {
      j++;
      continue;
    }
  }
}
/*
  Performs intersection of edges of thrackles A and B using
  the boolean vector in each of these. Leaves result on res vector.
  This performs (E) operations.
*/
void bool_thrackle_intersection(const Thrackle A, const Thrackle B, vector<bool> & res){
  //cout << "Size of vectors: " << A.edge_bool.size() << "," << B.edge_bool.size() << endl;

  for(int i = 0; i < (int) A.edge_bool.size(); i++){
    res[i] = res[i] && (A.edge_bool[i] && B.edge_bool[i]);
  }


}
/*
  Performs union of edges of thrackles A and B using
  the boolean vector in each of these. Leaves result on res vector.
  This performs (E) operations.
*/
void bool_thrackle_union(Thrackle A, Thrackle B, vector<bool> & res){
  for(int i = 0; i < (int) A.edge_bool.size(); i++){
    res[i] = res[i] || (A.edge_bool[i] || B.edge_bool[i]);
  }
}

bool union_covers(vector<Thrackle> T){
  if (T.size() <= 1 ) return false;
  vector<bool> res(false,T[0].edge_bool.size());
  bool final_res;
  final_res = true;
  for(int i = 0 ; i < (int) T.size() - 1 ; i++){

    bool_thrackle_union(T[i],T[i+1],res);
  }
  for(int i = 0; i < (int) res.size(); i++){
    final_res &= res[i];
  }
  return final_res;
}

bool isThrackle(vector<Edge> & edges){
  //If every pair of edges cross or share an endpoint, return true.
  unsigned int k = edges.size();
  bool flag;
  flag = true;
    for(unsigned int i = 0; i < k ; i++){
        for(unsigned int j = 0; j < k; j++){
            if (!( share_ep(edges[i],edges[j]) || crossing(edges[i],edges[j]) )) {
              return false;
            }


        }
    }

  if (flag) return true;
  return false;
}

//From a given thrackle list, find those which contain
//a cycle of size k.
void findThrackle_withCycleK(int k, vector<Thrackle> thrackles, vector<Thrackle> & result){
    //For each thrackle, calculate all the subsets of size k
    vector<vector<Edge>> buff;
    Thrackle tmp;
    for(int i =0; i<(int) thrackles.size();i++)
        pwrsetk(k,thrackles[i].edges,buff);
    //Test if they are a cycle.
    for(int i = 0; i < (int) buff.size() ; i++){
        if(isCycle(buff[i])){
            tmp.edges = buff[i];
            result.push_back(tmp);
        }
    }
}
void findThrackle(unsigned int k, vector<Point> points, vector<Thrackle> & thrackles){
      //Generate all edges.
      vector<Edge> complete;
      generateAllEdges(points,complete);
      //printEdges(complete);
      //Generate the power set of all edges.
      vector<vector<Edge>> edgeCombos;
      pwrset_edges(complete,edgeCombos);
      //printf("The powerset of edges is of size: %d\n",(int)edgeCombos.size());

      //For each element of the powerset of edges, choose only those whose size is k.
      vector<vector<Edge>> filteredEdges;
      for(unsigned int i = 0; i < edgeCombos.size(); i++){
          if(edgeCombos[i].size() == k){
              filteredEdges.push_back(edgeCombos[i]);
              // printf("Printing set %d\n",i);
              // printEdges(edgeCombos[i]);
              // printf("Finished priting set %d\n",i);
          }
      }
      //printf("There are %u sets of edges of size %d\n",(int)filteredEdges.size(),k);
      //For each element of filteredEdges choose only those which are thrackles.
      Thrackle tmp_thrackle;
      for(unsigned int i = 0; i < filteredEdges.size(); i++){
          //printf("Found Thrackle of size %d\n", k );
          if (isThrackle(filteredEdges[i])){
              tmp_thrackle.edges = filteredEdges[i]; //Vector operator=, copies.
              thrackles.push_back(tmp_thrackle);
          }
      }
     // printf("From these, only %d are thrackles\n",(int)thrackles.size());
  }
void writeOne4All_bin(ofstream& myfile, const vector<Thrackle> T, const vector<Point> points, const int set_size,
const int t_size, const int ot, const int min_inter_count){
  int i,j;
  myfile.write( (char*) &set_size,sizeof(uint16_t));
  for(i = 0; i< set_size; i++){
    myfile.write( (char*) &points[i].x,sizeof(uint16_t));
    myfile.write( (char*) &points[i].y,sizeof(uint16_t));
  }
  int number_of_thrackles = (int) T.size();
  myfile.write( (char*) &ot,sizeof(uint16_t));
  myfile.write( (char*) &t_size,sizeof(uint16_t));
  myfile.write( (char*) &number_of_thrackles,sizeof(uint16_t));
  //An edge consists of a pair of Points, this is 4 uint16_t variables.
  for(i = 0; i < number_of_thrackles; i++){
    for(j = 0; j < t_size ; j++){
      myfile.write( (char*) &(T[i].edges[j].v1.x),sizeof(uint16_t));
      myfile.write( (char*) &(T[i].edges[j].v1.y),sizeof(uint16_t));
      myfile.write( (char*) &(T[i].edges[j].v2.x),sizeof(uint16_t));
      myfile.write( (char*) &(T[i].edges[j].v2.y),sizeof(uint16_t));
    }
  }
  //myfile.write( (char* ) "\xFF", sizeof(uint16_t));
}
void writeThrackles_bin(const vector<Thrackle> T, const vector<Point> points,
  const int set_size, const int t_size, const int ot, const int min_inter_count){
  ofstream myfile;
  int i,j;
  string file_name = "ths/" + to_string(set_size) + "/" + to_string(ot) + "_" + to_string(t_size) + ".ths";
  system( ("mkdir -p ths/" + to_string(set_size)).c_str() );
  myfile.open(file_name, ios::out | ios::binary);
  myfile.write( (char*) &set_size,sizeof(char));
  //Each point consists of 2 coordinates stored in uint16_t variables which are 2 bytes each.
  for(i = 0; i< set_size; i++){
    myfile.write( (char*) &points[i].x,sizeof(uint16_t));
    myfile.write( (char*) &points[i].y,sizeof(uint16_t));
  }
  int number_of_thrackles = (int) T.size();
  myfile.write( (char*) &ot,sizeof(char));
  myfile.write( (char*) &t_size,sizeof(char));
  myfile.write( (char*) &number_of_thrackles,sizeof(char));
  //An edge consists of a pair of Points, this is 4 uint16_t variables.
  for(i = 0; i < number_of_thrackles; i++){
    for(j = 0; j < t_size ; j++){
      myfile.write( (char*) &(T[i].edges[j].v1.x),sizeof(uint16_t));
      myfile.write( (char*) &(T[i].edges[j].v1.y),sizeof(uint16_t));
      myfile.write( (char*) &(T[i].edges[j].v2.x),sizeof(uint16_t));
      myfile.write( (char*) &(T[i].edges[j].v2.y),sizeof(uint16_t));
    }
  }
  myfile.close();
}

//Writes thrackle information to a text file, this procedure needs all thrackles to be of the same size.
/*The format of the output:
  <set size>
  <point list>
  <ot_number>
  <thrackle size>
  <number of thrackles found>
  <thrackle list>
*/
void writeThrackles(vector<Thrackle> & thrackles, vector<Point> & points, int set_size, int thrackle_size, int ot_number,
int minimal_intersection_counter ){
    ofstream myfile;
    string file_name = "ths/" + to_string(set_size) + "/" + to_string(ot_number) + "_" + to_string(thrackle_size) + ".ths";

    system( ("mkdir -p ths/" + to_string(set_size)).c_str() );
    myfile.open(file_name);
    myfile << set_size << "\n";
    //Write the points on file.
    for(auto i = 0; i < (int) points.size() ; i++){
        myfile << points[i].x << "," << points[i].y<< " " ;
    }
    myfile << endl;
    myfile << ot_number << "\n";
    myfile << thrackle_size << "\n";
    myfile << thrackles.size() <<"\n";
    for(auto i = 0; i < (int)thrackles.size() ; i++){
      for(auto j = 0; j < (int)thrackles[i].edges.size(); j++){
        myfile << "(" << thrackles[i].edges[j].v1.x << "," << thrackles[i].edges[j].v1.y << " "<< thrackles[i].edges[j].v2.x << "," << thrackles[i].edges[j].v2.y << ") ";
      }
      myfile << endl;
    }
    myfile << minimal_intersection_counter;
    myfile.close();
}
void printThrackle(Thrackle t){
    cout << "Thrackle tag: " << t.tag << endl;
    cout << "Thrackle Edges:\n";
    for(unsigned int i = 0; i < t.edges.size();i++){
        printEdge(t.edges[i]);
    }
    cout << "Thrackle bool edges\n [ ";
    for(int i = 0; i < (int)t.edge_bool.size();i++){
        cout << t.edge_bool[i] << " ";
    }
    cout << "]\n";
}
void printThrackleVector(vector<Thrackle> T){
  for(int i = 0; i < (int) T.size(); i++){
    printThrackle(T[i]);
  }
}
