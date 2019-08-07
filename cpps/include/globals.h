#ifndef GLOBALS_H
#define GLOBALS_H
extern int opt;
extern int ot_number; // starting from 0.
//bool draw_flag;
extern bool one_ot_flag;
extern Point *vPoints;
extern int k;  //Thrackle size we're looking for
extern int otypes; //Number of order types for a file
extern int npuntos;
extern string otfile_str;
extern vector<int> otlist;
extern int ** matrix; //matrix to store the disjointness matrix.

extern int thrackleCounter;
extern vector<Point> vec; //Here we store the points that will be read.
extern vector<Edge> edges; //Here we store the (n take 2) edges of the complete graph
extern vector<Thrackle> foundThrackles; //Here we store the thrackles of size k.
extern vector<vector<int>> positions; // Each element of this vector, is a list of positions of edges which together are a thrackle.
#endif
