CC=gcc

all: main

main: main.c 
	gcc -fsanitize=address -march=native main.c -o main
clean:
	rm main *.o
