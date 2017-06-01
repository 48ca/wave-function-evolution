#!venv/bin/python3


import sys
if len(sys.argv) < 2:
    sys.stderr.write("No file to read given\n")
    sys.exit(1)

import matplotlib.pyplot as plt
import csv

from time import sleep


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
            if c == '':
                # This is often due to an extra comma at the end
                break
            cstr = c.split(" + ")

            re = float(cstr[0])
            im = float(cstr[1].split("i")[0])
            hist['re'][i].append(re)
            hist['im'][i].append(im)
            hist['co'][i].append(complex(re, im))
            hist['pr'][i].append(re*re - im*im)

    plt.ion()
    fig = plt.figure()
    ax = fig.add_subplot(1,1,1)
    re, = ax.plot(hist['pr'][0])
    fig.canvas.draw()
    for p in hist['pr']:
        re.set_ydata(p)
        fig.canvas.draw()

with open(sys.argv[1], 'r') as f:
    plot(csv.reader(f))
