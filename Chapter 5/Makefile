#
# Makefile
# Chapter 5 Aufgabe 1
#
# Autor: @sehirsig
#


CC=gcc -g
CFLAGS=-W -Wall -Wextra -Wpedantic -std=$(STD)
STD=gnu17
RM=rm -f

HW2TXT = hw2/test.txt

TARGET=hw1/hw1 hw2/hw2 hw3/hw3 hw4/hw4 hw5/hw5 hw6/hw6 hw7/hw7 hw8/hw8

.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) $(TARGET) $(TARGET:=.o) $(HW2TXT) 

hw1/hw1: hw1/hw1.c
	$(CC) $(CFLAGS) -o $@ $^

hw2/hw2: hw2/hw2.c
	$(CC) $(CFLAGS) -o $@ $^
	
hw3/hw3: hw3/hw3.c
	$(CC) $(CFLAGS) -o $@ $^

hw4/hw4: hw4/hw4.c
	$(CC) $(CFLAGS) -o $@ $^
	
hw5/hw5: hw5/hw5.c
	$(CC) $(CFLAGS) -o $@ $^

hw6/hw6: hw6/hw6.c
	$(CC) $(CFLAGS) -o $@ $^
	
hw7/hw7: hw7/hw7.c
	$(CC) $(CFLAGS) -o $@ $^

hw8/hw8: hw8/hw8.c
	$(CC) $(CFLAGS) -o $@ $^

#$(TARGET): $(TARGET).c
#	$(CC) $(CFLAGS) -o $@ $^
