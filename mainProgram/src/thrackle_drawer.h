#ifndef THRACKLE_DRAWER
#define THRACKLE_DRAWER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <GL/glut.h>
#include "gl2ps.h"
#include <sstream>
#include "thrackle.h"

int process_file_bin(string filename, int desired_ot);
void reshape_cb (int w, int h);
void draw();
#endif
