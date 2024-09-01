#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

#define BACKLOG 10
#define PORT "4040"


void sigchld_handler(int s)
{
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0);

    errno = saved_errno;
}



void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}




int serverfunc() {
  int yes = 1;
  int status;
  int sockfd, new_fd;
  socklen_t addr_size;
  char s[INET6_ADDRSTRLEN];
  struct sigaction sa;
  struct sockaddr_storage their_addr;
  struct addrinfo hints, *servinfo, *p;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;
  hints.ai_protocol = 0;

  status = getaddrinfo(NULL, PORT, &hints, &servinfo);

  if (status != 0) {
    fprintf(stderr, "listen_and_accept(), getaddrinfo(): %s", gai_strerror(status));
    return 1;
  }

  for (p = servinfo; p != NULL; p = p->ai_next) {


    sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
 

    if (sockfd == -1) {
      // fprintf(stderr, "Error: listen_and_accept(), socket()");
      // fprintf(stderr, "Errno: %d", errno);
      // return 1;
      perror("server: socket");
      continue;
    }

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
      perror("setsockopt");
      return 1;
    }

    status = bind(sockfd, p->ai_addr, p->ai_addrlen);

    if (status == -1) {
      close(sockfd);
      perror("server: bind\n");
      fprintf(stderr, "listen_and_accept(), bind()");
      fprintf(stderr, "Errno: %d\n", errno);
      continue;
    }
    break;
  }

  freeaddrinfo(servinfo);


  status = listen(sockfd, BACKLOG);

  if (status == -1) {
    fprintf(stderr, "listen_and_accept(), listen():");
    fprintf(stderr, "Errno: %d\n", errno);
    return 1;
  }



    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

 printf("server: waiting for connections...\n");

  while(1) {
    addr_size = sizeof their_addr;
    new_fd = accept(sockfd, (struct sockaddr*)&their_addr, &addr_size);

    if (new_fd == -1) {
      fprintf(stderr, "Error: listen_and_accept(), accept(): %s\n", strerror(errno));
      return 1;
    }

    int peername;
    struct sockaddr addr;
    unsigned int addrlen = sizeof(struct sockaddr);


    peername = getpeername(new_fd, &addr, &addrlen);

    if (peername == -1) {
      fprintf(stderr, "Error: listen_and_accept(), getpeername(): %d\n", errno);
    } else {
      printf("The peername is %i\n", peername);
    }

    inet_ntop(their_addr.ss_family,
              get_in_addr((struct sockaddr *)&their_addr),
              s, sizeof s);
    printf("server: got connection from %s\n", s);



    if (!fork()) {
      close(sockfd);
 
      char buffer[4096];
      int bytes_received = recv(new_fd, buffer, sizeof buffer - 1, 0);

      if (bytes_received < 0) {
        perror("recv");
        close(new_fd);
        return 1;
      }

      buffer[bytes_received] = '\0';

      printf("buffer received:  %s", buffer);



      char *http_status = "HTTP/1.1 200 OK\r\n";
      char *content_type = "Content-Type: text/html\r\n";
      char *body = "<!DOCTYPE html><html lang='en'><div>hello from the other side...</div></html>";
      int body_size = strlen(body);
      char content_length[sizeof("Content-Length: \r\n") + body_size];
      char *break_line = "\r\n";
      sprintf(content_length, "Content-Length: %i\r\n", body_size);

      printf("content length: %s", content_length);
      
      char *response = malloc(strlen(http_status) + strlen(content_type) + strlen(break_line) + strlen(body) + strlen(content_length) + strlen(body) + 1);
      strcpy(response, http_status);
      strcat(response, content_type);
      strcat(response, content_length);
      strcat(response, break_line);
      strcat(response, body);

      printf("%s", response);
      
      int len, bytes_sent;

        

      len = strlen(response);
      bytes_sent = send(new_fd, response, len, 0);
      free(response);

      if (bytes_sent == -1) perror("send");
      close(new_fd);
      exit(0);
    }
    close(new_fd);
  }
  return 0;
}




