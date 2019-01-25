#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
int main(){
  char str1[45];
  char str2[45];
  char str3[45];
  char str4[45];
  char str5[45];
  char str6[45];
  strcpy(str1, "000000000111111");
  strcpy(str2, "000000000000111");
  strcpy(str3, "000001000000001");
  strcpy(str4, "000001100100000");
  strcpy(str5, "000001110110100");
  strcpy(str6, "000000000110100");

  char res_or[45];
  cout << (str1 || str2) << endl;
  return 0;
}
