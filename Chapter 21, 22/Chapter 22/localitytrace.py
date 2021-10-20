#!/usr/bin/env python

from random import randint

liste = []
maxnumber = 9
minnumber = 0

p = randint(0,9)
for i in range(0,9):
	ran = randint(0,4)
	if (ran == 1):
		if (p+1 > maxnumber):
			liste.append(p-1)
			p = p-1
		else:
			liste.append(p+1)
			p = p+1
			
	elif (ran == 0):
		if (p-1 < minnumber):
			liste.append(p+1)
			p = p+1
		else:
			liste.append(p-1)
			p = p-1
	elif (ran == 2):
		liste.append(p)
	elif (ran == 3 or ran == 4):
		t = randint(0,9)
		liste.append(t)
	


print(liste)
