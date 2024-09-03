#include "polygons.cpp"

void triangulate_polygon_n2(point* head, int num_vertices, ofstream& output)
{
    point* _second_prev, *_second_next;
    point* moving = head;
    point* _prev, *_next;
    int n = num_vertices;

    ear_init(head);
    while(n > 3)
    {
        do
        {
            if(moving->is_ear)
            {
                if(moving == head)
                {
                    head = moving->next;
                }
                _next = moving->next;
                _second_next = _next->next;
                _prev = moving->prev;
                _second_prev = _prev->prev;
                output << _prev->index << " " << _next->index << endl;

                _prev->is_ear = diagonal(_second_prev, _next, head);
                _next->is_ear = diagonal(_prev, _second_next, head);

                _prev->next = _next;
                _next->prev = _prev;
                moving = _next;
                n--;
                break;
            }
            moving = moving->next;
        }while(moving != head);
    }
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
    triangulate_polygon_n2(head, num_vertices, output);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    ofstream output_time("time.txt", ios::app);
    output_time << duration.count() << " ";
}