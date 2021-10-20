from random import seed, randint
seed(1)
f = open("genrand2.txt", "w")
name = ""
lastint = 0
for x in range(0, 10000):    
    if (randint(0,4) % 2 == 0):
        for _ in range(0, randint(0, 6)):
            name = name + "\n" + str(lastint)
            lastint = lastint +1
    else:
        name = name + "\n" + str(lastint)
    lastint = randint(0,9)
f.write(name)
f.close()