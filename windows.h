#include <ncurses.h>
#include "word.h"
#include "config.h"

#define ALPH_SIZE       26
#define WINDOW_TYPES    3
#define KEY_ALPH_IDX(key)((key) - 'a')
static const char *querty_layout = {"qwertyuiopasdfghjklzxcvbnm"};
// accesed with key - 'a'
static const size_t key_2_idx[ALPH_SIZE] = {10, 23, 21, 12, 2, 13, 14, 15, 7, 16, 17, 18,
                25, 24, 8, 9, 0, 3, 11, 4, 6, 22, 1, 20, 5, 19};
static const int keys_per_row[3] = {10, 10 + 9, 10 + 9 + 7};


typedef struct{
    int x, y;
}Point;

typedef struct{
    float x, y;
}Pointf;

typedef struct WinBundle{
    WINDOW **wins;
    size_t  size;
}WinBundle;

WinBundle *init_win_bundle(size_t size);
void draw_keyboard(WinBundle *keyboard_wins, int color[ALPH_SIZE]);
void draw_guesses(WinBundle *guesses_wins, word **words);
void draw_logo(WinBundle *logo_win);

void draw_col_key(WinBundle *keyboard_win, char key, int color);
void draw_col_word(WinBundle *word_win, size_t idx, word *word);
