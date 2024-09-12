//
//
//
//
//
//
//
//
//

#include <stdio.h>
#include "parse_request.h"
#include <stdlib.h>
#include <string.h>




void parse_request(char* buffer) {
  printf("%s\n", buffer);
  Request request;

  int position = 0;
  init_request(&request);

  printf("$$$$$ Parsing Request $$$$$$ \n");
  get_method(&request, buffer, &position);
  printf("method: %d\n", request.method);
  move_to_next_non_space(buffer, &position);
  // position++;
  // position++;
  get_path(&request, buffer, &position);

  printf("path_size: %d\n", request.path_size);
  printf("paths: \n");
  for (int i = 0; i < request.path_size; i++) {
    printf("%s\n", request.path[i]);
  } 

  free_paths(&request);

  return;
}

void move_to_next_non_space(char* buffer, int* position) {
  char curr = buffer[*position];
  while (curr == ' ') {
    *position = *position + 1;
    printf("moved to %d\n", *position);
    curr = buffer[*position];
  }
  printf("buffer[*position]: %c\n", buffer[*position]);
}


void init_request(Request* request) {
    request->path_size = 0;
    request->path = (char**)malloc(sizeof(char*));
}

void get_method(Request* request, char* buffer, int* position) {
  printf("get_method \n");
  int sum = 0;
  // int i = 0;
  while (*buffer != ' ')  {
    sum += *buffer;
    buffer++;
    *position = *position + 1;
    printf("position %d\n", *position);
  }

  switch (sum) {
    case 556:
      request->method = OPTIONS;
    break;
    case 224: 
      request->method = GET;
    break;
    case 274:
     request->method = HEAD;
    break;
    case 326:
      request->method = POST;
    break;
    case 249:
      request->method = PUT;
    break;
    case 'D' + 'E' + 'L' + 'E' + 'T' + 'E':
      request->method = DELETE;
    break;
    case 'T' + 'R' + 'A' + 'C' + 'E':
      request->method = TRACE;
    break;
    case 'C' + 'O' + 'N' + 'N' + 'E' + 'C' + 'T':
      request->method = CONNECT;
    break;
    default:
      request->method = INVALID;
  }
 
  request_method method = GET;
  request->method = method;
  return;
}


void get_path(Request* request, char* buffer, int* position) {
  if (buffer[*position] == ' ') return;
  // char* param = &buffer[*position];
  char* head = &buffer[*position];
  *position = *position + 1;
  int param_length = 0;
  
  
  while (buffer[*position] != '/' && buffer[*position] != ' ') {
    printf("buffer[*position]: %c\n", buffer[*position]);
    param_length++;
    *position = *position + 1;
  }
  
  size_t param_size = (param_length + 1) * sizeof(char);
  char* param = (char*)malloc(param_size);

  strncpy(param, head, param_size );

  printf("buffer[*position]: %c\n", buffer[*position]);


  request->path = (char**)realloc(request->path, sizeof(char**) * request->path_size);
  (request->path)[request->path_size] = param;
  request->path_size++;

  printf("ending get_path(): buffer[*position]: %c\n", buffer[*position]);
  if (buffer[*position] == '/') {
    printf("getting next param!\n");
    get_path(request, buffer, position);
  }
}


void free_paths(Request* request) {
  for (int i = 0; i < request->path_size; i++) {
    free(request->path[i]);
  }
}














  // OPTIONS =  79 + 80 + 84 + 73 + 79 + 78 + 83 =  556
  // GET = 71 + 69 + 84 = 224
  // HEAD = 72 + 69 + 65 + 68 = 274
  // POST = 80 + 79 + 83 + 84 = 326
  // PUT =  80 + 85 + 84 =  249
  // DELETE =  68 + 69 + 76 + 69 + 84 + 69 =  435
  // TRACE = 84 + 82 + 
  // CONNECT,


