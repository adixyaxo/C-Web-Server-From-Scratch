#ifndef SERVER_H
#define SERVER_H
# include <sys/socket.h>
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
  struct sockaddr_in address;

}Server;

struct Server constructor(int domain,
  int service,
  int protocol,
  long interface,
  int port,
  int backlog);


#endif