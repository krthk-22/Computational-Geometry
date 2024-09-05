g++ triangulation_n4.cpp -o triangulation_n4 -std=c++20
g++ triangulation_n2.cpp -o triangulation_n2 -std=c++20
g++ triangulation_my.cpp -o triangulation_my -std=c++20

mkdir -p diagonals/naive
mkdir -p diagonals/ear_clipping
mkdir -p diagonals/my_algo

for i in {1..19}
do
    # echo "running for polygon$i"
    ./triangulation_n4 polygons/polygon$i.txt diagonals/naive/diagonals$i.txt
    ./triangulation_n2 polygons/polygon$i.txt diagonals/ear_clipping/diagonals$i.txt
    ./triangulation_my polygons/polygon$i.txt diagonals/my_algo/diagonals$i.txt
done

mkdir -p gifs/naive
mkdir -p gifs/ear_clipping
mkdir -p gifs/my_algo
python3 visualisation.py