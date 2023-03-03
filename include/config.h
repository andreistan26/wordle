#ifndef CONF_H
#define CONF_H
#include <stdio.h>
#include <stdlib.h>
//const char *const config_path = "config";

typedef struct{
    char    *path;
    int     word_len;
    int     guesses;
}Config;

typedef struct{
    int     official_word;

    /* files have to match *legal.txt and *wordle.txt */
    char    *dict_path;
}Options;

#endif
