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
static const int keys_per_row[3] = {10, 9, 7};
static const int keys_new_line[3] = {10 - 1, 10 + 9 - 1, 10 + 9 + 7 - 1};

typedef struct{
    int x, y;
}Point;

typedef struct{
    float x, y;
}Pointf;

typedef struct {
    WINDOW *win;
    int color;
}WordleKeyboardWin;

typedef struct {
    WINDOW  *win;
    word    *word;
}WordleInputWin;

typedef struct WinBundle{
    WordleInputWin *input_wins;
    WordleKeyboardWin *keyboard_wins;
    WINDOW **logo_win;
}WinBundle;

WinBundle *init_win_bundle(size_t guesses);
void draw_keyboard(WordleKeyboardWin *keyboard_wins);
void draw_all_input_win(WordleInputWin *input_wins);
void draw_logo(WINDOW **logo_win);

void draw_input_win(WordleInputWin *input_wins, int idx);

void draw_col_key(WordleKeyboardWin *keyboard_wins, char key, int color);
void draw_col_word(WINDOW **input_wins, size_t idx, word *word);
