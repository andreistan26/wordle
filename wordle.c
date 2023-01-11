#include "wordle.h"

void init(){
    srand(time(NULL));
    initscr();
    noecho();
    curs_set(0);
    start_color();
    init_pair(NORMAL, COLOR_WHITE, COLOR_BLACK);
    init_pair(USED_KEY, COLOR_BLACK, COLOR_WHITE);
    init_pair(EXACT_MATCH, COLOR_GREEN, COLOR_BLACK);
    init_pair(PARTIAL_MATCH, COLOR_YELLOW, COLOR_BLACK);
    init_pair(ALERT, COLOR_RED, COLOR_BLACK);
    
}

AppData *init_app_data(){
    static const char *path = "dicts/dict_5.txt";
    AppData *app_data = malloc(sizeof(AppData));
    if((app_data->dict_file = fopen(path, "r")) == NULL){
        fprintf(stderr, "Could not open dictionary file with path : %s", path);
        exit(1);
    }

    load_dict(app_data);
    app_data->guess_idx = 0;
    app_data->max_guesses = 6;
    app_data->wins = 
}

static int load_dict(AppData* app_data){
    
}

