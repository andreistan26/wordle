#ifndef STRING_H
#define STRING_H

#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "utils.h"

typedef struct{
    char    *value;
    int     *color;
    size_t  len;
}word;

word    *init_word();
int     word_append(word *word, const char c);
int     word_remove(word *word);
void    word_clear(word *word);
void    word_free(word *str);

int     word_check(word *word, char *seeked_word);
int     is_word_input(int key);
#endif
