import numpy as np
import time
import matplotlib.pyplot as plt

# Function to generate random masses and positions
def generate_masses_and_positions(num_masses):
    masses = np.random.randint(1, 200, size=num_masses)
    np.random.seed(43)  # For reproducibility
    positions = [(np.random.uniform(-10, 10), np.random.uniform(-10, 10)) for _ in range(num_masses)]
    return masses, positions

# Function to calculate gravitational pull
def gravitational_pull(x, y, mass, pos):
    distance = np.sqrt((x - pos[0])**2 + (y - pos[1])**2)
    return mass / (distance**2 + 1e-10)  # Add a small value to avoid division by zero

# Function to plot regions dominated by point masses
def plot_dominant_regions(num_points, ax, masses, positions):
    x = np.linspace(-20, 20, num_points)
    y = np.linspace(-20, 20, num_points)
    X, Y = np.meshgrid(x, y)

    total_pull = np.zeros_like(X)
    dominant_mass_index = np.zeros_like(X, dtype=int)

    for i, (mass, pos) in enumerate(zip(masses, positions)):
        pull = gravitational_pull(X, Y, mass, pos)
        mask = pull > total_pull
        total_pull[mask] = pull[mask]
        dominant_mass_index[mask] = i

    colors = plt.cm.get_cmap('tab10', len(masses))
    for i in range(len(masses)):
        ax.scatter(X[dominant_mass_index == i], Y[dominant_mass_index == i], color=colors(i), s=1, label=f'Mass {masses[i]}')

    for i, (mass, pos) in enumerate(zip(masses, positions)):
        ax.plot(pos[0], pos[1], 'o', color='black')

    ax.legend()
    ax.set_xlabel('X')
    ax.set_ylabel('Y')

# Main script
num_masses = 5  # Change this value to set the number of masses
masses, positions = generate_masses_and_positions(num_masses)

# Plot for different grid resolutions
num_points_list = [40, 80, 100, 400]
fig, axs = plt.subplots(2, 2, figsize=(8, 8))

start_time = time.time()
for ax, num_points in zip(axs.flatten(), num_points_list):
    plot_dominant_regions(num_points, ax, masses, positions)
end_time = time.time()
print(f"Execution time: {end_time - start_time} seconds")

plt.savefig('dominant_regions.png')

fig1, axs1 = plt.subplots(2, 2, figsize=(8, 8))

start_time = time.time()
equal_masses = [1] * num_masses
for ax, num_points in zip(axs1.flatten(), num_points_list):
    plot_dominant_regions(num_points, ax, equal_masses, positions)
end_time = time.time()
print(f"Execution time: {end_time - start_time} seconds")

plt.savefig('dominant_regions_voronoi.png')