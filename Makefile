CFLAGS = -g -Wall -ggdb3 
NCURSES = -lncurses
CC = gcc

wordle: wordle.c
	$(CC) -o wordle main.c wordle.c windows.c word.c $(CFLAGS) $(NCURSES)
clean :
	rm wordle
run : 
	./wordle 2> logs.log
