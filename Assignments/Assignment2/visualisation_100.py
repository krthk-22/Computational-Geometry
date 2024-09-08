from matplotlib import pyplot as plt
from matplotlib.animation import FuncAnimation

num_vertices = []

def animate_n4(t):
    with open(f"100_tests/polygons1/polygon{t}.txt", 'r') as file:
        data = file.readlines()
        data = [line.strip() for line in data]
        num_vertices.append(len(data))

    vertices = []
    for line_data in data:
        coordinates = list(map(int, line_data.split()))
        vertices.append(coordinates)

    diagonals = []
    with open(f"100_tests/diagonals/naive/diagonals{t}.txt", 'r') as file:
        data = file.readlines()
        data = [line.strip() for line in data]
        for line_data in data:
            end_points = list(map(int, line_data.split()))
            diagonals.append(end_points)

    fig, ax = plt.subplots()
    ax.axis('equal')

    # Draw polygon edges
    for i in range(len(vertices)):
        x = [vertices[i][0], vertices[(i + 1) % len(vertices)][0]]
        y = [vertices[i][1], vertices[(i + 1) % len(vertices)][1]]
        ax.plot(x, y, 'r')
        ax.plot(vertices[i][0], vertices[i][1], 'ro')
        ax.text(vertices[i][0], vertices[i][1], f'{i}', fontsize=12, ha='right')
    
    def update(frame):
        if frame < len(diagonals):
            x = [vertices[diagonals[frame][0]][0], vertices[diagonals[frame][1]][0]]
            y = [vertices[diagonals[frame][0]][1], vertices[diagonals[frame][1]][1]]
            ax.plot(x, y, 'b')

    ani = FuncAnimation(fig, update, frames=len(diagonals), repeat=False)
    ani.save(f"100_tests/gifs/naive/polygon{t}.gif", writer='pillow', fps=3)
    plt.close()

def animate_n2(t):
    with open(f"100_tests/polygons1/polygon{t}.txt", 'r') as file:
        data = file.readlines()
        data = [line.strip() for line in data]

    vertices = []
    for line_data in data:
        coordinates = list(map(int, line_data.split()))
        vertices.append(coordinates)

    diagonals = []
    with open(f"100_tests/diagonals/ear_clipping/diagonals{t}.txt", 'r') as file:
        data = file.readlines()
        data = [line.strip() for line in data]
        for line_data in data:
            end_points = list(map(int, line_data.split()))
            diagonals.append(end_points)

    fig, ax = plt.subplots()
    ax.axis('equal')

    # Draw polygon edges
    for i in range(len(vertices)):
        x = [vertices[i][0], vertices[(i + 1) % len(vertices)][0]]
        y = [vertices[i][1], vertices[(i + 1) % len(vertices)][1]]
        ax.plot(x, y, 'r')
        ax.plot(vertices[i][0], vertices[i][1], 'ro')
        ax.text(vertices[i][0], vertices[i][1], f'{i}', fontsize=12, ha='right')
    
    def update(frame):
        if frame < len(diagonals):
            x = [vertices[diagonals[frame][0]][0], vertices[diagonals[frame][1]][0]]
            y = [vertices[diagonals[frame][0]][1], vertices[diagonals[frame][1]][1]]
            ax.plot(x, y, 'b')

    ani = FuncAnimation(fig, update, frames=len(diagonals), repeat=False)
    ani.save(f"100_tests/gifs/ear_clipping/polygon{t}.gif", writer='pillow', fps=3)
    plt.close()

def animate_my(t):
    with open(f"100_tests/polygons1/polygon{t}.txt", 'r') as file:
        data = file.readlines()
        data = [line.strip() for line in data]

    vertices = []
    for line_data in data:
        coordinates = list(map(int, line_data.split()))
        vertices.append(coordinates)

    diagonals = []
    with open(f"100_tests/diagonals/my_algo/diagonals{t}.txt", 'r') as file:
        data = file.readlines()
        data = [line.strip() for line in data]
        for line_data in data:
            end_points = list(map(int, line_data.split()))
            diagonals.append(end_points)

    fig, ax = plt.subplots()
    ax.axis('equal')

    # Draw polygon edges
    for i in range(len(vertices)):
        x = [vertices[i][0], vertices[(i + 1) % len(vertices)][0]]
        y = [vertices[i][1], vertices[(i + 1) % len(vertices)][1]]
        ax.plot(x, y, 'r')
        ax.plot(vertices[i][0], vertices[i][1], 'ro')
        ax.text(vertices[i][0], vertices[i][1], f'{i}', fontsize=12, ha='right')
    
    def update(frame):
        if frame < len(diagonals):
            x = [vertices[diagonals[frame][0]][0], vertices[diagonals[frame][1]][0]]
            y = [vertices[diagonals[frame][0]][1], vertices[diagonals[frame][1]][1]]
            ax.plot(x, y, 'b')

    ani = FuncAnimation(fig, update, frames=len(diagonals), repeat=False)
    ani.save(f"100_tests/gifs/my_algo/polygon{t}.gif", writer='pillow', fps=3)
    plt.close()

for t in range(4, 101):
    animate_n4(t)
    animate_n2(t)
    animate_my(t)

naive_time = []
ear_clip_time = []
my_algo_time = []
cgal_time = []
with open("time.txt", 'r') as file:
        data = file.readlines()
        data = [line.strip() for line in data]
        for line_data in data:
            time = list(map(float, line_data.split()))
            naive_time.append(time[0])
            ear_clip_time.append(time[1])
            my_algo_time.append(time[2])
            cgal_time.append(time[3])

fig, ax = plt.subplots()
ax.set_title('Time Complexity')
ax.scatter(num_vertices, naive_time, label='Naive')
ax.scatter(num_vertices, ear_clip_time, label='Ear Clipping')
ax.scatter(num_vertices, my_algo_time, label='My Algorithm')
ax.scatter(num_vertices, cgal_time, label='CGAL')
ax.set_xlabel('Number of Vertices')
ax.set_ylabel('Time (ms)')
ax.legend()
plt.savefig('time.png')