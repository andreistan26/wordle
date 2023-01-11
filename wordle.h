#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include "word.h"
#include "windows.h"

typedef enum{
    LOGO, GUESSES, KB 
}WIN_IDX;

typedef struct{
    FILE            *dict_file;
    char            **dict_words;
    char            *seeked_word;
    int             guess_idx;
    const int       max_guesses;
    WordleWinBundle **wins;
}AppData;

AppData     *init_app_data();
static int  load_dict(AppData *app_data);
void        init();
void        get_random(AppData *app_data);
void        parse_input();
