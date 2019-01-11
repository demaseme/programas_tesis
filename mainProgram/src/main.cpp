#include "thrackle.h"

int main() {
    vector<Point> vPoints;
    int k;
    k = 6;
    if(readPoints(k,"../../OT/otypes06.b08",vPoints) == 1){
        fprintf(stderr,"Error de lectura\n");
        exit(-1);
    }
    //printPoints(vPoints);
    //Select first 6 points
    vector<Point> vec;
    vec.resize(k);
    copy(vPoints.begin()+0,vPoints.begin()+k,vec.begin());
    printVectorPoint(vec);
    if (isConvex(vec)){
        printf("Points are in convex position.\n");
    } else {
        printf("Points are NOT in convex position.\n");
    }

    vector<Edge> edges;
    generateAllEdges(vec,edges);
    vector<vector<Edge>> combinations;
    vector<Thrackle> foundThrackles;

    int counter,thrackleCounter;
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

    return 0;
}
