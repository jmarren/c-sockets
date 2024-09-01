
CC=clang

all: main

main: main.c
	$(CC) -o main main.c
