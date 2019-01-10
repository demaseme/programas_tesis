#include "thrackle.h"

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
// The main function that prints all combinations of
// size r in arr[] of size n. This function mainly
// uses combinationUtil()
void k_Combination(vector<Edge> arr, int r, vector<vector<Edge>> & combinations, int & counter, int & thrackleCounter){
    // A temporary array to store all combination
    // one by one
    vector<Edge> data;
    data.resize(r);
    // Print all combination using temprary array 'data[]'
    combinationUtil(arr, r, 0, data, 0, combinations, counter, thrackleCounter);

}
/* arr[]  ---> Input Array
   n      ---> Size of input array
   r      ---> Size of a combination to be printed
   index  ---> Current index in data[]
   data[] ---> Temporary array to store current combination
   i      ---> index of current element in arr[]     */
void combinationUtil(vector<Edge> arr, int r,int index, vector<Edge> data, int i,vector<vector<Edge>> & combinations,
  int & counter, int & thrackleCounter){
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
          cout<< thrackleCounter << "\n";
          printThrackle(tmp_thrackle);

        }
        tmp.clear();
        return;
    }
    // When no more elements are there to put in data[]
    if (i >= n)
        return;
    // current is included, put next at next location
    data[index] = arr[i];
    combinationUtil(arr, r, index + 1, data, i + 1, combinations,counter, thrackleCounter);
    // current is excluded, replace it with next
    // (Note that i+1 is passed, but index is not
    // changed)
    combinationUtil(arr, r, index, data, i + 1,combinations, counter, thrackleCounter);

}

bool isThrackle(vector<Edge> edges){
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
void printThrackle(Thrackle t){
    for(unsigned int i = 0; i < t.edges.size();i++){
        printEdge(t.edges[i]);
    }
}
