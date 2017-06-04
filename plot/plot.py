#!venv/bin/python3


import sys
if len(sys.argv) < 2:
    sys.stderr.write("No file to read given\n")
    sys.exit(1)

import matplotlib.pyplot as plt
import csv

from time import sleep

# Get current size
fig_size = plt.rcParams["figure.figsize"]
 
# Set figure width to 32 and height to 24
fig_size[0] = 32
fig_size[1] = 24
plt.rcParams["figure.figsize"] = fig_size

def plot(r):
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

    plt.xlim([-500,500])
    plt.ylim([-4,4])
    plt.ion()
    fig = plt.figure()
    ax = fig.add_subplot(1,1,1)
    re, = ax.plot(hist['re'][0])
    im, = ax.plot(hist['im'][0])
    fig.canvas.draw()
    for p in range(0,len(hist['re'])):
        re.set_ydata(hist['re'][p])
        im.set_ydata(hist['im'][p])
        fig.canvas.draw()
        #sleep(.05)

with open(sys.argv[1], 'r') as f:
    plot(csv.reader(f))
