#
# Makefile
# Chapter 31
#
# Autor: @sehirsig
#


CC=gcc -o
CFLAGS=-Wall -pthread
STD=c11
RM=rm -f

TARGET=fork-join barrier reader-writer reader-writer-nostarve mutex-nostarve

.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) $(TARGET) $(TARGET:=.o)

#$(TARGET): $(TARGET).c
#    $(CC) $(CFLAGS) -o $@ $^

fork-join:fork-join.c
	$(CC) $(CFLAGS) -o $@ $^

barrier:barrier.c
	$(CC) $(CFLAGS) -o $@ $^

reader-writer:reader-writer.c
	$(CC) $(CFLAGS) -o $@ $^

reader-writer-nostarve:reader-writer-nostarve.c
	$(CC) $(CFLAGS) -o $@ $^

mutex-nostarve:mutex-nostarve.c
	$(CC) $(CFLAGS) -o $@ $^
