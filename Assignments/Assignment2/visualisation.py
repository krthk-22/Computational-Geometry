from matplotlib import pyplot as plt
from matplotlib.animation import FuncAnimation

def animate2(t):
    with open(f"polygons/polygon{t}.txt", 'r') as file:
        data = file.readlines()
        data = [line.strip() for line in data]

    vertices = []
    for line_data in data:
        coordinates = list(map(int, line_data.split()))
        vertices.append(coordinates)

    diagonals = []
    with open(f"diagonals/ear_clipping/diagonals{t}.txt", 'r') as file:
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
    ani.save(f"gifs/ear_clipping/polygon{t}.gif", writer='pillow', fps=3)

def animate3(t):
    with open(f"polygons/polygon{t}.txt", 'r') as file:
        data = file.readlines()
        data = [line.strip() for line in data]

    vertices = []
    for line_data in data:
        coordinates = list(map(int, line_data.split()))
        vertices.append(coordinates)

    diagonals = []
    with open(f"diagonals/my_algo/diagonals{t}.txt", 'r') as file:
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
    ani.save(f"gifs/my_algo/polygon{t}.gif", writer='pillow', fps=3)

for t in range(1, 10):
    animate2(t)
    animate3(t)

ear_clip_time = []
my_algo_time = []
with open("time.txt", 'r') as file:
        data = file.readlines()
        data = [line.strip() for line in data]
        for line_data in data:
            time = list(map(float, line_data.split()))
            ear_clip_time.append(time[0])
            my_algo_time.append(time[1])

fig, ax = plt.subplots()
ax.plot(range(1, 10), ear_clip_time, label='Ear Clipping')
ax.plot(range(1, 10), my_algo_time, label='My Algorithm')
ax.set_xlabel('Polygon Number')
ax.set_ylabel('Time (s)')
ax.legend()
plt.savefig('time.png')