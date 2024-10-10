import random
import sys

def generate_random_points(num_points, lower_bound, upper_bound):
    points = []
    for _ in range(num_points):
        x = random.randint(lower_bound, upper_bound)
        y = random.randint(lower_bound, upper_bound)
        z = random.randint(lower_bound, upper_bound)
        points.append((x, y, z))
    return points

def write_points_to_file(points, filename):
    with open(filename, 'w') as file:
        for point in points:
            file.write(f"{point[0]} {point[1]} {point[2]}\n")

if __name__ == "__main__":
    num_points = int(sys.argv[1])
    file_name = sys.argv[2]
    lower_bound = -10
    upper_bound = 10
    points = generate_random_points(num_points, lower_bound, upper_bound)
    write_points_to_file(points, file_name)