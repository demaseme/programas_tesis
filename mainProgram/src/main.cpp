#include "thrackle.h"

int main() {
    vector<Point> vPoints;
    int k;  //Thrackle size we're looking for
    int otypes; //Number of order types for a file
    string otfile_str;
    k = 6;
    //Read from console
    setSize = 6; //Actual number of points on set
    switch(setSize){
      case 3:
        otfile_str = "../../OT/otypes06.b08"; otypes = 1; break;
      case 4:
        otfile_str = "../../OT/otypes06.b08"; otypes = 2; break;
      case 5:
        otfile_str = "../../OT/otypes06.b08"; otypes = 3; break;
      case 6:
        otfile_str = "../../OT/otypes06.b08"; otypes = 16; break;
      case 7:
        otfile_str = "../../OT/otypes07.b08"; otypes = 135; break;
      case 8:
        otfile_str = "../../OT/otypes08.b08"; otypes = 3315; break;
      case 9:
        otfile_str = "../../OT/otypes09.b16"; otypes = 158817; break;
      case 10:
        otfile_str = "../../OT/otypes10.b16"; otypes = 14309547; break;
    }

    if(readPoints(setSize,otfile_str,vPoints) == 1){
        fprintf(stderr,"Error de lectura\n");
        exit(-1);
    }

    //If a given order type is specified, process only that one.
    //Otherwise, process all order types of a file.
    int ot_number; // starting from 0.
    int counter,thrackleCounter;
    vector<Point> vec; //Here we store the points that will be read.
    vector<Edge> edges; //Here we store the (n take 2) edges of the complete graph
    vector<vector<Edge>> combinations; //Here we store the combinations of edges depending on k.
    vector<Thrackle> foundThrackles; //Here we store the thrackles of size k.
    //Select the points of the current order type.
    while(ot_number < otypes){
      vec.resize(setSize);
      copy(vPoints.begin()+(setSize*ot_number),vPoints.begin()+( (setSize*ot_number) + setSize ),vec.begin());
      generateAllEdges(vec,edges);

      counter = 0;
      thrackleCounter = 0;

      std::chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

      k_Combination(edges,k,combinations,counter,thrackleCounter,foundThrackles);
      printf("There are %d combinations of size %d\nFrom which %d are thrackles (%1.8f)\n",
      counter,k,thrackleCounter,(float)thrackleCounter/counter);

      std::chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
      chrono::duration<double, std::milli> time_span = t2 - t1;
      cout << "It took me " << time_span.count() << " milliseconds.";
      cout << std::endl;

      vector<Edge> union_of_edges;
      if (covers(foundThrackles,edges)){
        cout << "Found thrackles cover the whole edge set\n";
      } else {
        cout << "Found thrackles DO NOT cover the whole edge set\n";
      }

      minimal_thrackle_intersection(foundThrackles);

      //Write found thrackles on text file.
      writeThrackles(foundThrackles,setSize,k,ot_number);

      //Clear all that.
      vec.clear();
      edges.clear();
      combinations.clear();
      foundThrackles.clear();
      cout << "=====Finished workign with order type " << ot_number << "=====" << endl;
      ot_number++;

    }
    return 0;
}
