#include <stdio.h>
#include "connect_domain.h"
#include "print_ip.h"
#include "listen_and_accept.h"

int main(int argc, char *argv[]) {
  printf("main works!\n");
  int k = serverfunc();
  if (k != 0) {
    fprintf(stderr, "An error occurred\n");
  }

  // print_ip("google.com");
  // connect_domain("google.com");
  return 1;
}

