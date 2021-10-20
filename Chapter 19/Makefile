#
# Makefile
# Chapter 19
#
# Autor: @sehirsig
#


CC=gcc -g
CFLAGS=-W -Wall -Wextra -Wpedantic -std=$(STD) -O0
STD=gnu17
RM=rm -f

TARGET=tlb

.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) $(TARGET) $(TARGET:=.o)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $@ $^
