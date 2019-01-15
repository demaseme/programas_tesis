#include "thrackle_drawer.h"

int ancho,alto;
vector<Point> points;
vector<Edge> edges;
vector<Thrackle> thrackles;
int ot;
int thrackle_size;
int number_thrackles;

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
void initialize_opengl(){
	glutInitDisplayMode (GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize (ancho,alto);
	glutInitWindowPosition (100,100);
	glutCreateWindow ("Thrackles");
	// glutKeyboardFunc(keyboard);
	// glutSpecialFunc (special);
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
	glLineWidth(.2);
	gl2psLineWidth(1);
    if(number_thrackles>0){
        //Draw the first thrackle.
        for(i=0; i < (int) thrackles[0].edges.size();i++){ //for each edge of it.
                glBegin(GL_LINE_STRIP); //Draw edge
                glVertex2i(thrackles[0].edges[i].v1.x,thrackles[0].edges[i].v1.y);
                glVertex2i(thrackles[0].edges[i].v2.x,thrackles[0].edges[i].v2.y);
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
    string file_name(argv[1]);
    process_file(file_name);
    draw();
    glutMainLoop();
	return 0;

}
