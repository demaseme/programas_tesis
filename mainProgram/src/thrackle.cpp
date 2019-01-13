#include "thrackle.h"

float alto;
float ancho; //Used by opengl

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
void k_Combination(vector<Edge> arr, int r, vector<vector<Edge>> & combinations,
   int & counter, int & thrackleCounter, vector<Thrackle> & foundThrackles){
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
void edge_set_intersection(vector<Edge> A, vector<Edge> B, vector<Edge> & C){
  for(unsigned int i = 0; i < A.size(); i++){
    if( edge_in(A[i],B) ) C.push_back(A[i]);
  }
}
//Performs the intersection of thracklese A and B,
//Stores teh result in vector of edges result
void thrackle_intersection(Thrackle A, Thrackle B, vector<Edge> & result){
  edge_set_intersection(A.edges,B.edges,result);
}
void minimal_thrackle_intersection(vector<Thrackle> thrackles){
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
  cout << "Smaller intersection size is : " << minimal << endl;
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

void reshape_cb (int w, int h) {
  	if (w==0||h==0) return;
  	glViewport(0,0,w,h);
  	glMatrixMode (GL_PROJECTION);
  	glLoadIdentity ();
  	gluOrtho2D(0,w,0,h);
  	glMatrixMode (GL_MODELVIEW);
  	glLoadIdentity ();
  }

void dibuja(){
  int i;
	glClear(GL_COLOR_BUFFER_BIT);
}

void procesa_puntos(vector<vector<Point>> points){

}
//Draws thrackles using opengl
void drawThrackles(vector<Thrackle> thrackles, vector<vector<Point>> points){


  alto = glutGet(GLUT_SCREEN_HEIGHT) * .8;
	ancho = glutGet(GLUT_SCREEN_WIDTH) * .6;
  procesa_puntos(points);
  glutInitDisplayMode (GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize (ancho,alto);
	glutInitWindowPosition (100,100);
	glutCreateWindow ("Thrackles");
	// glutKeyboardFunc(keyboard);
	// glutSpecialFunc (special);
	glutDisplayFunc (dibuja);
	glutReshapeFunc (reshape_cb);
	glClearColor(1.f,1.f,1.f,1.f);
  dibuja();
  glutMainLoop();
}

//Writes thrackle information to a text file, this procedure needs all thrackles to be of the same size.
void writeThrackles(vector<Thrackle> thrackles, int set_size, int thrackle_size, int ot_number){
    ofstream myfile;
    string file_name = "ths/" + to_string(set_size) + "_" + to_string(ot_number) + "_" + to_string(thrackle_size) + ".ths";
    myfile.open(file_name);
    myfile << set_size << " #set size\n";
    myfile << ot_number << " #ot number\n";
    myfile << thrackle_size << " #thrackle size\n";
    myfile << thrackles.size() <<" #number of thrackles\n";
    for(auto i = 0; i < (int)thrackles.size() ; i++){
      for(auto j = 0; j < (int)thrackles[i].edges.size(); j++){
        myfile << "(" << thrackles[i].edges[j].v1.x << "," << thrackles[i].edges[j].v1.y << " "<< thrackles[i].edges[j].v2.x << "," << thrackles[i].edges[j].v2.y << ") ";
      }
      myfile << endl;
    }
    myfile.close();
}
void printThrackle(Thrackle t){
    for(unsigned int i = 0; i < t.edges.size();i++){
        printEdge(t.edges[i]);
    }
}
