#include "thrackle_drawer.h"

int ancho,alto;
vector<Point> points;
vector<Edge> edges;
vector<Thrackle> thrackles;
uint16_t ot;
uint16_t desired_ot_g;
uint16_t thrackle_size;
uint16_t number_thrackles;
uint16_t current_thrackle;
string file_name;

int process_file_bin(string filename, int desired_ot){
  ifstream myfile;
  int current_ot = -1;
  uint16_t character;
  streampos size;
  uint16_t set_size ;
  uint16_t a,b,x,y;
  int i,j;
  int xmax,xmin,ymax,ymin,ancho_otype,alto_otype;
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
    while (current_ot != (desired_ot - 1) ) {
      //We look for the desired ot.
      myfile.read((char*) &character, sizeof(uint16_t));
      //myfile.read((char*) &character, sizeof(uint16_t));
      // cout << character << endl;
      if ( character == 0xFF ) {
        current_ot++;
        cout << "End of OT REACHED\n";
        continue;
      }
      if ( myfile.eof() ) {
        cout << "EOF\n";
        myfile.seekg(0,ios::beg);
        current_ot = -1;
        return 0; //false
        //break;
      }
    }
    cout << "We arrived at desired OT " << desired_ot << " " << current_ot << endl;
    myfile.read((char*) & set_size, sizeof(uint16_t)); //First line is size char.
    cout << "Set size : " << set_size << endl;
    //Read Points.
    points.clear();
    for(i = 0; i < set_size; i++){
      myfile.read((char*) & pointa.x, sizeof(uint16_t));
      myfile.read((char*) & pointa.y, sizeof(uint16_t));
      points.push_back(pointa);
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

    myfile.read((char*) &ot,sizeof(uint16_t));
    myfile.read((char*) &thrackle_size,sizeof(uint16_t));
    myfile.read((char*) &number_thrackles,sizeof(uint16_t));
    cout << "Working with OT " << ot <<endl;
    cout << "Working with thrackle size  " << thrackle_size <<endl;
    cout << "Working with number_thrackles  " << number_thrackles <<endl;

    for( i = 0 ; i < number_thrackles; i++){
      for(j = 0; j < thrackle_size ; j++){
        myfile.read((char*) & pointa.x, sizeof(uint16_t));
        myfile.read((char*) & pointa.y, sizeof(uint16_t));
        myfile.read((char*) & pointb.x, sizeof(uint16_t));
        myfile.read((char*) & pointb.y, sizeof(uint16_t));
        if(flag){
          pointa.x = (((pointa.x - xmin) * (alto - 30))/alto_otype) + 10;
          pointa.y = (((pointa.y - ymin) * (alto - 30))/alto_otype) + 10;

          pointb.x = (((pointb.x - xmin) * (alto - 30))/alto_otype) + 10;
          pointb.y = (((pointb.y - ymin) * (alto - 30))/alto_otype) + 10;
        }else {
          pointa.x = (((pointa.x - xmin) * (alto - 30))/ancho_otype) + 10;
          pointa.y = (((pointa.y - ymin) * (alto - 30))/ancho_otype) + 10;

          pointb.x = (((pointb.x - xmin) * (alto - 30))/ancho_otype) + 10;
          pointb.y = (((pointb.y - ymin) * (alto - 30))/ancho_otype) + 10;
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
        if(current_thrackle < number_thrackles - 1){
            current_thrackle++;
        } else{
            current_thrackle = 0;
        }
        draw();
        //cout << "Right arrow \n";
    }
    else if(key == GLUT_KEY_LEFT){
        if(current_thrackle > 0 ){
            current_thrackle--;
        } else {
            current_thrackle = number_thrackles - 1 ;
        }
        cout << current_thrackle << endl;
        draw();
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

//This programs takes a .ths file as argument
//Draws its information using OpenGL.
int main(int argc, char* argv[]){
    if(argc == 1){
        fprintf(stderr, "Usage: %s <.ths file>\n",argv[0]);
        exit(-1);
    }

    glutInit(&argc, argv);
    alto = glutGet(GLUT_SCREEN_HEIGHT) * .8;
    ancho = glutGet(GLUT_SCREEN_WIDTH) * .6;
    initialize_opengl();
    file_name = argv[1];
    desired_ot_g = 0;
    process_file_bin(file_name,desired_ot_g);
    //process_file(file_name);
    draw();
    glutMainLoop();
	return 0;

}
