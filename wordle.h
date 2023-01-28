#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "word.h"
#include "windows.h"

#define TRIM_NEW_LINE(buf) ((buf[strlen(buf) - 1] = 0))

typedef enum{
    LOGO, GUESSES, KB 
}WIN_IDX;

typedef struct{
    FILE            *dict_file;
    char            **dict_words;
    char            *seeked_word;
    size_t          dict_word_count;
    int             guess_idx;
    int             word_size;
    int             max_guesses;
    WinBundle       *app_windows;
}AppData;

AppData     *init_app_data();
static void load_dict(AppData *app_data);
void        wordle_init();
void        generate_random_word(AppData *app_data);
void        parse_input();
