#include "wordle.h"
#include "utils.h"
#include "log.h"
int main(){
    wordle_init();
    AppData *app_data = init_app_data();
    
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
