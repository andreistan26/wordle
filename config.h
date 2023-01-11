#include <stdio.h>
#include <stdlib.h>
const char *const config_path = "config";

typedef struct{
    char    *path;
    int     word_len;
    int     guesses;
}Config;

