#ifndef POINT_H
#define POINT_H

#include <stdio.h>
#include <string>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <ctime>
#include <ratio>
#include <chrono>
#include <unistd.h>
#include <GL/glut.h>
#include "gl2ps.h"
using namespace std;

extern int setSize;
class Point {
public:
    int x;
    int y;
    bool operator==(const Point q){
        return (q.x == this->x && q.y == this->y);
    }
};

class Edge {
public:
    Point v1;
    Point v2;
    int color;
    bool operator==(const Edge e){
        return  ( (this->v1 == e.v1 && this->v2 == e.v2) || (this->v1 == e.v2 && this->v2 == e.v1) );
    }
    bool operator != (const Edge e){
        return !( (this->v1 == e.v1 && this->v2 == e.v2) || (this->v1 == e.v2 && this->v2 == e.v1) );
    }
};

int orientation(Point p, Point q, Point r);
void pwrsetn(int n, vector<vector<int>> & buff );
void pwrset_edges(vector<Edge> edges,vector<vector<Edge>> & result);
void printPoints(vector<Point> v);
void printVectorInt(vector<int> v);
void printVectorPoint(vector<Point> v);
int readPoints(int n, string file_name, vector<Point> & vPoints);
bool isConvex(vector<Point> v);
void generateAllEdges(vector<Point> vPoints,vector<Edge> & vEdges);
void printEdge(Edge e);
void printEdges(vector<Edge> vE);
int findNext(vector<Edge> edges, Edge current);
bool isCycle(vector<Edge> edges);
void pwrsetk(int k, vector<Edge> input,vector<vector<Edge>> & output);

#endif
