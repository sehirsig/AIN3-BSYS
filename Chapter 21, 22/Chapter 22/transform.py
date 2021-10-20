#!/usr/bin/env python

tF = open('ls-trace.txt', 'r')
vF = open('vpn.txt', 'w')

for b in tF:
	if (!b.startswith('=')):
		vF.write(str((int(b[3:11], 16) & 0xFFFFF000) >> 12) + "\n")

vF.close()
tF.close()
