#!/usr/bin/env python

import matplotlib.pyplot as plt
import numpy as np

x = np.arange(0,10)

y1gb = [3059, 6300, 6617, 7275, 7710, 7600, 7574, 7719, 7700, 7680]

y2gb = [3102, 7414, 7331, 7343, 7553, 7551, 7557, 7574, 7694, 7690]

y4gb = [3166, 7755, 7738, 7738, 7737, 7740, 7738, 7747, 7731, 7741]

y8gb = [3177, 7735, 7691, 7720, 7704, 7717, 7731, 7733, 7733, 7729]

y12gb = [3227, 7749, 7652, 7734, 7753, 7750, 7754, 7740, 7654, 7743]

y16gb = [2902, 257, 180, 171, 163, 164, 165, 164, 165, 163]

plt.plot(x, y1gb, 'green')
plt.plot(x, y2gb, 'red')
plt.plot(x, y4gb, 'blue')
plt.plot(x, y8gb, 'yellow')
plt.plot(x, y12gb, 'black')
plt.plot(x, y16gb, 'orange')


plt.legend(["1GB", "2GB", "4GB", "8GB", "12GB", "16GB"])
plt.xlabel('Schleifen')
plt.ylabel('Bandbreite in MB/s')
plt.show()
