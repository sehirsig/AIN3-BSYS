#!/usr/bin/env python

import matplotlib.pyplot as plt
import numpy as np
from random import randint

cacheSizes = np.arange(1,9)
policies = ["FIFO", "LRU", "MRU", "RAND", "CLOCK", "UNOPT", "OPT"]

hitRates = [
		[ 51.38, 80.88, 91.10, 94.08, 95.01, 95.96, 96.66, 97.03],
		[ 51.38, 86.42, 92.43, 95.32, 96.26, 96.93, 97.47, 97.75],
		[ 51.38, 52.24, 56.26, 56.70, 57.16, 57.64, 59.17, 59.33],
		[ 51.38, 80.83, 89.82, 93.13, 94.65, 95.54, 96.22, 96.64],
		[ 51.38, 82.48, 91.12, 94.29, 95.53, 96.38, 96.98, 97.41],
		[ 51.38, 51.38, 51.39, 51.40, 51.47, 51.71, 51.73, 51.74],
		[ 51.38, 86.80, 94.44, 96.53, 97.31, 97.85, 98.22, 98.45]
]

for i in range(7):
	plt.plot(cacheSizes, hitRates[i])

plt.legend(policies)
plt.margins(0)
plt.xticks(cacheSizes, cacheSizes)
plt.xlabel('Cache Size in Blocks')
plt.ylabel('Hit Rate')

p = randint(0,10000)

plt.savefig(f'fin{p}.png')

# python3 ./paging-policy.py -c -p FIFO -f ./vpn.txt -N -C 1
# python3 ./paging-policy.py -c -p LRU -f ./vpn.txt -N -C 1
# python3 ./paging-policy.py -c -p MRU -f ./vpn.txt -N -C 1
# python3 ./paging-policy.py -c -p RAND -f ./vpn.txt -N -C 1
# python3 ./paging-policy.py -c -p CLOCK -f ./vpn.txt -N -C 1
# python3 ./paging-policy.py -c -p UNOPT -f ./vpn.txt -N -C 1
# python3 ./paging-policy.py -c -p OPT -f ./vpn.txt -N -C 1


