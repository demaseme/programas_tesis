#include "thrackle.h"
//
// float alto;
// float ancho; //Used by opengl

bool share_ep(Edge e_1, Edge e_2){

    if( e_1.v1 == e_2.v1 || e_1.v1 == e_2.v2 || e_2.v1 == e_1.v2 || e_2.v2 == e_1.v2) {
        // printf("The following edges share an endpoint: \n");
        // printEdge(e_1);
        // printEdge(e_2);
        // printf("===========================\n");
    return true;
    }
    return false;
}
bool crossing(Edge e_1, Edge e_2){
  //Check if endpoints of e_2 are in different
  //semiplanes defined by e_1
  int ori1 = orientation(e_1.v1,e_1.v2,e_2.v1);
  int ori2 = orientation(e_1.v1,e_1.v2,e_2.v2);
  if (ori1 != ori2){
      // printf("The following edges cross: \n");
      // printEdge(e_1);
      // printEdge(e_2);
      // printf("===========================\n");
      return true;
  }
  return false;
}

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
*/

void findThrackles_size(const vector<Edge> edges, int k, long & comboCtr, vector<Thrackle> & foundThrackles){
    //Find the combinations of size k for a set of size edges.size();
    int n;
    n = (int) edges.size();
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
        //L5. Upadte and Return to L2.
        c[j] = c[j] + 1;
    }
}

// The main function that prints all combinations of
// size r in arr[] of size n. This function mainly
// uses combinationUtil()
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

//Returns true if edge a is in set A.
//Returns false otherwise
bool edge_in(Edge a, vector<Edge> A){
  for(auto i = A.begin(); i < A.end() ; i++) {
    if(a == *i) return true;
  }
  return false;
}

//Performs the intersection of sets of edges A and B
//Stores the result in vector C.
void edge_set_intersection(const vector<Edge> A, const vector<Edge> B, vector<Edge> & C){
  for(unsigned int i = 0; i < A.size(); i++){
    if( edge_in(A[i],B) ) C.push_back(A[i]);
  }
}
//Performs the intersection of thracklese A and B,
//Stores teh result in vector of edges result
void thrackle_intersection(const Thrackle A, const Thrackle B, vector<Edge> & result){
  edge_set_intersection(A.edges,B.edges,result);
}
void minimal_thrackle_intersection(const vector<Thrackle> thrackles,int & result){
  int minimal;
  minimal = 9999; //This value is accepted for this project max is 10.
  vector<Edge> currentIntersection;
  for(unsigned int i = 0; i < thrackles.size(); i++){
    for(unsigned int j = i+1; j < thrackles.size(); j++){
      //Compare thrackles i and j and update minimal if their intersection is
      //smaller than current minimal value.
      thrackle_intersection(thrackles[i],thrackles[j],currentIntersection);
      if( (int) currentIntersection.size() < minimal){
        minimal = currentIntersection.size();
      }
      currentIntersection.clear();
    }
  }
  result = minimal;
  //cout << "Smaller intersection size is : " << minimal << endl;
}
//Performs the union of 2 sets of edges A and B
//Stores result in A.
void edge_set_union(vector<Edge> & A,vector<Edge> B){
  for(unsigned int i = 0; i < B.size(); i++){
    if( !edge_in(B[i],A) ) {
      A.push_back(B[i]);
    }
  }
}
//Performs the union of thrackles in the vector
//Stores the result on a vector of Edge's
void thrackle_union(vector<Thrackle> thrackles, vector<Edge> & result){
  for(unsigned int i = 0 ; i < thrackles.size(); i++)
    edge_set_union(result,thrackles[i].edges);
}
//Returns true if the union of the thrackles cover the vector of edges.
//Returns false otherwise
bool covers(vector<Thrackle> thrackles,vector<Edge> edges){
  //Perform the union of the thrackles.
  //This is, a union of edges of all the thrackles
  vector<Edge> edge_union;
  thrackle_union(thrackles,edge_union);
  //Check if every element of the union is in the vector of edges
  //(or just check size [might be tricky])
  cout << "Original  edge size: " << edges.size() << endl;
  cout << "Union of edges size: " << edge_union.size() << endl;
  if (edges.size() == edge_union.size()) return true;
  return false;
}
bool isThrackle(vector<Edge> & edges){
  //If every pair of edges cross or share an endpoint, return true.
  unsigned int k = edges.size();
  for(unsigned int i = 0; i < k; i++){
      for(unsigned int j = 0; j < k; j++){
          if (!( share_ep(edges[i],edges[j]) || crossing(edges[i],edges[j]) )) return false;
      }
  }
  return true;
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
    for(unsigned int i = 0; i < t.edges.size();i++){
        printEdge(t.edges[i]);
    }
}
