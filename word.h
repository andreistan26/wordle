#ifndef STRING_H
#define STRING_H

#include <string.h>

typedef struct{
    char    *value;
    int     *color;
    size_t  len;
}word;

word    *init_word();
void    add_ch(word *str, const char c);
int     remove_ch(word *str);
void    clear_word(word *str);
void    delete_word(word *str);

#endif
