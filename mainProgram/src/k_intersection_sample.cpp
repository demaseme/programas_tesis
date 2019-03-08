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
void fill_found_thrackles_info(int);
void find_thrackles(int );
void copy_points();
void clear_vectors();
void q_intersection_size(int q,float & , float & , int &);
void read_file(int, char* argv[]);
void write_results(int ot, int set_size, int subset_size, int no_exp,int total_cov,int total_repeat, int max_cov);
void write_results_all(ofstream & myfile, int ot, int subset_size,int total_cov,int total_repeat, int max_cov);
void ready_dat_file(ofstream &myfile, int ot, int number_of_diff_subsets );
void read_results(string file_name);
int load_thrackles(int set_size, int t_size,int desired_ot);

int main(int argc, char* argv[]) {
    one_ot_flag = false;
    read_file(argc,argv);
    int rows = (setSize*(setSize-1.0)/2.0);
    int cols = (setSize*(setSize-1.0)/2.0);
    matrix = (int **)malloc(rows * sizeof(int*));
    for(int i = 0; i < rows; i++) matrix[i] = (int *)malloc(cols * sizeof(int));
    int convex_at =  setSize - floor(sqrt(setSize + (1/4.0)) - (1/2.0));


    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    char buffer [90];
    char directory[90];
    string strr= "ths/"+to_string(setSize)+"/intersection/";
    system( ("mkdir -p ths/" + to_string(setSize) + "/intersection/" ).c_str() );
    sprintf(directory,"ths/%d/intersection/",setSize);
    strftime (buffer,90,"results-%Y-%m-%d-%R.dat",now);
    strcat(directory,buffer);
    ofstream results_file;
    results_file.open(directory, ios::binary);
    if(results_file.fail()){
        fprintf(stderr,"Error opening results file.\n");
        return 0;
    }
    if(one_ot_flag) printf("Working with only 1 OT\n");
    while(ot_number < otypes){
        ready_dat_file(results_file,ot_number,convex_at-1);
        g_q = convex_at; //g_q is the current subset size
        load_thrackles(setSize, k,ot_number);
        while(g_q >= 2){

          // copy_points();
          // generateAllEdges(vec,edges);
          // find_thrackles(rows);
          if(thrackleCounter == 0) {
              write_results_all(results_file,ot_number,g_q,0,0,0);
              // ot_number++;
              //clear_vectors();
              g_q --;
              continue;
          }
          if(thrackleCounter < g_q ) {
            write_results_all(results_file,ot_number,g_q,0,0,0);
            // ot_number++;
            //clear_vectors();
            g_q --;
            continue;
          }
          //fill_found_thrackles_info(rows);
          int number_of_exp = 100;
          float avg_cov;
          float avg_rep;
          float total_cov = 0.0;
          float total_rep = 0.0;
          int max_cov_overall =0 ;
          int max_cov_curr = 0;
          for(int i = 0; i < number_of_exp ; i++){
            q_intersection_size(g_q,avg_cov, avg_rep, max_cov_curr);
            total_cov += avg_cov;
            total_rep += avg_rep;
            if( max_cov_curr > max_cov_overall ) max_cov_overall = max_cov_curr;
          }
          total_cov /= number_of_exp;
          total_rep /= number_of_exp;
          printf("From %d experiments: covered edges %f\nAverage repeated edges: %f\n"
          "Max union size: %d\n",number_of_exp,total_cov,total_rep,max_cov_overall);
          //clear_vectors();
          write_results_all(results_file,ot_number,g_q,floor(total_cov),floor(total_rep),max_cov_overall);
          printf("Finished OT %d\n",ot_number);
          g_q--;
        }
        ot_number++;
        printf("Next OT is : %d\n",ot_number);
        if(one_ot_flag) break;
    }
    freeMatrix(matrix,rows);
    results_file.close();
  }

int load_thrackles(int set_size, int t_size,int desired_ot){
  string file_name;
  file_name = "ths/"+to_string(set_size)+"_"+to_string(t_size)+"_All_bool.ths";
  ifstream myfile;
  int current_ot = 0;
  int i,j,c;
  int cols = set_size*(set_size-1)/2.0;
  cout << "Opening " << file_name << endl;
  myfile.open(file_name, ios::binary);
  myfile.seekg(0,myfile.beg);
  if(!myfile.is_open()) {
    fprintf(stderr, "%s\n", "Error opening thrackle boolean file\n");
    return 0;
  }
  foundThrackles.clear();
  int eater = 0;
  while(current_ot != desired_ot){
    //cout << current_ot << endl;
    myfile.read( (char*)&eater,sizeof(char));//ot
    myfile.read( (char*)&eater,sizeof(char)); //number_of_t
    c = eater;
    for(i = 0; i < c; i++){
      for ( j = 0 ; j < cols ; j++){
        myfile.read( (char*)&eater,sizeof(char)); //boolean
      }
      // list of thrackles.
    }
    current_ot++;
  }
  //When we get out of this while, we're in position to read
  //the information that we actually care about.
  eater = 0;
  myfile.read( (char*)&eater,sizeof(char));//ot
  myfile.read( (char*)&eater,sizeof(char)); //number_of_t
  c = eater;
  thrackleCounter = c;
  cout << "Reading " << thrackleCounter << " thrackles\n";
  for(i = 0; i < thrackleCounter; i++){
    Thrackle tmp_thrackle;
    for ( j = 0 ; j < cols ; j++){
      myfile.read( (char*)&eater,sizeof(char)); //boolean
      tmp_thrackle.edge_bool.push_back(eater);
    }
    foundThrackles.push_back(tmp_thrackle);

  }
  myfile.close();
  return 1;
}

/*
    The results file is written in the following order:
    ot,number_of_diff_subsets,(subset_size,total_cov,total_rep,max_cov)*(depending on number of diff subsets)
    ot,number_of_diff_subsets,(subset_size,total_cov,total_rep,max_cov)*(depending on number of diff subsets)
    ot,number_of_diff_subsets,(subset_size,total_cov,total_rep,max_cov)*(depending on number of diff subsets)
    ...
    for every ot.
    all in binary format, all in char size. The ot with unsufficent maximal thrackles are still written with 0 0 0 inforrmation
    on the totalcov,total_rep,maxcov fields
*/

/*
    Writes in dat file the ot and the number of subsets.
*/
void ready_dat_file(ofstream &myfile, int ot, int number_of_diff_subsets ){
    myfile.write( (char*) & ot, sizeof(char));
    myfile.write( (char*) & number_of_diff_subsets, sizeof(char));
  }
  /*
    Writes in dat file subset_size,total-cov,total_rev,max_cov on binary char.
  */
  void write_results_all(ofstream & myfile, int ot, int subset_size,int total_cov,int total_repeat, int max_cov){

      myfile.write( (char*) & subset_size, sizeof(char));
      myfile.write( (char*) & total_cov, sizeof(char));
      myfile.write( (char*) & total_repeat, sizeof(char));
      myfile.write( (char*) & max_cov, sizeof(char));
  }
  void write_results(int ot, int set_size, int subset_size, int no_exp,int total_cov,int total_repeat, int max_cov){
    ofstream myfile;
    string file_name = "ths/" + to_string(set_size) + "/intersection/" + to_string(ot) + "_" + to_string(subset_size) + "_" + to_string(no_exp)+".dat";
    system( (("mkdir -p ths/" + to_string(set_size)) + "/intersection/").c_str());
    myfile.open(file_name, ios::out | ios::binary);
    myfile.write( (char*) & no_exp, sizeof(char));
    myfile.write( (char*) & total_cov, sizeof(char));
    myfile.write( (char*) & total_repeat, sizeof(char));
    myfile.write( (char*) & max_cov, sizeof(char));
    myfile.close();
  }
void q_intersection_size(int q,float & avg_cov, float & avg_rep, int & max_cov){
  //Select p q-sets of thrackles.
  int p = (int)foundThrackles.size()/2.0;
  if ( (int) foundThrackles.size() < 4) p = 2;
  if (p<2) return;
  int p_bk = p;
  float avg_covered = 0.0;
  float avg_repeated = 0.0;
  int max_covered = 0;
  vector<Thrackle> local_foundT = foundThrackles;
  //printf("Choosing %d %d-sets\n",p,q);
  //To emulate the selection, we shuffle the found thrackles vector
  //and select the first k items
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  //printf("Total of edges selected: %d\n",q*k);
  while ( p > 0 ){

    shuffle(local_foundT.begin(),local_foundT.end(),default_random_engine(seed));
    //For each set q, do the union, and contrast with the sum of edges.
    vector<bool> res(false,k);
    int union_size = 0;
    //for(int i = 0; i < q; i++) printf(" Thrackle %d\n",local_foundT[i].tag);
    for(int i = 0; i < q - 1 ; i++){
      bool_thrackle_union(local_foundT[i],local_foundT[i+1],res);
    }
    for(auto i=0; i < k; i++) {
      if(res[i]) union_size++;
    }
    //printf("This set union' size : %d\n",union_size);
    avg_covered += union_size;
    avg_repeated += (q*k)-union_size;
    if(max_covered < union_size) max_covered = union_size;
    //printf("Repeated edges amongst these thrackles: %d\n", q*k - union_size);
    //printf("---------------\n");
    p--;
  }
  //printf("Average covered edges : %f\nAverage repeated edges: %f\n",avg_covered/p_bk,avg_repeated/p_bk);
  avg_cov = avg_covered/p_bk;
  //cout << avg_repeated << endl;
  avg_rep = avg_repeated/p_bk;
  max_cov = max_covered;
  //the intersection size is k*n - size of union.

}


void clear_vectors(){
  vec.clear();
  edges.clear();
  foundThrackles.clear();
  positions.clear();
}
void fill_found_thrackles_info(int rows){
  int i,j,m;
  // foundThrackles.resize(positions.size());
  // Thrackle *t_ptr = &foundThrackles[0];
  //#pragma omp parallel for private(j,k)
  for(i = 0; i < (int)positions.size(); i++) {
     vector<Edge> foundEdges;
     Thrackle tmp_thrackle;
     tmp_thrackle.tag = i;
     for(  j = 0 ; j < (int) rows ; j ++){
         tmp_thrackle.edge_bool.push_back(false);
     }
     for(  m = 0 ; m < (int)positions[i].size() ;m ++){
         //printf("Thread number %d i:%d, j:%d \n",omp_get_thread_num(),i,k);
         foundEdges.push_back(edges[positions[i][m]]);
         tmp_thrackle.edges=foundEdges;
         tmp_thrackle.edge_bool[positions[i][m]] = true;
     }
     //t_ptr[i]=(tmp_thrackle);
     foundThrackles.push_back(tmp_thrackle);
     foundEdges.clear();
     tmp_thrackle.edge_bool.clear();
  }
}
void find_thrackles(int rows){
  thrackleCounter = 0;
  construct_disjointness_matrix(edges,matrix,rows,false);
  thrackleCounter=get_kthrackles_of_matrix(matrix,rows,k,positions);
  cout << "There are " << thrackleCounter << " thrackles of size " << k << endl;
}
void copy_points(){
  //vec.resize(setSize);
  cout << "Copying points\n";
  // copy(begin(*vPoints)+(setSize*ot_number),begin(vPoints)+( (setSize*ot_number) + setSize ),vec.begin());
  for(int i = setSize*ot_number; i < (setSize*ot_number) + setSize ; i++){
      vec.push_back(vPoints[i]);
      //cout << vPoints[i].x << " " << vPoints[i].y << endl;
  }

}
void read_file(int argc, char* argv[]){
  while ((opt = getopt(argc, argv, "dt:")) != -1) {
    switch(opt){
      case 'd':
        //We want to draw! Set drawing flag to true.
        //draw_flag = true;
        break;
      case 't':
        //Exactly 1 order type.
        ot_number = atoi(optarg);
        one_ot_flag = true;
        break;
      default: /* '?' */
            fprintf(stderr, "Usage: %s [-t order_type_number] set_size thrackle_size \n",
                    argv[0]);
            exit(EXIT_FAILURE);
    }
  }
  if (optind+1 >= argc) {
       fprintf(stderr, "Expected argument after options\n");
       exit(EXIT_FAILURE);
   }
   setSize = atoi(argv[optind]);
   optind++;
   k = atoi(argv[optind]);
   // optind++;
   // g_q = atoi(argv[optind]);

  switch(setSize){
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
  npuntos = otypes*setSize;
  vPoints = (Point*)malloc(sizeof(Point)*npuntos);
  if(!readPoints_bin2(setSize,otfile_str,vPoints,otypes,npuntos)){
      fprintf(stderr,"Error de lectura\n");
      exit(-1);
  }
  cout << "Finished reading point file\n";
}
