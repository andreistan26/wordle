#include "windows.h"

WinBundle *init_win_bundle(size_t size){
    WinBundle *bundle = malloc(sizeof(WinBundle));
    bundle->wins = malloc(size * sizeof(WINDOW *));
    for(size_t i = 0; i < size; i++){
        bundle->wins[i] = NULL;
    }
    bundle->size = size;

    return bundle;
}

void draw_logo(WinBundle *logo_win){
    //TODO add logo from config
    static const char *logo[6] = {"W", "O", "R", "D", "L", "E"};
    static const Pointf pos_scale = {.x = 0.5, .y = 0.1};
    static const Point logo_dim = {.x = 1 + 2, .y = 6 + 2};
    if(logo_win != NULL){
        wclear(logo_win->wins[0]);
    }

    Point display_size;
    getmaxyx(stdscr, display_size.y, display_size.x);
    
    // center the logo
    logo_win->wins[0] = newwin(
            logo_dim.x, logo_dim.y,
            display_size.y * pos_scale.y,
            display_size.x * pos_scale.x - logo_dim.x * 0.5
        );
    
    for(size_t i = 0; i < logo_dim.y; i++){
        mvwprintw(logo_win->wins[0], i + 1, 1, "%s", logo[i]);
    }

    box(logo_win->wins[0], 0, 0);
    wrefresh(logo_win->wins[0]);
}

void draw_guesses(WinBundle *input_wins, word **words){
    static const Pointf pos_scale = {.x = 0.5, .y = 0.4};
    static const Point input_dim = {.x = 5 + 2, .y = 1 + 2};
    static const int vertical_gap = 1;
    //TODO add guesses from config
    static const int guesses = 6;
    static const int word_len = 5;
    Point display_size;
    getmaxyx(stdscr, display_size.y, display_size.x);
    
    for(size_t i = 0; i < guesses; i++){
        input_wins->wins[i] = newwin(
                input_dim.y, input_dim.x,
                display_size.x * pos_scale.x - input_dim.x * 0.5,
                display_size.y * pos_scale.y + i * input_dim.y + vertical_gap
        );
        for(size_t word_it = 0; word_it < words[i]->len; word_it++){
            attron(COLOR_PAIR(words[i]->color[word_it]));
            mvwaddch(input_wins->wins[i], 1, word_it + 1, words[i]->value[word_it]);
            attroff(COLOR_PAIR(words[i]->color[word_it]));
        }
        box(input_wins->wins[i], 0, 0);
        wrefresh(input_wins->wins[i]);
    }
} 

void draw_keyboard(WinBundle *keyboard_wins, int color[ALPH_SIZE]){
    static const Pointf pos_scale = {.x = 0.5, .y = 0.4};
    static const Point key_dim = {.x = 1 + 2, .y = 1 + 2};
    static const Point gap = {.x = 1, .y = 1};
    static const int querty_rows = 3;

    Point display_size;
    getmaxyx(stdscr, display_size.y, display_size.x);
    
    WINDOW **it = keyboard_wins->wins;
    size_t row = 1;
    for(size_t key_idx = 0; key_idx < ALPH_SIZE; key_idx++){
        if(key_idx > keys_per_row[row] - 1)
            row++;
        *it = newwin(
                key_dim.y, key_dim.x,
                display_size.x * pos_scale.x - keys_per_row[row] * key_dim.x * 0.5 + gap.x + key_dim.x * (keys_per_row[row] - key_idx),
                display_size.y * pos_scale.y + row * key_dim.y + gap.y
        );
        box(*it, 0, 0);
        wrefresh(*it);
        it++;
    }
}

void draw_col_word(WinBundle *word_win, size_t idx, word *word){
    WINDOW **win = &(word_win->wins[idx]);
    Point pos;
    getmaxyx(*win, pos.y, pos.x);
    for(size_t i = 0; i < word->len; i++){
        attron(COLOR_PAIR(word->color[i]));
        mvwaddch(*win, 1, 1, word->value[i]);
        attroff(COLOR_PAIR(word->color[i]));
    }
    wrefresh(*win);
}

void draw_col_key(WinBundle *keyboard_win, char key, int color){
    WINDOW **key_win = &(keyboard_win->wins[key_2_idx[KEY_ALPH_IDX(key)]]);
    Point pos;
    getmaxyx(*key_win, pos.y, pos.x);
    attron(COLOR_PAIR(color));
    mvwaddch(*key_win, 1, 1, key);
    attroff(COLOR_PAIR(color));
    wrefresh(*key_win);
}


