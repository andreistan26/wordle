#include "../include/wordle.h"
#include "../include/utils.h"
#include "../include/config.h"
#include "../include/log.h"
#include <unistd.h>

int main(int argc, char **argv) {
    Options opts = {
        .official_word  = 0,
        .dict_path      = NULL,
    };

    int c;
    while((c = getopt(argc, argv, "hod:")) != -1) {
        switch(c) {
            case 'o': 
                opts.official_word = 1;
                break;
            case 'd':
                if(opts.official_word == 0)
                    opts.dict_path = optarg;
                break;
            case 'h':
                printf("wordle: a tui implementation of the popular wordle game\n");
                printf("usage: %s [-d dict_dir] [-o]\n\n", argv[0]);
                printf("-o\t\tplay the official wordle of the day\n");
                printf("-d <directory>\tchange the default dictionary\n");
                printf("\t\tthe files should match *legal.txt and *wordles.txt\n");
                return 0;
            case '?':
                return 0;
            default:
                printf("Unknown arguments provided %c\n", c);
                abort();
                break;
        }
    }

    wordle_init();
    AppData *app_data = init_app_data(opts);

    draw_logo(app_data->app_windows->logo_win);
    draw_all_input_win(app_data->app_windows->input_wins);
    draw_keyboard(app_data->app_windows->keyboard_wins);
 
    refresh();

    while(!is_lost(app_data, 1)){
        process_input(app_data);
    }

    exit_game(app_data);
    return 0;
}   
