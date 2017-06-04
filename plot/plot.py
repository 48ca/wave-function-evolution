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
        're': [],
        'im': [],
        'co': [],
        'pr': []
    }
    for i, row in enumerate(r):
        for t in ['re', 'im', 'co', 'pr']:
            hist[t].append([])
        for c in row:
            if c == "": continue
            cstr = c.split(" + ")
            re = float(cstr[0])
            im = float(cstr[1].split("i")[0])
            hist['re'][i].append(re)
            hist['im'][i].append(im)
            hist['co'][i].append(complex(re, im))
            hist['pr'][i].append(re*re + im*im)

fig, ax = plt.subplots()
ax.set_ylim(-7, 7)
re, = ax.plot(hist['re'][0])
im, = ax.plot(hist['im'][0])
def update(data):
    re.set_ydata(hist['re'][data])
    im.set_ydata(hist['im'][data])
ani = animation.FuncAnimation(fig, update, np.arange(0, len(hist['re'])), interval=100)
plt.show()
#for p in range(0,len(hist['re'])):
#    re.set_ydata(hist['re'][p])
#    im.set_ydata(hist['im'][p])
#    fig.canvas.draw()
