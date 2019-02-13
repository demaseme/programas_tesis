#include "../include/thrackle_drawer.h"

int ancho=1000,alto=800;
vector<Point> points;
vector<Edge> edges;
vector<Thrackle> thrackles;
uint16_t ot;
uint16_t desired_ot_g;
uint16_t thrackle_size;
uint16_t number_thrackles;
uint16_t current_thrackle;
uint16_t current_pair;
bool pairwise_flag;

string file_name;

void print(int x, int y, char *string){
	glRasterPos2f(x,y);

	int len = strlen(string);
	gl2psTextOpt(string, "Courier", 12, GL2PS_TEXT_BL, 0);

	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,string[i]);
	}
}

int process_file_bin(string filename, int desired_ot){
  ifstream myfile;
  int current_ot = 0;
  // uint16_t character;
  streampos size;
  uint16_t set_size ;
  uint16_t a,b,x,y;
  int i,j;
  uint16_t xmax,xmin,ymax,ymin,ancho_otype,alto_otype;
  bool flag;
  Point pointa,pointb;
  Edge tmp_edge;
  Thrackle tmp_thrackle;
  points.clear();
  edges.clear();
  thrackles.clear();
  myfile.open(filename, ios::in|ios::binary|ios::ate);

  if(myfile.is_open()){
    size = myfile.tellg();
    myfile.seekg(0,ios::beg);
    while (current_ot != (desired_ot) ) {
        //cout << "Current ot : " << current_ot << endl;
        //We read thrackle info desired_ot times.
        myfile.read( (char*) & set_size, sizeof(uint16_t));
        for(i = 0; i < set_size; i++){
          myfile.read((char*) & pointa.x, sizeof(uint16_t));
          myfile.read((char*) & pointa.y, sizeof(uint16_t));
        }
        myfile.read((char*) &ot,sizeof(uint16_t));
        myfile.read((char*) &thrackle_size,sizeof(uint16_t));
        myfile.read((char*) &number_thrackles,sizeof(uint16_t));
        for( i = 0 ; i < number_thrackles; i++){
          for(j = 0; j < thrackle_size ; j++){
            myfile.read((char*) & pointa.x, sizeof(uint16_t));
            myfile.read((char*) & pointa.y, sizeof(uint16_t));
            myfile.read((char*) & pointb.x, sizeof(uint16_t));
            myfile.read((char*) & pointb.y, sizeof(uint16_t));
          }
        }
        current_ot++;
        if (myfile.eof()) { cout << "EOT\n" ; return 0;}
    }
    //cout << "We arrived at desired OT " << desired_ot << " " << current_ot << endl;
    myfile.read((char*) & set_size, sizeof(uint16_t)); //First line is size char.
    if (myfile.eof()) { cout << "EOT\n" ; return 0;}
    //cout << "Set size : " << set_size << endl;
    //Read Points.
    points.clear();
    //cout << "Points read\n";
    for(i = 0; i < set_size; i++){
      myfile.read((char*) & pointa.x, sizeof(uint16_t));
      myfile.read((char*) & pointa.y, sizeof(uint16_t));
      points.push_back(pointa);
      //printf("%d,%d\n",pointa.x,pointa.y);
    }
    //////// ADJUST POINTS TO FIT SCREEN

    xmin = xmax = points[0].x;
    ymin = ymax = points[0].y;
    for(i = 1; i < set_size; i++){
  		if(points[i].x < xmin)
  			xmin = points[i].x;
  		else if(points[i].x > xmax)
  			xmax = points[i].x;

  		if(points[i].y < ymin)
  			ymin = points[i].y;
  		else if(points[i].y > ymax)
  			ymax = points[i].y;
	  }
    ancho_otype = (xmax-xmin);
	alto_otype = (ymax-ymin);
    //cout << "xmin, ymin, ancho, alto " << xmin << " " << ymin << " " << ancho_otype << " " << alto_otype << endl;
    if(alto_otype > ancho_otype){
      flag = true;
  		for(i = 0; i < set_size; i++){
  			points[i].x = (((points[i].x - xmin) * (alto-30))/alto_otype) + 10;
  			points[i].y = (((points[i].y - ymin) * (alto-30))/alto_otype) + 10;
  		}
      }
    else{
        flag = false;
    	for(i = 0; i < set_size; i++){
            points[i].x = (((points[i].x - xmin) * (alto-30))/ancho_otype) + 10;
            points[i].y = (((points[i].y - ymin) * (alto-30))/ancho_otype) + 10;
    	}
  	}

    myfile.read((char*) &ot,sizeof(uint16_t));
    myfile.read((char*) &thrackle_size,sizeof(uint16_t));
    myfile.read((char*) &number_thrackles,sizeof(uint16_t));
    // cout << "Working with OT " << ot <<endl;
    // cout << "Working with thrackle size  " << thrackle_size <<endl;
    // cout << "Working with number_thrackles  " << number_thrackles <<endl;

    for( i = 0 ; i < number_thrackles; i++){
      for(j = 0; j < thrackle_size ; j++){
        myfile.read((char*) & a, sizeof(uint16_t));
        myfile.read((char*) & b, sizeof(uint16_t));
        myfile.read((char*) & x, sizeof(uint16_t));
        myfile.read((char*) & y, sizeof(uint16_t));
        if(flag){
          pointa.x = (((a - xmin) * (alto - 30))/alto_otype) + 10;
          pointa.y = (((b - ymin) * (alto - 30))/alto_otype) + 10;

          pointb.x = (((x - xmin) * (alto - 30))/alto_otype) + 10;
          pointb.y = (((y - ymin) * (alto - 30))/alto_otype) + 10;
        }else {
          pointa.x = (((a - xmin) * (alto - 30))/ancho_otype) + 10;
          pointa.y = (((b - ymin) * (alto - 30))/ancho_otype) + 10;

          pointb.x = (((x - xmin) * (alto - 30))/ancho_otype) + 10;
          pointb.y = (((y - ymin) * (alto - 30))/ancho_otype) + 10;
        }
        tmp_edge.v1 = pointa;
        tmp_edge.v2 = pointb;
        edges.push_back(tmp_edge);
      }
      tmp_thrackle.edges = edges;
      thrackles.push_back(tmp_thrackle);
      edges.clear();
    }
    myfile.close();
    return 1; //true
  } else {
    fprintf(stderr, "Error reading file\n" );
    exit(-3);
  }

  myfile.close();
  return 1;
}
//Loads the vectors points and edges with information
//to be drawn later.
void process_file(string filename){
    ifstream thracklefile;
    string line;
    int set_size;
    int i;
    thracklefile.open(filename);

    getline(thracklefile,line); //store set size.
    set_size = stoi(line);

    //Store points in following line
    points.clear();
    //points.resize(set_size);
    Point tmp,tmp2;
    getline(thracklefile,line); //store the points.
    char comma;
    istringstream iss(line);
    int x,y;
    int a,b;
    while(iss >> x >> comma >> y){
        tmp.x = x;
        tmp.y = y;
        points.push_back(tmp);
        //cout << x << " " << y << endl;
    }

    //////// ADJUST POINTS TO FIT SCREEN
    int xmax,xmin,ymax,ymin,ancho_otype,alto_otype;
    xmin = xmax = points[0].x;
	ymin = ymax = points[0].y;

    for(i = 1; i < set_size; i++){
  		if(points[i].x < xmin)
  			xmin = points[i].x;
  		else if(points[i].x > xmax)
  			xmax = points[i].x;
  		if(points[i].y < ymin)
  			ymin = points[i].y;
  		else if(points[i].y > ymax)
  			ymax = points[i].y;
	}
    ancho_otype = (xmax-xmin);
	alto_otype = (ymax-ymin);
    bool flag;
    if(alto_otype > ancho_otype){
        flag = true;
		for(i = 0; i < set_size; i++){
			points[i].x = (((points[i].x - xmin) * (alto-30))/alto_otype) + 10;
			points[i].y = (((points[i].y - ymin) * (alto-30))/alto_otype) + 10;
		}
	}else{
        flag = false;
		for(i = 0; i < set_size; i++){
			points[i].x = (((points[i].x - xmin) * (alto-30))/ancho_otype) + 10;
			points[i].y = (((points[i].y - ymin) * (alto-30))/ancho_otype) + 10;
		}
	}
    ///////////////////////////////////////


    getline(thracklefile,line); //store order type;
    ot = stoi(line);
    getline(thracklefile,line); //store thrackle size;
    thrackle_size = stoi(line);
    getline(thracklefile,line); //store number of thrackles.
    number_thrackles = stoi(line);
    char openp,closep,comma2;
    Edge tmp_edge;
    Thrackle tmp_thrackle;
    for(int i = 0; i < number_thrackles;i++){
        getline(thracklefile,line); //store each thrackle information.
        istringstream iss2(line);
        while(iss2 >> openp >> a >> comma >> b >> x >> comma2 >> y >> closep){
            if(flag){
                tmp.x = (((a - xmin) * (alto - 30))/alto_otype) + 10;
                tmp.y = (((b - ymin) * (alto - 30))/alto_otype) + 10;

                tmp2.x = (((x - xmin) * (alto - 30))/alto_otype) + 10;
                tmp2.y = (((y - ymin) * (alto - 30))/alto_otype) + 10;

            }else{
                tmp.x = (((a - xmin) * (alto - 30))/ancho_otype) + 10;
                tmp.y = (((b - ymin) * (alto - 30))/ancho_otype) + 10;

                tmp2.x = (((x - xmin) * (alto - 30))/ancho_otype) + 10;
                tmp2.y = (((y - ymin) * (alto - 30))/ancho_otype) + 10;

            }
            tmp_edge.v1 = tmp; tmp_edge.v2 = tmp2;
            edges.push_back(tmp_edge);
            //cout << "pushing edge\n";
        }
        tmp_thrackle.edges = edges;
        thrackles.push_back(tmp_thrackle);

        edges.clear();
    }



}
void keyboard(unsigned char key, int x, int y){
    if (key == 39) {

    }
}
void special(int key, int x, int y){
    if(key == GLUT_KEY_RIGHT){
      if(pairwise_flag){
        if(current_pair < (number_thrackles-1)){
          current_pair++;
        } else{
          current_thrackle++;
          if ( current_thrackle >= number_thrackles) current_thrackle = 0;
          current_pair = current_thrackle + 1;

        }
        cout << "Current thrackle: " << current_thrackle << " Current pair: " << current_pair << endl;
        draw();
      }
      else{
        if(current_thrackle < number_thrackles - 1){
            current_thrackle++;
        } else{
            current_thrackle = 0;
        }
        draw();
      }
        //cout << "Right arrow \n";
    }
    else if(key == GLUT_KEY_LEFT){
      if ( pairwise_flag ){
        if ( current_pair > current_thrackle ){
          if ( (current_pair-1) == current_thrackle ) {
            if (current_thrackle == 0) {
              current_thrackle = number_thrackles - 1 ;
              current_pair = current_thrackle;
            } else {
            current_thrackle --;
            current_pair = number_thrackles -1;
          }
          } else{
            current_pair --;
          }
        }
        if (current_thrackle == number_thrackles - 1){
          current_thrackle--;
          current_pair = number_thrackles - 1;
        }

        cout << "Current thrackle: " << current_thrackle << " Current pair: " << current_pair << endl;
        draw();
      }
      else{
        if(current_thrackle > 0 ){
          current_thrackle--;
        }else{
          if (number_thrackles > 0) current_thrackle = number_thrackles - 1 ;
          current_thrackle = 0;
          }
          cout << "Current thrackle : " << current_thrackle << endl;
          draw();
      }
    }
    else if(key == GLUT_KEY_DOWN){
      desired_ot_g ++;
      if (!process_file_bin(file_name,desired_ot_g)){
        desired_ot_g = 0;
        process_file_bin(file_name,desired_ot_g);
      } ;
      draw();
    }
    else if(key == GLUT_KEY_UP){
      if(desired_ot_g == 0) return;
      desired_ot_g --;
      process_file_bin(file_name,desired_ot_g);
      draw();
    }
}
void initialize_opengl(){
	glutInitDisplayMode (GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize (ancho,alto);
	glutInitWindowPosition (100,100);
	glutCreateWindow ("Thrackles");
	glutKeyboardFunc(keyboard);
	glutSpecialFunc (special);
	glutDisplayFunc (draw);
	glutReshapeFunc (reshape_cb);
	glClearColor(1.f,1.f,1.f,1.f);
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

void draw(){
  int i;
  glClear(GL_COLOR_BUFFER_BIT);
  char thrackle_number[50] ;
  char order_type_number[10];
  char buffer[20];

  strcpy(order_type_number,"OT: ");
  cout << "desired ot g: " << desired_ot_g << endl;
  sprintf(buffer, "%d",desired_ot_g);
  strcat(order_type_number, buffer);
  print(ancho-200,alto-100,order_type_number);
  
  if( pairwise_flag ){
    glColor3f(.5,.5,.5);
    glLineWidth(3);
    gl2psLineWidth(3);
    cout << "Drawing current_thrackle: " << current_thrackle << " and current pair: " << current_pair << endl;
    if(number_thrackles>1){
      //draw the first thrackle
      for(i=0; i < (int) thrackles[current_thrackle].edges.size();i++){ //for each edge of it.
              glBegin(GL_LINE_STRIP); //Draw edge
              glVertex2i(thrackles[current_thrackle].edges[i].v1.x,thrackles[current_thrackle].edges[i].v1.y);
              glVertex2i(thrackles[current_thrackle].edges[i].v2.x,thrackles[current_thrackle].edges[i].v2.y);
              glEnd();
      }
      glColor3f(.8,.5,.2);
      glLineWidth(1);
      gl2psLineWidth(5);
      //draw the pair thrackle.
      for(i=0; i < (int) thrackles[current_pair].edges.size();i++){ //for each edge of it.
              glBegin(GL_LINE_STRIP); //Draw edge
              glVertex2i(thrackles[current_pair].edges[i].v1.x,thrackles[current_pair].edges[i].v1.y);
              glVertex2i(thrackles[current_pair].edges[i].v2.x,thrackles[current_pair].edges[i].v2.y);
              glEnd();
              //cout << i << endl;
      }

      strcpy(thrackle_number,"Thrackle ");
      sprintf(buffer, "%d", current_thrackle);
      strcat(thrackle_number, buffer);
	  strcat(thrackle_number, "+");
      sprintf(buffer, "%d", current_pair);
	  strcat(thrackle_number, buffer);
      print(ancho-200,alto-50,thrackle_number);


    }
    //Draw points.
    glColor3f(0.0, 0.0, 1.0);

    glPointSize(5);
    gl2psPointSize(10);
    glBegin(GL_POINTS);
    for(i = 0; i < (int)points.size(); i++){
      glVertex2i(points[i].x, points[i].y);
    }
    glEnd();
    glutSwapBuffers();
  } else{
	glColor3f(.5,.5,.5);
	glLineWidth(1);
	gl2psLineWidth(3);
    if(number_thrackles>0){
        //Draw the first thrackle.
        for(i=0; i < (int) thrackles[current_thrackle].edges.size();i++){ //for each edge of it.
                glBegin(GL_LINE_STRIP); //Draw edge
                glVertex2i(thrackles[current_thrackle].edges[i].v1.x,thrackles[current_thrackle].edges[i].v1.y);
                glVertex2i(thrackles[current_thrackle].edges[i].v2.x,thrackles[current_thrackle].edges[i].v2.y);
                glEnd();
        }
    }
    //Draw points.
    glColor3f(0.0, 0.0, 1.0);

	glPointSize(5);
	gl2psPointSize(10);
	glBegin(GL_POINTS);
    for(i = 0; i < (int)points.size(); i++){
		glVertex2i(points[i].x, points[i].y);
	}
    glEnd();

    glutSwapBuffers();
  }

}

//This programs takes a .ths file as argument
//Draws its information using OpenGL.
int main(int argc, char* argv[]){
    int opt;
    while (( opt = getopt(argc, argv, "p")) != -1){
      switch(opt){
        case 'p':
          pairwise_flag = true;
          break;
        // default:
        //   fprintf(stderr,"Usage %s <.ths file> [-p]",argv[0]);
        //   exit(EXIT_FAILURE);
      }
    }

    if (optind >= argc) {
         fprintf(stderr, "Expected argument after options\n");
         exit(EXIT_FAILURE);
     }


    glutInit(&argc, argv);
    alto = glutGet(GLUT_SCREEN_HEIGHT) * .8;
    ancho = glutGet(GLUT_SCREEN_WIDTH) * .6;
    initialize_opengl();
    file_name = argv[optind];

    desired_ot_g = 0;
    current_pair = 1;
    process_file_bin(file_name,desired_ot_g);
    //process_file(file_name);
    draw();
    glutMainLoop();
	return 0;

}
