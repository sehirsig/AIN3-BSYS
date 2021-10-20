#
# Makefile
# Chapter 14 Aufgabe 1
#
# Autor: @sehirsig
#


CC=gcc -g
CFLAGS=-W -Wall -Wextra -Wpedantic -std=$(STD)
STD=gnu17
RM=rm -f

TARGET=null nofree nofree100 free100 vector

.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) $(TARGET) $(TARGET:=.o)


null: null.c
	$(CC) $(CFLAGS) -o $@ $^

nofree: nofree.c
	$(CC) $(CFLAGS) -o $@ $^

nofree100: nofree100.c
	$(CC) $(CFLAGS) -o $@ $^

free100: free100.c
	$(CC) $(CFLAGS) -o $@ $^

vector: vector.c
	$(CC) $(CFLAGS) -o $@ $^
#$(TARGET): $(TARGET).c
#	$(CC) $(CFLAGS) -o $@ $^
