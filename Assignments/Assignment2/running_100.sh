g++ triangulation_n4.cpp -o triangulation_n4 -std=c++20
g++ triangulation_n2.cpp -o triangulation_n2 -std=c++20
g++ triangulation_my.cpp -o triangulation_my -std=c++20

mkdir -p 100_tests/diagonals/naive
mkdir -p 100_tests/diagonals/ear_clipping
mkdir -p 100_tests/diagonals/my_algo
mkdir -p 100_tests/gifs/naive
mkdir -p 100_tests/gifs/ear_clipping
mkdir -p 100_tests/gifs/my_algo

for i in {4..100}
do
    # echo "running for polygon$i"
    ./triangulation_n4 100_tests/polygons1/polygon$i.txt 100_tests/diagonals/naive/diagonals$i.txt
    ./triangulation_n2 100_tests/polygons1/polygon$i.txt 100_tests/diagonals/ear_clipping/diagonals$i.txt
    ./triangulation_my 100_tests/polygons1/polygon$i.txt 100_tests/diagonals/my_algo/diagonals$i.txt
    ./polygon_triangulation 100_tests/polygons1/polygon$i.txt
done

python3 visualisation_100.py