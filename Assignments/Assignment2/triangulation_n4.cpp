#include "polygons.cpp"
vector<pair<point*, point*> > diagonals;

bool not_intersecting(point* first, point* second)
{

    for(auto it = diagonals.begin(); it != diagonals.end(); it++)
    {
        if(it->first == first || it->first == second || it->second == first || it->second == second)
        {
            continue;
        }
        if(intersect(*it->first, *it->second, *first, *second))
        {
            return false;
        }
    }

    return true;
}

void triangulate_polygon_n4(point* head, ofstream& output)
{
    point* moving = head;
    point* second_moving = head->next;

    do{
        do{
            if(diagonal(moving, second_moving, head) && not_intersecting(moving, second_moving))
            {
                diagonals.push_back(make_pair(moving, second_moving));
                output << moving->index << " " << second_moving->index << endl;
            }
            second_moving = second_moving->next;
        }while(second_moving != head);
        moving = moving->next;
        second_moving = moving->next;
    }while(moving != head);
}

int main(int argv, char* argc[])
{
    string input_file = argc[1];
    string output_file = argc[2];
    ifstream input(input_file);
    ofstream output(output_file);

    point* head = nullptr;
    int num_vertices = 0;
    read_vertices(input, head, num_vertices);

    auto start = chrono::high_resolution_clock::now();
    triangulate_polygon_n4(head, output);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    ofstream output_time("time.txt", ios::app);
    output_time << duration.count() << " ";
}