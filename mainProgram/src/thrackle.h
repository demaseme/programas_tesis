#ifndef THRACKLE_H
#define THRACKLE_H

#include "point.h"
//Thrackle object. A collection of edges.
//An edge is a pair of Point objects.
//Each element of edges is a vector of size 2.
class Thrackle{
public:
    vector<Edge> edges;
};

// Edge operations (line segment operations)

//Returns true if line segments e_1 and e_2 cross.
bool crossing(Edge e_1, Edge e_2);
//Returns true if line segments e_1 and e_2 share an endpoint.
bool share_ep(Edge e_1, Edge e_2);
//Thrackle operations.

//Finds all thrackles of size k, this is thrackles with k edges
//stores it on vector of Thrackle objects thrackles
void findThrackle(unsigned int k, vector<Point> points, vector<Thrackle> & thrackles);
//Returns true if the collection of edges 'edges' is a thackle and false otherwise.
bool isThrackle(vector<Edge> edges);

void k_Combination(vector<Edge> arr, int r, vector<vector<Edge>> & combinations, int & counter, int & thrackleCounter);
void combinationUtil(vector<Edge> arr, int r,int index, vector<Edge> data, int i,vector<vector<Edge>> & combinations,
  int & counter, int & thrackleCounter);

void printThrackle(Thrackle t);
#endif
