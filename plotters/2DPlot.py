'''
2D PLOT.py
==========
Created: 17.05.2024

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Plot data in 2D from the .dat file using matplotlib The variable to be plotted can be customized.
'''

from utils import extractVariables
import matplotlib.pyplot as plt

t, x, y, z = extractVariables()


fig, axs = plt.subplots(nrows=3, ncols=1, sharex=True)

# Plot scatter plots
sc = axs[0].scatter(t, x, c=t, cmap='viridis', s=0.01)
axs[0].set_title('x vs t')
axs[0].set_ylabel('x')

sc = axs[1].scatter(t, y, c=t, cmap='viridis', s=0.01)
axs[1].set_title('y vs t')
axs[1].set_ylabel('y')
axs[1].set_xlabel('Time')

sc = axs[2].scatter(t, z, c=t, cmap='viridis', s=0.01)
axs[2].set_title('z vs t')
axs[2].set_xlabel('t')
axs[2].set_ylabel('z')

# Show the plot
fig.suptitle('Particle Trajectories')
plt.show()
