#include <stdio.h>
#include "server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

Server constructor(int domain,
                   int service,
                   int protocol,
                   long interface,
                   int port,
                   int backlog,
                  void(*launch)(void))
{
  Server server;
  server.domain = domain;
  server.service = service;
  server.protocol = protocol;
  server.interface = interface;
  server.port = port;
  server.backlog = backlog;
  server.socket_fd = socket(domain, AF_INET, protocol);

  server.address.sin_addr.s_addr = protocol;
  server.address.sin_port = htons(port);
  server.address.sin_family = AF_INET;

  server.socket_fd = socket(domain, AF_INET, protocol);

  if (server.socket_fd == 0)
  {
    perror("The socket creation failed\n");
    exit(EXIT_FAILURE);
  }

  server.bind_int = bind(server.socket_fd, (struct sockaddr *)(&server.address), sizeof(server.address));

  if (server.bind_int < 0)
  {
    perror("The binding of the socket failed\n");
    exit(EXIT_FAILURE);
  }

  server.listen_int = listen(server.socket_fd, server.backlog);
  if (server.listen_int < 0)
  {
    perror("Listening function failed\n");
    exit(EXIT_FAILURE);
  }

  server.launch = launch;
  return server;
};