CC = gcc
ARGS = -march=native -O3 -g #-fsanitize=address 
EXEC = main.c print_page.c 
OUTPUT = print_page
all: main 

main:
	$(CC) $(ARGS) $(EXEC) -o print_page

clean:
	rm $(OUTPUT)
