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




void parse_request(char* buffer) {
  printf("%s\n", buffer);
  Request request;

  int position = 0;
  init_request(&request);

  printf("$$$$$ Parsing Request $$$$$$ \n");
  get_method(&request, buffer, &position);
  printf("method: %d\n", request.method);
  position++;
  position++;
  get_path(&request, buffer, &position);

  printf("paths: \n");
  for (int i = 0; i < request.path_size; i++) {
    printf("%s\n", *request.path);
  } 

  return;
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
  char* param = &buffer[*position];
  char* head = param;

  while (buffer[*position] != '/' && buffer[*position] != ' ') {
    printf("buffer[*position]: %c\n", buffer[*position]);
    *param = buffer[*position];
    param++;
    *position = *position + 1;
  }
  *param = '\0';
  request->path = realloc(request->path, sizeof(char*) * request->path_size);
  (request->path)[request->path_size] = head;
  request->path_size++;
}














  // OPTIONS =  79 + 80 + 84 + 73 + 79 + 78 + 83 =  556
  // GET = 71 + 69 + 84 = 224
  // HEAD = 72 + 69 + 65 + 68 = 274
  // POST = 80 + 79 + 83 + 84 = 326
  // PUT =  80 + 85 + 84 =  249
  // DELETE =  68 + 69 + 76 + 69 + 84 + 69 =  435
  // TRACE = 84 + 82 + 
  // CONNECT,


