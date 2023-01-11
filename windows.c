#include "windows.h"

WordleWinBundle *init_win_bundle(size_t size, void (*draw_wins)(WordleWinBundle *)){
    WordleWinBundle *bundle = malloc(sizeof(WordleWinBundle));
    bundle->wins = malloc(size * sizeof(WINDOW *));
    for(size_t i = 0; i < size; i++){
        bundle->wins[i] = NULL;
    }
    bundle->size = size;
    bundle->draw_wins = draw_wins;

    return bundle;
}

void draw_logo(WordleWinBundle *logo_win){
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

void draw_guesses(WordleWinBundle *input_wins){
    static const Pointf pos_scale = {.x = 0.5, .y = 0.4};
    static const Point input_dim = {.x = 5 + 2, .y = 1 + 2};
    static const int vertical_gap = 1;
    //TODO add guesses from config
    static const int guesses = 6;
    Point display_size;
    getmaxyx(stdscr, display_size.y, display_size.x);
    
    for(size_t i = 0; i < guesses; i++){
        input_wins->wins[i] = newwin(
                input_dim.y, input_dim.x,
                display_size.x * pos_scale.x - input_dim.x * 0.5,
                display_size.y * pos_scale.y + i * input_dim.y + vertical_gap
        );
        box(input_wins->wins[i], 0, 0);
        wrefresh(input_wins->wins[i]);
    }
} 

void draw_keyboard(WordleWinBundle *keyboard_wins){
    static const Pointf pos_scale = {.x = 0.5, .y = 0.4};
    static const Point key_dim = {.x = 1 + 2, .y = 1 + 2};
    static const Point gap = {.x = 1, .y = 1};
    static const int querty_rows = 3;

    Point display_size;
    getmaxyx(stdscr, display_size.y, display_size.x);
    
    WINDOW **it = keyboard_wins->wins;
    for(size_t row = 0; row < querty_rows; row++){
        for(size_t col = 0; col < sizeof(querty_layout[row]); col++){
            *it = newwin(
                    key_dim.y, key_dim.x,
                    display_size.x * pos_scale.x - sizeof(querty_layout[row]) * key_dim.x * 0.5 + gap.x + key_dim.x * col,
                    display_size.y * pos_scale.y + row * key_dim.y + gap.y
            );
            box(*it, 0, 0);
            wrefresh((*it));
            it++;
        }
    }
}

void draw_all_windows(WordleWinBundle **wins){
    clear();

    for(size_t i = 0; i < 3; i++){
        wins[i]->draw_wins(wins[i]);
    }

    refresh();
}





