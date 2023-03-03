CFLAGS = -g -Wall -ggdb3 
NCURSES = -lncurses
CURL = -lcurl
CC = gcc

wordle: 
	$(CC) -o wordle $(wildcard src/*.c) $(CFLAGS) $(NCURSES) $(CURL)
clean :
	rm wordle
run : 
	./wordle 2> logs.log
