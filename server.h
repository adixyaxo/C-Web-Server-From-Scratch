#ifndef SERVER_H
#define SERVER_H
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct
{
  int domain;
  int service;
  int protocol;
  long interface;
  int port;
  int backlog;
  int socket_fd;
  int bind_int;
  int listen_int;
  struct sockaddr_in address;

  void (*launch)(void);

} Server;

Server constructor(int domain,
                          int service,
                          int protocol,
                          long interface,
                          int port,
                          int backlog,
                          void (*launch)(Server *server));

#endif