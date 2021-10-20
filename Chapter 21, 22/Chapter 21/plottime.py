#!/usr/bin/env python

import matplotlib.pyplot as plt
import numpy as np

x = [1,2,4,8,12,16]

y = [ 7600, 7550, 7730, 7700, 7710, 160 ]

y1gb = [3059, 6300, 6617, 7275, 7710, 7600, 7574, 7719, 7700, 7680]

plt.plot(x, y)

plt.xlabel('Memory in GB')
plt.ylabel('Durschnittliche Bandbreite in MB/s')
plt.show()
