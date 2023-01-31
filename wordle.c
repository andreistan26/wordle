#include "wordle.h"
#include "utils.h"
#include "log.h"

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

    app_data->word_size = 5;
    app_data->guess_idx = 0;
    app_data->max_guesses = 6;
    app_data->seeked_word = NULL;
    app_data->dict_word_count = 0;
    load_dict(app_data);

    app_data->app_windows = init_win_bundle(app_data->max_guesses);

    generate_random_word(app_data);
    
    LOG_DEBUG("%s", app_data->seeked_word);

    return app_data;
}

static void load_dict(AppData* app_data){
    fseek(app_data->dict_file, 0, SEEK_END);
    app_data->dict_word_count = ftell(app_data->dict_file) / (app_data->word_size + 1);
    fseek(app_data->dict_file, 0, SEEK_SET);

    app_data->dict_words = malloc(sizeof(char *) * (app_data->dict_word_count));
    
    size_t i = 0;
    char buf[BUFSIZ];
    while(fgets(buf, BUFSIZ, app_data->dict_file) && buf[0]!='\n'){
        TRIM_LAST_CHAR(buf);
        if(strlen(buf) != (app_data->word_size)){
            fprintf(stderr, "Dictionary data is structured incorrectly\n\
                    [buf = %s, at idx = %ld]", buf, i);
            exit(1);
        }

        app_data->dict_words[i++] = strdup(buf);
    }

    fclose(app_data->dict_file);
    assert(i == app_data->dict_word_count);
}

void generate_random_word(AppData *app_data){
     app_data->seeked_word = app_data->dict_words[rand() % app_data->dict_word_count];
}

void quit_app(AppData *app_data);

WordleInputWin *current_input_win(AppData *app_data){
    return &app_data->app_windows->input_wins[app_data->guess_idx];
}

void process_input(AppData *app_data){
    int input_key = getch();
    if(is_word_input(input_key)){
        if(word_append(current_input_win(app_data)->word, input_key) == 1){
            draw_input_win(current_input_win(app_data), app_data->guess_idx);
        }
       //do input window logic
    }else if(input_key == KEY_BACKSPACE){
        if(word_remove(current_input_win(app_data)->word) == 1){
            draw_input_win(current_input_win(app_data), app_data->guess_idx);
        }
    }else if(input_key == KEY_ENTER){
        if(word_check(current_input_win(app_data)->word, app_data->seeked_word) == 1){
            //check word 
            //color word
            //draw word
        }
        //try and submit
    }else if(input_key == ctrl(KEY_QUIT_WORDLE)){
        //quit game
    }
}
