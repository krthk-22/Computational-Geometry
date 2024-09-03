#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class point
{
    public:
        int index;
        bool is_ear;
        vector<int> coordinates;
        point* next;
        point* prev;
    
    // methods for point
        point();
        point(vector<int>, int, bool);
        vector<int> get_coordinates();
        void set_coordinates(vector<int>);
        void set_index(int);
        void set_is_ear(bool);
};

int area2(point, point, point);
int area_polygon2(vector<point>);
bool left(point, point, point);
bool lefton(point, point, point);
bool collinear(point, point, point);
bool intersect_inside(point, point, point, point);
bool between(point, point, point);
bool intersect(point, point, point, point);
bool diagonalie(point*, point*);
bool in_cone(point*, point*);
bool diagonal(point*, point*);
void ear_init(point*);
void read_vertices(point* head);