#include "../include/disjointness.h"

void write_max_thrackle_count(const vector<int> count,const vector<int> otlist, const vector<int> min_inter,
vector<bool> union_covers_bool, int n, int k){
  ofstream myfile;
  string filename = "K_" + to_string(n) + "_" + to_string(k) + "_statistics.dat";
  myfile.open(filename);
  myfile << "#OT    #Max_Thr_Count   #minimal_intersection    #union_covers?\n";
  for(int i = 0; i < (int) count.size(); i++){
    //cout << i << "\t\t" << count[i] << endl;
    myfile << otlist[i] << "\t\t" << count[i] << "\t\t" << min_inter[i] << "\t\t" << union_covers_bool[i] << endl;
  }
  myfile.close();
  cout << "write max th coutn \n";
}
//From console the parameters will be
//set_size thrackle_size draw? ot_number
//./main 6 6 -d -ot 5
int main(int argc, char* argv[]) {
    int opt;
    int ot_number = 0; // starting from 0.
    //bool draw_flag;
    bool one_ot_flag;
    vector<Point> vPoints;
    int k;  //Thrackle size we're looking for
    int otypes; //Number of order types for a file
    string otfile_str;
    int minimal_intersection_counter;
    vector<int> otlist;
    int ** matrix; //matrix to store the disjointness matrix.

    //draw_flag = false;
    one_ot_flag = false;

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
              fprintf(stderr, "Usage: %s [-t order_type_number] [-d to draw] set_size thrackle_size\n",
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
     //Read from console
      //Actual number of points on set
    // printf("name argument = %s\n", argv[optind++]);
    // printf("name argument = %s\n", argv[optind]);


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

    //This will fail for last ot, too many points. Must read one OT at once.
    // if(readPoints(setSize,otfile_str,vPoints) == 1){
    //     fprintf(stderr,"Error de lectura\n");
    //     exit(-1);
    // }

    if(!readPoints_bin(setSize,otfile_str,vPoints,otypes)){
        fprintf(stderr,"Error de lectura\n");
        exit(-1);
    }
    cout << "Finished reading point file\n";
    //###############ALLOCATING MATRIX ####################
    //At this point we can initialize the matrix, for we know it'll have n take 2 rows and cols.
    //Allocate matrix.
    int rows = (setSize*(setSize-1.0)/2.0);
    int cols = (setSize*(setSize-1.0)/2.0);
    cout << "There will be " << rows << " rows\n";

    matrix = (int **)malloc(rows * sizeof(int*));
    for(int i = 0; i < rows; i++) matrix[i] = (int *)malloc(cols * sizeof(int));

    /*##########################################*/
    int thrackleCounter;
    //long counter;
    vector<Point> vec; //Here we store the points that will be read.
    vector<Edge> edges; //Here we store the (n take 2) edges of the complete graph
    vector<vector<Edge>> combinations; //Here we store the combinations of edges depending on k.
    vector<Thrackle> foundThrackles; //Here we store the thrackles of size k.
    vector<Thrackle> tbd_thrackles; //Thrackles to be drawn later.
    vector<vector<Point>> tbd_points; //A set of points for every thrackle to be drawn.
    vector<vector<int>> positions; // Each element of this vector, is a list of positions of edges which together are a thrackle.
    vector<int> coveredEdges;
    vector<int> nextThrackle;
    vector<int> startingThrackle;
    vector<int> min_inter;
    vector<bool> union_covers_bool;
    //bool union_covers_bool = false;
    //Edge tmp_edge;
    //Select the points of the current order type.
    vector<int> max_thrackle_count; //Vector to store how many max thrackles were found for each ot

    /*##########################################*/
    ofstream myfile,myfile_bool;
    string file_name = "ths/" + to_string(setSize) + "_" + to_string(k) +"_All" + ".ths";
    string file_name_bool = "ths/" + to_string(setSize) + "_" + to_string(k) +"_All_bool" + ".ths";
    system( "mkdir -p ths/" );
    myfile.open(file_name, ios::out | ios::binary);
    myfile_bool.open(file_name_bool, ios::out | ios::binary );
    std::chrono::high_resolution_clock::time_point totalt1 = chrono::high_resolution_clock::now();
    while(ot_number < otypes){

      otlist.push_back(ot_number);
      //cout << "Starting copy\n";
      vec.resize(setSize);
      copy(vPoints.begin()+(setSize*ot_number),vPoints.begin()+( (setSize*ot_number) + setSize ),vec.begin());
      //cout << "Copy finished\n";
      //sortPoints(vec);
      printVectorPoint(vec);

      generateAllEdges(vec,edges);
      //return 0;
      //cout << "All edges generated\n";
      //counter = 0;
      thrackleCounter = 0;
      std::chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
      //Testing disjointness matrix construction.
      //cout << "Constructing disjointness matrix\n";
      construct_disjointness_matrix(edges,matrix,rows,false);
      //return 0;
      thrackleCounter=get_kthrackles_of_matrix(matrix,rows,k,positions);
      cout << "There are " << thrackleCounter << " thrackles of size " << k << endl;
      // for(auto p = positions.begin(); p < positions.end(); ++p){
      //   printVectorInt(*p);
      // }
      int testing[] = {0,1,2,3,7,8};
      // int testing2[] = {7,9};
      vector<int> test (testing,testing+sizeof(testing)/sizeof(int));
      //  vector<int> test2 (testing2,testing2+sizeof(testing2)/sizeof(int));
      vector<int> test3;
      // cout << int_thrackle_areDifferent(test,test2); cout << endl;
      // printVectorInt(test3);
      // find_next_thrackle(matrix,cols,test,startingThrackle,4,true);
      // printVectorInt(startingThrackle);

     // cout << int_thrackle_areDifferent(test,test2); cout << endl;
      // find_next_thrackle(matrix,cols,test,test3,5,false);
      // printVectorInt(test3);
      // return 0;
      //find_next_thrackle2(matrix,test,test3,cols,false);
      //printVectorInt(test3);
      // exhaustive_at(matrix, cols, setSize, startingThrackle, 0,0);

      // cout << "Anti-thickness : " << minAt  << endl;
      // cout << "Minimal number of thrackles needed " << lowAt << endl;
      std::chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
      chrono::duration<double, std::milli> time_span = t2 - t1;
      cout << "It took me " << time_span.count() << " milliseconds.";
      cout << std::endl;
      //return 0;
      //positions is loaded. We must then get their equivalent edge objects and then turn them into thrackle objects.
      // cout << "FILLING BOOLEAN VECTOR FOR SET OPERATIONS!\n";
      /* Filling the boolean vector for in operation*/

      //
      // for(int i = 0 ; i < rows ; i ++){
      //     tmp_thrackle.edge_bool.push_back(false);
      // }

      cout << "Position size: " << positions.size() << endl;
      int i;
      foundThrackles.resize(positions.size());
      Thrackle *t_ptr = &foundThrackles[0];
      int j,k;
      //#pragma omp parallel for private(j,k)
      for(i = 0; i < (int)positions.size(); i++) {
         vector<Edge> foundEdges;
         Thrackle tmp_thrackle;
         //cout << "Processing thrackle " << i << endl;
         for(  j = 0 ; j < (int) rows ; j ++){
             tmp_thrackle.edge_bool.push_back(false);
         }
         for(  k = 0 ; k < (int)positions[i].size() ;k ++){
             foundEdges.push_back(edges[positions[i][k]]);
             tmp_thrackle.edges=foundEdges;
             tmp_thrackle.edge_bool[positions[i][k]] = true;
         }
         t_ptr[i]=(tmp_thrackle);
         foundEdges.clear();
         tmp_thrackle.edge_bool.clear();
      }

      //thrackle_real_intersection_wrt(foundThrackles, ot_number, setSize,k);

      thrackle_intersection_all(foundThrackles,minimal_intersection_counter);
      // cout << "Minimal intersection calculated!\n";
      min_inter.push_back(minimal_intersection_counter);
      if (union_covers(foundThrackles)){
      //   //cout << "Found thrackles cover the whole edge set\n";
       union_covers_bool.push_back(true);
      } else {
      //   //cout << "Found thrackles DO NOT cover the whole edge set\n";
       union_covers_bool.push_back(false);
      }
      //cout << "Union calculated!\n";

      //Count how many thrackles of size n were found for current ot.
      //Write that information into a text file.
      max_thrackle_count.push_back((int)foundThrackles.size());

      //minimal_thrackle_intersection(foundThrackles,minimal_thrackle_intersection);

      //Write found thrackles on text file.
      //writeThrackles_bin(foundThrackles,vec,setSize,k,ot_number,minimal_intersection_counter);
      writeOne4All_bin(myfile, foundThrackles,vec,setSize,k,ot_number, minimal_intersection_counter );
      writeOne4All_bin_bool( myfile_bool, foundThrackles,k,ot_number );
      //cout << "Writing finished!\n";
      //Clear all that.
      vec.clear();
      //cout << "Vec clear!\n";
      edges.clear();
      //cout << "edges clear!\n";
      combinations.clear();
      //cout << "combinations clear!\n";
      foundThrackles.clear();
      //cout << "foundThrackles clear!\n";
      positions.clear();
      //cout << "positions clear!\n";
      cout << "=====Finished working with order type " << ot_number << "=====" << endl;
      ot_number++;

      //If a given order type is specified, process only that one.
      //Otherwise, process all order types of a file.
      if(one_ot_flag) break;
      cout << "Starting next order type\n";
    }
    cout << "Freeing matrix!\n";
    freeMatrix(matrix,rows);
    myfile.close();
    myfile_bool.close();
    std::chrono::high_resolution_clock::time_point totalt2 = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> time_span_total = totalt2 - totalt1;
    cout << "It took me " << time_span_total.count() << " milliseconds.";
    cout << std::endl;

    //Write max thrackle count to text file
    write_max_thrackle_count(max_thrackle_count,otlist, min_inter, union_covers_bool, setSize,k);
    return 0;
}
