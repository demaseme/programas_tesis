#include "../include/thrackle.h"

void load_bool_thrackles();
bool intersection_optimal();
void print_bool_thrackles();

std::vector<std::vector<bool>> T;
std::vector<int> current_decomp;
int n,ot_g;
string text_file;
/*
  Lee un archivo de texto donde cada una de los renglones
  es una descomposición en thrackles máximos.
  Los carga a memoria y verifica su intersección.
*/
int main(int argc, char* argv[]){
  if (argc < 4){
    fprintf(stderr, "Usage ./exec <n> <order_type> <text_file>\n");
    exit(-1);
  }
  n = atoi(argv[1]);
  ot_g = atoi(argv[2]);
  text_file = argv[3];
  ifstream file;
  string str;
  // printf("%s\n",text_file.c_str());
  file.open(text_file.c_str());
  if (!file){
    fprintf(stderr, "Error opening file %s\n", text_file.c_str() );
    exit(-1);
  }
  while(getline(file,str)){
    istringstream S(str);
    current_decomp.clear();
    int c;
    while (S >> c){
      current_decomp.push_back(c);
    }
    load_bool_thrackles();
    print_bool_thrackles();
    if (intersection_optimal()){
      printf("Intersection is optimal\n");
      print_bool_thrackles();
    } else{
      printf("Intersection is not optimal\n");
    }
    T.clear();
  }

  return 0;
}
/* Prints T. */
void print_bool_thrackles(){
  for (auto i = T.begin(); i != T.end(); i++){
    for( auto j = (i)->begin(); j != (i)->end(); j++){
      cout << *j <<" ";
    }
    cout << "\n" ;
  }
  cout << endl;
}
/*
  Recibe una vector de enteros y carga a memoria (en un vector de vectores)
  el vector booleano de cada thrackle cuya etiqueta
  es uno de los enteros del vector.
*/
void load_bool_thrackles(){
  string file_name;
  file_name = "ths/"+to_string(n)+"_"+to_string(n)+"_All_bool.ths";
  ifstream myfile;
  vector<bool> thrackle_bool;
  myfile.open(file_name, ios::binary);
  myfile.seekg(0,myfile.beg);
  if(!myfile.is_open()) {
    fprintf(stderr, "%s\n", "Error loading thrackle boolean file\n");
    exit(-1);
  }
  int eater = 0;
  int current_ot = 0;
  int desired_ot = ot_g;
  int cols = n*(n-1)/2;
  int c,i,j;
  while(current_ot != desired_ot){
    //cout << current_ot << endl;
    myfile.read( (char*)&eater,sizeof(uint16_t));//ot
    myfile.read( (char*)&eater,sizeof(uint16_t)); //number_of_t
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
  myfile.read( (char*)&eater,sizeof(uint16_t));//ot
  myfile.read( (char*)&eater,sizeof(uint16_t)); //number_of_t
  int current_thr = 0;

  for(auto it = current_decomp.crbegin(); it != current_decomp.crend(); it ++){
    int desired_thr = *it;
    while ( desired_thr != current_thr ){
      for( int j = 0 ; j < n*(n-1)/2; j++){
        myfile.read( (char*)&eater,sizeof(char)); //boolean
      }
      current_thr++;
    }
    //printf("Loading thrackle %d | %d\n",current_thr, desired_thr);
    for( int j = 0 ; j < n*(n-1)/2; j++){
      myfile.read( (char*)&eater,sizeof(char)); //boolean
      thrackle_bool.push_back(eater);
    }

    T.push_back(thrackle_bool);
    thrackle_bool.clear();
    current_thr++;
  }
  //printf("\n");
  myfile.close();
}
/*
  Entrega verdadero si la intersección entre los thrackles de T
  es óptima y falso en otro caso.
*/
bool intersection_optimal(){
  vector<bool> res;
  int tamano = n*(n-1)/2;
  int cuenta;
  for(int i = 0; i < (int)T.size(); i ++){
    cuenta = 0;
    for( int j = i+1; j < (int) T.size(); j++){
      for ( int m = 0; m < tamano ; m++) res.push_back(true);
      for(int k = 0; k < tamano; k++){
        res[k] = res[k] && ( T[i][k] && T[j][k]);
        if(res[k]) cuenta++;
        if (cuenta > 1) return false;
      }
      res.clear();
    }

  }

  return true;
}
