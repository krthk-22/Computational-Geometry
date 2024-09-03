g++ triangulation_n2.cpp -o triangulation2 -std=c++20
g++ triangulation_n3.cpp -o triangulation3 -std=c++20

mkdir -p diagonals/ear_clipping
mkdir -p diagonals/my_algo

for i in {1..9}
do
    ./triangulation2 polygons/polygon$i.txt diagonals/ear_clipping/diagonals$i.txt
    ./triangulation3 polygons/polygon$i.txt diagonals/my_algo/diagonals$i.txt
done

mkdir -p gifs/ear_clipping
mkdir -p gifs/my_algo
python3 visualisation.py