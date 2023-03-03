#ifndef REQUEST_H
#define REQUEST_H

#include "curl/curl.h"
#include "log.h"
#include "time.h"
#include "string.h"
#include "stdlib.h"

#define QUERY_DEF_LEN 256

typedef struct {
    size_t  size;
    char    *data;
} response ;

static const char *req = "https://www.nytimes.com/svc/wordle/v2/%d-%02d-%02d.json";

char *          generate_query(int year, int month, int day);
char *          generate_current_query();
char *          parse_json_response(response *resp);

response *      get_response(char *query);

size_t static   write_callback(void *data, size_t size,
                        size_t nmemb, void *clientp);

char *          get_wordle();
#endif
