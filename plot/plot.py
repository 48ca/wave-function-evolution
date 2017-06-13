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

numlines = 0

def classical(r):
    hist = {
        'vl': [],
        'dt': []
    }
    for i, row in enumerate(r):
        if i == 0: continue
        sys.stdout.write("\rProgress: {0:6.4f}%".format(100.0 * i/numlines))
        for t in ['vl', 'dt']:
            hist[t].append([])
        for c in row:
            if c == "": continue
            cstr = c.split(";")
            vl = cstr[0]
            dt = cstr[1]
            hist['vl'][-1].append(vl)
            hist['dt'][-1].append(dt)
    print("\rProgress: done         ")

    fig, ax = plt.subplots()
    ax.set_ylim(-2.5, 2.5)
    vl, = ax.plot(hist['vl'][0], 'o', ms=.75)
    dt, = ax.plot(hist['dt'][0], 'o', ms=.75)
    def update(data):
        vl.set_ydata(hist['vl'][data])
        dt.set_ydata(hist['dt'][data])
    ani = animation.FuncAnimation(fig, update, np.arange(0, len(hist['vl'])), interval=1)
    plt.show()

def schrodinger(r):
    hist = {
        're': [],
        'im': [],
        'co': [],
        'pr': []
    }
    for i, row in enumerate(r):
        if i == 0:
            continue
        sys.stdout.write("\rProgress: {0:6.4f}%".format(100.0 * i/numlines))
        for t in ['re', 'im', 'co', 'pr']:
            hist[t].append([])
        for c in row:
            if c == "": continue
            cstr = c.split(" + ")
            re = float(cstr[0])
            im = float(cstr[1].split("i")[0])
            hist['re'][-1].append(re)
            hist['im'][-1].append(im)
            hist['co'][-1].append(complex(re, im))
            hist['pr'][-1].append((re*re + im*im)**.5)
    print("\rProgress: done         ")

    fig, ax = plt.subplots()
    ax.set_ylim(-1.5, 1.5)
    re, = ax.plot(hist['re'][0], 'o', ms=.75)
    im, = ax.plot(hist['im'][0], 'o', ms=.75)
    pr, = ax.plot(hist['pr'][0], 'o', ms=.75)
    def update(data):
        re.set_ydata(hist['re'][data])
        im.set_ydata(hist['im'][data])
        pr.set_ydata(hist['pr'][data])
    ani = animation.FuncAnimation(fig, update, np.arange(0, len(hist['re'])), interval=1)
    plt.show()

t = ""
with open(sys.argv[1], 'r') as f:
    d = f.read().split("\n")
    numlines = len(d)
    t = d[0].split(";")[1]

with open(sys.argv[1], 'r') as f:
    r = csv.reader(f)
    if t == "schrodinger":
        print("Detected schrodinger output")
        schrodinger(r)
    elif t == "classical":
        print("Detected classical output")
        classical(r)
    else:
        print("Couldn't detect filetype")
