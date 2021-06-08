CC=gcc
CFLAGS=-I.

makemapfinder: main.o
	$(CC) -o mapfinder main.o
