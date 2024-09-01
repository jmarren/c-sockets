//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include "main.h"

int main(int argc, char *argv[]) {

  connect_domain("http://localhost:4000");
  return 1;
}

