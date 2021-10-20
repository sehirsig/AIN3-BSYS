#!/usr/bin/env python

import matplotlib.pyplot as plt
import numpy as np

data = np.genfromtxt("tabelle.csv", delimiter=",");

plt.plot(data[:,0], data[:,1])

plt.xscale('log', basex=2)
plt.grid()
plt.xlabel("Page Number")
plt.ylabel("Time (ns)")
plt.show()
