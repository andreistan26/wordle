#include "wordle.h"
#include "utils.h"

void wordle_init(){
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
    if((app_data->dict_file = fopen(path, "rb")) == NULL){
        fprintf(stderr, "Could not open dictionary file with path : %s", path);
        exit(1);
    }

 //   load_dict(app_data);
    app_data->guess_idx = 0;
    app_data->max_guesses = 6;
    app_data->seeked_word = NULL;
    app_data->dict_word_count = 0;
    app_data->dict_words = NULL;

    app_data->app_windows = init_win_bundle(app_data->max_guesses);
    
    return app_data;
}

static void load_dict(AppData* app_data){

    fseek(app_data->dict_file, 0, SEEK_END);
    app_data->dict_word_count = ftell(app_data->dict_file) / (app_data->word_size + 1);
    
    fseek(app_data->dict_file, 0, SEEK_SET);

    app_data->dict_words = malloc(sizeof(char *) * (app_data->dict_word_count));
    
    size_t i = 0;
    char buf[BUFSIZ];
    while(fgets(buf, BUFSIZ, app_data->dict_file)){
        if(strlen(buf) != (app_data->word_size + 1)){
            fprintf(stderr, "Dictionary data is structured incorrectly\n");
            exit(1);
        }
        
        app_data->dict_words[i] = malloc(sizeof(char) * (app_data->word_size + 1));

        TRIM_NEW_LINE(buf);
        app_data->dict_words[i] = strdup(buf);
    }

    fclose(app_data->dict_file);
    assert(i == app_data->dict_word_count);
}

void generate_random_word(AppData *app_data){
     app_data->seeked_word = app_data->dict_words[rand() % app_data->dict_word_count];
}
