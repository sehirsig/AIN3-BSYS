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

TARGET=aufgabe1 aufgabe2

.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) $(TARGET) $(TARGET:=.o) *.txt

aufgabe1: aufgabe1.c
	$(CC) $(CFLAGS) -o $@ $^

aufgabe2: aufgabe2.c
	$(CC) $(CFLAGS) -o $@ $^


#$(TARGET): $(TARGET).c
#	$(CC) $(CFLAGS) -o $@ $^
