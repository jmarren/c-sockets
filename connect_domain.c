

#include <netdb.h>
#include <stdio.h>
#include <string.h>


void connect_domain(char* domain) {
  printf("connect domain: %s", domain);
  struct addrinfo hints, *res;
  int sockfd;

  // load up address structs with getaddrinfo();
  
  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  int status = getaddrinfo(domain, "http", &hints, &res);

  if (status == 1) {
      fprintf(stderr, "error getting addr info: %s\n", gai_strerror(status));
  }

  // make a socket:

  sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

  // connect!

  status = connect(sockfd, res->ai_addr, res->ai_addrlen);
  if (status == 1) { 
      fprintf(stderr, "error getting addr info: %s\n", gai_strerror(status));
  }

}
