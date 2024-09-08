#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/draw_triangulation_2.h>
#include <CGAL/mark_domain_in_triangulation.h>
#include <CGAL/Polygon_2.h>

#include <iostream>
#include <unordered_map>
#include <fstream>
using namespace std;

#include <boost/property_map/property_map.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel       K;
typedef CGAL::Triangulation_vertex_base_2<K>                      Vb;
typedef CGAL::Constrained_triangulation_face_base_2<K>            Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>               TDS;
typedef CGAL::Exact_predicates_tag                                Itag;
typedef CGAL::Constrained_Delaunay_triangulation_2<K, TDS, Itag>  CDT;
typedef CDT::Face_handle                                          Face_handle;
typedef CDT::Point                                                Point;
typedef CGAL::Polygon_2<K>                                        Polygon_2;

int main(int argc, char* argv[])
{
  //construct two non-intersecting nested polygons
  std::string input_file = argv[1];
  std::ifstream input(input_file);
  std::vector<K::Point_2> vertices;
  int x, y;
  
  while(input >> x >> y){
        vertices.push_back(Point(x, y));
    }
  
  auto start = chrono::high_resolution_clock::now();
  Polygon_2 polygon1(vertices.begin(), vertices.end());

  //Insert the polygons into a constrained triangulation
  CDT cdt;
  cdt.insert_constraint(polygon1.vertices_begin(), polygon1.vertices_end(), true);
  std::unordered_map<Face_handle, bool> in_domain_map;
  boost::associative_property_map< std::unordered_map<Face_handle,bool> >
    in_domain(in_domain_map);

  // //Mark facets that are inside the domain bounded by the polygon
  CGAL::mark_domain_in_triangulation(cdt, in_domain);
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
  
  std::ofstream output_time("time.txt", std::ios::app);
  output_time << duration.count() << std::endl;
}