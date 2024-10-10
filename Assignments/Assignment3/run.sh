# !/bin/bash
g++ -o convex_hull incremental_3d.cpp

for i in {4..10}
do
    ./convex_hull point_sets/point_set$i.txt hull_files/convex_hull$i.stl
    python3 visualisation.py $i save
done
