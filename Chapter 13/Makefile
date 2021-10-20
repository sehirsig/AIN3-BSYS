#
# Makefile
# Chapter 13 Aufgabe 3
#
# Autor: @sehirsig
#


CC=gcc -g
CFLAGS=-W -Wall -Wextra -Wpedantic -std=$(STD)
STD=gnu17
RM=rm -f

TARGET=memory-user

.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) $(TARGET) $(TARGET:=.o)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $@ $^
