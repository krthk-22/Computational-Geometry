#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;

#define ADD(head, p) if(head) { \
    p->next = head; \
    p->prev = head->prev; \
    head->prev = p; \
    p->prev->next = p; \
} else { \
    head = p; \
    head->prev = p; \
    head->next = p; \
}

#define SWAP(a, b, c) {a = b; b = c; c = a;}

#define DELETE(head, p) if(head) {\
    if(head == head->next) \
        head = nullptr; \
    else if (p == head) \
        head = head->next; \
    p->next->prev = p->prev; \
    p->prev->next = p->next; \
    if(p != nullptr) \
    delete p; \
}

class vertex;
class edge;
class face;

// head pointers
vertex* vertices = nullptr;
edge* edges = nullptr;
face* faces = nullptr;

class vertex
{
    public:
        vector<int> coordinates;
        int index;
        edge* duplicate;
        bool onhull, mark;
        vertex *prev, *next;

        vertex(vector<int> _coordinates = vector<int>(3), int _index = -1)
        {
            coordinates = _coordinates;
            index = _index;
            duplicate = nullptr;
            onhull = false;
            mark = false;
            prev = nullptr;
            next = nullptr;

            ADD(vertices, this);
        }
};

class edge
{
    public:
        vector<face*> adj_faces;
        vector<vertex*> end_points;
        face* newface;
        bool delete_flag;
        edge *prev, *next;

        edge()
        {
            end_points.resize(2, nullptr);
            adj_faces.resize(2, nullptr);
            newface = nullptr;
            delete_flag = false;
            prev = nullptr;
            next = nullptr;

            ADD(edges, this);
        }
};

class face
{
    public:
        vector<edge*> edges;
        vector<vertex*> vertices;
        bool visible;
        face *prev, *next;

        face()
        {
            edges.resize(3, nullptr);
            vertices.resize(3, nullptr);
            visible = false;
            prev = nullptr;
            next = nullptr;

            ADD(faces, this);
        }
};

void read_vertices(ifstream& in)
{
    vector<int> coords(3);
    int index = 0;

    while(in >> coords[0] >> coords[1] >> coords[2])
    {
        vertex* v = new vertex(coords, index++);
    }
}

bool collinear(vertex* a, vertex* b, vertex* c)
{
    return (((c->coordinates[2] - a->coordinates[2]) * (b->coordinates[1] - a->coordinates[1]) -
           (b->coordinates[2] - a->coordinates[2]) * (c->coordinates[1] - a->coordinates[1])) == 0) &&
           (((b->coordinates[2] - a->coordinates[2]) * (c->coordinates[0] - a->coordinates[0]) -
           (b->coordinates[0] - a->coordinates[0]) * (c->coordinates[2] - a->coordinates[2])) == 0) &&
           (((b->coordinates[0] - a->coordinates[0]) * (c->coordinates[1] - a->coordinates[1]) -
           (b->coordinates[1] - a->coordinates[1]) * (c->coordinates[0] - a->coordinates[0])) == 0);
}

face* makeface(vertex *v0, vertex *v1, vertex *v2, face *fold)
{
    face* f;
    edge *e0, *e1, *e2;

    if(!fold)
    {
        e0 = new edge();
        e1 = new edge();
        e2 = new edge();
    }
    else
    {
        e0 = fold->edges[2];
        e1 = fold->edges[1];
        e2 = fold->edges[0];
    }

    e0->end_points[0] = v0; e0->end_points[1] = v1;
    e1->end_points[0] = v1; e1->end_points[1] = v2;
    e2->end_points[0] = v2; e2->end_points[1] = v0;

    f = new face();
    f->edges[0] = e0; f->edges[1] = e1; f->edges[2] = e2;
    f->vertices[0] = v0; f->vertices[1] = v1; f->vertices[2] = v2;

    e0->adj_faces[0] = f; e1->adj_faces[0] = f; e2->adj_faces[0] = f;

    return f;
}

int vol_sign(face* f, vertex* p)
{
    double vol;
    double ax, ay, az, bx, by, bz, cx, cy, cz;

    ax = f->vertices[0]->coordinates[0] - p->coordinates[0];
    ay = f->vertices[0]->coordinates[1] - p->coordinates[1];
    az = f->vertices[0]->coordinates[2] - p->coordinates[2];
    bx = f->vertices[1]->coordinates[0] - p->coordinates[0];
    by = f->vertices[1]->coordinates[1] - p->coordinates[1];
    bz = f->vertices[1]->coordinates[2] - p->coordinates[2];
    cx = f->vertices[2]->coordinates[0] - p->coordinates[0];
    cy = f->vertices[2]->coordinates[1] - p->coordinates[1];
    cz = f->vertices[2]->coordinates[2] - p->coordinates[2];

    vol = ax * (by*cz - bz*cy)
        + ay * (bz*cx - bx*cz)
        + az * (bx*cy - by*cx);
    
    if (vol > 0.5) return 1;
    else if (vol < -0.5) return -1;
    else return 0;
}

void double_triangle()
{
    vertex *v0, *v1, *v2, *v3, *t;
    face *f0, *f1 = nullptr;
    edge *e0, *e1, *e2, *s;
    int vol;

    // find three noncollinear points
    v0 = vertices;
    while(collinear(v0, v0->next, v0->next->next))
    {
        if((v0 = v0->next) == vertices)
        {
            cout << "double_triangle: All points are collinear" << endl;
            exit(0);
        }
    }

    v1 = v0->next;
    v2 = v1->next;

    v0->mark = true;
    v1->mark = true;
    v2->mark = true;

    f0 = makeface(v0, v1, v2, f1);
    f1 = makeface(v2, v1, v0, f0);

    f0->edges[0]->adj_faces[1] = f1;
    f0->edges[1]->adj_faces[1] = f1;
    f0->edges[2]->adj_faces[1] = f1;
    f1->edges[0]->adj_faces[1] = f0;
    f1->edges[1]->adj_faces[1] = f0;
    f1->edges[2]->adj_faces[1] = f0;

    v3 = v2->next;
    vol = vol_sign(f0, v3);
    while(!vol)
    {
        if((v3 = v3->next) == v0)
        {
            cout << "double_triangle: All points are coplanar" << endl;
            exit(0);
        }
        vol = vol_sign(f0, v3);
    }

    vertices = v3;
}

void make_Ccw(face *f, edge *e, vertex *p)
{
    face *fv;
    int i;
    edge *s;

    if(e->adj_faces[0]->visible)
    {
        fv = e->adj_faces[0];
    }
    else
    {
        fv = e->adj_faces[1];
    }

    for(i = 0; fv->vertices[i] != e->end_points[0]; ++i);

    if(fv->vertices[(i + 1) % 3] != e->end_points[1])
    {
        f->vertices[0] = e->end_points[1];
        f->vertices[1] = e->end_points[0];
    }
    else
    {
        f->vertices[0] = e->end_points[0];
        f->vertices[1] = e->end_points[1];
        SWAP(s, f->edges[1], f->edges[2]);
    }

    f->vertices[2] = p;
}

face* make_cone_face(edge* e, vertex* p)
{
    vector<edge*> new_edge(2, nullptr);
    face* new_face;
    int i, j;

    for(i = 0; i < 2; ++i)
    {
        if(!(new_edge[i] = e->end_points[i]->duplicate))
        {
            new_edge[i] = new edge();
            new_edge[i]->end_points[0] = e->end_points[i];
            new_edge[i]->end_points[1] = p;
            e->end_points[i]->duplicate = new_edge[i];
        }
    }

    new_face = new face();
    new_face->edges[0] = e;
    new_face->edges[1] = new_edge[0];
    new_face->edges[2] = new_edge[1];
    make_Ccw(new_face, e, p);

    for(i = 0; i < 2; ++i)
    {
        for(j = 0; j < 2; ++j)
        {
            if(new_edge[i] == nullptr)
            {
                break;
            }

            if(!(new_edge[i]->adj_faces[j]))
            {
                new_edge[i]->adj_faces[j] = new_face;
                break;
            }
        }
    }
    return new_face;
}

bool add_one(vertex *p)
{
    face* f;
    edge *e, *temp;
    bool vis = false;

    f = faces;
    do
    {
        if(vol_sign(f, p) < 0)
        {
            f->visible = true;
            vis = true;
        }
        f = f->next;
    } while (f != faces);
    
    if(!vis)
    {
        p->onhull = false;
        return false;
    }

    e = edges;
    do
    {
        temp = e->next;
        if(e->adj_faces[0]->visible && e->adj_faces[1]->visible)
            e->delete_flag = true;
        else if (e->adj_faces[0]->visible || e->adj_faces[1]->visible)
            e->newface = make_cone_face(e, p);
        e = temp;
    } while (e != edges);
    return true;
}

void cleanfaces()
{
    face* f;
    face* t;

    while(faces && faces->visible)
    {
        f = faces;
        DELETE (faces, f);
    }

    f = faces->next;

    do
    {
        if(f->visible)
        {
            t = f;
            f = f->next;
            DELETE (faces, t);
        }
        else
        {
            f = f->next;
        }
    } while (f != faces);
}

void cleanedges()
{
    edge* e;
    edge* t;

    e = edges;
    do
    {
        if(e->newface)
        {
            if(e->adj_faces[0]->visible)
            {
                e->adj_faces[0] = e->newface;
            }
            else
            {
                e->adj_faces[1] = e->newface;
            }
            e->newface = nullptr;
        }
        e = e->next;
    } while (e != edges);
    
    while(edges && edges->delete_flag)
    {
        e = edges;
        DELETE (edges, e);
    }

    e = edges->next;
    do
    {
        if(e->delete_flag)
        {
            t = e;
            e = e->next;
            DELETE (edges, t);
        }
        else
        {
            e = e->next;
        }
    } while (e != edges);
}

void cleanvertices()
{
    edge *e;
    vertex *v, *t;

    e = edges;
    do
    {
        e->end_points[0]->onhull = true;
        e->end_points[1]->onhull = true;
        e = e->next;
    } while (e != edges);
    
    while(vertices && vertices->mark && !vertices->onhull)
    {
        v = vertices;
        DELETE (vertices, v);
    }
    v = vertices->next;
    do
    {
        if(v->mark && !v->onhull)
        {
            t = v;
            v = v->next;
            DELETE (vertices, t);
        }
        else
        {
            v = v->next;
        }
    } while (v != vertices);
    
    v = vertices;
    do
    {
        v->duplicate = nullptr;
        v->onhull = false;
        v = v->next;
    } while (v != vertices);
}

void cleanup()
{
    cleanedges();
    cleanfaces();
    cleanvertices();
}

void construct_hull()
{
    vertex *v, *vnext;
    int vol;
    v = vertices;
    do
    {
        vnext = v->next;
        if(!v->mark)
        {
            v->mark = true;
            add_one(v);
            cleanup();
        }
        v = vnext;
    } while (v != vertices);
}

void print()
{
    vertex* v = vertices;
    do
    {
        cout << v->index << endl;
        // cout << v->coordinates[0] << " " << v->coordinates[1] << " " << v->coordinates[2] << endl;
        v = v->next;
    } while (v != vertices);
}

void print_stl(const string& filename)
{
    ofstream out(filename);
    if (!out.is_open()) {
        cerr << "Error: Could not open output file!" << endl;
        return;
    }

    out << "solid convex_hull" << endl;
    
    face* f = faces;
    do {
        // Calculate normal for the face
        vertex* v0 = f->vertices[0];
        vertex* v1 = f->vertices[1];
        vertex* v2 = f->vertices[2];

        vector<double> normal(3);
        normal[0] = (v1->coordinates[1] - v0->coordinates[1]) * (v2->coordinates[2] - v0->coordinates[2]) -
                    (v1->coordinates[2] - v0->coordinates[2]) * (v2->coordinates[1] - v0->coordinates[1]);
        normal[1] = (v1->coordinates[2] - v0->coordinates[2]) * (v2->coordinates[0] - v0->coordinates[0]) -
                    (v1->coordinates[0] - v0->coordinates[0]) * (v2->coordinates[2] - v0->coordinates[2]);
        normal[2] = (v1->coordinates[0] - v0->coordinates[0]) * (v2->coordinates[1] - v0->coordinates[1]) -
                    (v1->coordinates[1] - v0->coordinates[1]) * (v2->coordinates[0] - v0->coordinates[0]);

        // Normalize the normal vector
        double length = sqrt(normal[0]*normal[0] + normal[1]*normal[1] + normal[2]*normal[2]);
        if (length != 0) {
            normal[0] /= length;
            normal[1] /= length;
            normal[2] /= length;
        }

        // Write the normal and vertices in STL format
        out << "  facet normal " << normal[0] << " " << normal[1] << " " << normal[2] << endl;
        out << "    outer loop" << endl;

        for (int i = 0; i < 3; ++i) {
            vertex* v = f->vertices[i];
            out << "      vertex " << v->coordinates[0] << " " << v->coordinates[1] << " " << v->coordinates[2] << endl;
        }

        out << "    endloop" << endl;
        out << "  endfacet" << endl;

        f = f->next;
    } while (f != faces);

    out << "endsolid convex_hull" << endl;

    out.close();
}

int main(int argc, char* argv[])
{
    string input_file = argv[1];
    string output_file = argv[2];
    ifstream in(input_file);

    read_vertices(in);
    double_triangle();
    construct_hull();
    print_stl(output_file);
}