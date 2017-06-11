#!venv/bin/python3


import sys
if len(sys.argv) < 2:
    sys.stderr.write("No file to read given\n")
    sys.exit(1)

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import csv

from time import sleep

# Get current size
fig_size = plt.rcParams["figure.figsize"]

# Set figure width to 32 and height to 24
fig_size[0] = 32
fig_size[1] = 24
plt.rcParams["figure.figsize"] = fig_size
hist = {}

with open(sys.argv[1], 'r') as f:
    r = csv.reader(f)
    hist = {
        'vl': [],
        'dt': []
    }
    for i, row in enumerate(r):
        for t in ['vl', 'dt']:
            hist[t].append([])
        for c in row:
            if c == "": continue
            cstr = c.split(";")
            vl = cstr[0]
            dt = cstr[1]
            hist['vl'][i].append(vl)
            hist['dt'][i].append(dt)

fig, ax = plt.subplots()
ax.set_ylim(-1.5, 1.5)
vl, = ax.plot(hist['vl'][0])
dt, = ax.plot(hist['dt'][0])
def update(data):
    vl.set_ydata(hist['vl'][data])
    dt.set_ydata(hist['dt'][data])
ani = animation.FuncAnimation(fig, update, np.arange(0, len(hist['vl'])), interval=1)
plt.show()
#for p in range(0,len(hist['re'])):
#    re.set_ydata(hist['re'][p])
#    im.set_ydata(hist['im'][p])
#    fig.canvas.draw()
