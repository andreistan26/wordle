#include "config.h"

Config *load_config(){
    FILE *config_file;
    if((config_file = fopen(config_path, "r")) == NULL){
        fprintf(stderr, "%s invaild config file path", config_path);
        return NULL;
    }

    Config *config = malloc(sizeof(Config));
    
    char buf[BUFSIZ];
    while(fgets(buf, BUFSIZ, config_file) != NULL){
        if(strstr(buf, "guesses") != NULL){
            
        }
        fgets(buf, BUFSIZ, config_file);
    }
    
}
