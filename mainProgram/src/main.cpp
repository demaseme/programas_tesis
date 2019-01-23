#include "thrackle.h"

void write_max_thrackle_count(vector<int> count, int n){
  ofstream myfile;
  string filename = "K_" + to_string(n) + "_statistics.dat";
  myfile.open(filename);
  myfile << "#OT    #Max_Thr_Count\n";
  for(int i = 0; i < (int) count.size(); i++){
    //cout << i << "\t\t" << count[i] << endl;
    myfile << i << "\t\t" << count[i] << endl;
  }
  myfile.close();
  //cout << "write max th coutn \n";
}
//From console the parameters will be
//set_size thrackle_size draw? ot_number
//./main 6 6 -d -ot 5
int main(int argc, char* argv[]) {
    int opt;
    int ot_number = 0; // starting from 0.
    bool draw_flag;
    bool one_ot_flag;
    vector<Point> vPoints;
    int k;  //Thrackle size we're looking for
    int otypes; //Number of order types for a file
    string otfile_str;


    draw_flag = false;
    one_ot_flag = false;

    while ((opt = getopt(argc, argv, "dt:")) != -1) {
      switch(opt){
        case 'd':
          //We want to draw! Set drawing flag to true.
          draw_flag = true;
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
        otfile_str = "../../OT/otypes06.b08"; otypes = 1; break;
      case 4:
        otfile_str = "../../OT/otypes06.b08"; otypes = 2; break;
      case 5:
        otfile_str = "../../OT/otypes06.b08"; otypes = 3; break;
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

    if(readPoints(setSize,otfile_str,vPoints) == 1){
        fprintf(stderr,"Error de lectura\n");
        exit(-1);
    }
    cout << "Finished reading point file\n";
    //If a given order type is specified, process only that one.
    //Otherwise, process all order types of a file.

    int thrackleCounter;
    long counter;
    vector<Point> vec; //Here we store the points that will be read.
    vector<Edge> edges; //Here we store the (n take 2) edges of the complete graph
    vector<vector<Edge>> combinations; //Here we store the combinations of edges depending on k.
    vector<Thrackle> foundThrackles; //Here we store the thrackles of size k.
    vector<Thrackle> tbd_thrackles; //Thrackles to be drawn later.
    vector<vector<Point>> tbd_points; //A set of points for every thrackle to be drawn.
    //Select the points of the current order type.
    vector<int> max_thrackle_count; //Vector to store how many max thrackles were found for each ot

    while(ot_number < otypes){
      vec.resize(setSize);
      copy(vPoints.begin()+(setSize*ot_number),vPoints.begin()+( (setSize*ot_number) + setSize ),vec.begin());
      sortPoints(vec);
      printVectorPoint(vec);
      generateAllEdges(vec,edges);

      counter = 0;
      thrackleCounter = 0;

      std::chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
      findThrackles_size(edges,k,counter,foundThrackles);
      //k_Combination(edges,k,combinations,counter,thrackleCounter,foundThrackles);
      //printf("There are %d combinations of size %d\nFrom which %d are thrackles (%1.8f)\n",
      //counter,k,thrackleCounter,(float)thrackleCounter/counter);

      std::chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
      chrono::duration<double, std::milli> time_span = t2 - t1;
      //cout << "It took me " << time_span.count() << " milliseconds.";
      cout << std::endl;

      vector<Edge> union_of_edges;
      // if (covers(foundThrackles,edges)){
      //   cout << "Found thrackles cover the whole edge set\n";
      // } else {
      //   cout << "Found thrackles DO NOT cover the whole edge set\n";
      // }
      // //Update information on thrackles to be displayed when drawn.
      for(int i = 0; i < (int) foundThrackles.size() ; i++){
        foundThrackles[i].set_size = setSize;
        foundThrackles[i].thrackle_size = k;
        foundThrackles[i].ot = ot_number;
        //If draw_thrackles flag is on, save it to draw it later.
        if(draw_flag){
          tbd_thrackles.push_back(foundThrackles[i]);
          tbd_points.push_back(vec);
        }
      }

      //Count how many thrackles of size n were found for current ot.
      //Write that information into a text file.
      max_thrackle_count.push_back((int)foundThrackles.size());

      //minimal_thrackle_intersection(foundThrackles);

      //Write found thrackles on text file.
      writeThrackles(foundThrackles,vec,setSize,k,ot_number);

      //Clear all that.
      vec.clear();
      edges.clear();
      combinations.clear();
      foundThrackles.clear();
      cout << "=====Finished working with order type " << ot_number << "=====" << endl;
      ot_number++;
      if(one_ot_flag) break;
    }
    if(draw_flag){
      //Draw thrackles on tbd vector.
      // glutInit(&argc, argv);
      // printf("draw flag\n");
      // drawThrackles(tbd_thrackles,tbd_points);
      ;
    }
    //Write max thrackle count to text file
    write_max_thrackle_count(max_thrackle_count, setSize);
    return 0;
}
