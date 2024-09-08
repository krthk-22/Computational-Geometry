#include "polygons.cpp"

void triangulate_polygon_n3(point* head, ofstream& output)
{
    point* moving = head;
    point* second_moving = head->next;

    // T(n) = T(x) + T(n-x) + O(x);
    while(moving->next != head)
    {
        do{
            if(diagonal(moving, second_moving, head))
            {
                output << moving->index << " " << second_moving->index << endl;
                point* temp1 = new point();
                point* temp2 = new point();
                temp1->set_coordinates(moving->get_coordinates());
                temp1->set_index(moving->index);
                temp2->set_coordinates(second_moving->get_coordinates());
                temp2->set_index(second_moving->index);
                temp1->next = second_moving;
                temp1->prev = moving->prev;
                temp2->next = moving;
                temp2->prev = second_moving->prev;
                moving->prev->next = temp1;
                second_moving->prev->next = temp2;
                moving->prev = temp2;
                second_moving->prev = temp1;
                triangulate_polygon_n3(temp1, output);
                triangulate_polygon_n3(temp2, output);
                return;
            }
            else
            {
                second_moving = second_moving->next;
            }
        }while(second_moving->next != head);
        moving = moving->next;
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
    triangulate_polygon_n3(head, output);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    ofstream output_time("time.txt", ios::app);
    output_time << duration.count() << " ";
}