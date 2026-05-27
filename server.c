#include <stdio.h>
#include "server.h"
#include <sys/socket.h>
#include <netinet/in.h>


Server constructor(int domain,
  int service,
  int protocol,
  long interface,
  int port,
  int backlog){
    Server server;
    server.domain = domain;
    server.service = service;
    server.protocol = protocol;
    server.interface = interface;
    server.port = port;
    server.backlog = backlog;
    server.socket_fd = socket(domain,AF_INET,protocol);

    server.address.sin_addr.s_addr = protocol;
    server.address.sin_port = htons(8080);
    server.address.sin_family = AF_INET;

    server.socket_fd = socket(domain,AF_INET,protocol);

    return server;
  };


int main() {

  int domain;
  int service;
  int protocol;
  long interface;
  int port;
  int backlog;
  int socket_fd;
  struct sockaddr_in address;

  Server server;
  server = constructor(domain,service,protocol,interface,port,backlog);




  return 0;
}