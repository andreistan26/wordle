#include <ncurses.h>
#include "word.h"
#include "config.h"

#define ALPH_SIZE       26
#define WINDOW_TYPES    3

static const char *querty_layout[3] = {"qwertyuiop", "asdfghjkl", "zxcvbnm"};


typedef struct{
    int x, y;
}Point;

typedef struct{
    float x, y;
}Pointf;

typedef struct WordleWinBundle{
    WINDOW **wins;
    size_t  size;
    void  (*draw_wins)(struct WordleWinBundle *);
}WordleWinBundle;

WordleWinBundle *init_win_bundle(size_t size, void (*draw_wins)(WordleWinBundle *));
void draw_all_windows(WordleWinBundle **wins);
void draw_keyboard(WordleWinBundle *keyboard_wins);
void draw_guesses(WordleWinBundle *guesses_wins);
void draw_logo(WordleWinBundle *logo_win);

void draw_col_key(WordleWinBundle *keyboard_wins, char key, size_t color);
void draw_col_word(WordleWinBundle *keyboard_wins, size_t idx, word *word, size_t color);
