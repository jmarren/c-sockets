


#ifndef PARSE_REQUEST_H
#define PARSE_REQUEST_H

typedef enum {
  OPTIONS,
  GET,
  HEAD,
  POST,
  PUT,
  DELETE,
  TRACE,
  CONNECT,
  INVALID,
} request_method;

typedef struct Request {
  request_method method;
  char **path;
  int path_size;
} Request;

void init_request(Request* request);
void get_method(Request* request, char* buffer, int* position);
void parse_request(char* buffer);
void get_path(Request* request, char* buffer, int* position);


#endif
