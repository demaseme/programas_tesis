#include "../include/decomposition.h"

int countPointsInside(Point points[],int n, int ot );
int loadPoints(int n, int ot, Point points[]);

int main(int argc, char * argv[]){
    vector<Point> vP;
    vector<Point> vec;
    int n = atoi(argv[1]);
    string otfile_str;
    int otypes, points_inside;
    int ot;
    switch(n){
      case 3:
        otfile_str = "../../OT/otypes03.b08"; otypes = 1; break;
      case 4:
        otfile_str = "../../OT/otypes04.b08"; otypes = 2; break;
      case 5:
        otfile_str = "../../OT/otypes05.b08"; otypes = 3; break;
      case 6:
        otfile_str = "../../OT/otypes06.b08"; otypes = 16; break;
      case 7:
        otfile_str = "../../OT/otypes07.b08"; otypes = 135; break;
      case 8:
        otfile_str = "../../OT/otypes08.b08"; otypes = 3315; break;
      case 9:
        otfile_str = "../../OT/otypes09.b16"; otypes = 158817; break;
      case 10:
        otfile_str = "../../OT/otypes10.b16"; otypes = 14309547; break;
      default:
        fprintf(stderr,"No existe base de datos para n>10\n"); exit(-1);
    }
    //Load points into array.
    if(!readPoints_bin(setSize,otfile_str,vPoints,otypes)){
        fprintf(stderr,"Error de lectura %s\n", otfile_str);
        exit(-1);
    }
    cout << "Finished reading point file\n";
    string info_file_str = to_string(n) + "_points_inside.dat";
    ofstream info_file;

    while (ot < otypes){
        vec.resize(setSize);
        copy(vP.begin()+(n*ot),vP.begin()+( (n*ot) + n ),vec.begin());
        //Count points inside.
        points_inside = pointsInsideConvex(vec);
        //Write information on first file.
        write_points_inside_info(info_file, ot, points_inside);
        //Process the file to output second file using sort and awk
        vec.clear();
        ot ++;
    }
    return 1;
}

/*
    Slower than reading all points into
    memory then save it into smaller vector for each ot.
*/
int loadPoints(int n, int desired_ot, Point points[]){
    string otfile_str;
    ifstream bin_file;
    int eater,i;
    int ot = 0;
    if (n < 9 ) otfile_str = "../../OT/otypes0"+to_string(n)+".b08";
    if (n == 9) otfile_str = "../../OT/otypes09.b16";
    if (n == 10) otfile_str = "../../OT/otypes10.b16";
    bin_file.open(otfile_str, ios::binary);
    if ( bin_file.good() ){
        fprintf(stderr,"Error opening file %s\n",otfile_str);
        exit(-1);
    }
    if ( n < 9 ) read_size = sizeof(char);
    if ( n >= 9) read_size = sizeof(uint16_t);
    while( ot != desired_ot ){
        for ( i = 0; i < n ; i++ ) {
            bin_file.read( (char*) &eater, read_size);
            bin_file.read( (char*) &eater, read_size);
        }
        ot ++;
    }
    for ( i = 0; i < n ; i++ ) {
        bin_file.read( (char*) &eater, read_size);
        points[i].x = eater;
        bin_file.read( (char*) &eater, read_size);
        points[i].y = eater;
    }

}
