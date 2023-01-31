#include "word.h"

word *init_word(){
    word *word = malloc(sizeof(word));
    word->value = malloc(sizeof(char) * WORD_SIZE);
    word->color = calloc(sizeof(int), WORD_SIZE);
    word->len = 0;
    return word;
}

int word_append(word *word, const char c){
    if(word->len == WORD_SIZE){
        return 0;
    }
    word->value[word->len] = c;
    return 1;
}

int word_remove(word *word){
    if(word->len == 0){
        return 0;
    }

    word->color[word->len] = 0;
    word->value[word->len] = 0;
    return 1;
}

void word_clear(word *word){
    memset(word->color, 0, sizeof(int) * WORD_SIZE);
    memset(word->value, 0, sizeof(char) * WORD_SIZE);
    word->len = 0;
}

void word_delete(word *word){
    free(word->color);
    free(word->value);
    free(word);
}

int word_check(word *word, char *seeked_word){
    int visited[WORD_SIZE] = {0};
    int winner = 1;
    for(size_t i = 0; i < WORD_SIZE; i++){
        if(word->value[i] == seeked_word[i]){
            word->color[i] = EXACT_MATCH;
            continue;
        }
        winner = 0;
        for(size_t j = 0; j < WORD_SIZE; j++)
            if(visited[j] == 0 && seeked_word[j] == word->value[i])
                word->color[i] = PARTIAL_MATCH;
    }
    return winner;
}

int is_word_input(int key){
    return isalpha(key);
}
