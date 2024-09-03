#include "polygons.hpp"
#include <fstream>

point::point() : coordinates (vector<int>(2, 0)), index (0), is_ear (true) {}

point::point(vector<int> _coordinates, int _index, bool _is_ear) : coordinates (_coordinates), index (_index), is_ear (_is_ear) {}

vector<int> point::get_coordinates()
{
    return coordinates;
}

void point::set_coordinates(vector<int> _coordinates)
{
    coordinates = _coordinates;
}

void point::set_index(int _index)
{
    index = _index;
}

void point::set_is_ear(bool _is_ear)
{
    is_ear = _is_ear;
}

int area2(point a, point b, point c)
{
    return (b.coordinates[0] - a.coordinates[0]) * (c.coordinates[1] - a.coordinates[1]) 
    - (c.coordinates[0] - a.coordinates[0]) * (b.coordinates[1] - a.coordinates[1]);
}

int area_polygon2(point* head)
{
    int area = 0;
    point* fixed = head;
    point* moving = head->next;
    do{
        area += area2(*fixed, *moving, *moving->next);
        moving = moving->next;
    } while(moving->next != head);
    
    return area;
}

bool left(point a, point b, point c)
{
    return area2(a, b, c) > 0;
}

bool lefton(point a, point b, point c)
{
    return area2(a, b, c) >= 0;
}

bool collinear(point a, point b, point c)
{
    return area2(a, b, c) == 0;
}

bool intersect_inside(point a, point b, point c, point d)
{
    if(collinear(a, b, c) || collinear(a, b, d) || collinear(c, d, a) || collinear(c, d, b))
    {
        return false;
    }
    return (left(a, b, c) ^ left(a, b, d)) && (left(c, d, a) ^ left(c, d, b));
}

bool between(point a, point b, point c)
{
    if(!collinear(a, b, c))
    {
        return false;
    }
    if(a.coordinates[0] != b.coordinates[0])
    {
        return (a.coordinates[0] <= c.coordinates[0] && c.coordinates[0] <= b.coordinates[0]) 
        || (a.coordinates[0] >= c.coordinates[0] && c.coordinates[0] >= b.coordinates[0]);
    }
    else
    {
        return (a.coordinates[1] <= c.coordinates[1] && c.coordinates[1] <= b.coordinates[1]) 
        || (a.coordinates[1] >= c.coordinates[1] && c.coordinates[1] >= b.coordinates[1]);
    }
}

bool intersect(point a, point b, point c, point d)
{
    if(intersect_inside(a, b, c, d))
    {
        return true;
    }
    if(between(a, b, c) || between(a, b, d) || between(c, d, a) || between(c, d, b))
    {
        return true;
    }
    return false;
}

bool diagonalie(point* a, point* b, point* head)
{
    point* _head = head;
    point* moving;
    do
    {
        moving = _head->next;
        if(_head != a && _head != b && moving != a && moving != b)
        {
            if(intersect(*a, *b, *_head, *moving))
            {
                return false;
            }
        }
        _head = _head->next;
    } while (_head != head);

    return true;
}

bool in_cone(point* a, point* b)
{
    point* a_prev = a->prev;
    point* a_next = a->next;
    
    if(lefton(*a, *a_next, *a_prev))
    {
        return left(*a, *b, *a_prev) && left(*b, *a, *a_next);
    }
    return !(lefton(*a, *b, *a_next) && lefton(*b, *a, *a_prev));
}

bool diagonal(point* a, point* b, point* head)
{
    return in_cone(a, b) && in_cone(b, a) && diagonalie(a, b, head);
}

void ear_init(point* head)
{
    point* moving = head;
    point* prev = head->prev;
    point* next = head->next;
    
    do
    {
        moving->set_is_ear(diagonal(prev, next, head));
        moving = moving->next;
        prev = prev->next;
        next = next->next;
    } while(moving != head);
}

void read_vertices(ifstream& input, point*& head, int& num_vertices)
{
    int x, y;
    while(input >> x >> y)
    {
        vector<int> coordinates;
        coordinates.push_back(x);
        coordinates.push_back(y);
        if(head == nullptr)
        {
            head = new point(coordinates, num_vertices, true);
            head->next = head;
            head->prev = head;
        }
        else
        {
            point* new_point = new point(coordinates, num_vertices, true);
            new_point->next = head;
            new_point->prev = head->prev;
            head->prev->next = new_point;
            head->prev = new_point;
        }
        num_vertices++;
    }
}