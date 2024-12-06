import numpy as np
import matplotlib.pyplot as plt
from scipy.spatial import Delaunay

# Function to compute the weighted distance between two points with masses
def weighted_distance(p1, p2, mass1, mass2):
    # Compute Euclidean distance
    d = np.linalg.norm(np.array(p1) - np.array(p2))
    # Modify distance by masses
    return d / (np.sqrt(mass1) + np.sqrt(mass2))

# Function to compute the bisector between two weighted points
def compute_bisector(A, B, massA, massB):
    x1, y1 = A
    x2, y2 = B
    
    # Midpoint of A and B
    midpoint = ((x1 + x2) / 2, (y1 + y2) / 2)
    
    # Weighted distance condition gives us the perpendicular bisector
    # Weighted condition is: (d(P, A)/sqrt(mass_A)) == (d(P, B)/sqrt(mass_B))
    
    # Slope of the line joining the two points
    slope = (y2 - y1) / (x2 - x1) if (x2 - x1) != 0 else np.inf
    intercept = y1 - slope * x1
    
    # Return the bisector equation (line in slope-intercept form)
    return slope, intercept, midpoint

# Function to compute Voronoi-like regions for weighted points
def compute_weighted_voronoi(masses, positions):
    plt.figure(figsize=(10, 10))
    ax = plt.gca()
    
    # Step 1: Calculate the boundaries for each pair of masses
    for i in range(len(masses)):
        for j in range(i + 1, len(masses)):
            A, B = positions[i], positions[j]
            massA, massB = masses[i], masses[j]
            
            # Compute the bisector between A and B
            slope, intercept, midpoint = compute_bisector(A, B, massA, massB)
            
            # Draw the bisector as a line (boundary between regions)
            if slope != np.inf:
                x_range = np.linspace(-20, 20, 200)
                y_range = slope * x_range + intercept
                ax.plot(x_range, y_range, 'k-', linewidth=1)
            else:
                ax.plot(np.full_like(np.linspace(-20, 20, 200), midpoint[0]), 'k-', linewidth=1)

    # Step 2: Plot the masses and regions
    colors = ['blue', 'green', 'red', 'purple']
    for i, (mass, pos) in enumerate(zip(masses, positions)):
        ax.scatter(pos[0], pos[1], s=100, color=colors[i], label=f'Mass {mass}')
    
    ax.set_xlim(-20, 20)
    ax.set_ylim(-20, 20)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_title('Weighted Voronoi Diagram (without grid approximation)')
    ax.legend()
    plt.grid(True)
    plt.show()

# Example masses and positions
masses = [10, 40, 100, 180]
np.random.seed(42)
positions = [(np.random.uniform(-10, 10), np.random.uniform(-10, 10)) for _ in masses]

# Compute and plot the weighted Voronoi diagram
compute_weighted_voronoi(masses, positions)
