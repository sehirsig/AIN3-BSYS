CC=gcc -o -g
CFLAGS=-W -Wall -Wextra -Wpedantic -std=$(STD) -pthread
STD=c11
RM=rm -f

TARGET=counter sloppycounter linkedlist linkedlist_hand

.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) $(TARGET) $(TARGET:=.o)

#$(TARGET): $(TARGET).c
#	$(CC) $(CFLAGS) -o $@ $^

counter: counter.c
	$(CC) $(CFLAGS) -o $@ $^

linkedlist: linkedlist.c
	$(CC) $(CFLAGS) -o $@ $^

linkedlist_hand: linkedlist_hand.c
	$(CC) $(CFLAGS) -o $@ $^

sloppycounter: sloppycounter.c
	$(CC) $(CFLAGS) -o $@ $^

