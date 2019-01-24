#ifndef THRACKLE_H
#define THRACKLE_H

#include "point.h"
//Thrackle object. A collection of edges.
//An edge is a pair of Point objects.
//Each element of edges is a vector of size 2.
class Thrackle{
public:
    int set_size;
    int thrackle_size;
    int ot;
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
bool isThrackle(vector<Edge> & edges);
bool edge_in(Edge a, vector<Edge> A);
void edge_set_intersection(vector<Edge> A, vector<Edge> B, vector<Edge> & C);
void thrackle_intersection(Thrackle A, Thrackle B, vector<Edge> & result);
void minimal_thrackle_intersection(const vector<Thrackle> thrackles,int & result);
void edge_set_union(vector<Edge> & A,vector<Edge> B);
void thrackle_union(vector<Thrackle> thrackles, vector<Edge> & result);
bool covers(vector<Thrackle> thrackles,vector<Edge> edges);
void k_Combination(vector<Edge> arr, int r, vector<vector<Edge>> & combinations,
  int & counter, int & thrackleCounter, vector<Thrackle> & foundThrackles);
void combinationUtil(vector<Edge> arr, int r,int index, vector<Edge> data, int i,
  vector<vector<Edge>> & combinations, int & counter, int & thrackleCounter, vector<Thrackle> & foundThrackles);
void printThrackle(Thrackle t);
void writeThrackles(vector<Thrackle> & thrackles, vector<Point> & points, int set_size, int thrackle_size, int ot_number,
int minimal_intersection_counter );
//void drawThrackles(vector<Thrackle> thrackles, vector<vector<Point>> puntos);
void dibuja();
void procesa_puntos(vector<vector<Point>> points);
void findThrackles_size(const vector<Edge> edges, int k, long & comboCtr, vector<Thrackle> & foundThrackles);
#endif
