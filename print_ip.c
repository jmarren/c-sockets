
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include "main.h"

void printIPAddress(char* domain) {
    struct addrinfo hints, *res, *p;
    int status = 1;
    char ipstr[INET6_ADDRSTRLEN];

    if (domain == NULL) {
      fprintf(stderr, "printIPAddress error: please enter a domain\n");
    }
 
    if ((status == getaddrinfo(domain, "http", &hints, &res) != 0)) {
      fprintf(stderr, "error getting addr info: %s\n", gai_strerror(status));
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET6;
    hints.ai_socktype = SOCK_STREAM;
    
    printf("IP addresses for %s: \n\n", domain);
  
    for (p = res; p != NULL; p = p->ai_next) {
      void *addr;
      char *ipver;

      // get the pointer to the address itself
      // different fields in ipv6 and ipv4
      if (p->ai_family == AF_INET) {
        struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
        addr = &(ipv4->sin_addr);
        ipver = "IPv4";
      } else {
        struct  sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
        addr = &(ipv6->sin6_addr);
        ipver = "IPv6";
      }
    inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
    printf("  %s: %s\n", ipver, ipstr);
  }

  freeaddrinfo(res);
}
