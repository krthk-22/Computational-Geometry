import numpy as np
import plotly.graph_objects as go
from stl import mesh
import sys

i = int(sys.argv[1])
status = sys.argv[2]
convex_mesh = mesh.Mesh.from_file(f'hull_files/convex_hull{i}.stl')

points_file = f'point_sets/point_set{i}.txt'
points = np.loadtxt(points_file, delimiter=' ')
fig = go.Figure()

mesh_x = convex_mesh.vectors[:, :, 0].flatten()
mesh_y = convex_mesh.vectors[:, :, 1].flatten()
mesh_z = convex_mesh.vectors[:, :, 2].flatten()


fig.add_trace(go.Mesh3d(
    x=mesh_x,
    y=mesh_y,
    z=mesh_z,
    color='lightblue',
    opacity=0.8,
    name='Convex Hull',
    alphahull=0
))

# Add the points
fig.add_trace(go.Scatter3d(
    x=points[:, 0],
    y=points[:, 1],
    z=points[:, 2],
    mode='markers',
    marker=dict(size=5, color='red'),
    name='3D Points'
))

# Adding edges of the convex hull
for vector in convex_mesh.vectors:
    for i1 in range(3):
        start_vertex = vector[i1]
        end_vertex = vector[(i1 + 1) % 3]
        
        fig.add_trace(go.Scatter3d(
            x=[start_vertex[0], end_vertex[0]],
            y=[start_vertex[1], end_vertex[1]],
            z=[start_vertex[2], end_vertex[2]],
            mode='lines',
            line=dict(color='black', width=2),
            name='Edges'
        ))

# Update layout
fig.update_layout(
    scene=dict(
        xaxis=dict(showticklabels=False, title=''),
        yaxis=dict(showticklabels=False, title=''),
        zaxis=dict(showticklabels=False, title='') 
    ),
    title='Convex Hull and 3D Points',
    margin=dict(l=0, r=0, b=0, t=50)
)

if status == 'save':
    fig.write_html(f'hull_images/convex_hull{i}.html')
else:
    fig.show()
