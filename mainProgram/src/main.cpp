#include "thrackle.h"

int main() {
    vector<Point> vPoints;
    if(readPoints(5,"../../OT/otypes05.b08",vPoints) == 1){
        fprintf(stderr,"Error de lectura\n");
        exit(-1);
    }
    //printPoints(vPoints);
    //Select first 6 points
    vector<Point> vec;
    vec.resize(5);
    copy(vPoints.begin()+5,vPoints.begin()+10,vec.begin());
    printVectorPoint(vec);
    if (isConvex(vec)){
        printf("Points are in convex position.\n");
    } else {
        printf("Points are NOT in convex position.\n");
    }

    //TESTING IF THRACKLE DETECTION WORKS
    //TESTING IF CYCLE DETECTION WORKS
    // vector<Edge> thrackleSecure;
    // Edge tmp;
    // tmp.v1 = vec[0];
    // tmp.v2 = vec[2];
    // thrackleSecure.push_back(tmp);
    // tmp.v1 = vec[2];
    // tmp.v2 = vec[5];
    // thrackleSecure.push_back(tmp);
    // tmp.v1 = vec[5];
    // tmp.v2 = vec[1];
    // thrackleSecure.push_back(tmp);
    // tmp.v1 = vec[1];
    // tmp.v2 = vec[4];
    // thrackleSecure.push_back(tmp);
    // tmp.v1 = vec[4];
    // tmp.v2 = vec[0];
    // thrackleSecure.push_back(tmp);
    // if(isCycle(thrackleSecure)){
    //     printf("ES UN CICLO\n");
    //     return 0;
    // } else{
    //     printf("NO ES UN CICLO  \n");
    //     return -1;
    // }
    vector<Edge> edges;
    generateAllEdges(vec,edges);
    vector<vector<Edge>> combinations;
    int k;
    k = 5;
    int counter,thrackleCounter;
    counter = 0;
    thrackleCounter = 0;
    std::chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    k_Combination(edges,k,combinations,counter,thrackleCounter);
    printf("There are %d combinations of size %d\nFrom which %d are thrackles (%1.8f)\n",
    counter,k,thrackleCounter,(float)thrackleCounter/counter);
    std::chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> time_span = t2 - t1;
    cout << "It took me " << time_span.count() << " milliseconds.";
    cout << std::endl;

    return 0;
}
