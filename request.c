#include "request.h"

char *generate_current_query(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char * query = generate_query(tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    return query;
}

char *generate_query(int year, int month, int day){
    char *query = malloc(QUERY_DEF_LEN * sizeof(char));
    sprintf(query, req, year, month, day);
    return query;
}

response *get_response(char *query){
    CURL *curl      = curl_easy_init();
    response *resp  = calloc(1, sizeof(response));

    curl_easy_setopt(curl, CURLOPT_URL, query);
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, resp);

    curl_easy_perform(curl);

    curl_easy_cleanup(curl);

    return resp;
}

size_t static write_callback(void *data, size_t size,
        size_t nmemb, void *clientp){
    response *resp  = (response *)clientp;
    size_t new_size = (size_t)(size * nmemb);

    resp->data = realloc(resp->data, resp->size + new_size + 1);
    memcpy(resp->data + resp->size, data, new_size);
    resp->size += new_size;
    resp->data[resp->size] = 0;

    return new_size;
}

char *parse_json_response(response *resp){
    char *it = strstr(resp->data, "solution");
    if(it == NULL){
        exit(2);
        return NULL;
    }
    it = strchr(it, ':');
    return strndup(it + 2, 5);
}

char *get_wordle(){
    char *query = generate_current_query();
    response *resp = get_response(query);
    char *wordle = parse_json_response(resp);
    free(query);
    free(resp->data);
    free(resp);

    return wordle;
}

