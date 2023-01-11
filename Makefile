# Declaratiile de variabile
CC = gcc
CFLAGS = -g -Wall -lm -ggdb3
 
# Regula de compilare
wordle: wordle.c
	$(CC) -o wordle wordle.c $(CFLAGS) -lncursesw

clean :
	rm wordle
