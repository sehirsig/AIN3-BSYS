#
# Makefile
# Chapter 33
#
# Autor: @sehirsig
#


CC=gcc -o
CFLAGS=-Wall -g
CFLAGS2 =-lrt
STD=c11
RM=rm -f

TARGET=my_client_file my_server_file my_server my_server_file_async my_client_signal_sync my_server_signal_sync

.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) $(TARGET) $(TARGET:=.o)

#$(TARGET): $(TARGET).c
#    $(CC) $(CFLAGS) -o $@ $^

my_server_file:my_server_file.c
	$(CC) $(CFLAGS) -o $@ $^ $(CFLAGS2)

my_client_file:my_client_file.c
	$(CC) $(CFLAGS) -o $@ $^ $(CFLAGS2)

my_server:my_server.c
	$(CC) $(CFLAGS) -o $@ $^ $(CFLAGS2)

my_server_file_async:my_server_file_async.c
	$(CC) $(CFLAGS) -o $@ $^ $(CFLAGS2)

my_client_signal_sync:my_client_signal_sync.c
	$(CC) $(CFLAGS) -o $@ $^ $(CFLAGS2)

my_server_signal_sync:my_server_signal_sync.c
	$(CC) $(CFLAGS) -o $@ $^ $(CFLAGS2)
