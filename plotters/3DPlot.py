'''
3D PLOT.py
==========
Created: 17.05.2024

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Plot data in 3D from the .dat file using matplotlib.
'''

from utils import extractVariables
import matplotlib.pyplot as plt


# Unpack into variables.
t, x, y, z = extractVariables()
x,y,z = x/1e-2,y/1e-2,z/1e-2

# Plot data
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
sc = ax.scatter(x, y, z, c=t, cmap="viridis", s=0.03)
fig.colorbar(sc, label="Time", location='left')

ax.set_xlabel('X (cm)')
ax.set_ylabel('Y (cm)')
ax.set_zlabel('Z (cm)')
ax.set_title('Particle Trajectory')

plt.show()
