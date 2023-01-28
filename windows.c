#include "windows.h"

WinBundle *init_win_bundle(size_t guesses){
    WinBundle *bundle = malloc(sizeof(WinBundle));
    
    bundle->logo_win = malloc((sizeof(WINDOW *)));
    bundle->input_wins = malloc(guesses * sizeof(WordleInputWin));
    for(size_t i = 0; i < guesses; i++){
        bundle->input_wins[i].win = NULL;
        bundle->input_wins[i].word = init_word();
    }
    bundle->keyboard_wins = calloc(sizeof(WordleKeyboardWin), ALPH_SIZE);
    
    return bundle;
}

void draw_logo(WINDOW **logo_win){
    //TODO add logo from config
    static const char *logo[6] = {"W", "O", "R", "D", "L", "E"};
    static const Pointf pos_scale = {.x = 0.5, .y = 0.1};
    static const Point logo_dim = {.y = 1 + 2, .x = 6 + 2};
    if(*logo_win != NULL){
        wclear(*logo_win);
    }

    Point display_size;
    getmaxyx(stdscr, display_size.y, display_size.x);
    
    // center the logo
    *logo_win = newwin(
            logo_dim.y, logo_dim.x,
            display_size.y * pos_scale.y,
            display_size.x * pos_scale.x - logo_dim.x * 0.5
        );
    
    for(size_t i = 0; i < logo_dim.x - 2; i++){
        mvwprintw(*logo_win, 1, 1 + i, "%s", logo[i]);
    }
    refresh();
    wrefresh(*logo_win);
    refresh();
}

void draw_all_input_win(WordleInputWin *input_wins){
    static const Pointf pos_scale = {.x = 0.5, .y = 0.3};
    static const Point input_dim = {.x = 5 + 2, .y = 1 + 2};
    static const int vertical_gap = 1;
    //TODO add guesses from config
    static const int guesses = 6;
    static const int word_len = 5;
    Point display_size;
    getmaxyx(stdscr, display_size.y, display_size.x);
   
    for(size_t i = 0; i < guesses; i++){
        input_wins[i].win = newwin(
                input_dim.y, input_dim.x,
                display_size.y * pos_scale.y + i * input_dim.y + vertical_gap,
                display_size.x * pos_scale.x - input_dim.x * 0.5
        );
        for(size_t word_it = 0; word_it < input_wins[i].word->len; word_it++){
            attron(COLOR_PAIR(input_wins[i].word->color[word_it]));
            mvwaddch(input_wins[i].win, 1, word_it + 1, input_wins[i].word->value[word_it]);
            attroff(COLOR_PAIR(input_wins[i].word->color[word_it]));
        }
        box(input_wins[i].win, 0, 0);
        refresh();
        wrefresh(input_wins[i].win);
        refresh();
    }
}

void draw_input_win(WordleInputWin *input_wins, int idx){
    static const Pointf pos_scale = {.x = 0.5, .y = 0.4};
    static const Point input_dim = {.x = 5 + 2, .y = 1 + 2};
    static const int vertical_gap = 1;
    //TODO add guesses from config
    static const int guesses = 6;
    static const int word_len = 5;
    
    Point display_size;
    getmaxyx(stdscr, display_size.y, display_size.x);
    
    input_wins[idx].win = newwin(
            input_dim.y, input_dim.x,
            display_size.y * pos_scale.y + idx * input_dim.y + vertical_gap,
            display_size.x * pos_scale.x - input_dim.x * 0.5
    );

    for(size_t word_it = 0; word_it < input_wins[idx].word->len; word_it++){
        attron(COLOR_PAIR(input_wins[idx].word->color[word_it]));
        mvwaddch(input_wins[idx].win, 1, word_it + 1, input_wins[idx].word->value[word_it]);
        attroff(COLOR_PAIR(input_wins[idx].word->color[word_it]));
    }

    box(input_wins[idx].win, 0, 0);
    wrefresh(input_wins[idx].win);
}

void draw_keyboard(WordleKeyboardWin *keyboard_wins){
    static const Pointf pos_scale = {.x = 0.5, .y = 0.7};
    static const Point key_dim = {.x = 1 + 2, .y = 1 + 2};
    static const Point gap = {.x = 1, .y = 1};

    Point display_size;
    getmaxyx(stdscr, display_size.y, display_size.x);
    
    size_t row = 0;
    for(size_t key_idx = 0; key_idx < ALPH_SIZE; key_idx++){
        if(key_idx > keys_new_line[row])
            row++;
        keyboard_wins[key_idx].win = newwin(
                key_dim.y, key_dim.x,
                display_size.y * pos_scale.y + row * key_dim.y + gap.y,
                display_size.x * pos_scale.x + keys_per_row[row] * key_dim.x * 0.5 - gap.x - key_dim.x * (keys_new_line[row] - key_idx)
        );
        
        box(keyboard_wins[key_idx].win, 0, 0);
        
        wattron(keyboard_wins[key_idx].win, keyboard_wins[key_idx].color);
        mvwaddch(keyboard_wins[key_idx].win, 1, 1, querty_layout[key_idx]);
        wattroff(keyboard_wins[key_idx].win, keyboard_wins[key_idx].color);

        refresh();
        wrefresh(keyboard_wins[key_idx].win);
        refresh();
    }
}

void draw_col_word(WINDOW **word_win, size_t idx, word *word){
    WINDOW *win = word_win[idx];
    Point pos;
    getmaxyx(win, pos.y, pos.x);
    for(size_t i = 0; i < word->len; i++){
        attron(COLOR_PAIR(word->color[i]));
        mvwaddch(win, 1, 1, word->value[i]);
        attroff(COLOR_PAIR(word->color[i]));
    }
    wrefresh(win);
}

void draw_col_key(WordleKeyboardWin *keyboard_wins, char key, int color){
    WordleKeyboardWin *key_win = &keyboard_wins[key_2_idx[KEY_ALPH_IDX(key)]];
    key_win->color = color;
    wattron(key_win->win, COLOR_PAIR(color));
    mvwaddch(key_win->win, 1, 1, key);
    wattroff(key_win->win, COLOR_PAIR(color));
    refresh();
    wrefresh(key_win->win);
    refresh();
}
