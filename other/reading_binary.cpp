#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>

int main(){
  std::ifstream input("OT/otypes06.b08", std::ios::binary);
  int number_points = 6;
  // copies all data into buffer
  std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});
  std::cout << "Buffer size: " << buffer.size() << std::endl;
  std::cout << "Total number of points: " << buffer.size()/2 << std::endl;
  std::cout << "Number of sets: " << (buffer.size()/2)/number_points << std::endl;
  std::cout << "Number of points on each set: " << number_points << std::endl;

  return 0;
}
//3f7e6ab2-75f6-47cb-8f9f-fc0a53f08269
