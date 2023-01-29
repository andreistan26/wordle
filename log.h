#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <time.h>

#ifndef LOG_PATH
#define LOG_PATH stderr
#endif

#define LOG(type, path, fmt, ...) do {                                          \
    char buf[32];                                                               \
    time_t timer = time(NULL);                                                  \
    strftime(buf, 32, "%H:%M:%S", localtime(&timer));                           \
    fprintf(path, "%s %-5s [%s : %s():%d] " fmt "\n", buf, type, __FILE__,        \
            __FUNCTION__, __LINE__, ##__VA_ARGS__);                             \
}while(0)

#define LOG_ERROR(fmt, ...) LOG("ERROR", LOG_PATH, fmt, ##__VA_ARGS__)
#define LOG_INFO (fmt, ...) LOG("INFO" , LOG_PATH, fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...) LOG("DEBUG", LOG_PATH, fmt, ##__VA_ARGS__)

#endif
