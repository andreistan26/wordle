#ifndef UTILS_H
#define UTILS_H

typedef enum{
    NORMAL, USED_KEY, EXACT_MATCH, PARTIAL_MATCH, ALERT
}COLORS_WRD;

#define ENTER_KEY           10
#define WORD_SIZE           5
#define GUESSES             6
#define KEY_QUIT_WORDLE     'Q'

#define ctrl(key)(key & 0x1f)

#endif
