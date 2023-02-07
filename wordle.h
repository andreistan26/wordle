#ifndef WORDLE_H
#define WORDLE_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "word.h"
#include "windows.h"
#include "utils.h"

#define TRIM_LAST_CHAR(buf) ((buf[strlen(buf) - 1] = 0))

static const char *win_alert = "You won!";
static const char *lost_alert = "You lost word was %s :(";

typedef enum{
    RUNNING, WON, LOST
}GameState;

typedef struct{
    WinBundle       *app_windows;
    GameState       game_state;
    
    FILE            *dict_file;
    char            **dict_words;
    char            *seeked_word;

    size_t          dict_word_count;
    int             guess_idx;
    int             word_size;
    int             max_guesses;
}AppData;

WordleInputWin *current_input_win(AppData *app_data);

AppData     *init_app_data();
static void load_dict(AppData *app_data);
static void quit_app(AppData *app_data);
void        wordle_init();
void        generate_random_word(AppData *app_data);
void        process_input(AppData *app_data);
int         is_lost(AppData *app_data, int show_alert);
void        exit_game(AppData *app_data);

#endif
