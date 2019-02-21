#include "../include/disjointness.h"
#include "../include/globals.h"
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include <cmath>
#include <cstring>

int g_q;
int opt;
int ot_number = 0; // starting from 0.
//bool draw_flag;
bool one_ot_flag= false;
Point *vPoints;
int k;  //Thrackle size we're looking for
int otypes; //Number of order types for a file
int npuntos;
string otfile_str;
vector<int> otlist;
int ** matrix; //matrix to store the disjointness matrix.
int thrackleCounter;
vector<Point> vec; //Here we store the points that will be read.
vector<Edge> edges; //Here we store the (n take 2) edges of the complete graph
vector<Thrackle> foundThrackles; //Here we store the thrackles of size k.
vector<vector<int>> positions; // Each element of this vector, is a list of positions of edges which together are a thrackle.

int main(int argc, char* argv[){

}

void read_results(string file-name){

}
