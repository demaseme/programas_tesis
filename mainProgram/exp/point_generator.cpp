#include <iostream>
#include <vector>
#include <CGAL/Cartesian_d.h>
#include <CGAL/point_generators_d.h>
typedef CGAL::Cartesian_d<int>                           Kd;
typedef Kd::Point_d                                         Point;
int main ()
{
  int nb_points = 100;
  int dim =2;
  double size = 100.0;
  std::cout << "Generating "<<nb_points<<" random points in a cube in "
        <<dim<<"D, coordinates from "<<-size<<" to "<<size<<std::endl;
  std::vector<Point> v;
  v.reserve (nb_points);
  CGAL::Random_points_in_cube_d<Point> gen (dim, size);
  for (int i = 0; i < nb_points; ++i) v.push_back (*gen++);
  for (int i = 0; i < nb_points; ++i) std::cout<<" "<<v[i]<<std::endl;
  return 0;
}
